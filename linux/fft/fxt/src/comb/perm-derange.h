#if !defined HAVE_PERM_DERANGE_H__
#define      HAVE_PERM_DERANGE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/perm-trotter.h"
#include "comb/comb-print.h"
#include "perm/rotate.h"
#include "fxttypes.h"


class perm_derange
// Permutations in derangement order.
// There is no derangement order for n=3 elements.
{
public:
    ulong n_;   // number of elements
    ulong *x_;  // current permutation
    ulong ctm_;  // counter modulo n
    perm_trotter* T_;

private:  // have pointer data
    perm_derange(const perm_derange&);  // forbidden
    perm_derange & operator = (const perm_derange&);  // forbidden

public:
    explicit perm_derange(ulong n)
    {
        n_ = n;
        x_ = new ulong[n_];
        T_ = new perm_trotter(n_-1);
        first();
    }

    ~perm_derange()
    {
        delete [] x_;
        delete T_;
    }

    void first()
    {
        ctm_ = 0;
        for (ulong k=0; k<n_; ++k)  x_[k] = k;
    }

    bool next()
    {
        ++ctm_;
        if ( ctm_>=n_ )  // every n steps: need next perm_trotter
        {
            ctm_ = 0;
            if ( ! T_->next() )  return false;  // current permutation is last
            const ulong *t = T_->data();
            for (ulong k=0; k<n_-1; ++k)  x_[k] = t[k];
            x_[n_-1] = n_-1;  // last element
        }
        else  // rotate
        {
            if ( ctm_==n_-1 )  rotate_left1(x_, n_);
            else  // last two elements swapped
            {
                rotate_right1(x_, n_);
                if ( ctm_==n_-2 )  rotate_right1(x_, n_);
            }
        }
        return true;
    }

    const ulong * data()  const  { return x_; }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PERM_DERANGE_H__
