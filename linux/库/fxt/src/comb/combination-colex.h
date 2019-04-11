#if !defined HAVE_COMBINATION_COLEX_H__
#define      HAVE_COMBINATION_COLEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "comb/comb-print.h"


class combination_colex
// Combinations n choose k (co-lexicographic order)
{
public:
    ulong *x_;    // combination: k elements 0<=x[j]<k in increasing order
    ulong n_, k_;  // Combination (n choose k)

private:  // have pointer data
    combination_colex(const combination_colex&);  // forbidden
    combination_colex & operator = (const combination_colex&);  // forbidden

public:
    explicit combination_colex(ulong n, ulong k)
    {
        n_ = n;  k_ = k;
        x_ = new ulong[k_+1];
        x_[k_] = n_ + 2;  // sentinel
        first();
    }

    ~combination_colex()  { delete [] x_; }


    void first()
    {
        for (ulong i=0; i<k_; ++i)  x_[i] = i;
    }

    void last()
    {
        for (ulong i=0; i<k_; ++i)  x_[i] = n_ - k_ + i;
    }

    ulong next()
    // Return greatest position that changed, return k with last combination
    {
        if ( x_[0] == n_ - k_ )  // current combination is the last
        { first();  return k_; }

        ulong j = 0;
        // until lowest rising edge:  attach block at low end
        while ( 1 == (x_[j+1] - x_[j]) )  { x_[j] = j;  ++j; }  // can read sentinel

        ++x_[j];  // move edge element up

        return  j;
    }

    ulong prev()
    // Return greatest position that changed, return k with last combination
    {
        if ( x_[k_-1] == k_-1 )  // current combination is the first
        { last();  return k_; }

        // find lowest falling edge:
        ulong j = 0;
        while ( j == x_[j] )  ++j;  // can read sentinel

        --x_[j];  // move edge element down
        ulong ret = j;

        // attach rest of low block:
        while ( 0!=j-- )  x_[j] = x_[j+1] - 1;

        return  ret;
    }

    const ulong * data()  const  { return x_; }

    void print_set(const char *bla=0)  const
    { ::print_set(bla, x_, k_); }

    void print_deltaset(const char *bla=0)  const
    { print_set_as_deltaset(bla, x_, k_, n_); }
};
// -------------------------


#endif  // !defined HAVE_COMBINATION_COLEX_H__
