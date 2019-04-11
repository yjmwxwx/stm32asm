#if !defined HAVE_PERM_STAR_SWAPS_H__
#define      HAVE_PERM_STAR_SWAPS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"

#define PERM_STAR_SWAPS_FIXARRAYS  // speedup

class perm_star_swaps
// Permutations in star-transposition order (a Gray code).
// Compute swaps only.
// Algorithm of Gideon Ehrlich, as given by Knuth
{
public:
    ulong n_;    // number of elements
    ulong swp_;  // index of element that was swapped (with index 0)
#ifndef PERM_STAR_SWAPS_FIXARRAYS
    ulong *b_;   // auxiliary array
    ulong *c_;   // auxiliary array: mixed radix number in rising factorial base
#else
    ulong b_[32];
    ulong c_[32];
#endif

private:  // have pointer data
    perm_star_swaps(const perm_star_swaps&);  // forbidden
    perm_star_swaps & operator = (const perm_star_swaps&);  // forbidden

public:
    explicit perm_star_swaps(ulong n)
    {
        n_ = n;
        if ( n==0 )  n_ = 1;  // avoid loop with zero size
#ifndef PERM_STAR_SWAPS_FIXARRAYS
        b_ = new ulong[n_];
        c_ = new ulong[n_+1];
#endif
        first();
    }

    ~perm_star_swaps()
    {
#ifndef PERM_STAR_SWAPS_FIXARRAYS
        delete [] b_;
        delete [] c_;
#endif
    }

    void first()
    {
//        swp_ = n_ - 1;
        swp_ = 0;
        for (ulong k=0; k<n_; ++k)  b_[k] = k;
        for (ulong k=0; k<=n_; ++k)  c_[k] = 0;
    }

    bool next()
    {
        ulong k = 1;
        while ( c_[k]==k )  { c_[k]=0;  ++k; }

        if ( k == n_ )   return false;

        ++c_[k];
        swp_ = b_[k];

        ulong j = 1;
        --k;
        while ( j < k )  // < 0.18 iterations per call
        {
            swap2(b_[j], b_[k]);
            ++j;
            --k;
        }
        return  true;
    }

    ulong get_swap()  const  { return swp_; }
    void get_swap(ulong &s1, ulong &s2)  const  { s1=0; s2=swp_; }
};
// -------------------------



#endif  // !defined HAVE_PERM_STAR_SWAPS_H__
