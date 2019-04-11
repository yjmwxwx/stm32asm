#if !defined HAVE_TINYFACTORS_H__
#define      HAVE_TINYFACTORS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"

static inline bool is_tiny_prime(ulong n)
// For n < BITS_PER_LONG (!)
// return whether n is prime
{
#if  ( BITS_PER_LONG <= 32 )
    return  ( 1UL == (( 2693408940UL>> n) & 1));
#else
    return  ( 1UL == (( 2891462833508853932UL>> n) & 1));
#endif
}
// -------------------------


extern const ulong tiny_factors_tab[BITS_PER_LONG];

static inline bool is_tiny_factor(ulong x, ulong d)
// For x,d < BITS_PER_LONG (!)
// return whether d divides x  (1 and x included as divisors)
// No need to check whether d==0
//
{
    return  ( 0 != ( (tiny_factors_tab[x]>>d) & 1 ) );
}
// -------------------------



#endif  // !defined HAVE_TINYFACTORS_H__
