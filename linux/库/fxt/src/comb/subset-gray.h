#if !defined HAVE_SUBSET_GRAY_H__
#define      HAVE_SUBSET_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "comb/comb-print.h"

// If defined, an array is used instead of a pointer, this gives small speedup:
#define SUBSET_GRAY_MAX_ARRAY_LEN 64  // default on


class subset_gray
// Subsets of the set {1,2,...,n} in minimal-change (Gray code) order.
// Loopless algorithm following Jenkyns ("Loopless Gray Code Algorithms").
{
public:
#ifndef SUBSET_GRAY_MAX_ARRAY_LEN
    ulong *x_;  // data k-subset of {1,2,...,n} in x[1,...,k]
#else
    ulong x_[SUBSET_GRAY_MAX_ARRAY_LEN + 1];
#endif
    ulong n_;   // subsets of the n-set;  must have n>=1
    ulong k_;   // number of elements in subset

private:  // have pointer data
    subset_gray(const subset_gray&);  // forbidden
    subset_gray & operator = (const subset_gray&);  // forbidden

public:
    explicit subset_gray(ulong n)
    {
        n_ = n;
#ifndef SUBSET_GRAY_MAX_ARRAY_LEN
        x_ = new ulong[n_+1];
#endif
        x_[0] = 0;
        first();
    }

    ~subset_gray()
    {
#ifndef SUBSET_GRAY_MAX_ARRAY_LEN
        delete [] x_;
#endif
    }

    ulong first()  { k_ = 0;  return k_; }
    ulong last()  { x_[1] = 1;  k_ = 1;  return k_; }

    const ulong * data() const { return x_+1; }
    ulong num() const { return k_; }

private:
    ulong next_even()
    {
        if ( x_[k_]==n_ )  // remove n (from end):
        {
            --k_;
        }
        else  // append n:
        {
            ++k_;
            x_[k_] = n_;
        }
        return  k_;
    }

    ulong next_odd()
    {
        if ( x_[k_]-1==x_[k_-1] )  // remove x[k]-1 (from position k-1):
        {
            x_[k_-1] = x_[k_];
            --k_;
        }
        else  // insert x[k]-1 as second last element:
        {
            x_[k_+1] = x_[k_];
            --x_[k_];
            ++k_;
        }
        return  k_;
    }

public:
    ulong next()
    {
        if ( 0==(k_&1 ) ) return next_even();
        else              return next_odd();
    }

    ulong prev()
    {
        if ( 0==(k_&1 ) )  // k even
        {
            if ( 0==k_ )  return last();
            return next_odd();
        }
        else  return next_even();
    }

    void print_set(const char *bla=0)  const
    { ::print_set(bla, x_+1, k_); }

    void print_deltaset(const char *bla=0)  const
    { print_set1_as_deltaset(bla, x_+1, k_, n_); }
};
// -------------------------

//#undef SUBSET_GRAY_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_SUBSET_GRAY_H__

