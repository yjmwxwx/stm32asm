#if !defined HAVE_COMPOSITION_EX_LEX_H__
#define      HAVE_COMPOSITION_EX_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"
#include "fxttypes.h"


//#define COMPOSITION_EX_LEX_FIXARRAYS  // default off
// slight speedup with GCC 4.8.0


class composition_ex_lex
// Compositions of n into exactly k parts (k-compositions of n),
// lexicographic order.
// Must have:  n>=k.
{
public:
    ulong n_, k_;  // composition of n into exactly k parts
    ulong nk1_;    // == n - k + 1
#ifndef COMPOSITION_EX_LEX_FIXARRAYS
    ulong *x_;     // data (k elements)
#else
    ulong x_[64];
#endif

private:  // have pointer data
    composition_ex_lex(const composition_ex_lex&);  // forbidden
    composition_ex_lex & operator = (const composition_ex_lex&);  // forbidden

public:
    explicit composition_ex_lex(ulong n, ulong k)
    // Must have n>=k
    {
        n_ = n;
        k_ = k;
        nk1_ = n - k + 1;  // must be >= 1
        if ( (long)nk1_ < 1 )  nk1_ = 1;  // avoid hang with invalid pair n,k
#ifndef COMPOSITION_EX_LEX_FIXARRAYS
        x_ = new ulong[k_ + 1];
#endif
        x_[0] = 0;  // must be != 1 (sentinel)
        first();
    }

    ~composition_ex_lex()
    {
#ifndef COMPOSITION_EX_LEX_FIXARRAYS
        delete [] x_;
#endif
    }

    const ulong * data()  const  { return x_ + 1; }

    ulong num_parts()  const  { return k_; }

    void first()
    {
        for (ulong k=1; k<=k_; ++k)  x_[k] = 1;
        x_[k_] = nk1_;  // all in last position
    }

    void last()
    {
        x_[1] = nk1_;  // all in first position
        for (ulong k=2; k<=k_; ++k)  x_[k] = 1;
    }

    ulong next()
    // Return 1 + position of leftmost change, return 0 with last composition.
    {
        ulong j = k_;
        while ( 1==x_[j] )  --j;  // find first greater than one
        // can read sentinel x[0]

        if ( j <= 1 )  return 0;  // current composition is last

        ulong v = x_[j];  // value of first greater one
        x_[j] = 1;        // set to 1
        x_[k_] = v - 1;   // value-1 to last position
        --j;
        ++x_[j];        // increment left position

        return  j;
    }

    ulong prev()
    // Return 1 + position of leftmost change, return 0 with last composition.
    {
        const ulong v = x_[k_];   // value at last position

        if ( nk1_==v )  return 0;  // current composition is first

        x_[k_] = 1;               // set last position to 1
        ulong j = k_ - 1;
        while ( 1==x_[j] )  --j;  // find next greater than one
        --x_[j];                  // decrement value
        x_[j+1] = 1 + v;          // set next position

        return  j;
    }

    bool OK()  const
    { return is_composition_nz(data(), k_, n_); }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }
};
// -------------------------

#endif  // !defined HAVE_COMPOSITION_EX_LEX_H__
