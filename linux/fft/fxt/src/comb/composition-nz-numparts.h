#if !defined HAVE_COMPOSITION_NZ_NUMPARTS_H__
#define      HAVE_COMPOSITION_NZ_NUMPARTS_H__
// This file is part of the FXT library.
// Copyright (C) 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"
#include "fxttypes.h"


class composition_nz_numparts
// Compositions of n into nonzero parts.
// Ordering is firstly by number of parts  (1, 2, ..., n)
//   and secondly co-lexicographic (colex).
{
public:
    ulong n_, k_;  // composition of n into exactly k parts
    ulong *x_;     // data (k elements)
    ulong nk1_;    // ==n-k+1

private:  // have pointer data
    composition_nz_numparts(const composition_nz_numparts&);  // forbidden
    composition_nz_numparts & operator = (const composition_nz_numparts&);  // forbidden

public:
    explicit composition_nz_numparts(ulong n)
    {
        n_ = n;
        x_ = new ulong[n_ + 1];
        first();
    }

    ~composition_nz_numparts()  { delete [] x_; }

    const ulong * data()  const  { return x_; }
    ulong num_parts()  const  { return k_; }

private:
    void first_k(ulong k)
    // First composition into k parts.
    {
        k_ = k;
        nk1_ = n_ - k + 1;  // must be >= 1
        x_[0] = nk1_;  // all in first position
        for (ulong j=1; j<k_; ++j)  x_[j] = 1;
        x_[k_] = 0;  // not one
    }

    ulong next_k()
    // Next composition into k parts.
    // Return position of rightmost change, return k with last composition.
    {
        ulong j = 0;
        while ( 1==x_[j] )  ++j;  // find first greater than one

        if ( j >= k_ - 1 )  return k_;  // current composition is last

        ulong v = x_[j];  // value of first greater one
        x_[j] = 1;        // set to 1
        x_[0] = v - 1;    // value-1 to first position
        ++j;
        ++x_[j];          // increment next position

        return  j;
    }

public:
    void first()  { first_k(1); }

    ulong next()
    // Return number of parts (==k_).
    // Return n+1 if current composition is last.
    {
        ulong j = next_k();
        if ( j==k_ )  // last composition with k parts
        {
            if ( j==n_ )  return n_+1;  // current is last
            first_k(j+1);
        }

        return k_;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    bool OK()  const
    { return is_composition_nz(data(), num_parts(), n_); }
};
// -------------------------

#endif  // !defined HAVE_COMPOSITION_NZ_NUMPARTS_H__
