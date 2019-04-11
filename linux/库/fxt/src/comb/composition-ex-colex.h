#if !defined HAVE_COMPOSITION_EX_COLEX_H__
#define      HAVE_COMPOSITION_EX_COLEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"
#include "fxttypes.h"


//#define COMPOSITION_EX_COLEX_FIXARRAYS  // default off
// speedup with GCC 4.8.0


class composition_ex_colex
// Compositions of n into exactly k parts (k-compositions of n),
// co-lexicographic (colex) order.
// Must have:  n>=k.
{
public:
    ulong n_, k_;  // composition of n into exactly k parts
    ulong nk1_;    // == n - k + 1
#ifndef COMPOSITION_EX_COLEX_FIXARRAYS
    ulong *x_;     // data (k elements)
#else
    ulong x_[64];
#endif

private:  // have pointer data
    composition_ex_colex(const composition_ex_colex&);  // forbidden
    composition_ex_colex & operator = (const composition_ex_colex&);  // forbidden

public:
    explicit composition_ex_colex(ulong n, ulong k)
    // Must have n>=k
    {
        n_ = n;
        k_ = k;
        nk1_ = n - k + 1;  // must be >= 1
        if ( (long)nk1_ < 1 )  nk1_ = 1;  // avoid hang with invalid pair n,k
#ifndef COMPOSITION_EX_COLEX_FIXARRAYS
        x_ = new ulong[k_ + 1];
#endif
        x_[k] = 0;  // must be != 1 (sentinel)
        first();
    }

    ~composition_ex_colex()
    {
#ifndef COMPOSITION_EX_COLEX_FIXARRAYS
        delete [] x_;
#endif
    }

    const ulong * data()  const  { return x_; }

    ulong num_parts()  const  { return k_; }

    void first()
    {
        x_[0] = nk1_;  // all in first position
        for (ulong k=1; k<k_; ++k)  x_[k] = 1;
    }

    void last()
    {
        for (ulong k=0; k<k_; ++k)  x_[k] = 1;
        x_[k_-1] = nk1_;  // all in last position
    }

    ulong next()
    // Return position of rightmost change, return k with last composition.
    {
        ulong j = 0;
        while ( 1==x_[j] )  ++j;  // find first greater than one
        // can read sentinel x[k]

        if ( j >= k_ - 1 )  return k_;  // current composition is last

        ulong v = x_[j];  // value of first greater one
        x_[j] = 1;        // set to 1
        x_[0] = v - 1;    // value-1 to first position
        ++j;
        ++x_[j];          // increment next position

        return  j;
    }

    ulong prev()
    // Return position of rightmost change, return k with last composition.
    {
        const ulong v = x_[0];   // value at first position

        if ( nk1_==v )  return k_;  // current composition is first

        x_[0] = 1;          // set first position to 1
        ulong j = 1;
        while ( 1==x_[j] )  ++j;  // find next greater than one
        --x_[j];                  // decrement value
        x_[j-1] = 1 + v;          // set previous position

        return  j;
    }

    bool OK()  const
    { return is_composition_nz(data(), k_, n_); }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }
};
// -------------------------

#endif  // !defined HAVE_COMPOSITION_EX_COLEX_H__
