
#include <stdlib.h>

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    size_t l = 0;
    size_t r = nmemb - 1;

    while (l <= r)
    {
        // Find the middle index without overflowing
        size_t m = l + (r - l) / 2;
        // and from that the middle element
        void *mel = (char *)base + m * size;
        int cmp = compar(mel, key);
        if (cmp < 0 )
        {
            l = m + 1;
        }
        else if (cmp > 0)
        {
            r = m - 1;
        }
        else
        {
            return mel;
        }
    }
    return NULL;
}
