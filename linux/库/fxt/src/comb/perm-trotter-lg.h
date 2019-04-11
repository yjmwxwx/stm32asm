#if !defined HAVE_PERM_TROTTER_LG_H__
#define      HAVE_PERM_TROTTER_LG_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"


class perm_trotter_lg
// Gray code for permutations
// Trotter/Johnson algorithm.
// Largest element moves most often.
{
public:
    ulong n_;     // number of elements to permute
    ulong *xi_;   // inverse permutation
    ulong *x_;    // permutation of {0, 1, ..., n-1}
    ulong *d_;    // auxiliary: directions
    ulong sw1_, sw2_;  // indices of elements swapped most recently

private:  // have pointer data
    perm_trotter_lg(const perm_trotter_lg&);  // forbidden
    perm_trotter_lg & operator = (const perm_trotter_lg&);  // forbidden

public:
    explicit perm_trotter_lg(ulong n)
    {
        n_ = n;
        xi_ = new ulong[n_+2];
        x_ = new ulong[n_+2 + (n_==0)];
        d_ = new ulong[n_+2];

        ulong sen = n_;  // sentinel value maximal
        x_[0] = x_[n_+1] = sen;

        ++x_;
        first();
    }

    ~perm_trotter_lg()
    {
        --x_;
        delete [] xi_;
        delete [] d_;
        delete [] x_;
    }

private:
    void small_n()
    // Make cases n==0 and n==1 work.
    {
        if ( n_ <= 1 )
        {
            x_[0] = 0;  x_[1] = 1;
            xi_[0] = 0;  xi_[1] = 1;
            d_[0] = 0;  d_[1] = 0;
        }
    }

public:
    void first()
    {
        for (ulong i=0; i<n_; i++)  xi_[i] = i;
        for (ulong i=0; i<n_; i++)  x_[i] = i;
        for (ulong i=0; i<n_; i++)  d_[i] = -1UL;
        sw1_ = 0;  sw2_ = 1;  // relative to last permutation
        small_n();
    }

    void last()
    {
        for (ulong i=0; i<n_; i++)  xi_[i] = i;
        for (ulong i=0; i<n_; i++)  x_[i] = i;
        for (ulong i=0; i<n_; i++)  d_[i] = +1;
        sw1_ = 0;  sw2_ = 1;  // relative to first permutation
        d_[sw1_] = -1UL;
        d_[sw2_] = -1UL;
        swap2(x_[sw1_], x_[sw2_]);
        swap2(xi_[sw1_], xi_[sw2_]);
        small_n();
    }

    bool next()
    {
        ulong e1 = n_;
        while ( e1-- )
        {
            // e1 is the element we try to move
            ulong i1 = xi_[e1];   // position of element e1
            ulong d = d_[e1];     // direction to move e1
            ulong i2 = i1 + d;    // position to swap with
            ulong e2 = x_[i2];    // element to swap with

            if ( e1 > e2 )  // can we swap?
            {
                xi_[e1] = i2;
                xi_[e2] = i1;
                x_[i1] = e2;
                x_[i2] = e1;
                sw1_ = i1;  sw2_ = i2;
                while ( ++e1<n_ )  d_[e1] = -d_[e1];
                return true;
            }
        }

        first();
        return false;
    }


    bool prev()
    {
        ulong e1 = n_;
        while ( e1-- )
        {
            // e1 is the element we try to move
            ulong i1 = xi_[e1];   // position of element e1
            ulong d = -d_[e1];     // direction to move e1 (NOTE: negated)
            ulong i2 = i1 + d;    // position to swap with
            ulong e2 = x_[i2];    // element to swap with

            if ( e1 > e2 )  // can we swap?
            {
                xi_[e1] = i2;
                xi_[e2] = i1;
                x_[i1] = e2;
                x_[i2] = e1;
                sw1_ = i1;  sw2_ = i2;
                while ( ++e1<n_ )  d_[e1] = -d_[e1];
                return true;
            }
        }

        last();
        return false;
    }

    const ulong * data()  const  { return x_; }
    const ulong * invdata()  const  { return xi_; }
    void get_swap(ulong &s1, ulong &s2)  const  { s1=sw1_; s2=sw2_; }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }

    void print_inv(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, invdata(), n_, dfz); }
};
// -------------------------



#endif  // !defined HAVE_PERM_TROTTER_LG_H__
