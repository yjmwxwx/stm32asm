// This file is part of the FXT library.
// Copyright (C) 2010, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/bitpolmod-arith.h"
#include "bits/parity.h"
//#include "bits/bitsperlong.h"
#include "fxttypes.h"

bool
bitpol_need_gcd(ulong h)
// Return whether GCDs are needed for irreducibility test.
{
    // degrees where GCDs are needed:
    // 12, 18, 20, 24, 28, 30, 36, 40, 42,     45, 48, 50,     54, 56, 60, 63
#if BITS_PER_LONG == 64
    const ulong gn =
        (1UL<<12)|(1UL<<18)|(1UL<<20)|(1UL<<24)|(1UL<<28)|(1UL<<30)|
        (1UL<<36)|(1UL<<40)|(1UL<<42)|(1UL<<45)|(1UL<<48)|(1UL<<50)|
        (1UL<<54)|(1UL<<56)|(1UL<<60)|(1UL<<63);
#else
    const ulong gn =
        (1UL<<12)|(1UL<<18)|(1UL<<20)|(1UL<<24)|(1UL<<28)|(1UL<<30);
#endif
    return  0 != ( h & (gn>>1) );
}
// -------------------------


bool
bitpol_spi_q(ulong c, ulong h)
// Return whether C is a strong pseudo irreducible (SPI).
// A polynomial C of degree d is an SPI if
//   it has no linear factors, x^(2^k)!=x for 0<k<d, and x^(2^d)==x.
// h needs to be a mask with one bit set:
//  h == highest_one(C) >> 1  == 1UL << (degree(C)-1)
{
    const bool md = ((h<<1)==0);  // whether degree == BITS_PER_LONG

    if ( md )
    {
        if ( (c&1)==0 )  return false;        // factor x
        if ( 0 != parity(c) )  return false;  // factor x+1
    }
    else
    {
        if ( c<4 )  // C is one of 0, 1, x, 1+x
        {
            if ( c>=2 )  return true;   // x, and 1+x are irreducible
            else         return false;  // constant polynomials are reducible
        }

        if ( (c&1)==0 )  return false;        // factor x
        if ( 0 == parity(c) )  return false;  // factor x+1
    }

    ulong t = 1;
    ulong m = 2;  // x
    m = bitpolmod_square(m, c, h);
    do
    {
        if ( m==2 )  return false;
        m = bitpolmod_square(m, c, h);
        t <<= 1;
    }
    while ( t!=h );

    if ( m!=2 )  return false;

    return true;
}
// -------------------------
