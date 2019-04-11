// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/mtypes.h"
//#include "mod/factor.h"


int
kronecker(umod_t a, umod_t b)
// Return Kronecker symbol (a/b).
// Equal to Legendre symbol (a/b) if b is an odd prime.
//.
// Cf. Cohen p.29
{
//    if ( a>=b )  a %= b;
    static const int  tab2[] = {0, 1, 0, -1, 0, -1, 0, 1};
    // tab2[ a & 7 ] := (-1)^((a^2-1)/8)

    if ( 0==b )  return (1==a);

    if ( 0==((a|b)&1) )  return 0;  // a and b both even ?

    int v = 0;
    while ( 0==(b&1) )  { ++v;  b>>=1; }

    int k;
    if ( 0==(v&1) )  k = 1;
    else             k = tab2[ a & 7 ];

    // signed:   if ( b<0 )  { b=-b;  if (a<0) {k=-k}; }

    // step3:
    while ( 1 )
    {
        // here b is odd
        if ( 0==a )  return ( b>1 ? 0 : k );

        v = 0;
        while ( 0==(a&1) )  { ++v;  a>>=1; }

        if ( 1==(v&1) )  k *= tab2[ b & 7 ];  // k *= (-1)**((b*b-1)/8)

        // step4:
        if ( a & b & 2 )  k = -k;  // k = k*(-1)**((a-1)*(b-1)/4)

        umod_t r = a;  // signed:  r = abs(a)
        a = b % r;
        b = r;
        // goto step3;
    }
}
// -------------------------



//int
//reciprocity(umod_t a, umod_t b)
////
//// (a/b) = (b/a) * (-1)^((a1-1)*(b1-1)/4 + (as-1)*(bs-1)/4)
//// where a==a1*2^ae, b=b1*2^be
//// and as=sign(a), bs=sign(b)
//// cf. Cohen p.43
////
//// UNTESTED
//{
//    if ( (0==a) || (0==b) )  return 0;
//    while ( 0==(a&1) )  a >>= 1;
//    while ( 0==(b&1) )  b >>= 1;
//    int k = 1;
//    if ( a & b & 2 )  k = -k;
//    return k;
//}
//// -------------------------
