
#include <ctype.h>

int tolower(int c)
{
    int cc =_ANVIL_CTYPE_RANGE_FIX(c);
    return _C_tolower[cc] ? _C_tolower[cc] : c;
}
