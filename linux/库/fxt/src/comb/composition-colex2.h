#if !defined HAVE_COMPOSITION_COLEX2_H__
#define      HAVE_COMPOSITION_COLEX2_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/comb-print.h"
#include "fxttypes.h"

// If defined, an array is used instead of a pointer, this gives no speedup:
//#define COMP_COLEX2_MAX_ARRAY_LEN  128  // default off, because limits max k


class composition_colex2
// Compositions of n into (at most) k parts (k-compositions of n),
// co-lexicographic (colex) order.
// Implementation efficient also with sparse case, i.e. k much greater than n.
// Loopless algorithm.
{
public:
    ulong n_, k_;  // composition of n into k parts
    ulong p0_;     // position of the first nonzero element
#ifndef COMP_COLEX2_MAX_ARRAY_LEN
    ulong *x_;     // data (k elements)
#else
    ulong x_[COMP_COLEX2_MAX_ARRAY_LEN];
#endif

private:  // have pointer data
    composition_colex2(const composition_colex2&);  // forbidden
    composition_colex2 & operator = (const composition_colex2&);  // forbidden

public:
    explicit composition_colex2(ulong n, ulong k)
    {
        n_ = n;  k_ = k;
#ifndef COMP_COLEX2_MAX_ARRAY_LEN
        x_ = new ulong[k_];
#endif
        first();
    }

    ~composition_colex2()
    {
#ifndef COMP_COLEX2_MAX_ARRAY_LEN
        delete [] x_;
#endif
    }

    const ulong * data()  const  { return x_; }

    void first()
    {
        x_[0] = n_;  // all in first position
        for (ulong k=1; k<k_; ++k)  x_[k] = 0;
        p0_ = 0;
    }

    ulong next()
    // Return position of rightmost change, return k with last composition.
    // Loopless algorithm.
    {
        ulong j = p0_;  // position of first nonzero

        if ( j==k_-1 )  return k_;  // current composition is last

        ulong v = x_[j];  // value of first nonzero
        x_[j] = 0;        // set to zero
        --v;
        x_[0] = v;        // value-1 to first position

        ++p0_;            // first nonzero one more right except ...
        if ( 0!=v )  p0_ = 0;   // ... if value v was not one

        ++j;
        ++x_[j];          // increment next position

        return  j;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), k_, dfz); }
};
// -------------------------

//#undef COMP_COLEX2_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_COMPOSITION_COLEX2_H__
