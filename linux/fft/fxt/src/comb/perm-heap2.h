#if !defined  HAVE_PERM_HEAP2_H__
#define       HAVE_PERM_HEAP2_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"


#define PERM_HEAP2_FIXARRAYS  // use arrays instead of pointers (speedup)


class perm_heap2
// Gray code for permutations.
// Algorithm following
//   B. R. Heap: "Permutations by interchanges" (1963)
// Optimized implementation, very fast.
{
public:
#ifndef PERM_HEAP2_FIXARRAYS
    ulong *d_;  // mixed radix digits with radix = [2, 3, 4, 5, ..., n-1, (sentinel=-1)]
    ulong *p_;  // permutation
#else
    ulong d_[32];
    ulong p_[32];  // permutation
#endif  // PERM_HEAP2_FIXARRAYS

    ulong n_;   // permutations of n elements
    ulong sw1_, sw2_;   // indices of swapped elements
    ulong ct_;  // count 5,4,3,2,1,(0); nonzero ==> easy cases

private:  // have pointer data
    perm_heap2(const perm_heap2&);  // forbidden
    perm_heap2 & operator = (const perm_heap2&);  // forbidden

public:
    explicit perm_heap2(ulong n)  // must have n>=3
    {
        n_ = n;
#ifndef PERM_HEAP2_FIXARRAYS
        const ulong s = ( n_<3 ? 3 : n_ );
        d_ = new ulong[s];
        p_ = new ulong[s];
#endif
        // d[0] and d[1] are unused
        first();
    }

    ~perm_heap2()
    {
#ifndef PERM_HEAP2_FIXARRAYS
        delete [] p_;
        delete [] d_;
#endif
    }

    const ulong * data()  const  { return p_; }

    void first()
    {
        const ulong s = ( n_<3 ? 3 : n_ );
        for (ulong k=0; k<s; ++k)  d_[k] = 0;
        d_[s-1] = -1UL;  // sentinel
        for (ulong k=0; k<s; ++k)  p_[k] = k;
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
            swap2(p_[sw1_], p_[sw2_]);
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
            swap2(p_[k], p_[x]);
            sw1_ = k;  sw2_ = x;

            ++d_[j];

            return k;
        }
    }

    void get_swap(ulong &s1, ulong &s2)  const  { s1=sw1_; s2=sw2_; }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------

//#undef PERM_HEAP2_FIXARRAYS  // leave in

#endif  // !defined HAVE_PERM_HEAP2_H__
