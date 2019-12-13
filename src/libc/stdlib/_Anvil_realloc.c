
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG
#if !defined (DEBUG)
#define malloc_debug(...)
#else
#define _MALLOC_DEBUG
#include <stdio.h>
#define malloc_debug(...) printf(__VA_ARGS__)
#endif

#if (__SIZEOF_SIZE_T__ == 4)
#define MALLOC_ALIGN_LOG    (3)
#else
#define MALLOC_ALIGN_LOG    (4)
#endif

#define MALLOC_ALIGN        (1 << MALLOC_ALIGN_LOG)
#define MALLOC_ALIGN_MASK   ((1 << MALLOC_ALIGN_LOG) - 1)

/* These are stored in the low bits of size_this - room for (or 4) */
#define BLK_PREV_USED       (1<<0)
#define BLK_BITMASK         (BLK_PREV_USED)

#define MALBLK_TO_PTR(__p) ((char *)__p + 2 * sizeof(size_t))
#define PTR_TO_MALLOC_BLOCK(__p) ((malblk_t *)((char *)__p - 2 * sizeof(size_t)))

struct malblk
{
    /*
     * size_this is the entire size of the malloc block. This includes the
     * user data and the 2 size_this-es
     */
    size_t size_prev;
    size_t size_this;
    /* The user area starts here */
    struct malblk *prev;
    struct malblk *next;
};
typedef struct malblk malblk_t;

static malblk_t *freelist_get(size_t size);
static void freelist_put(malblk_t *blk);
static void freelist_remove(malblk_t *blk);

#if defined (_MALLOC_DEBUG)
static int _SysmemCheck(void);
#endif

static malblk_t *malblk_split(malblk_t *blk, size_t size);
static size_t malblk_round_up(size_t val);
static malblk_t *malblk_try_join_prev(malblk_t *blk);
static malblk_t *malblk_try_join_next(malblk_t *blk, size_t extra_req);


static void blk_size_and_flags_set(malblk_t *pblk, size_t size_and_flags);
void blk_size_set(malblk_t *pblk, size_t size);
static size_t blk_size_get(malblk_t *pblk);
static void blk_used_set(malblk_t *pblk);
static void blk_used_clr(malblk_t *pblk);

static malblk_t *blk_prev(malblk_t *pblk);
static malblk_t *blk_next(malblk_t *pblk);
static int blk_used_get(malblk_t *pblk);
//static int blk_end_get(malblk_t *pblk);

static malblk_t *_Core;

extern char __ebss__;
extern char __eram__;

static const size_t s_min_blk_size = 2 * sizeof(size_t) + 2 * sizeof(void *);

malblk_t *malblk_split(malblk_t *blk, size_t new_size)
{
    /* Split a block into 2 */

    malblk_t *rem_blk;
    size_t rem_size;
    size_t curr_size;

    /* Size of the block we are splitting */
    curr_size = blk_size_get(blk);

    malloc_debug("splitting %d bytes, split_size=%d\n", curr_size, new_size);

    /* Check that the split is possible. Both parts must end up > (2 size_t + 2 void *) */
    if (new_size < s_min_blk_size || new_size + s_min_blk_size > curr_size)
    {
        malloc_debug("Split not possible %u %u %u\n", curr_size, s_min_blk_size, new_size);
        /* It's only just big enough so return NULL to indicate no split */
        return NULL;
    }

    /* We'll split off from the front of the blk. Firstly we figure out where
     * the remaining block will start
     */
    rem_blk = (malblk_t *)((char *)blk + new_size);
    rem_size = curr_size - new_size;
    malloc_debug("rem_size=%d\n", rem_size);
    blk_size_set(rem_blk, rem_size);
    blk_size_set(blk, new_size);

    return rem_blk;
}

size_t malblk_round_up(size_t val)
{
    /*
     * The minimum allocable size is 2 ptrs. In fact this is the granularity
     * of the allocator.
     *
     * Each block must also contain 2 size_t fields. Therefore roundup as
     * follows.
     *
     *  0 - 12 bytes >> 4 ptrs >> 16 bytes
     * 13 - 20 bytes >> 6 ptrs >> 24 bytes
     * 21 - 28 bytes >> 8 ptrs >> 32 bytes
     * etc.
     *
     * For 64 bit libs the values double.
     *
     *  0 - 24 bytes >> 4 ptrs >> 32 bytes
     * 25 - 40 bytes >> 6 ptrs >> 48 bytes
     * 41 - 56 bytes >> 8 ptrs >> 64 bytes
     * etc.
     */

    if (val < 5)
    {
        val = 5;
    }

    val -= sizeof(size_t);
    val += MALLOC_ALIGN_MASK;
    val &= ~MALLOC_ALIGN_MASK;
    val += 2 * sizeof(void *);

    /* Check that we didn't overflow */
    if (val > (SIZE_MAX - 4 * sizeof(void*)))
    {
        malloc_debug("OFLOW: size=%d\n", val);
        return 0;
    }

    return val;
}

malblk_t *malblk_try_join_prev(malblk_t *blk)
{
    /* Join blk with the prev block but only if the prev block is not busy */
    malblk_t *prev;
    size_t total;

    malloc_debug("%08x malblk_try_join_prev - ", blk);

    prev = blk_prev(blk);
    if (prev == NULL)
    {
        malloc_debug("prev in use\n");
        return blk;
    }

    /* Take the prev from the free list */
    freelist_remove(prev);

    /* Now join them */
    total = blk_size_get(prev) + blk_size_get(blk);
    malloc_debug("done, join %d %d ", blk_size_get(prev), blk_size_get(blk));
    blk_size_set(prev, total);
    malloc_debug("got %d\n", total);

    return prev;
}

malblk_t *malblk_try_join_next(malblk_t *blk, size_t extra_req)
{
    /* Join blk with the next block but only if the next block is not busy */
    malblk_t *next;
    size_t total;

    malloc_debug("malblk_try_join_next - ");

    next = blk_next(blk);

    if (!next || (blk_size_get(next) < extra_req) || blk_used_get(next))
    {
        malloc_debug("fail\n");
        return blk;
    }

    malloc_debug("used=%d\n", blk_used_get(next));

    /* Take the next from the free list */
    freelist_remove(next);

    /* Now join them */
    total = blk_size_get(blk) + blk_size_get(next);
    malloc_debug("done, join %d %d ", blk_size_get(blk), blk_size_get(next));
    blk_size_set(blk, total);
    malloc_debug("got %d\n", total);

    return blk;
}

/*
 *
 * Moving forward or back through a 'zone' of blocks
 *
 *
 */

static malblk_t *blk_prev(malblk_t *pblk)
{
    /* This function returns the previous block BUT ONLY IF THE BLOCK IS FREE */
    if (pblk->size_this & BLK_PREV_USED)
    {
        return NULL;
    }
    return (malblk_t *)((char *)pblk - pblk->size_prev);
}

static malblk_t *blk_next(malblk_t *pblk)
{
    /* We just need to look at the size_this of the next block. If it is
     * zero we are at the end
     */
    malblk_t *pnext;

    pnext = (malblk_t *)((char *)pblk + blk_size_get(pblk));

    if (blk_size_get(pnext) == 0)
    {
        /* It's an end so ... */
        return NULL;
    }

    return pnext;
}

/*
 *
 * Access functions for the members of malblk_t
 *
 *
 */

void blk_size_and_flags_set(malblk_t *pblk, size_t size_and_flags)
{
    pblk->size_this = size_and_flags;
}

size_t blk_size_get(malblk_t *pblk)
{
    return pblk->size_this & ~BLK_BITMASK;
}

void blk_size_set(malblk_t *pblk, size_t size)
{
    pblk->size_this = (pblk->size_this & BLK_BITMASK) | size;
}

int blk_used_get(malblk_t *pblk)
{
    malblk_t *next = (malblk_t *)(((char *)pblk) + blk_size_get(pblk));
    return (next->size_this & BLK_PREV_USED) == BLK_PREV_USED;
}

void blk_used_set(malblk_t *pblk)
{
    malblk_t *next = (malblk_t *)(((char *)pblk) + blk_size_get(pblk));
    next->size_this |= BLK_PREV_USED;
}

void blk_used_clr(malblk_t *pblk)
{
    malblk_t *next = (malblk_t *)(((char *)pblk) + blk_size_get(pblk));
    next->size_prev = pblk->size_this & ~BLK_PREV_USED;
    next->size_this &= ~BLK_PREV_USED;
}

#if defined (_MALLOC_DEBUG)
int _SysmemCheck()
{
    malblk_t *item;

    /* Move to the first item */
    item = (malblk_t *)_Core;

    malloc_debug("========================\n");

    while (1)
    {
        size_t  size;
        int     flags;

        size  = item->size_this & ~0x7;

        /* Move to the next item */
        malblk_t *next_item = (malblk_t *)((char *)item + size);
        flags = next_item->size_this & 0x7;

        malloc_debug("%08lx %d(%x) f=%x\n", item, size, size, flags);

        if (blk_size_get(item) == 0)
        {
            break;
        }

        item = next_item;
    }

    malloc_debug("========================\n");

    return 0;
}
#endif

#define MAX_BUCKETS (65)

#define MALBLK_TO_BUCKET(__p) ((bucket_t *)(MALBLK_TO_PTR(__p)))
#define BUCKET_TO_MALLOC_BLOCK(__p) PTR_TO_MALLOC_BLOCK(__p)

struct bucket
{
    struct bucket *prev;
    struct bucket *next;
};
typedef struct bucket bucket_t;

bucket_t *Bucket;

static int get_bkt_num(size_t size)
{
    if (size <= (1 << (MALLOC_ALIGN_LOG + 5))) /* <= 256 */
    {
        return (size >> MALLOC_ALIGN_LOG) - 1; /* 0 - 31 */
    }
    if (size <= (1 << (MALLOC_ALIGN_LOG + 5 + 5))) /* <= 8192 */
    {
        return (1 << 5) + (size >> (MALLOC_ALIGN_LOG + 5)) - 1; /* 32 - 63 */
    }
    return (1 << 5) + (1 << 5); /* 64 */
}

static int bktlist_is_empty(bucket_t *list)
{
    return list == list->next;
}

static bucket_t *bktlist_peek_head(bucket_t *list)
{
    if (bktlist_is_empty(list))
    {
        return NULL;
    }
    return list->next;
}

static void bktlist_rem_item(bucket_t *item)
{
    item->next->prev = item->prev;
    item->prev->next = item->next;
}

static int bktlist_is_tail(bucket_t *list, bucket_t *item)
{
    return item->next == list;
}

static bucket_t *bktlist_peek_next(bucket_t *list, bucket_t *item)
{
    if (bktlist_is_tail(list, item))
    {
        return NULL;
    }
    return item->next;
}

static void bktlist_add_head(bucket_t *list, bucket_t *item)
{
    /* Add item between list and list->next */
    bucket_t *first_item = list->next;
    first_item->prev = item;
    item->next = first_item;
    item->prev = list;
    list->next = item;
}

malblk_t *freelist_get(size_t size)
{
    bucket_t *pbkt;
    bucket_t *item;
    int bkt_num;
    int b;

    bkt_num = get_bkt_num(size);
    malloc_debug("bkt_num %d\n", bkt_num);

    for (b=bkt_num; b<MAX_BUCKETS; ++b)
    {
        pbkt = &Bucket[b];
        item = bktlist_peek_head(pbkt);
        while (item)
        {
            size_t  item_size;
            item_size = blk_size_get((BUCKET_TO_MALLOC_BLOCK(item)));
            if (item_size > size)
            {
                bktlist_rem_item(item);
                malloc_debug("using freelist bkt %d\n", b);
                return BUCKET_TO_MALLOC_BLOCK(item);
            }
            item = bktlist_peek_next(pbkt, item);
        }
    }

    malloc_debug("free list empty\n");
    return NULL;
}

void freelist_put(malblk_t *blk)
{
    bucket_t *pbkt;
    size_t size;
    int bkt_num;

    size = blk_size_get(blk);
    bkt_num = get_bkt_num(size);

    malloc_debug("adding %d bytes to freelist bkt %d\n", size, bkt_num);

    pbkt = &Bucket[bkt_num];

    bktlist_add_head(pbkt, MALBLK_TO_BUCKET(blk));
}

void freelist_remove(malblk_t *blk)
{
    bucket_t *bkt;
    bkt = MALBLK_TO_BUCKET(blk);
    bktlist_rem_item(bkt);
}

static int initialised = 0;

void initialise()
{
    size_t alignment;
    char *heap_start;
    size_t heap_len;
    size_t buckets_len;
    int i;

    // In this version of malloc we take all available memory and use it to create the heap
    malloc_debug("Malloc initialise\n");
    malloc_debug("__ebss__ = %08x\n", &__ebss__);
    malloc_debug("__erom__ = %08x\n", &__eram__);

    // We need to align to 2 x sizeof(size_t)
    alignment = 2 * sizeof(size_t);
    malloc_debug("Aligning to %d bytes\n", alignment);

    heap_start = &__ebss__;
    while ((uintptr_t)heap_start & (alignment - 1))
    {
        ++heap_start;
    }
    malloc_debug("heap_start  = %08x\n", heap_start);

    // How much heap have we got?
    heap_len = &__eram__ - heap_start;
    malloc_debug("heap_len    = %08x\n", heap_len);

    // Carve off some for our bucket list
    buckets_len = MAX_BUCKETS * sizeof(bucket_t);
    malloc_debug("buckets_len = %08x\n", buckets_len);

    Bucket = (bucket_t *)heap_start;
    heap_start = (char *)(Bucket + MAX_BUCKETS);
    malloc_debug("heap_start  = %08x\n", heap_start);

    for (i=0; i<MAX_BUCKETS; ++i)
    {
        Bucket[i].prev = Bucket[i].next = &Bucket[i];
    }

    _Core = (malblk_t *)heap_start;
    heap_len -= 1024;

    memset(_Core, 0, heap_len);

    blk_size_and_flags_set(_Core, heap_len | BLK_PREV_USED);

    malblk_t *next = (malblk_t *)(((char *)_Core) + heap_len);
    next->size_this = 0;

    /* Make this into a free block */
    malloc_debug("getting system memory %08lx %d\n", _Core, _Core->size_this);
    malloc_debug("getting system memory %08lx %d\n", next, next->size_this);

    freelist_put(_Core);

    _SysmemCheck();

//    return _Core;
}

void *_Anvil_realloc(void *old_ptr, size_t new_size)
{
    malblk_t *old_blk;
    malblk_t *new_blk = NULL;
    void *new_ptr = NULL;
    size_t old_size;

    if (!initialised)
    {
        initialise();
        initialised = 1;
    }

    malloc_debug("---------------------------------\n", new_size);
    malloc_debug("realloc %x to %d bytes\n", old_ptr, new_size);

    if (new_size)
    {
        if ((new_size = malblk_round_up(new_size)) == 0)
        {
            return NULL;
        }
        malloc_debug("size %d bytes\n", new_size);

        if (old_ptr)
        {
            old_blk = PTR_TO_MALLOC_BLOCK(old_ptr);
            old_size = blk_size_get(old_blk);

            if (new_size > old_size)
            {
                /* Try to extend to the new size */
                old_blk = malblk_try_join_next(old_blk, new_size - old_size);
                old_size = blk_size_get(old_blk);
            }

            if (new_size == old_size)
            {
                malloc_debug("No need to grow size %d bytes\n", new_size);
                return old_ptr;
            }

            /* If we get here we either coulnn't extend the block or it's now
             * too big
             */
            if (old_blk->size_this >= new_size)
            {
                new_blk = old_blk;
                old_blk = NULL;
            }
        }

        if (!new_blk)
        {
            /* Search for some memory in the free list */
            if ((new_blk = freelist_get(new_size)) == NULL)
            {
                /* That's it, no more memory */
                return NULL;
            }
        }

        /* It might have started too big or perhaps we over-extended */
        if (new_blk->size_this > new_size)
        {
            /* Trim the block */
            malloc_debug("Trimming from %d to %d bytes\n", new_blk->size_this, new_size);
            malblk_t *rem_blk;
            if ((rem_blk = malblk_split(new_blk, new_size)) != NULL)
            {
                /* Free up the bit we don't need */
                rem_blk = malblk_try_join_next(rem_blk, 0);
                freelist_put(rem_blk);
            }
        }

        blk_used_set(new_blk);

        new_ptr = MALBLK_TO_PTR(new_blk);
    }

    if (old_ptr)
    {
        if (new_ptr)
        {
            memcpy(new_ptr, old_ptr, new_size);
        }

        /* Are the adjacent blocks free ? */
        old_blk = PTR_TO_MALLOC_BLOCK(old_ptr);
        old_blk = malblk_try_join_prev(old_blk);
        old_blk = malblk_try_join_next(old_blk, 0);

        /* Add the block to the bucket list for its size */
        blk_used_clr(old_blk);

        freelist_put(old_blk);
    }

#if defined (_MALLOC_DEBUG)
    _SysmemCheck();
#endif

    return new_ptr;
}