// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "graph/digraph-paths.h"
#include "graph/digraph.h"

#include "bits/bit2pow.h"

#include "fxttypes.h"
#include "fxtio.h"

//#include "jjassert.h"


digraph_paths::digraph_paths(digraph &g)
    : g_(g), ng_(g_.ng_)
{
    rv_ = new ulong[ng_];
    qq_ = new ulong[ng_];
    ngbits_ = next_exp_of_2(ng_);
    init();
    pfunc_ = 0;
}
// -------------------------

digraph_paths::~digraph_paths()
{
    delete [] qq_;
    delete [] rv_;
}
// -------------------------

void
digraph_paths::init()
{
    for (ulong k=0; k<ng_; ++k)  qq_[k] = 0;
    pct_ = 0;
    cct_ = 0;
    pfct_ = 0;
    maxnp_ = 0;
    pfdone_ = false;
}
// -------------------------


bool
digraph_paths::path_is_cycle()  const
// Return whether the path is a cycle.
{
    ulong p0 = rv_[0];  // first node visited
    ulong p = rv_[ng_-1];  // last node visited
    return graph().has_edge(p, p0);
//    ulong fe = g_.ep_[p];   // (index of) First Edge
//    ulong en = g_.ep_[p+1];  // (index of) first edge of Next node
//    const ulong *a = g_.e_;
//    for (ulong p=fe; p<en; ++p)  if ( p0==a[p] )  return true;
//    return  false;
}
// -------------------------

ulong
digraph_paths::test_lucky_path()  const
// Return 0 if path is a lucky path,
// else return 1+k where k is the index where
//  the edge used was not the first free edge.
{
    for (ulong k=0; k<ng_-1; ++k)
    {
        if ( qq_[rv_[k]] - 1 )  return  k+1;
    }
    return  0;
}
// -------------------------

bool
digraph_paths::mark(ulong p, ulong &ns)
{
    if ( p>=ng_ )  return false;
    if ( ns>=ng_ )  return false;
    if ( 0!=ns )
    {
        bool ha = graph().has_edge(rv_[ns-1], p);
        if ( false==ha )  return false;
    }
    rv_[ns] = p;
    qq_[p] = 1;
    ++ns;
    return true;
}
// -------------------------

void
digraph_paths::print_turns(bool shortq/*=true*/) const
{
    cout << "Path:";
    if ( shortq )  cout << " (short print) ";
    cout << endl;
    ulong nffct = 0;  // count non-first-free turns
    for (ulong k=0; k<ng_-1; ++k)
    {
        ulong pk = rv_[k];
        ulong ft = qq_[pk] - 1;
        nffct += (0!=ft);
        if ( !shortq || ft )
        {
            ulong nt = g_.num_edges(pk);
            ulong pn = rv_[k+1];
            ulong tt = g_.edge_idx(pk, pn);
            cout << setw(4) << k << ":";
            cout << " " << setw(4) << pk << " ->" << setw(4) << pn;
            cout << "  [" << setw(2) << ft;
            cout << " " << setw(2) << tt;
            cout << " / " << setw(2) << nt << "]";
            cout << endl;
//            jjassert( g_.has_edge(pk, pn) );
        }
    }
    cout << "Path: #non-first-free turns = " << nffct;
    if ( 0==nffct )  cout << "  (lucky path)";
    cout << endl;
}
// -------------------------

