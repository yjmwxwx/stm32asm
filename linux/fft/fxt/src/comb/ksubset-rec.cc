// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/ksubset-rec.h"
//#include "fxtio.h"
//#include "fxttypes.h"

#include "sort/minmaxmed23.h"  // min2()


void
ksubset_rec::next_rec(ulong d)
{
    if ( d > kmax_ )  return;

    ++rct_;  // measure computational work
    ulong rv1 = rv_[d-1];  // left neighbor
    bool q = 1;
    switch ( rq_ % 4 )
    {
    case 0:  q = 1;  break;
    case 1:  q = ! (d & 1);  break;
    case 2:  q = rv1 & 1;  break;
    case 3:  q = (d ^ rv1) & 1;  break;
    }

    if ( nq_ )  q = !q;

    ulong x0 = rv1 + 1;
    ulong rx = n_ - (kmin_ - d);
    ulong x1 = min2( n_-1, rx );

#define PCOND(x) if ( (pq_==x) && (d>=kmin_) )  { visit_(*this, d);  ++ct_; }
    PCOND(0);
    if ( q )  // forward:
    {
        PCOND(1);
        for (ulong x=x0; x<=x1; ++x)  { rv_[d] = x;  next_rec(d+1); }
        PCOND(2);
    }
    else  // backward:
    {
        PCOND(2);
        for (ulong x=x1; x>=x0; --x)  { rv_[d] = x;  next_rec(d+1); }
        PCOND(1);
    }
    PCOND(3);
#undef PCOND
}
// -------------------------
