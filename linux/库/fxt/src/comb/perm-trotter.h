#if !defined HAVE_PERM_TROTTER_H__
#define      HAVE_PERM_TROTTER_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


#define PERM_TROTTER_OPT  // default on
// gcc 4.5.0: massive speedup, about a factor of 2
// gcc 4.8.0: speedup (but big overall regression against gcc 4.5.0)

class perm_trotter
// Gray code for permutations, Trotter/Johnson algorithm.
// Smallest element moves most often.
{
public:
    ulong n_;     // number of elements to permute
    // Must have n>=1
    ulong *xi_;   // inverse permutation
    ulong *x_;    // permutation of {0, 1, ..., n-1}
    ulong *d_;    // auxiliary: directions
    ulong sw1_, sw2_;  // indices of elements swapped most recently
#ifdef PERM_TROTTER_OPT
    ulong ctm_;  // counter to detect easy case
    ulong xi0_;  // position of element zero
    ulong d0_;   // direction of element zero
#endif  // PERM_TROTTER_OPT


private:  // have pointer data
    perm_trotter(const perm_trotter&);  // forbidden
    perm_trotter & operator = (const perm_trotter&);  // forbidden

public:
    explicit perm_trotter(ulong n)
    {
        n_ = n;
        xi_ = new ulong[n_+2 + (n_==0)];
        x_ = new ulong[n_+2 + (n_==0)];
        d_ = new ulong[n_+2];

        x_[0] = x_[n_+1] = 0;  // sentinel value minimal
        ++x_;  // nota bene

        first();
    }

    ~perm_trotter()
    {
        --x_;
        delete [] xi_;
        delete [] d_;
        delete [] x_;
    }

private:
    void fl_swaps()
    // Auxiliary routine for first() and last().
    // Set sw1, sw2 to swaps between first and last permutation.
    {
        sw1_ = ( n_==0 ? 0 : n_ - 1 );
        sw2_ = ( n_<=1 ? 0 : n_ - 2 );
    }

    void small_n()
    // Make cases n==0 and n==1 work.
    {
        if ( n_ <= 1 )
        {
#ifdef PERM_TROTTER_OPT
            ctm_ = 1;
#endif
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
        for (ulong i=0; i<n_; i++)  d_[i] = 1;
        fl_swaps();

#ifdef PERM_TROTTER_OPT
        ctm_ = n_;
        d0_ = d_[0];
        xi0_ = xi_[0];
#endif  // PERM_TROTTER_OPT

        small_n();  // also if PERM_TROTTER_OPT not defined
    }

    void last()
    {
        for (ulong i=0; i<n_; i++)  xi_[i] = i;
        for (ulong i=0; i<n_; i++)  x_[i] = i;
        for (ulong i=0; i<n_; i++)  d_[i] = -1UL;
        fl_swaps();
        d_[sw1_] = +1;  d_[sw2_] = +1;
        swap2(x_[sw1_], x_[sw2_]);
        swap2(xi_[sw1_], xi_[sw2_]);

#ifdef PERM_TROTTER_OPT
        ctm_ = n_;
        d0_ = d_[0];
        xi0_ = xi_[0];

        small_n();
#endif  // PERM_TROTTER_OPT
    }


    bool next()
    {
#ifdef PERM_TROTTER_OPT
        if ( --ctm_ )  // easy case: move element 0
        {
            ulong i1 = xi0_;   // position of element 0
            ulong d = d0_;     // direction to move 0
            ulong i2 = i1 + d;   // position to swap with
            ulong e2 = x_[i2];   // element to swap with
            xi_[0] = i2;
            xi0_ = i2;
            xi_[e2] = i1;
            x_[i1] = e2;
            x_[i2] = 0;
            sw1_ = i1;  sw2_ = i2;
            return true;
        }
        d0_ = -d0_;
        ctm_ = n_;
#endif  // PERM_TROTTER_OPT


#ifdef PERM_TROTTER_OPT
        ulong e1 = 1;  // note: start at e1=1
#else   // PERM_TROTTER_OPT
        ulong e1 = 0;
#endif  // PERM_TROTTER_OPT
        do
        {
            // e1 is the element we try to move
            ulong i1 = xi_[e1];   // position of element e1
            ulong d = d_[e1];     // direction to move e1
            ulong i2 = i1 + d;    // position to swap with
            ulong e2 = x_[i2];    // element to swap with

            if ( e1 < e2 )  // can we swap?
            {
                xi_[e1] = i2;
                xi_[e2] = i1;
                x_[i1] = e2;
                x_[i2] = e1;
                sw1_ = i1;  sw2_ = i2;
                while ( e1-- )  d_[e1] = -d_[e1];
                return true;
            }
            ++e1;
        }
        while ( e1<n_ );

        first();
        return false;
    }


    bool prev()
    {
#ifdef PERM_TROTTER_OPT
        if ( --ctm_ )  // easy case: move element 0
        {
            ulong i1 = xi0_;   // position of element 0
            ulong d = -d0_;     // direction to move 0 (NOTE: negated)
            ulong i2 = i1 + d;   // position to swap with
            ulong e2 = x_[i2];   // element to swap with
            xi_[0] = i2;
            xi0_ = i2;
            xi_[e2] = i1;
            x_[i1] = e2;
            x_[i2] = 0;
            sw1_ = i1;  sw2_ = i2;
            return true;
        }
        d0_ = -d0_;
        ctm_ = n_;
#endif  // PERM_TROTTER_OPT

#ifdef PERM_TROTTER_OPT
        ulong e1 = 1;  // note: start at e1=1
#else   // PERM_TROTTER_OPT
        ulong e1 = 0;
#endif  // PERM_TROTTER_OPT
        do
        {
            // e1 is the element we try to move
            ulong i1 = xi_[e1];   // position of element e1
            ulong d = -d_[e1];     // direction to move e1 (NOTE: negated)
            ulong i2 = i1 + d;    // position to swap with
            ulong e2 = x_[i2];    // element to swap with

            if ( e1 < e2 )  // can we swap?
            {
                xi_[e1] = i2;
                xi_[e2] = i1;
                x_[i1] = e2;
                x_[i2] = e1;
                sw1_ = i1;  sw2_ = i2;
                while ( e1-- )  d_[e1] = -d_[e1];
                return true;
            }
            ++e1;
        }
        while ( e1<n_ );

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

//#undef PERM_TROTTER_OPT  // leave in


#endif  // !defined HAVE_PERM_TROTTER_H__
