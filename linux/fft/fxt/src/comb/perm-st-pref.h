#if !defined  HAVE_PERM_ST_PREF_H__
#define       HAVE_PERM_ST_PREF_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "comb/endo-enup.h"
#include "comb/comb-print.h"
#include "fxttypes.h"


class perm_st_pref
// Permutations in single track order:
// all columns are cyclic shifts of the first column.
// swaps of inverse permutation are done in prefix.
{
public:
    ulong *d_;  // mixed radix digits with radix = [2, 3, 4, ..., n-1, (sentinel=-1)]
    ulong *p_;  // permutation
    ulong *pi_;  // inverse permutation
    ulong n_;   // permutations of n elements

private:  // have pointer data
    perm_st_pref(const perm_st_pref&);  // forbidden
    perm_st_pref & operator = (const perm_st_pref&);  // forbidden

public:
    explicit perm_st_pref(ulong n)
    {
        n_ = n;
        d_ = new ulong[n_];
        p_ = new ulong[n_];
        pi_ = new ulong[n_];
        d_[n-1] = -1UL;  // sentinel
        first();
    }

    ~perm_st_pref()
    {
        delete [] p_;
        delete [] pi_;
        delete [] d_;
    }

    const ulong * data()  const  { return p_; }
    const ulong * invdata()  const  { return pi_; }

    void first()
    {
        for (ulong k=0; k<n_-1; ++k)  d_[k] = 0;
        for (ulong k=0, e=0;  k<n_;  ++k)
        {
            p_[k] = e;
            pi_[e] = k;
            e = next_enup(e, n_-1);
        }
    }

    void first_id()  // start with identical permutation
    {
        for (ulong k=0; k<n_-1; ++k)  d_[k] = 0;
        for (ulong k=0; k<n_; ++k)  p_[k] = pi_[k] = k;
    }

    bool next()
    {
        // increment mixed radix number:
        ulong j = 0;
        while ( d_[j]==j+1 )  { d_[j]=0;  ++j; }

        if ( j==n_-1 )  return false;  // current permutation is last
        ++d_[j];

        // j   swaps (positions in inverse permutation, or elements in permutation)
        // 0:  (0,1)
        // 1:  (1,2)
        // 2:  (0,1) (2,3)
        // 3:  (1,2) (3,4)
        // 4:  (0,1) (2,3) (4,5)
        // 5:  (1,2) (3,4) (5,6)
        // j:  (m, m+1) (m+2, m+3) ... (j, j+1)  where m = j%2

#if 1  // do-while (slightly faster):
        ulong e1 = j & 1,  e2 = e1 + 1;
        do
        {
            const ulong i1 = pi_[e1];  // position of element e1
            const ulong i2 = pi_[e2];  // position of element e2
            pi_[e1] = i2;
            pi_[e2] = i1;
            p_[i1] = e2;
            p_[i2] = e1;
            e1+=2; e2+=2;
        }
        while ( e1<=j );
#else  // for-loop:
//        for (ulong e1=n_-2-j, e2=e1+1;  e2<n_;  e1+=2, e2+=2)  // class perm_st
        for (ulong e1=j&1, e2=e1+1;  e1<=j;  e1+=2, e2+=2)
        {
            const ulong i1 = pi_[e1];  // position of element e1
            const ulong i2 = pi_[e2];  // position of element e2
            pi_[e1] = i2;
            pi_[e2] = i1;
            p_[i1] = e2;
            p_[i2] = e1;
        }
#endif  // do-while vs. for-loop

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    {
        print_perm(bla, data(), n_, dfz);
    }

    void print_inv(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    {
        print_perm(bla, invdata(), n_, dfz);
    }
};
// -------------------------


#endif  // !defined HAVE_PERM_ST_PREF_H__
