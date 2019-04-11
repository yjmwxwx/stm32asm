#if !defined HAVE_COMBINATION_LEX_H__
#define      HAVE_COMBINATION_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "comb/comb-print.h"


class combination_lex
// Combinations n choose k (lexicographic order)
{
public:
    ulong *x_;    // combination: k elements 0<=x[j]<k in increasing order
    ulong n_, k_;  // Combination (n choose k)

private:  // have pointer data
    combination_lex(const combination_lex&);  // forbidden
    combination_lex & operator = (const combination_lex&);  // forbidden

public:
    explicit combination_lex(ulong n, ulong k)
    {
        n_ = n;  k_ = k;
        x_ = new ulong[k_];
        first();
    }

    ~combination_lex()  { delete [] x_; }


    void first()
    {
        for (ulong k=0; k<k_; ++k)  x_[k] = k;
    }

    void last()
    {
        for (ulong i=0; i<k_; ++i)  x_[i] = n_ - k_ + i;
    }

    ulong next()
    // Return smallest position that changed, return k with last combination
    {
        if ( x_[0] == n_ - k_ )  // current combination is the last
        { first();  return k_; }

        ulong j = k_ - 1;
        // easy case:  highest element != highest possible value:
        if ( x_[j] < (n_-1) )  { ++x_[j];  return j; }

        // find highest falling edge:
        while ( 1 == (x_[j] - x_[j-1]) )  { --j; }

        // move lowest element of highest block up:
        ulong ret = j - 1;
        ulong z = ++x_[j-1];

        // ... and attach rest of block:
        while ( j < k_ )  { x_[j] = ++z;  ++j; }

        return  ret;
    }

    ulong prev()
    // Return smallest position that changed, return k with last combination
    {
        if ( x_[k_-1] == k_-1 )  // current combination is the first
        { last();  return k_; }

        // find highest falling edge:
        ulong j = k_ - 1;
        while ( 1 == (x_[j] - x_[j-1]) )  { --j; }

        ulong ret = j;
        --x_[j];  // move down edge element

        // ... and move rest of block to high end:
        while ( ++j < k_ )  x_[j] = n_ - k_ + j;

        return  ret;
    }

    const ulong * data()  const  { return x_; }

    void print_set(const char *bla=0)  const
    { ::print_set(bla, x_, k_); }

    void print_deltaset(const char *bla=0)  const
    { print_set_as_deltaset(bla, x_, k_, n_); }
};
// -------------------------



#endif  // !defined HAVE_COMBINATION_LEX_H__
