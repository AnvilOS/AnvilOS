
#include <ctype.h>

int ispunct(int c)
{
	c = _ANVIL_CTYPE_RANGE_FIX(c);
    return _C_Ctype[c] & _Anvil_CtPnc;
}
