#if !defined  HAVE_BITPOL_IRRED_H__
#define       HAVE_BITPOL_IRRED_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bittransforms.h"  // blue_code()
#include "fxttypes.h"
#include "bits/bitsperlong.h"


// bpol/bitpol-irred-ben-or.cc:
bool bitpol_irreducible_ben_or_q(ulong c, ulong h);

// bpol/bitpol-irred-rabin.cc:
bool bitpol_irreducible_rabin_q(ulong c, ulong h);

// bpol/bitpol-spi.cc:
bool bitpol_need_gcd(ulong h);
bool bitpol_spi_q(ulong c, ulong h);


inline bool bitpol_irreducible_q(ulong c, ulong h)
{
#if 1  // use SPI test only for degree==BITS_PER_LONG
    // default because SPI test is slower

    // if degree==BITS_PER_LONG we must use the SPI test:
    if ( 0==(h<<1) )  return  bitpol_spi_q(c, h);

    return bitpol_irreducible_ben_or_q(c, h);
//    return bitpol_irreducible_rabin_q(c, h);


#else  // use SPI test whenever possible

    if ( bitpol_need_gcd(h) )  return bitpol_irreducible_ben_or_q(c, h);
    else                       return bitpol_spi_q(c, h);

#endif
}
// -------------------------


inline ulong bitpol_compose_xp1(ulong c)
// Return C(x+1).
// Self-inverse.
// If C is irreducible then C(x+1) is also irreducible.
// If C is primitive then x+1 is a generator modulo C(x+1).
{
#if 1
    // log_2(BITS_PER_LONG) - version:
    return  blue_code(c);

#else
    ulong z = 1;
    ulong r = 0;
    while ( c )
    {
        if ( c & 1 )  r ^= z;
        c >>= 1;
        z ^= (z<<1);
    }
    return  r;

#endif
}
// -------------------------


inline ulong bitpol_recip(ulong c)
// Return x^deg(C) * C(1/x)  (the reciprocal polynomial)
// Self-inverse.
// If C is irreducible/primitive then the returned
//   polynomial is also irreducible/primitive.
//.
// Note: could use revbin(c, deg(c)-1)
{
    ulong t = 0;
    while ( c )
    {
        t <<= 1;
        t |= (c & 1);
        c >>= 1;
    }
    return  t;
}
// -------------------------


#endif  // !defined HAVE_BITPOL_IRRED_H__
