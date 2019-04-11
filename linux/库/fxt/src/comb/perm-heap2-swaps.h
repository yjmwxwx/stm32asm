#if !defined  HAVE_PERM_HEAP2_SWAPS_H__
#define       HAVE_PERM_HEAP2_SWAPS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


// use arrays instead of pointers:
#define PERM_HEAP2_SWAPS_FIXARRAYS  // speedup


class perm_heap2_swaps
// Swaps for Gray code for permutations.
// Algorithm following
//   B. R. Heap: "Permutations by interchanges" (1963)
// Optimized implementation, very fast.
{
public:
#ifndef PERM_HEAP2_SWAPS_FIXARRAYS
    ulong *d_;  // mixed radix digits with radix = [2, 3, 4, 5, ..., n-1, (sentinel=-1)]
#else
    ulong d_[32];
#endif  // PERM_HEAP2_SWAPS_FIXARRAYS

    ulong n_;   // permutations of n elements
    ulong sw1_, sw2_;   // indices of swapped elements
    ulong ct_;  // count 5,4,3,2,1,(0); nonzero ==> easy cases

private:  // have pointer data
    perm_heap2_swaps(const perm_heap2_swaps&);  // forbidden
    perm_heap2_swaps & operator = (const perm_heap2_swaps&);  // forbidden

public:
    explicit perm_heap2_swaps(ulong n)  // must have n>=3
    {
        n_ = n;
#ifndef PERM_HEAP2_SWAPS_FIXARRAYS
        const ulong s = ( n_<3 ? 3 : n_ );
        d_ = new ulong[s];
#endif
        // d[0] and d[1] are unused
        first();
    }

    ~perm_heap2_swaps()
    {
#ifndef PERM_HEAP2_SWAPS_FIXARRAYS
        delete [] d_;
#endif
    }

    void first()
    {
        const ulong s = ( n_<3 ? 3 : n_ );
        for (ulong k=0; k<s; ++k)  d_[k] = 0;
        d_[s-1] = -1UL;  // sentinel
        sw1_=0;  sw2_=0;
        ct_ = 5;
    }

    ulong next()
    // Return index of last element with reversal.
    // Return n with last permutation.
    {
        if ( ct_!=0 )  // easy cases
        {
            --ct_;
            sw1_ = 1 + (ct_ & 1);  // == 1,2,1,2,1
            sw2_ = 0;
            return  sw1_;
        }
        else
        {
            ct_ = 5;  // reset counter

            // increment mixed radix number:
            ulong j = 2;
            while ( d_[j]==j+1 )  { d_[j]=0; ++j; }  // can read sentinel

            // j==n-1 for last permutation:
            if ( j==n_-1 )  return  n_;

            ulong k = j+1;
            ulong x = ( k&1 ? d_[j] : 0 );
            sw1_ = k;  sw2_ = x;

            ++d_[j];

            return k;
        }
    }

    void get_swap(ulong &s1, ulong &s2)  const  { s1=sw1_; s2=sw2_; }
};
// -------------------------



#endif  // !defined HAVE_PERM_HEAP2_SWAPS_H__
