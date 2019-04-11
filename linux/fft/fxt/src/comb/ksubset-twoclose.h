#if !defined  HAVE_KSUBSET_TWOCLOSE_H__
#define       HAVE_KSUBSET_TWOCLOSE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "fxttypes.h"

// If defined, an array is used instead of a pointer, this gives a small speedup:
//#define KSUBSET_TWOCLOSE_MAX_ARRAY_LEN 64  // default off because limits max n

class ksubset_twoclose
// k-subsets (kmin<=k<=kmax) in a two-close order with homogeneous moves.
// Recursive algorithm.
{
public:
#ifndef KSUBSET_TWOCLOSE_MAX_ARRAY_LEN
    ulong *rv_;  // record of visits in graph (delta set)
#else
    ulong rv_[KSUBSET_TWOCLOSE_MAX_ARRAY_LEN];
#endif
    ulong n_;    // subsets of the n-element set

    // function to call with each combination:
    void (*visit_)(const ksubset_twoclose &);

private:  // have pointer data
    ksubset_twoclose(const ksubset_twoclose&);  // forbidden
    ksubset_twoclose & operator = (const ksubset_twoclose&);  // forbidden

public:
    explicit ksubset_twoclose(ulong n)
    {
        n_ = n;
#ifndef KSUBSET_TWOCLOSE_MAX_ARRAY_LEN
        rv_ = new ulong[n_];
#endif
    }


    ~ksubset_twoclose()
    {
#ifndef KSUBSET_TWOCLOSE_MAX_ARRAY_LEN
        delete [] rv_;
#endif
    }

    void generate(void (*visit)(const ksubset_twoclose &),
                  ulong kmin, ulong kmax)
    {
        visit_ = visit;
        ulong kmax0 = n_ - kmin;
        next_rec(n_, kmax, kmax0, 0);
    }

private:
    void next_rec(ulong d, ulong n1, ulong n0, bool q)
    // d:  remaining depth in recursion
    // n1: remaining ones to fill in
    // n0: remaining zeros to fill in
    // q:  direction in recursion
    {
        if ( 0==d )  { visit_(*this);  return; }

        --d;

        if ( q )
        {
            if ( n0 )  { rv_[d]=0;  next_rec(d, n1-0, n0-1, d&1); }
            if ( n1 )  { rv_[d]=1;  next_rec(d, n1-1, n0-0, q); }
        }
        else
        {
            if ( n1 )  { rv_[d]=1;  next_rec(d, n1-1, n0-0, q); }
            if ( n0 )  { rv_[d]=0;  next_rec(d, n1-0, n0-1, d&1); }
        }
    }
};
// -------------------------

//#undef KSUBSET_TWOCLOSE_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_KSUBSET_TWOCLOSE_H__
