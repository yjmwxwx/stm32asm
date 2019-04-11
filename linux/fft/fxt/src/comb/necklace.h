#if !defined  HAVE_NECKLACE_H__
#define       HAVE_NECKLACE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"

// If defined, arrays are used instead of pointers, this gives a small speedup:
//#define NECKLACE_MAX_ARRAY_LEN 96  // default off

class necklace
// Generate necklaces, iterative algorithm.
{
public:
#ifndef NECKLACE_MAX_ARRAY_LEN
    ulong *a_;  // the string, NOTE: one-based
    ulong *dv_;  // delta sequence of divisors of n
#else
    ulong a_[NECKLACE_MAX_ARRAY_LEN + 1];
    ulong dv_[NECKLACE_MAX_ARRAY_LEN + 1];
#endif
    ulong n_;   // length of strings
    ulong m1_;  // m-ary strings, m1=m-1
    ulong j_;   // period of the word (if necklaces)

private:  // have pointer data
    necklace(const necklace&);  // forbidden
    necklace & operator = (const necklace&);  // forbidden

public:
    explicit necklace(ulong m, ulong n)
    {
        n_ = ( n ? n : 1 );  // at least 1
        m1_ = ( m>1 ? m-1 : 1);  // at least 2
#ifndef NECKLACE_MAX_ARRAY_LEN
        a_ = new ulong[n_+1];
        dv_ = new ulong[n_+1];
#endif
        for (ulong j=1; j<=n; ++j)  dv_[j] = ( 0==(n_%j ) );  // divisors
        first();
    }

    ~necklace()
    {
#ifndef NECKLACE_MAX_ARRAY_LEN
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
        while ( a_[j] == m1_ )  { --j; }

        // Increment:
        // if ( 0==j_ )   return 0;  // last
        ++a_[j];

        // Copy periodically:
        for (ulong k=j+1; k<=n_; ++k)  a_[k] = a_[k-j];

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

//#undef NECKLACE_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_NECKLACE_H__
