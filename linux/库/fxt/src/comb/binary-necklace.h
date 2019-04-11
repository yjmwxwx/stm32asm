#if !defined  HAVE_BINARY_NECKLACE_H__
#define       HAVE_BINARY_NECKLACE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"

// Cf. bits/bit-necklace.h for binary necklaces in a binary word

// If defined, arrays are used instead of pointers, this gives a speedup:
//#define BINARY_NECKLACE_MAX_ARRAY_LEN 96  // default off

class binary_necklace
// Binary necklaces, pre-necklaces, and Lyndon words.
// Cf. OEIS sequences A062692 (pre-necklaces), A000031 (necklaces),
// and A001037 (Lyndon words).
{
public:
#ifndef BINARY_NECKLACE_MAX_ARRAY_LEN
    ulong *a_;  // the string, NOTE: one-based
    ulong *dv_;  // delta sequence of divisors of n
#else
    ulong a_[BINARY_NECKLACE_MAX_ARRAY_LEN + 1];
    ulong dv_[BINARY_NECKLACE_MAX_ARRAY_LEN + 1];
#endif
    ulong n_;  // length of strings
    ulong j_;  // period of the word (if necklaces)

private:  // have pointer data
    binary_necklace(const binary_necklace&);  // forbidden
    binary_necklace & operator = (const binary_necklace&);  // forbidden

public:
    explicit binary_necklace(ulong n)
    {
        n_ = ( n ? n : 1 );  // at least one
#ifndef BINARY_NECKLACE_MAX_ARRAY_LEN
        a_ = new ulong[n_+1];
        dv_ = new ulong[n_+1];
#endif
        for (ulong j=1; j<=n; ++j)  dv_[j] = ( 0==(n_%j ) );
        first();
    }

    ~binary_necklace()
    {
#ifndef BINARY_NECKLACE_MAX_ARRAY_LEN
        delete [] a_;
        delete [] dv_;
#endif
    }

    void first()
    {
        for (ulong j=0; j<=n_; ++j)  a_[j] = 0;
        j_ = 1;
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong next_pre()  // next pre-necklace
    // return j (zero when finished)
    {
        // Find rightmost digit that can be incremented:
        ulong j = n_;
        while ( 0!=a_[j] )  { --j; }

        // Increment:
        // if ( 0==j )  return 0;  // last
        a_[j] = 1;

        // Copy periodically:
        for (ulong k=j+1; k<=n_; ++k)  a_[k] = a_[k-j];  // divisors

        j_ = j;
        return  j;
    }

    bool is_necklace()  const
    {
        return ( 0!=dv_[j_] );  // whether j divides n
    }

    bool is_lyn()  const
    {
        return ( j_==n_ );  // whether j equals n
    }

    ulong next()  // next necklace
    {
        do
        {
            next_pre();
            if ( 0==j_ )  return 0;
        }
        while ( 0==dv_[j_] );  // until j divides n
        return j_;
    }

    ulong next_lyn()  // next Lyndon word
    {
        do
        {
            next_pre();
            if ( 0==j_ )  return 0;
        }
        while ( j_==n_ );  // until j equals n
        return j_;  // == n
    }
};
// -------------------------


//#undef BINARY_NECKLACE_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_BINARY_NECKLACE_H__
