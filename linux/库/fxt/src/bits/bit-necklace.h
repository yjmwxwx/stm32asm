#if !defined  HAVE_BIT_NECKLACE_H__
#define       HAVE_BIT_NECKLACE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitperiodic.h"  // bit_copy_periodic()
#include "bits/bithigh.h"  // highest_zero_idx()
#include "bits/tinyfactors.h"

// Cf. comb/binary-necklace.h for binary necklaces as array

class bit_necklace
// Binary necklaces as binary words.
// The cyclic maximal words are produced.
// Must have 0<n<=BITS_PER_LONG.
{
public:
    ulong a_;   // necklace
    ulong j_;   // period of the necklace
    ulong n2_;  // bit representing n: n2==2**(n-1)
    ulong j2_;  // bit representing j: j2==2**(j-1)
    ulong n_;   // number of bits in words
    ulong mm_;  // mask of n ones
    ulong tfb_;  // for fast factor lookup

public:
    explicit bit_necklace(ulong n)  { init(n); }
    ~bit_necklace()  { ; }

    void init(ulong n)
    {
        if ( 0==n )  n = 1;  // avoid hang
        if ( n>=BITS_PER_LONG )  n = BITS_PER_LONG;
        n_ = n;

        n2_ = 1UL<<(n-1);
        mm_ = (~0UL) >> (BITS_PER_LONG-n);
        tfb_ = tiny_factors_tab[n] >> 1;
        tfb_ |= n2_;  // needed for n==BITS_PER_LONG
        first();
    }

    void first()
    {
        a_ = 0;
        j_ = 1;
        j2_ = 1;
    }

    ulong data() const { return  a_; }
    ulong period() const { return j_; }

    ulong next()
    // Create next necklace.
    // Return the period, zero when current necklace is last.
    {
        if ( a_==mm_ )  { first();  return 0; }

        do
        {
#if 0
            j_ = highest_zero_idx( a_ ^ (~mm_)  );
#else  // with explicit bit scan:
            j_ = n_ - 1;
            ulong jb = 1UL << j_;
            while ( 0!=(a_ & jb) )  { --j_;  jb>>=1; }
#endif
            j2_ = 1UL << j_;
            ++j_;
            a_ |= j2_;
//            a_ = bit_copy_periodic(a_, j_);  a_ &= mm_;
            a_ = bit_copy_periodic(a_, j_, n_);
        }
        while ( 0==(tfb_ & j2_) );  // necklaces only

        return  j_;
    }

    ulong is_lyndon_word()  const  { return (j2_ & n2_); }

    ulong next_lyn()
    // Create next Lyndon word.
    // Return the period (==n), zero when current necklace is last.
    {
        if ( a_==mm_ )  { first();  return 0; }
        do  { next(); }  while ( !is_lyndon_word() );
        return  n_;
    }
};
// -------------------------


#endif  // !defined HAVE_BIT_NECKLACE_H__
