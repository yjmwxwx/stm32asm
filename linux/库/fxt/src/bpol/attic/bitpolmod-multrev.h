#if !defined  HAVE_BITPOLMOD_MULTREV_H__
#define       HAVE_BITPOLMOD_MULTREV_H__

#include "fxttypes.h"


static inline ulong bitpolmod_times_x_rev(ulong a, ulong c)
// Return  (A * reverse(x)) mod C
// where A and C represent polynomials over Z/2Z:
//   W = pol(w) =: \sum_k{ [bit_k(w)] * x^k}
//
// If C is a primitive polynomial of degree n
// successive calls will cycle through all 2**n-1
// n-bit words and the sequence of bits
// (any fixed position) of A constitutes
// a shift register sequence (SRS).
// Start with a=(1UL<<(n-1)) to get a SRS
// that starts with n-1 consecutive zeros
//
// The consecutive A are in reversed order as in class lfsr()
{
    if ( a & 1 )  a ^= c;
    a >>= 1;
    return  a;
}
// -------------------------

inline ulong bitpolmod_mult_rev(ulong a, ulong b, ulong c)
// Return  (A * reverse(B)) mod C
// where A, B and C represent polynomials over Z/2Z:
//   W = pol(w) =: \sum_k{ [bit_k(w)] * x^k}
//
// With b=2 (== 'x') the result is identical to
//   bitpolmod_times_x_rev(a, c)
//.
// bitpolmod_mult_rev(a, 3, 1) == gray_code(a)
// bitpolmod_mult_rev(a, 5, 1) == gray_code(gray_code(a))
{
    ulong t = 0;
    while ( b )
    {
        if ( b & 1 )  t ^= a;
        b >>= 1;
        if ( a & 1 )  a ^= c;
        a >>= 1;
    }
    return  t;
}
// -------------------------


#endif  // !defined HAVE_BITPOLMOD_MULTREV_H__
