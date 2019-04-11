// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "graph/digraph-paths.h"

#include "fxttypes.h"
#include "fxtio.h"


ulong
digraph_paths::try_lucky_path(ulong ns/*=0*/, ulong p/*=0*/)
{
    pct_ = 0;
    cct_ = 0;
    init();

 start:
    rv_[ns] = p;  // record position
    ++ns;
    // ns == how many nodes seen
    // p == position (node we are on)

    if ( ns==ng_ )  // all nodes seen ?
    {
        cq_ = path_is_cycle();
        if ( cq_ )  ++cct_;
        ++pct_;
        return  pct_;  // ==1
    }
    else
    {
        ulong fe, en;
        g_.get_edge_idx(p, fe, en);
        for (ulong ep=fe; ep<en; ++ep)
        {
            ulong t = g_.e_[ep];  // next node
            if ( 0==qq_[t] )  // first free node is taken as next
            {
                qq_[p] = 1;
                p = t;
                goto start;
            }
        }
        return 0;
    }

//    return 0;  // never reached
}
// -------------------------

