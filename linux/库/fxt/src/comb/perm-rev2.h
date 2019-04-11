#if !defined  HAVE_PERM_REV2_H__
#define       HAVE_PERM_REV2_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "perm/reverse.h"
#include "comb/comb-print.h"
#include "fxttypes.h"


//#define PERM_REV2_FIXARRAYS  // use arrays instead of pointers

class perm_rev2
// Permutations by reversing prefixes, CAT algorithm.
// Optimized version.
{
public:
#ifndef PERM_REV2_FIXARRAYS
    ulong *d_;  // mixed radix digits with radix = [2, 3, 4, ..., n-1, (sentinel=-1)]
    ulong *p_;  // permutation
#else
    ulong d_[32];
    ulong p_[32];
#endif
    ulong n_;   // permutations of n elements
    ulong ct_;  // count 5,4,3,2,1,(0); nonzero ==> easy cases

private:  // have pointer data
    perm_rev2(const perm_rev2&);  // forbidden
    perm_rev2 & operator = (const perm_rev2&);  // forbidden

public:
    explicit perm_rev2(ulong n)
    {
        n_ = n;
#ifndef PERM_REV2_FIXARRAYS
        const ulong s = ( n_<3 ? 3 : n_ );
        p_ = new ulong[s+1];
        d_ = new ulong[s];
#endif
        first();
    }

    ~perm_rev2()
    {
#ifndef PERM_REV2_FIXARRAYS
        delete [] p_;
        delete [] d_;
#endif
    }

    const ulong * data()  const { return p_; }

    void first()
    {
        const ulong s = ( n_<3 ? 3 : n_ );
        for (ulong k=0; k<s; ++k)  d_[k] = 0;
        d_[s-1] = -1UL;  // sentinel
        for (ulong k=0; k<s; ++k)  p_[k] = k;
        ct_ = 5;
    }

    ulong next()
    // Return index of last element with reversal.
    // Return n with last permutation.
    {
        if ( ct_!=0 )  // easy case(s)
        {
            --ct_;
            const ulong e = 1 + (ct_ & 1);
            swap2(p_[0], p_[e]);
            return  e;
        }
        else
        {
            ct_ = 5;  // reset counter
            ulong j = 2;  // note: start with 2
            while ( d_[j]==j+1 )  { d_[j]=0; ++j; }  // can read sentinel
            ++d_[j];
            reverse(p_, j+2);  // update permutation
            return  j + 1;
        }
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------

//#undef PERM_REV2_FIXARRAYS


#endif  // !defined HAVE_PERM_REV2_H__
