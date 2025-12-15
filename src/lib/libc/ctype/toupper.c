
#include <ctype.h>

int toupper(int c)
{
    int cc = _ANVIL_CTYPE_RANGE_FIX(c);
    return _C_toupper[cc] ? _C_toupper[cc] : c;
}
