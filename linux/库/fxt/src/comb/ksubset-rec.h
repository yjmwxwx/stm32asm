#if !defined  HAVE_KSUBSET_REC_H__
#define       HAVE_KSUBSET_REC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"  // swap2()
#include "fxttypes.h"

class ksubset_rec
// k-subsets where kmin<=k<=kmax in various orders.
// Recursive CAT algorithm.
{
public:
    ulong n_;    // subsets of a n-element set
    ulong kmin_, kmax_;  //  k-subsets where kmin<=k<=kma
    ulong *rv_;  // record of visits in graph (list of elements in subset)
    ulong ct_;   // count subsets
    ulong rct_;  // count recursions (==work)
    ulong rq_;   // condition that determines the order
    ulong pq_;   // condition that determines the (printing) order
    ulong nq_;   // whether to reverse order
    // function to call with each combination:
    void (*visit_)(const ksubset_rec &, ulong);

private:  // have pointer data
    ksubset_rec(const ksubset_rec&);  // forbidden
    ksubset_rec & operator = (const ksubset_rec&);  // forbidden

public:
    explicit ksubset_rec(ulong n)
    {
        n_ = n;
        rv_ = new ulong[n_+1];
        ++rv_;
        rv_[-1] = -1UL;
    }

    ~ksubset_rec()
    {
        --rv_;
        delete [] rv_;
    }

    void generate(void (*visit)(const ksubset_rec &, ulong),
                  ulong kmin, ulong kmax, ulong rq, ulong nq=0)
    {
        ct_ = 0;
        rct_ = 0;

        kmin_ = kmin;
        kmax_ = kmax;
        if ( kmin_ > kmax_ )  swap2(kmin_, kmax_);
        if ( kmax_ > n_ )  kmax_ = n_;
        if ( kmin_ > n_ )  kmin_ = n_;

        visit_ = visit;
        rq_ = rq % 4;
        pq_ = (rq>>2) % 4;
        nq_ = nq;
        next_rec(0);
    }

private:
    void next_rec(ulong d);
};
// -------------------------


#endif  // !defined HAVE_KSUBSET_REC_H__
