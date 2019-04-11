#if !defined  HAVE_PERM_HEAP_H__
#define       HAVE_PERM_HEAP_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"


class perm_heap
// Gray code for permutations.
// Algorithm following
//   B. R. Heap: "Permutations by interchanges" (1963)
{
public:
    ulong *d_;  // mixed radix digits with radix = [2, 3, 4, ..., n-1, (sentinel=-1)]
    ulong *p_;  // permutation
    ulong n_;   // permutations of n elements
    ulong sw1_, sw2_;   // indices of swapped elements

private:  // have pointer data
    perm_heap(const perm_heap&);  // forbidden
    perm_heap & operator = (const perm_heap&);  // forbidden

public:
    explicit perm_heap(ulong n)
    {
        n_ = n;
        d_ = new ulong[n_];
        p_ = new ulong[n_];
        d_[n-1] = -1UL;  // sentinel
        first();
    }

    ~perm_heap()
    {
        delete [] p_;
        delete [] d_;
    }

    const ulong * data()  const  { return p_; }

    void first()
    {
        for (ulong k=0; k<n_-1; ++k)  d_[k] = 0;
        for (ulong k=0; k<n_; ++k)  p_[k] = k;
        sw1_=0;  sw2_=0;
    }

    bool next()
    {
        // increment mixed radix number:
        ulong j = 0;
        while ( d_[j]==j+1 )  { d_[j]=0; ++j; }  // can read sentinel

        // j==n-1 for last permutation:
        if ( j==n_-1 )  return false;

        ulong k = j+1;
        ulong x = ( k&1 ? d_[j] : 0 );
        swap2(p_[k], p_[x]);  // omit statement to just compute swaps
        sw1_ = k;  sw2_ = x;

        ++d_[j];
        return true;
    }

    void get_swap(ulong &s1, ulong &s2)  const  { s1=sw1_; s2=sw2_; }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PERM_HEAP_H__
