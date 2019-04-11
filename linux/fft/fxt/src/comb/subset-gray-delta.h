#if !defined HAVE_SUBSET_GRAY_DELTA_H__
#define      HAVE_SUBSET_GRAY_DELTA_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/bitlow.h"
//#include "bits/bitsperlong.h"
#include "fxttypes.h"

// If defined, an array is used instead of a pointer, this gives small speedup:
#define SUBSET_GRAY_DELTA_MAX_ARRAY_LEN 64  // default on (slight speedup)

class subset_gray_delta
// Subsets of the set {0,1,2,...,n-1} in minimal-change (Gray code) order.
// Loopless algorithm.
{
public:
#ifndef SUBSET_GRAY_DELTA_MAX_ARRAY_LEN
    ulong *x_;  // current subset as delta set
#else
    ulong x_[SUBSET_GRAY_DELTA_MAX_ARRAY_LEN];
#endif
    ulong n_;   // number of elements in set <= BITS_PER_LONG
    ulong j_;   // position of last change
    ulong ct_;  // gray_code(ct_) corresponds to the current subset
    ulong mct_;  // max value of ct.

private:  // have pointer data
    subset_gray_delta(const subset_gray_delta&);  // forbidden
    subset_gray_delta & operator = (const subset_gray_delta&);  // forbidden

public:
    explicit subset_gray_delta(ulong n)
    {
        n_ = (n ? n : 1);  // not zero
#ifndef SUBSET_GRAY_DELTA_MAX_ARRAY_LEN
        x_ = new ulong[n_];
#endif
        mct_ = (1UL<<n) - 1;
        first(0);
    }

    ~subset_gray_delta()
    {
#ifndef SUBSET_GRAY_DELTA_MAX_ARRAY_LEN
        delete [] x_;
#endif
    }


    void first(ulong v=0)
    {
        ct_ = 0;
        j_ = n_ - 1;
        for (ulong j=0; j<n_; ++j)  x_[j] = v;
    }

    const ulong * data()  const  { return x_; }
    ulong pos()  const { return j_; }
    ulong current()  const  { return ct_; }

    ulong next()
    // Return position of change, return n with last subset
    {
        if ( ct_ == mct_ )  { return n_; }

        ++ct_;
        j_ = lowest_one_idx( ct_ );
        x_[j_] ^= 1;

        return  j_;
    }

    ulong prev()
    // Return position of change, return n with first subset
    {
        if ( ct_ == 0 )  { return n_; }

        j_ = lowest_one_idx( ct_ );
        x_[j_] ^= 1;
        --ct_;

        return  j_;
    }
};
// -------------------------

//#undef SUBSET_GRAY_DELTA_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_SUBSET_GRAY_DELTA_H__
