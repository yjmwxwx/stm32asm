#if !defined HAVE_PERM_GRAY_FFACT2_H__
#define      HAVE_PERM_GRAY_FFACT2_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "comb/mixedradix-gray2.h"
#include "comb/comb-print.h"
#include "fxttypes.h"


class perm_gray_ffact2
// Gray code for permutations (Trotter/Johnson ordering).
// Loopless algorithm based on mixed radix Gray code
//   for the factorial number system.
{
public:
    mixedradix_gray2 *mrg_;  // loopless routine
    ulong n_;   // number of elements to permute
    ulong *x_;  // current permutation (of {0, 1, ..., n-1})
    ulong *ix_;  // inverse permutation
    ulong sw1_, sw2_;  // indices of elements swapped most recently

private:  // have pointer data
    perm_gray_ffact2(const perm_gray_ffact2&);  // forbidden
    perm_gray_ffact2 & operator = (const perm_gray_ffact2&);  // forbidden

public:
    explicit perm_gray_ffact2(ulong n)
    {
        n_ = n;
        x_ = new ulong[n_];
        ix_ = new ulong[n_];
        mrg_ = new mixedradix_gray2(n_-1, 0);  // falling factorial base

        first();
    }

    ~perm_gray_ffact2()
    {
        delete [] x_;
        delete [] ix_;
        delete mrg_;
    }

    void first()
    {
        mrg_->first();
        for (ulong k=0; k<n_; ++k)  x_[k] = ix_[k] = k;
        sw1_=n_-1;  sw2_=n_-2;
    }

    bool next()
    {
        // Compute next mixed radix number in Gray code order:
        if ( false == mrg_->next() )  { first(); return false; }
        const ulong j = mrg_->pos();  // position of changed digit
        const int d = mrg_->dir();    // direction of change

        // swap:
        const ulong x1 = j;        // element j
        const ulong i1 = ix_[x1];  // position of j
        const ulong i2 = i1 + (ulong)d;   // neighbor
        const ulong x2 = x_[i2];   // position of neighbor
        x_[i1] = x2;   x_[i2] = x1;   // swap2(x_[i1], x_[i2]);
        ix_[x1] = i2;  ix_[x2] = i1;  // swap2(ix_[x1], ix_[x2]);
        sw1_=i1;  sw2_=i2;
        return true;
    }

    const ulong * data()  const  { return x_; }
    const ulong * invdata()  const  { return ix_; }
    void get_swap(ulong &s1, ulong &s2)  const  { s1=sw1_; s2=sw2_; }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }

    void print_inv(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, invdata(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PERM_GRAY_FFACT2_H__
