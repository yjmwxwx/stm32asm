#if !defined  HAVE_BITPOL_SQUAREFREE_H__
#define       HAVE_BITPOL_SQUAREFREE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/bitpol-deriv.h"
#include "bpol/bitpol-gcd.h"
#include "bits/bitzip.h"
#include "bits/bitsperlong.h"
#include "fxttypes.h"  // ulong
//#include "cmath.h"


inline ulong bitpol_test_squarefree(ulong c)
// Return  0 if polynomial is square-free
// else return square factor
{
    ulong d = bitpol_deriv(c);
    if ( 0==d )  return  (1==c ? 0 : c);  // pure square != 1 ==> c
    ulong g = bitpol_gcd(c, d);
    return  (1==g ? 0 : g);  // ==> square factor
}
// -------------------------

inline ulong bitpol_pure_square_q(ulong c)
// Return whether polynomial is a pure square != 1
{
    if ( 1UL==c )  return 0;  // constant polynomial
#if  BITS_PER_LONG >= 64
    c &= 0xaaaaaaaaaaaaaaaaUL;
#else
    c &= 0xaaaaaaaaUL;
#endif
    return  (0==c);
}
// -------------------------

inline ulong bitpol_pure_sqrt(ulong c)
// Return t = sqrt(c)
// c must be a pure square: bits at odd positions must be zero.
{
#if 1
    return bit_unzip0(c);
#else
    ulong t = 0;
    for (ulong mc=1, mt=1;  mc;  mc<<=2, mt<<=1)
    {
        if ( mc & c )  t |= mt;
    }
    return  t;
#endif
}
// -------------------------

// bpol/bitpol-squarefree.cc:
ulong bitpol_sreduce(ulong c);
ulong bitpol_factor_squarefree(ulong c, ulong *sf, ulong *se);


inline ulong bitpol_squarefree_part(ulong c)
// remove all factors with even exponents
{
    ulong g = bitpol_gcd(c, bitpol_deriv(c));
    if ( 1==g )  return c;
    else  return bitpol_div(c, g);
}
// -------------------------


inline ulong bitpol_make_squarefree(ulong c)
// reduce all exponents to 1
{
    ulong z = c, t;
    while ( z!=(t=bitpol_sreduce(z)) )  z = t;
    return z;
}
// -------------------------



#endif  // !defined HAVE_BITPOL_SQUAREFREE_H__
