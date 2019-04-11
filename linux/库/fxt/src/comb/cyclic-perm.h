#if !defined HAVE_CYCLIC_PERM_H__
#define      HAVE_CYCLIC_PERM_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "comb/mixedradix-gray.h"
#include "perm/perminvert.h"  // make_inverse()

#include "fxttypes.h"


class cyclic_perm
// Cyclic permutations in minimal-change order.
// CAT algorithm based on mixed radix Gray code
//   for the factorial number system.
{
public:
    mixedradix_gray *M_;
    ulong n_;   // number of elements to permute
    ulong *ix_;  // current permutation (of {0, 1, ..., n-1})
    ulong *x_;  // inverse permutation

private:  // have pointer data
    cyclic_perm(const cyclic_perm&);  // forbidden
    cyclic_perm & operator = (const cyclic_perm&);  // forbidden

public:
    explicit cyclic_perm(ulong n)
        : n_(n)
    {
        ix_ = new ulong[n_];
        x_ = new ulong[n_];
        M_ = new mixedradix_gray(n_-2, 0);  // falling factorial base
        first();
    }

    ~cyclic_perm()
    {
        delete [] ix_;
        delete [] x_;
        delete M_;
    }

private:
    void setup()
    {
        const ulong *fc = M_->data();
        for (ulong k=0; k<n_; ++k)  ix_[k] = k;

        for (ulong k=n_-1; k>1; --k)
        {
            ulong z = n_-3-(k-2);  // 0, ..., n-3
            ulong i = fc[z];
            swap2(ix_[k], ix_[i]);
        }
        if ( n_>1 )  swap2(ix_[0], ix_[1]);

        make_inverse(ix_, x_, n_);
    }

public:
    void first()
    {
        M_->first();
        setup();
    }

    bool next()
    {
        if ( false == M_->next() )  { first();  return false; }
        ulong j = M_->pos();

        if ( j && (x_[0]==n_-1) )  // once in 2*n cases
        {
            setup();  // work proportional to n
            // only 3 elements are interchanged
        }
        else  // easy case
        {
            ulong d = (ulong)( M_->dir() );
            ulong x2 = (M_->data())[j];
            ulong x1 = x2 - d,  x3 = n_ - 1;
            ulong i1 = x_[x1], i2 = x_[x2], i3 = x_[x3];

            swap2(x_[x1], x_[x2]);
            swap2(x_[x1], x_[x3]);
            swap2(ix_[i1], ix_[i2]);
            swap2(ix_[i2], ix_[i3]);
        }

        return true;
    }

    const ulong * data()  const  { return x_; }
    const ulong * invdata()  const  { return ix_; }
};
// -------------------------


#endif  // !defined HAVE_CYCLIC_PERM_H__
