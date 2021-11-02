
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static const size_t QSORT_LIMIT = 8;

struct Node
{
    char *base;
    size_t nmemb;
};

static void memswp(char *s1, char *s2, size_t n)
{
    // Work with ints
    if ((((uintptr_t)s1 | (uintptr_t)s2) & 0x3) == 0)
    {
        while (n >= sizeof(int))
        {
            int tmp = *(int*)s2;
            *(int*)s2 = *(int*)s1;
            *(int*)s1 = tmp;
            s1 += sizeof(int);
            s2 += sizeof(int);
            n -= sizeof(int);
        }
    }
    
    // Swap the remaining chars
    while (n)
    {
        char tmp = *s2;
        *s2++ = *s1;
        *s1++ = tmp;
        --n;
    }
}

static void insertion_sort(char *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    for (size_t i=1; i<nmemb; ++i)
    {
        for (size_t j=i; j>0 && compar(base+(j-1)*size, base+j*size)>0; --j)
        {
            memswp(base+j*size, base+(j-1)*size, size);
        }
    }
}

static size_t partition(char *p_low, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    // Find address of last element
    char *p_high = p_low + size * (nmemb - 1);
    // p_low will be the pivot...
    char *p_piv = p_low;
    //  so point pi at the pivot so the first pre-increment starts 1 above the pivot
    char *pi = p_low;
    // Point pj 1 above the end so the first pre-decrement finds the end item
    char *pj = p_high + size;

    // Choose the pivot to be the median of the first middle and last positions then
    // re-arrange the 3 items so that the pivot is in the first position.
    // Therefore we want: p_mid <= p_low (pivot) <= p_high
    char *p_mid = p_low + size * ((nmemb - 1) / 2);
    
    if (compar(p_high, p_low) < 0)
    {
        memswp(p_high, p_low, size);
    }
    if (compar(p_low, p_mid) < 0)
    {
        memswp(p_low, p_mid, size);
        if (compar(p_high, p_low) < 0)
        {
            memswp(p_high, p_low, size);
        }
    }
    
    while (1)
    {
        while (compar(pi += size, p_piv) < 0)
        {
            if (pi == p_high)
            {
                break;
            }
        }

        while (compar(pj -= size, p_piv) > 0)
        {
//            if (pj == p_low)
//            {
//                break;
//            }
        }

        if (pi >= pj)
        {
            break;
        }

        memswp(pi, pj, size);
    }

    // Restore the pivot value to position j
    memswp(p_piv, pj, size);

    // return the index of pj
    return (pj - p_low) / size;
}

void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    struct Node stack[25];
    size_t index = 0;

    while (1)
    {
        size_t n1 = partition(base, nmemb, size, compar);
        size_t n2;
        char *p1, *p2;

        // base[0] .. base[n1-1]          =====> n1 items below the pivot
        // base[n1]                       =====> the pivot in the correct place
        // base[n1+1] .. base[nmemb-1]    =====> (nmemb-n1-1) items above the pivot
        
        // We have 2 partitions - look at the bigger one first
        if (n1 > nmemb - n1 - 1)
        {
            p1 = base;
            p2 = (char *)base + (n1+1) * size;
            n2 = nmemb - n1 - 1;
        }
        else
        {
            p2 = base;
            n2 = n1;
            p1 = (char *)base + (n1+1) * size;
            n1 = nmemb - n1 - 1;
        }
        
        if (n2 >= QSORT_LIMIT)
        {
            // Both big so push the bigger
            stack[index].base = p1;
            stack[index].nmemb = n1;
            ++index;
            base = p2;
            nmemb = n2;
        }
        else if (n1 >= QSORT_LIMIT)
        {
            // Only n1 is big enough to qsort
            base = p1;
            nmemb = n1;
            if (n2 >= 2)
            {
                insertion_sort(p2, n2, size, compar);
            }
        }
        else
        {
            // both too small so insertion sort them
            if (n1 >= 2)
            {
                insertion_sort(p1, n1, size, compar);
            }
            if (n2 >= 2)
            {
                insertion_sort(p2, n2, size, compar);
            }
            if (index)
            {
                // pop another if available
                --index;
                base = stack[index].base;
                nmemb = stack[index].nmemb;
            }
            else
            {
                // Nothing more to do
                break;
            }
        }
    }
}
