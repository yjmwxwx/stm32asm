#if !defined  HAVE_DIGRAPH_PATHS_H__
#define       HAVE_DIGRAPH_PATHS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "graph/digraph.h"
#include "graph/print-path.h"
#include "fxttypes.h"  // ulong


class digraph_paths
// Find all full paths in a directed graph.
{
public:
    digraph &g_;  // the graph
    ulong *rv_;  // Record of Visits: rv[k] == node visited at step k
    ulong *qq_;  // qq[k] == whether node k has been visited yet

    ulong pct_;  // count Paths
    ulong cct_;  // count Cycles
    ulong pfct_;  // count Paths where pfunc() returns 1

    bool cq_;  // whether current path is a cycle

    bool pany_;    // whether to print anything (set automatically)
    ulong ng_;  // == g_.ng_
    ulong ngbits_;  // number of bits in ng_, used for printing

    // function to call with each path found with all_paths():
    ulong (*pfunc_)(const digraph_paths &);

    bool pfdone_;  // if set (by pfunc()) then search is stopped
    ulong maxnp_;  // stop after maxnp times that pfunc returned one (0==forever)

    // function to impose condition with all_cond_paths():
    bool (*cfunc_)(digraph_paths &, ulong ns);  // can set pfdone_

private:  // have pointer data
    digraph_paths(const digraph_paths&);  // forbidden
    digraph_paths & operator = (const digraph_paths&);  // forbidden

public:
    // graph/digraph.cc:
    explicit digraph_paths(digraph &g);
    ~digraph_paths();
    void init();

    const digraph & graph()  const  { return g_; }

    bool path_is_cycle()  const;

    void print_turns(bool shortq=true) const;
    ulong test_lucky_path()  const;

    bool mark(ulong p, ulong &ns);

    void print_path() const
    // Print sequence of nodes.
    { ::print_path(rv_, ng_); }

    void print_bin_path() const
    // Print sequence of nodes both binary and decimal.
    { ::print_bin_path(rv_, ng_, ngbits_); }

    void print_bin_horiz_path()  const
    // Horizontally print sequence of nodes in binary.
    { ::print_bin_horiz_path(rv_, ng_, ngbits_); }


    // graph/search-digraph.cc:
public:
    ulong all_paths(ulong (*pfunc)(const digraph_paths &),
                    ulong ns=0, ulong p=0, ulong maxnp=0);
private:
    void next_path(ulong ns, ulong p);  // called by all_paths()

    // graph/search-digraph-cond.cc:
public:
    ulong all_cond_paths(ulong (*pfunc)(const digraph_paths &),
                         bool (*cfunc)(digraph_paths &, ulong),
                         ulong ns=0, ulong p=0, ulong maxnp=0);
private:
    void next_cond_path(ulong ns, ulong p);  // called by all_cond_paths()

    // graph/search-digraph-trylucky.cc:
public:
    ulong try_lucky_path(ulong ns=0, ulong p=0);
private:
    void next_lucky(ulong ns, ulong p);  // called by try_lucky_path()
};
// -------------------------


#endif  // !defined HAVE_DIGRAPH_PATHS_H__
