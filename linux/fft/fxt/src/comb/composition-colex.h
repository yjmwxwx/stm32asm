#if !defined HAVE_COMPOSITION_COLEX_H__
#define      HAVE_COMPOSITION_COLEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/comb-print.h"
#include "fxttypes.h"


class composition_colex
// Compositions of n into (at most) k parts (k-compositions of n),
// co-lexicographic (colex) order
{
public:
    ulong n_, k_;  // composition of n into k parts
    ulong *x_;     // data (k elements)

private:  // have pointer data
    composition_colex(const composition_colex&);  // forbidden
    composition_colex & operator = (const composition_colex&);  // forbidden

public:
    explicit composition_colex(ulong n, ulong k)
    {
        n_ = n;  k_ = k;
        x_ = new ulong[k_];
        first();
    }

    ~composition_colex()
    {
        delete [] x_;
    }

    const ulong * data()  const  { return x_; }

    void first()
    {
        x_[0] = n_;  // all in first position
        for (ulong k=1; k<k_; ++k)  x_[k] = 0;
    }

    void last()
    {
        for (ulong k=0; k<k_; ++k)  x_[k] = 0;
        x_[k_-1] = n_;  // all in last position
    }

    ulong next()
    // Return position of rightmost change, return k with last composition.
    {
//        if ( n_==x_[k_-1] )  return false;  // current composition is last

        ulong j = 0;
        while ( 0==x_[j] )  ++j;  // find first nonzero

        if ( j==k_-1 )  return k_;  // current composition is last

        ulong v = x_[j];  // value of first nonzero
        x_[j] = 0;        // set to zero
        x_[0] = v - 1;    // value-1 to first position
        ++j;
        ++x_[j];          // increment next position

        return  j;
    }

    ulong prev()
    // Return position of rightmost change, return k with last composition.
    {
//        if ( n_==x_[0] )  return false;  // current composition is first

        const ulong v = x_[0];   // value at first position

        if ( n_==v )  return k_;  // current composition is first

        x_[0] = 0;          // set first position to zero
        ulong j = 1;
        while ( 0==x_[j] )  ++j;  // find next nonzero
        --x_[j];                  // decrement value
        x_[j-1] = 1 + v;          // set previous position

        return  j;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), k_, dfz); }
};
// -------------------------

#undef MAX_ARRAY_LEN

#endif  // !defined HAVE_COMPOSITION_COLEX_H__
