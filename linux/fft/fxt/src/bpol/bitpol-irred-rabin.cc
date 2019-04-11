// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "bpol/bitpol-arith.h"
#include "bpol/bitpol-gcd.h"
#include "bpol/bitpolmod-arith.h"

#include "bits/bithigh.h"
#include "bits/bitsperlong.h"
#include "fxttypes.h"


static const ulong rabin_tab[] =
{
    0UL,   // x = 0  (bits: ...........)    OPS:
    0UL,   // x = 1  (bits: ...........)    OPS:   finally sqr 1 times
    0UL,   // x = 2  (bits: ...........)    OPS:   finally sqr 2 times
    0UL,   // x = 3  (bits: ...........)    OPS:   finally sqr 3 times
    4UL,   // x = 4  (bits: ........1..)    OPS:  sqr 2 times,    finally sqr 2 times
    0UL,   // x = 5  (bits: ...........)    OPS:   finally sqr 5 times
    12UL,  // x = 6  (bits: .......11..)    OPS:  sqr 2 times,   sqr 1 times,    finally sqr 3 times
    0UL,   // x = 7  (bits: ...........)    OPS:   finally sqr 7 times
    16UL,  // x = 8  (bits: ......1....)    OPS:  sqr 4 times,    finally sqr 4 times
    8UL,   // x = 9  (bits: .......1...)    OPS:  sqr 3 times,    finally sqr 6 times
    36UL,  // x = 10 (bits: .....1..1..)    OPS:  sqr 2 times,   sqr 3 times,    finally sqr 5 times
    0UL,  // x = 11
    80UL,  // x = 12
    0UL,  // x = 13
    132UL,  // x = 14
    40UL,  // x = 15
    256UL,  // x = 16
    0UL,  // x = 17
    576UL,  // x = 18
    0UL,  // x = 19
    1040UL,  // x = 20
    136UL,  // x = 21
    2052UL,  // x = 22
    0UL,  // x = 23
    4352UL,  // x = 24
    32UL,  // x = 25
    8196UL,  // x = 26
    512UL,  // x = 27
    16400UL,  // x = 28
    0UL,  // x = 29
    33856UL,  // x = 30
    0UL,  // x = 31
    65536UL,  // x = 32
#if  ( BITS_PER_LONG > 32 )
    2056UL,  // x = 33
    131076UL,  // x = 34
    160UL,  // x = 35
    266240UL,  // x = 36
    0UL,  // x = 37
    524292UL,  // x = 38
    8200UL,  // x = 39
    1048832UL,  // x = 40
    0UL,  // x = 41
    2113600UL,  // x = 42
    0UL,  // x = 43
    4194320UL,  // x = 44
    33280UL,  // x = 45
    8388612UL,  // x = 46
    0UL,  // x = 47
    16842752UL,  // x = 48
    128UL,  // x = 49
    33555456UL,  // x = 50
    131080UL,  // x = 51
    67108880UL,  // x = 52
    0UL,  // x = 53
    134479872UL,  // x = 54
    2080UL,  // x = 55
    268435712UL,  // x = 56
    524296UL,  // x = 57
    536870916UL,  // x = 58
    0UL,  // x = 59
    1074794496UL,  // x = 60
    0UL,  // x = 61
    2147483652UL,  // x = 62
    2097664UL,  // x = 63
    4294967296UL,  // x = 64
#endif  // ( BITS_PER_LONG > 32 )
};
// -------------------------


bool
bitpol_irreducible_rabin_q(ulong c, ulong h)
// Return whether C is irreducible (via Rabin's irreducibility test).
// h needs to be a mask with one bit set:
//  h == highest_one(C) >> 1  == 1UL << (degree(C)-1)
{
    if ( c<4 )  // C is one of 0, 1, x, 1+x
    {
        if ( c>=2 )  return true;   // x, and 1+x are irreducible
        else         return false;  // constant polynomials are reducible
    }

    if ( 0==(1&c) )  return false;  // x is a factor

//#if BITS_PER_LONG == 64
//    if ( 0==(c & 0xaaaaaaaaaaaaaaaaUL ) )  return 0;  // at least one odd degree term
//#else
//    if ( 0==(c & 0xaaaaaaaaUL ) )  return 0;  // at least one odd degree term
//#endif

    // if ( 0==parity(c) )  return 0;  // need odd number of nonzero coeff.
    // if ( 0!=bitpol_test_squarefree(c) )  return 0;  // must be square-free

    ulong d = 1 + lowest_one_idx(h);  // degree
    ulong rt = rabin_tab[d];
    ulong m = 2;  // =^= 'x'

    while ( rt > 1 )
    {
        do
        {
            --d;
            m = bitpolmod_square(m, c, h);
            rt >>= 1;
        }
        while ( 0 == (rt & 1) );

        ulong g = bitpol_binary_gcd( m ^ 2UL, c );
        if ( g!=1 )  return false;
    }

    do  { m = bitpolmod_square(m, c, h); }  while ( --d );
    if ( m ^ 2UL )  return false;

    return true;
}
// -------------------------

