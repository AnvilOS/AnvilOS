
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "_Anvil_double.h"
#include "_Anvil_xint.h"

//char ret_str[1000];

int cc0, cc1, cc2, cc3, cc4, cc5, cc6, cc7;

//char *_Anvil_dragon4(int e, uint64_t f, int p, int cutoff_mode, int cutoff_place, int *pk);

char *_Anvil_dtoa(double dd, int cutoff_mode, int ndigits, int *decpt, int *sign, char **rve)
{
    ++cc0;

    char *ret_str;
    int e = 0;
    uint64_t f = 0;
    int32_t p = 0;
    int cutoff_place = -ndigits;

    //
    // Our double is f * 2^(e-p)
    //
    split_double(dd, sign, &f, &e);
    p = 52;

    if (f == 0)
    {
    	ret_str = malloc(2);
        strcpy(ret_str, "0");
        *decpt = 1;
        return ret_str;
    }

    _Anvil_xint R;
    _Anvil_xint S;
    
    int no_print = 0;

    uint32_t U;
    int R5e=0, S5e=0;
    int R2e=0, S2e=0;

    // NOTE: Instead of actually modifying any of the Xints we record what
    // needs to be done and calculate and optimise it all later
    // Don't worry about recording values for M+ and M- since they follow
    // R early on.

    // INITIALISE THE VARIABLES
    // R = f << max(e-p, 0)
    // S = 1 << max(0, -(e-p))
    // M+ = 1 << max(e-p, 0)
    // M- = 1 << max(e-p, 0)
    if (e - p >= 0)
    {
        R2e = e - p;
    }
    else
    {
        S2e = p - e;
    }

    // Dragon4 has a pair of loops, one executed while R < ceil(S/10)
    // and the second while R + M+/2 >= S. The result of these is to give
    // S/10 <= R < S.
    //
    // David M Gay in "Correctly Rounded Binary-Decimal and Decimal Binary
    // Conversion" suggests that if we calculate an approximation of the log10
    // of the input number we can speed this up.
    // As long as we err in the correct direction we can remove the need for
    // the first loop and cause the 2nd loop to be executed either 0 or 1 times
    // We will keep both loops but expect them to be executed rarely
    //
    uint64_t f1 = f;
    //int e1 = e;
    while ((f1 & 0x10000000000000) == 0)
    {
        f1 <<= 1;
        --e;
    }
    int k = (e * 30103 / 100000 + 1);
    if (k < 0)
    {
        --k;
    }

    if (k < 0)
    {
        R2e -= k;
        R5e -= k;
    }
    else
    {
        S5e += k;
        S2e += k;
    }
    
    // We need S = S / 10
    --S5e; --S2e;

    // Remove common factors now
    if (R2e < S2e)
    {
        S2e -= R2e;
        R2e = 0;
    }
    else
    {
        R2e -= S2e;
        S2e = 0;
    }
    if (R5e < S5e)
    {
        S5e -= R5e;
        R5e = 0;
    }
    else
    {
        R5e -= S5e;
        S5e = 0;
    }

    // while (R < ceil(S/10))
    // {
    //    --k;
    //    R = R * 10
    //    M- = M- * 10
    //    M+ = M+ * 10
    // }
    // calculate ceil(S/10)

    _Anvil_xint_init(&R);
    _Anvil_xint_assign_64(&R, f);
    _Anvil_xint_lshift(&R, &R, R2e);
    _Anvil_xint_mul_5exp(&R, R5e);

    _Anvil_xint_init(&S);
    _Anvil_xint_assign_64(&S, 1);
    _Anvil_xint_lshift(&S, &S, S2e);
    _Anvil_xint_mul_5exp(&S, S5e);

    // while R < ceil(S/B)
    while (_Anvil_xint_cmp(&R, &S) < 0)
    {
        // k = k-1
        // R = R * B
        ++cc2;
        --k;
        _Anvil_xint_mul_int(&R, 10);
//        ++R5e; ++R2e;
    }

    _Anvil_xint_mul_int(&S, 10);
    //++S5e; ++S2e;

    // while R >= S
    while (_Anvil_xint_cmp(&R, &S) >= 0)
    {
        // S = S * B
        // k = k + 1
        ++cc3;
        _Anvil_xint_mul_int(&S, 10);
        ++k;
//		++S5e;
//		++S2e;
    }
    int sz = cutoff_mode == e_relative ? ndigits : ndigits + k;
//    printf("strlen=%lu %lu\n", strlen(ret_str), sz);
    if (sz < 1)
    {
        sz = 1;
    }
    ++sz;
    ret_str = malloc((size_t)sz);
    memset(ret_str, 0, sz);
    char *pret_str = ret_str;
    
    switch (cutoff_mode)
    {
        case e_relative:
            cutoff_place += k;
            break;

        case e_absolute:
            if (k <= cutoff_place)
            {
                _Anvil_xint_lshift(&R, &R, 1);
//				++R2e;
                no_print = 1;
                int cmp = _Anvil_xint_cmp(&R, &S);
                if (k == cutoff_place && cmp > 0)
                {
                    // Output a 1
                    *pret_str++ = '1';
                }
                else
                {
                    // Output a 0 but don't print it
                }
                k = cutoff_place;
            }
            break;
    }

//    ++R2e;
//    ++S2e;
#if 0
    // Check all our variables are correct
    _Anvil_xint TEMP;
    _Anvil_xint_init(&TEMP, xint_size);
    _Anvil_xint_assign_64(&TEMP, f);
    _Anvil_xint_lshift(&TEMP, &TEMP, R2e);
    _Anvil_xint_mul_5exp(&TEMP, R5e);
    if (_Anvil_xint_cmp(&TEMP, &R) != 0)
    {
        _Anvil_xint_print("R   : ", &R);
        _Anvil_xint_print("TEMP: ", &TEMP);
        printf("R wrong\n");
    }
    _Anvil_xint_assign_64(&TEMP, 1);
    _Anvil_xint_lshift(&TEMP, &TEMP, S2e);
    _Anvil_xint_mul_5exp(&TEMP, S5e);
    if (_Anvil_xint_cmp(&TEMP, &S) != 0)
    {
        printf("S wrong\n");
    }
    _Anvil_xint_delete(&TEMP);
#endif

    // LOOP
    // S already holds 2S so let's make R be 2R
    //_Anvil_xint_lshift(&R, &R, 1);

    // The original Dragon4 algorithm doesn't have this test but it's
    // certainly needed
    if (!no_print)
    {
        // The 'div_small' algorithm requires the denominator to have the top
        // bit in its top word set. Scale every thing to make this true
        int hbit = _Anvil_xint_highest_bit(&S) % 32;
        _Anvil_xint_lshift(&R, &R, 31-hbit);
        _Anvil_xint_lshift(&S, &S, 31-hbit);

        U = 0;

        while (1)
        {
            ++cc1;
            --k;

            // U = floor ( R * 10 ) / S
            // R = ( R * 10 ) mod S
            _Anvil_xint_mul_int(&R, 10);

            U = _Anvil_xint_div_small(&R, &S);
            
            if (k <= cutoff_place || _Anvil_xint_is_zero(&R))
            {
                break;
            }
            *pret_str++ = U + 0x30;
        }

        // The loop is done so output the final digit
        // Scale R up by 2
        _Anvil_xint_lshift(&R, &R, 1);
        int cmp = _Anvil_xint_cmp(&R, &S);
        if (cmp < 0 || (cmp == 0 && (U & 1) == 0))
        {
            *pret_str++ = U + 0x30;
        }
        else
        {
            *pret_str = U + 1 + 0x30;
            while (*pret_str == '9' + 1)
            {
                // If we stopped because we hit the cutoff place or ran out
                // of precision it might be that U is 9
                // This is bad because we can't simply increment it. We need
                // to roll the carries all the way back through our string.
                if (pret_str == ret_str)
                {
                    *pret_str = '1';
                    ++k;
                    break;
                }
                --pret_str;
                *pret_str += 1;
                ++k;
            }
            ++pret_str;
        }
        // Remove trailing zeroes
        while (*(pret_str-1) == '0')
        {
            --pret_str;
            ++k;
        }
    }

    *pret_str = 0;
    *decpt = k + (int)strlen(ret_str);

    _Anvil_xint_delete(&R);
    _Anvil_xint_delete(&S);

    if (strlen(ret_str) + 1 > sz)
    {
        printf("strlen=%lu %d %d %s", strlen(ret_str), sz, cutoff_place, ret_str);
        printf("\n");
    }
    
    return ret_str;
}
