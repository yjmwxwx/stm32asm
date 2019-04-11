#if !defined  HAVE_PERM_GRAY_LIPSKI_H__
#define       HAVE_PERM_GRAY_LIPSKI_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/comb-print.h"
#include "aux0/swap.h"
#include "fxttypes.h"


class perm_gray_lipski
// Four Gray codes for permutations.
// Algorithms following
//   W. Lipski, Jr.: More on permutation generation methods,
//   Computing, vol.23, no.4, pp.357-365, December-1979.
{
public:
    ulong *d_;  // mixed radix digits with radix = [2, 3, 4, ..., n-1, (sentinel=-1)]
    ulong *p_;  // permutation
    ulong n_;   // permutations of n elements
    ulong sw1_, sw2_;   // indices of swapped elements
private:
    ulong r_;   // order (0<=r<4):
    // 0 ==> Lipski(9) == Heap,
    // 1 ==> Lipski(16),
    // 2 ==> Lipski(10),
    // 3 ==> order not in Lipski's paper

private:  // have pointer data
    perm_gray_lipski(const perm_gray_lipski&);  // forbidden
    perm_gray_lipski & operator = (const perm_gray_lipski&);  // forbidden

public:
    explicit perm_gray_lipski(ulong n, ulong r=1)
    {
        n_ = n;
        r_ = r;
        d_ = new ulong[n_];
        p_ = new ulong[n_];
        d_[n-1] = -1UL;  // sentinel
        first();
    }

    ~perm_gray_lipski()
    {
        delete [] p_;
        delete [] d_;
    }

    const ulong *data()  const { return p_; }

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
        while ( d_[j]==j+1 )  { d_[j]=0; ++j; }
        if ( j<n_-1 )  // only if no overflow
        {
            const ulong d = d_[j];

            ulong x;
            switch ( r_ )
            {
            case 0:  x = (j&1 ? 0 : d);  break;     // Lipski(9) == Heap
            case 1:  x = (j&1 ? 0 : j-d);  break;   // Lipski(16)
            case 2:  x = (j&1 ? j-1 : d);  break;   // Lipski(10)
            default: x = (j&1 ? j-1 : j-d);  break;  // not in Lipski's paper
            }
            const ulong k = j+1;
            swap2(p_[k], p_[x]);
            sw1_ = k;  sw2_ = x;

            d_[j] = d + 1;
            return true;
        }
        return  false;  // j==n-1 for last permutation
    }

    void get_swap(ulong &s1, ulong &s2)  const  { s1=sw1_; s2=sw2_; }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    {
        print_perm(bla, data(), n_, dfz);
    }
};
// -------------------------


#endif  // !defined HAVE_PERM_GRAY_LIPSKI_H__
