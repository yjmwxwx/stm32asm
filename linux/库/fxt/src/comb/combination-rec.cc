// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/combination-rec.h"
#include "fxttypes.h"


//#define TAIL_RECURSION  // define to use tail recursion

#ifdef TAIL_RECURSION
#include "aux0/swap.h"
#endif


void
comb_rec::next_rec(ulong d)
{
    ulong r = k_ - d;  // number of elements remaining

    if ( 0==r )
    {
        ++ct_;  // count objects
        visit_(*this);
    }
    else
    {
        ++rct_;  // measure computational work

        ulong rv1 = rv_[d-1];  // left neighbor

#if 1  // faster:
        bool q;
        switch ( rq_ )
        {
        case 0:  q = 1;  break;          //  0 ==> lexicographic order
        case 1:  q = !(d&1);  break;     //  1 ==> Gray code
        case 2:  q = rv1&1;  break;      //  2 ==> complemented enup order
        case 3:  q = (d^rv1)&1;  break;  //  3 ==> complemented Eades-McKay sequence
        default: q = 1;
        }
#else
        bool q = 1;
        q ^= (d & rq_ & 1);
        q ^= (rv1 & (rq_>>1) & 1);
#endif

        q ^= nq_;  // reversed order if  nq == true

#ifndef TAIL_RECURSION

        if ( q )  // forward
        {
            for (ulong x=rv1+1; x<=n_-r; ++x)
            {
                rv_[d] = x;
                next_rec(d+1);
            }
        }
        else     // backward
        {
            // GCC 4.9.1 with -Wstrict-overflow=5 issues the warning
            // "assuming signed overflow does not occur when ..."
            // This is a false positive.
            for (ulong x=n_-r; (long)x>=(long)rv1+1; --x)
            {
                rv_[d] = x;
                next_rec(d+1);
            }
        }

#else  //  TAIL_RECURSION

        long x0=rv1+1, x1=n_-r, i=1;  // forward
        if ( !q )  // backward
        {
            swap2(x0, x1);
            i=-i;
        }
        x1 += i;
        for (long x=x0; (long)x!=x1; x+=i)
        {
            rv_[d] = x;
            next_rec(d+1);
        }

#endif  //  TAIL_RECURSION
    }
}
// -------------------------
