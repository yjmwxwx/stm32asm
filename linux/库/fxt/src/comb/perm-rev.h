#if !defined  HAVE_PERM_REV_H__
#define       HAVE_PERM_REV_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "perm/reverse.h"
#include "perm/rotate.h"
#include "comb/comb-print.h"
#include "fxttypes.h"

class perm_rev
// Permutations by reversing prefixes, CAT algorithm
{
public:
    ulong *d_;  // mixed radix digits with radix = [2, 3, 4, ..., n-1, (sentinel=-1)]
    ulong *p_;  // permutation
    ulong n_;   // permutations of n elements

private:  // have pointer data
    perm_rev(const perm_rev&);  // forbidden
    perm_rev & operator = (const perm_rev&);  // forbidden

public:
    explicit perm_rev(ulong n)
    {
        n_ = n;
        p_ = new ulong[n_];
        d_ = new ulong[n_];
        d_[n-1] = -1UL;  // sentinel
        first();
    }

    ~perm_rev()
    {
        delete [] p_;
        delete [] d_;
    }

    const ulong * data()  const  { return p_; }

    void first()
    {
        for (ulong k=0; k<n_-1; ++k)  d_[k] = 0;
        for (ulong k=0; k<n_; ++k)  p_[k] = k;
    }

    void last()
    {
        for (ulong k=0; k<n_-1; ++k)  d_[k] = k+1;
        for (ulong k=0; k<n_; ++k)  p_[k] = n_-1-k;
    }

    bool next()
    {
        // increment mixed radix number:
        ulong j = 0;
        while ( d_[j]==j+1 )  { d_[j]=0; ++j; }

        // j==n-1 for last permutation
        if ( j!=n_-1 )  // only if no overflow
        {
            ++d_[j];
            reverse(p_, j+2);  // update permutation
            return true;
        }
        else  return false;
    }

    bool prev()
    {
        // decrement mixed radix number:
        ulong j = 0;
        while ( d_[j]==0 )  { d_[j]=j+1; ++j; }

         // j==n-1 for last permutation
        if ( j!=n_-1 )  // only if no overflow
        {
            --d_[j];
            reverse(p_, j+2);  // update permutation
            return true;
        }
        else  return false;
    }

    void goto_rfact(const ulong *d)
    // Goto permutation corresponding to d[] (i.e. unrank d[]).
    // d[] must be a valid (rising) factorial mixed radix string:
    // d[]==[d(0), d(1), d(2), ..., d(n-2)]  (n-1 elements) where 0<=d(j)<=j+1
    {
        for (ulong k=0; k<n_; ++k)  p_[k] = k;
        for (ulong k=0; k<n_-1; ++k)  d_[k] = d[k];
        for (ulong j=n_-2; (long)j>=0; --j)  rotate_right(p_, j+2, d_[j]);
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PERM_REV_H__
