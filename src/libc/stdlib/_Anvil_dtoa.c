
#include <stdio.h>
#include <string.h>

#include "_Anvil_xint.h"

#define MAX(a, b) ((a)>(b)?(a):(b))

enum
{
    e_normal,
    e_absolute,
    e_relative,
};

char ret_str[100];

char *_Anvil_dragon4(int32_t e, uint64_t f, int32_t p, int cutoff_mode, int cutoff_place, int *pk)
{
    _Anvil_xint R;
    _Anvil_xint S;
    _Anvil_xint Mplus;
    _Anvil_xint Mminus;
    uint32_t U;
    
    int roundup_flag = 0;
    
    char *pret_str = ret_str;
    
    int k = 0;
    
    _Anvil_xint_init(&R);
    _Anvil_xint_init(&S);
    _Anvil_xint_init(&Mplus);
    _Anvil_xint_init(&Mminus);

    // INITIALISE THE VARIABLES
    // R = f << max(e-p, 0)
    _Anvil_xint_assign_64(&R, f);
    _Anvil_xint_lshift(&R, &R, MAX(e-p, 0));

    // S = 1 << max(0, -(e-p))
    _Anvil_xint_assign_64(&S, 1);
    _Anvil_xint_lshift(&S, &S, MAX(0, -(e-p)));

    // M+ = 1 << max(e-p, 0)
    _Anvil_xint_assign_64(&Mplus, 1);
    _Anvil_xint_lshift(&Mplus, &Mplus, MAX(e-p, 0));

    // M- = 1 << max(e-p, 0)
    _Anvil_xint_assign(&Mminus, &Mplus);

    // FIXUP
    if (f == (1U << (p-1)))
    {
        // NYI
        printf("FIXUP gap\n");
    }

    k = 0;

    _Anvil_xint TEMP3;
    _Anvil_xint TEMP4;
    _Anvil_xint_init(&TEMP3);
    _Anvil_xint_init(&TEMP4);

    // calculate ceil(S/B)
    if (_Anvil_xint_div_int(&TEMP3, &S, 10))
    {
        // If there is a remainder round up to get ceiling
        _Anvil_xint_add_int(&TEMP3, 1);
    }
    
    // while R < ceil(S/B)
    while (_Anvil_xint_cmp(&R, &TEMP3) < 0)
    {
        // k = k-1
        --k;
        // R = R * B
        _Anvil_xint_mul_int(&R, 10);
        // M- = M- * B
        _Anvil_xint_mul_int(&Mminus, 10);
        // M+ = M+ * B
        _Anvil_xint_mul_int(&Mplus, 10);
    }
    
    // TEMP3 = 2 * R + M+
    _Anvil_xint_lshift(&TEMP3, &R, 1);
    _Anvil_xint_add(&TEMP3, &Mplus);

    // TEMP4 = 2 * S
    _Anvil_xint_lshift(&TEMP4, &S, 1);

    // while TEMP3 >= TEMP4
    while (_Anvil_xint_cmp(&TEMP3, &TEMP4) >= 0)
    {
        // S = S * B
        _Anvil_xint_mul_int(&S, 10);
        // TEMP4 = 2 * S
        _Anvil_xint_lshift(&TEMP4, &S, 1);

        // k = k + 1
        ++k;
        
        switch (cutoff_mode)
        {
            case e_normal:
                cutoff_place = k;
                break;
            case e_absolute:
                // NYI
                //roundup_flag = cutoff_adjust(&S, &Mplus, &Mminus, cutoff_place, k);
                break;
            case e_relative:
                // NYI
                //cutoff_place += k;
                //roundup_flag = cutoff_adjust(&S, &Mplus, &Mminus, cutoff_place, k);
                break;
        }
    }

    // LOOP
    int low;
    int high;
    while (1)
    {
        _Anvil_xint TEMP_MUL;

        --k;
        
        // U = floor ( R * 10 ) / S
        // R = ( R * 10 ) mod S
        _Anvil_xint_assign(&TEMP_MUL, &R);
        _Anvil_xint_mul_int(&TEMP_MUL, 10);
        U = _Anvil_xint_div(&R, &TEMP_MUL, &S);

        // M+ = M+ * 10
        _Anvil_xint_mul_int(&Mplus, 10);
        
        // M- = M- * 10
        _Anvil_xint_mul_int(&Mminus, 10);
        
        // low = 2 * R < M-
        _Anvil_xint_assign(&TEMP4, &R);
        _Anvil_xint_mul_int(&TEMP4, 2);
        low = _Anvil_xint_cmp(&TEMP4, &Mminus) == -1;
        
        // high = 2 * R > 2 * S - M+
        _Anvil_xint_assign(&TEMP3, &S);
        _Anvil_xint_mul_int(&TEMP3, 2);
        if (_Anvil_xint_cmp(&TEMP3, &Mplus) >= 0)
        {
            _Anvil_xint_sub(&TEMP3, &TEMP3, &Mplus);
            // According to the Dragon logic this should be >= 1 but >= 0 works - this is the 10^23 problem
            high = _Anvil_xint_cmp(&TEMP4, &TEMP3) >= 1;
        }
        else
        {
            high = 1;
        }
        
        //printf("Done\n");
        if (low || high || k == cutoff_place)
        {
            if (low && !high)
            {
                //printf("Low %d %d\n", low, high);
                *pret_str++ = U + 0x30;
            }
            else if (!low && high)
            {
                //printf("High %d %d\n", low, high);
                *pret_str++ = U + 1 + 0x30;
            }
            else
            {
                int cmp = _Anvil_xint_cmp(&TEMP4, &S);
                if (cmp < 0)
                {
                    *pret_str++ = U + 0x30;
                }
                else if (cmp > 0)
                {
                    *pret_str++ = U + 1 + 0x30;
                }
                else
                {
                    *pret_str++ = U + 0x30;
                }
                //printf("Both %d %d %d\n", low, high, cmp);
            }
            *pret_str = 0;
            *pk = k;
            break;
        }
        *pret_str++ = U + 0x30;
    }

    return ret_str;
}

char *_Anvil_dtoa(double dd, int mode, int ndigits, int *decpt, int *sign, char **rve)
{
    int32_t e = 0;
    uint64_t f = 0;
    int32_t p = 0;
    int cutoff_mode = 0;
    int cutoff_place = 0;
    
    union
    {
        uint64_t uint;
        double dbl;
    } value;
    
    if (dd == 0.0)
    {
        return "0";
    }

    value.dbl = dd;
    *sign = value.uint >> 63;
    e = ((value.uint >> 52) & 0x7ff) - 1023;
    f = value.uint & 0xfffffffffffff;
    if (e == -1023)
    {
        ++e;
    }
    else
    {
        f |= 0x10000000000000;
    }
    p = 52;

    char *ret = _Anvil_dragon4(e, f, p, cutoff_mode, cutoff_place, decpt);
    //*decpt += strlen(ret);
    return ret;
}
