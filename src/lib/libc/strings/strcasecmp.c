
#include <strings.h>
#include <ctype.h>

int strcasecmp(const char *s1, const char *s2)
{
    while (tolower(*s1) == tolower(*s2))
    {
        if (*s1 == 0)
        {
            return 0;
        }
        ++s1;
        ++s2;
    }
    return (unsigned char)tolower(*s1) < (unsigned char)tolower(*s2) ? -1 : 1;
}
