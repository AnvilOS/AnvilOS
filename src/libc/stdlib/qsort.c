
#include <stdlib.h>
#include <stdio.h>

static inline void memswp(void *s1, void *s2, size_t n)
{
    // Work with ints
    if ((((uintptr_t)s1 | (uintptr_t)s2) & 0x3) == 0)
    {
        while (n >= sizeof(int))
        {
            int tmp = *(int*)s2;
            *(int*)s2++  = *(int*)s1;
            *(int*)s1++  = tmp;
            n -= sizeof(int);
        }
    }
    
    // Swap the remaining chars
    while (n)
    {
        char tmp = *(char*)s2;
        *(char*)s2++  = *(char*)s1;
        *(char*)s1++  = tmp;
        --n;
    }
}

static inline void insertion_sort(char *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
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
            if (pj == p_low)
            {
                break;
            }
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

struct Node
{
    char *base;
    size_t nmemb;
};

void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    struct Node stack[100];
    size_t index = 0;
    
    stack[0].base = base;
    stack[0].nmemb = nmemb;
    ++index;
    
    while (index)
    {
        --index;
        base = stack[index].base;
        nmemb = stack[index].nmemb;
        
    if (nmemb < 2)
    {
        // Nothing to do
            continue;
    }
    
    if (nmemb < 8)
    {
        insertion_sort(base, nmemb, size, compar);
            continue;
    }

    size_t j = partition(base, nmemb, size, compar);

    // base[0] .. base[j-1]          =====> j items below the pivot
    // base[j]                       =====> the pivot in the correct place
    // base[j+1] .. base[nmemb-1]    =====> (nmemb-j-1) items above the pivot
        //qsort(base, j, size, compar);
        stack[index].base = base;
        stack[index].nmemb = j;
        ++index;

        //qsort((char *)base + (j+1)*size, nmemb-j-1, size, compar);
        stack[index].base = (char *)base + (j+1)*size;
        stack[index].nmemb = nmemb-j-1;
        ++index;
    }
}
