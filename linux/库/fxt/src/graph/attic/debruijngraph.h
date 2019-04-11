#if !defined  HAVE_DEBRUIJNGRAPH_H__
#define       HAVE_DEBRUIJNGRAPH_H__

#include "graph/printpath.h"  // print_path()
#include "bits/bit2pow.h"  // next_exp_of_2()
#include "fxttypes.h"


class debruijn_graph
// A special directed graph with ng=2*n nodes.
// Each node has two outgoing connections:
//  arc0 points to node (2*k) mod ng
//  arc1 points to node (2*k+1) mod ng
{
public:
    ulong ng_;         // number of Nodes of Graph
    ulong *a0_, *a1_;  // every node has two outgoing connections (Arcs)

public:
    debruijn_graph(ulong n)
        : ng_(2*n)
    {
        a0_ = new ulong[ng_];
        a1_ = new ulong[ng_];
        init();
    }

    ~debruijn_graph()
    {
        delete [] a1_;
        delete [] a0_;
    }

    void init()
    {
        for (ulong k=0; k<ng_; ++k)
        {
            ulong a = (2*k) % ng_;
            a0_[k] = a;  // connect node k to node (2*k) mod ng
            a = (a+1) % ng_;
            a1_[k] = a;  // connect node k to node (2*k+1) mod ng
        }
    }

    void print()  const;
};
// -------------------------


class debruijn_cycles
// Find all paths in a deBruijn graph.
// All paths are (Hamiltonian) cycles and
// for n a power of two correspond to deBruijn sequences.
{
public:
    debruijn_graph g_;  // the graph
    ulong *rv_;  // Record of Visits: rv[k] == node visited at step k
    ulong *qq_;  // qq[k] == whether node k has been visited yet

    ulong cct_;  // count Cycles
    ulong & ng_; // == size of graph

    // what to do when a cycle is found
    ulong ngbits_; // number of bits in ng_, useful for printing
    void (*cfunc_)(debruijn_cycles &);  // function to call with each cycle found
    bool cfdone_;  // if set (by cfunc()) then search is stopped

public:
    debruijn_cycles(ulong n)
        : g_(n), ng_(g_.ng_)
    {
        rv_ = new ulong[ng_];
        qq_ = new ulong[ng_];
        ngbits_ = next_exp_of_2(ng_);
        init();
        cfunc_ = 0;
    }

    ~debruijn_cycles()
    {
        delete [] qq_;
        delete [] rv_;
    }

    void init()
    {
        for (ulong k=0; k<ng_; ++k)  qq_[k] = 0;
        cfdone_ = false;
        cct_ = 0;
    }

    debruijn_graph & graph()  { return g_; }

    bool path_is_cycle()  const
    // Return whether the path is a cycle.
    // For ng even this is always the case.
    // For odd ng!=1 this is never the case.
    {
        ulong k0 = rv_[0]; // first node visited
        ulong k = rv_[ng_-1]; // last node visited
        ulong q0 = ( k0==g_.a0_[k] );
        ulong q1 = ( k0==g_.a1_[k] );
        return ( q0 || q1 );
    }

    void print_debruijn_seq() const;

    void print_path() const
    { ::print_path(rv_, ng_); }

    void print_bin_path() const
    { ::print_bin_path(rv_, ng_, ngbits_); }

    void print_bin_horiz_path()  const
    { ::print_bin_horiz_path(rv_, ng_, ngbits_); }

    void next_cycle(ulong ns, ulong p);

    ulong all_cycles()
    {
        init();
        next_cycle(0, 0);
        return cct_;
    }
};
// -------------------------

#endif  // !defined HAVE_DEBRUIJNGRAPH_H__
