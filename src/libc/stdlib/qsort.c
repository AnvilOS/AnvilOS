
#include <stdlib.h>
#include <stdio.h>

static inline void memswp(void *s1, void *s2, size_t n)
{
    // Work with ints
    int *si = (int *)s2;
    int *di = (int *)s1;
    while (n >= sizeof(int))
    {
        int tmp = *si;
        *si++  = *di;
        *di++  = tmp;
        n -= sizeof(int);
    }

    // Swap the remaining chars
    char *sc = (char *)si;
    char *dc = (char *)di;
    while (n)
    {
        char tmp = *sc;
        *sc++  = *dc;
        *dc++  = tmp;
        --n;
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

void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    if (nmemb < 2)
    {
        // Nothing to do
        return;
    }

    size_t j = partition(base, nmemb, size, compar);

    // base[0] .. base[j-1]          =====> j items below the pivot
    // base[j]                       =====> the pivot in the correct place
    // base[j+1] .. base[nmemb-1]    =====> (nmemb-j-1) items above the pivot
    qsort(base, j, size, compar);
    qsort((char *)base + (j+1)*size, nmemb-j-1, size, compar);
}
