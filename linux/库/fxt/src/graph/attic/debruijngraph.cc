
#include "graph/debruijngraph.h"

#include "bits/printbin.h"

#include "fxttypes.h"

#include "fxtio.h"
//#include "jjassert.h"


void
debruijn_graph::print()  const
// Print deBruijn graph.
// Example: the graph for n=8 (ng=16) is:
//  Node: 0  1  2  3  4  5  6  7  8  9
//  Arc0: 0  2  4  6  8  0  2  4  6  8
//  Arc1: 1  3  5  7  9  1  3  5  7  9
{
    const ulong w = 6;
    cout << setw(w) << "Node:";
    for (ulong k=0; k<ng_; ++k)  cout << setw(2) << k << " ";
    cout << endl;
    cout << setw(w) << "Arc0:";
    for (ulong k=0; k<ng_; ++k)  cout << setw(2) << a0_[k] << " ";
    cout << endl;
    cout << setw(w) << "Arc1:";
    for (ulong k=0; k<ng_; ++k)  cout << setw(2) << a1_[k] << " ";
    cout << endl;
    cout << endl;
}
// -------------------------

void
debruijn_cycles::next_cycle(ulong ns, ulong p)
// ns+1 == how many nodes seen
// p == position (node we are on)
{
    if ( cfdone_ )  return;

    rv_[ns] = p;  // record position
    ++ns;
    if ( ns==ng_ )  // all nodes seen ?
    {
        ++cct_;
        if ( cfunc_ )  cfunc_(*this);
    }
    else
    {
        qq_[p] = 1; // mark position as seen
        ulong t;  // next node

        t = g_.a0_[p];  if ( 0==qq_[t] )  { next_cycle(ns, t); }
        t = g_.a1_[p];  if ( 0==qq_[t] )  { next_cycle(ns, t); }

        qq_[p] = 0; // unmark position
    }
}
// -------------------------

void
debruijn_cycles::print_debruijn_seq()  const
// Print sequence of node labels modulo two.
// Example: the first sequence for n=8 (ng=16)
// is (dot for zero):  .1..11.1.1111...
{
    for (ulong k=0; k<ng_; ++k)  cout << (rv_[k]&1UL ? '1' : '.');
    cout << endl;
}
// -------------------------
