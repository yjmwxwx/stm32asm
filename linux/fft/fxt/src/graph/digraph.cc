// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "graph/digraph.h"
#include "sort/sortfunc.h"
#include "sort/sortidxfunc.h"

#include "perm/reverse.h"
#include "perm/permq.h"
#include "perm/permrand.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "jjassert.h"


ulong
digraph::num_edges(ulong p)  const
// Return how many outgoing edges are at node p.
{
    return  ep_[p+1] - ep_[p];
}
// -------------------------


ulong
digraph::edge_idx(ulong p, ulong pn)  const
// Return the index of the edge that goes from p to pn.
// Return value t:
//   0<=t<num_edges(p)  if an edge from p to pn exists
//   ~0UL  else
{
    ulong fe = ep_[p];   // (index of) First Edge
    ulong nt = num_edges(p);
    const ulong *e = e_ + fe;
    for (ulong t=0; t<nt; ++t)  if ( pn==e[t] )  return t;
    return  ~0UL;  // pn cannot be reached from p
}
// -------------------------

ulong
digraph::max_edges()  const
// Return max number (among all nodes) of outgoing edges.
{
    ulong ma = 0;  // max number of outgoing edges
    for (ulong k=0; k<ng_; ++k)
    {
        ulong n = ep_[k+1] - ep_[k];
        if ( n > ma )  ma = n;
    }
    return  ma;
}
// -------------------------

static inline int cmp1(const ulong &a, const ulong &b)
{
    if ( a==b )  return 0;
    if ( a<b )  return +1;
    else        return -1;
}
// -------------------------

static inline int cmp0(const ulong &a, const ulong &b)
{
    return -cmp1(a, b);
}
// -------------------------

void
digraph::sort_edges(int rq/*=1*/)
{
    if ( rq )  sort_edges(cmp0);
    else       sort_edges(cmp1);
}
// -------------------------

void
digraph::sort_edges(int (*cmp)(const ulong &, const ulong &))
{
    if ( 0==vn_ )  // value == index (in e[])
    {
        for (ulong k=0; k<ng_; ++k)
        {
            ulong x = ep_[k];
            ulong n = ep_[k+1] - x;
            selection_sort(e_+x, n, cmp);
        }
    }
    else  // values in vn[]
    {
        for (ulong k=0; k<ng_; ++k)
        {
            ulong x = ep_[k];
            ulong n = ep_[k+1] - x;
            idx_selection_sort(vn_, n, e_+x, cmp);
//            jjassert( is_idx_sorted(vn_, n, e_+x, cmp) );
        }
    }
}
// -------------------------

ulong
digraph::test_edge_sorted(int (*cmp)(const ulong &, const ulong &))  const
// Test for each node whether sets of outgoing edges are sorted.
// If the test fails for a node, return its index,
//  else return ng.
{
    if ( 0==vn_ )  // value == index (in e[])
    {
        for (ulong k=0; k<ng_; ++k)
        {
            ulong x = ep_[k];
            ulong n = ep_[k+1] - x;
            if ( ! is_sorted(e_+x, n, cmp) )  return k;
        }
    }
    else  // values in vn[]
    {
        for (ulong k=0; k<ng_; ++k)
        {
            ulong x = ep_[k];
            ulong n = ep_[k+1] - x;
            if ( ! is_idx_sorted(vn_, n, e_+x, cmp) )  return k;
        }
    }
    return ng_;
}
// -------------------------

bool
digraph::is_edge_sorted(int (*cmp)(const ulong &, const ulong &))  const
{
    return  ( ng_==test_edge_sorted(cmp) );
}
// -------------------------

void
digraph::reverse_edge_order(ulong p0, ulong p1/*=0*/)
// Reverse order of edges at positions p0,...,p1.
// If p1==0 then action is performed just for position p0.
{
    ulong p = p0;
    do
    {
        ulong n = num_edges(p);
        if ( n>1 )  reverse(e_+ep_[p], n);
    }
    while ( ++p<=p1 );  // note: inclusive p1
}
// -------------------------


void
digraph::randomize_edge_order(ulong p0, ulong p1/*=0*/)
// Random permute order of edges at positions p0,...,p1.
// If p1==0 then action is performed just for position p0.
{
    ulong p = p0;
    do
    {
        ulong n = num_edges(p);
        if ( n>1 )  random_permute(e_+ep_[p], n);
    }
    while ( ++p<=p1 );  // note: inclusive p1
}
// -------------------------



void
digraph::print(const char *bla/*=0*/)  const
// Print directed graph.
{
    if ( bla )  cout << bla << endl;
    cout << "Node: Edge0 Edge1 ..." << endl;
    for (ulong k=0; k<ng_; ++k)
    {
        cout << setw(3) << k << ":  ";
        for (ulong j=ep_[k]; j<ep_[k+1]; ++j)
        {
            cout << setw(3) << e_[j] << " ";
        }
        cout << endl;
    }
    cout << "  #nodes=" << num_nodes();
    cout << "  #edges=" << num_edges();
    cout << endl;
}
// -------------------------


void
digraph::print_horiz(const char *bla/*=0*/)  const
// Print directed graph.
{
    if ( bla )  cout << bla << endl;
    cout << setw(7) << "Node:";
    for (ulong k=0; k<ng_; ++k)  cout << " " << setw(2) << k;
    cout << endl;
    ulong ma = max_edges();
    for (ulong j=0; j<ma; ++j)
    {
        cout << setw(1) << "Edge" << setw(2) << j << ":";
        for (ulong k=0; k<ng_; ++k)
        {
            if ( num_edges(k) > j )  cout << " " << setw(2) << e_[ep_[k]+j];
            else  cout << "   ";
        }
        cout << endl;
    }
}
// -------------------------


ulong
digraph::test()  const
{
    ulong ng = ng_;
    for (ulong k=0; k<ng; ++k)  if ( ep_[k] > ep_[k+1] )  return 1;

    ulong ne = num_edges();
    for (ulong k=0; k<ng; ++k)  if ( ep_[k] >= ne  )  return 2;

    if ( ep_[ng] != ne )   return 3;

    for (ulong k=0; k<ne; ++k)  if ( e_[k]>=ng_ )  return 10;

    return 0;
}
// -------------------------
