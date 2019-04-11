#if !defined  HAVE_COMBINATION_REC_H__
#define       HAVE_COMBINATION_REC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "comb/comb-print.h"


class comb_rec
// Combinations in lexicographic, Gray code,
// complemented enup, and complemented Eades-McKay order.
// Recursive algorithm.
{
public:
    ulong n_, k_;  // (n choose k)
    ulong *rv_;   //  combination: k elements 0<=x[j]<k in increasing order
    // == Record of Visits in graph
    ulong rq_;   // condition that determines the order:
    // 0 ==> lexicographic order
    // 1 ==> Gray code
    // 2 ==> complemented enup order
    // 3 ==> complemented Eades-McKay sequence
    ulong nq_;   // whether to reverse order
    ulong ct_;   // count combinations
    ulong rct_;  // count recursions (==work)
    void (*visit_)(const comb_rec &);  // function to call with each combination

private:  // have pointer data
    comb_rec(const comb_rec&);  // forbidden
    comb_rec & operator = (const comb_rec&);  // forbidden

public:
    explicit comb_rec(ulong n, ulong k)
    {
        n_ = n;
        k_ = k;
        rv_ = new ulong[k_+1];
        ++rv_;
        rv_[-1] = -1UL;
    }

    ~comb_rec()
    {
        --rv_;
        delete [] rv_;
    }

    void generate(void (*visit)(const comb_rec &), ulong rq, ulong nq=0)
    {
        visit_ = visit;
        rq_ = rq;
        nq_ = nq;
        ct_ = 0;
        rct_ = 0;
        next_rec(0);
    }

    void print_set(const char *bla=0)  const
    { ::print_set(bla, rv_, k_); }

    void print_deltaset(const char *bla=0)  const
    { print_set_as_deltaset(bla, rv_, k_, n_); }

private:
    void next_rec(ulong d);
};
// -------------------------


#endif  // !defined HAVE_COMBINATION_REC_H__
