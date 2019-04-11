#if !defined  HAVE_DIGRAPH_H__
#define       HAVE_DIGRAPH_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


class digraph
// Directed graph with ng nodes.
// Initialization just allocates memory,
//  filling in the edges is left to the user.
{
public:
    ulong ng_;   // number of Nodes of Graph
    ulong *ep_;  // e[ep[k]], ..., e[ep[k+1]-1]: outgoing connections of node k
    ulong *e_;   // outgoing connections (Edges)
    ulong *vn_;  // optional: sorted values for nodes
    // if vn is used, then node k must correspond to vn[k]

private:  // have pointer data
    digraph(const digraph&);  // forbidden
    digraph & operator = (const digraph&);  // forbidden

public:
    explicit digraph(ulong ng, ulong ne, ulong *&ep, ulong *&e, bool vnq=false)
        : ng_(0), ep_(0), e_(0), vn_(0)
    {
        ng_ = ng;
        ep_ = new ulong[ng_+1];
        e_ = new ulong[ne];
        ep = ep_;
        e = e_;
        if ( vnq )  vn_ = new ulong[ng_];
    }

    ~digraph()
    {
        delete [] ep_;
        delete [] e_;
        if ( vn_ )  delete [] vn_;
    }


    ulong num_nodes()  const  { return ng_; }
    ulong num_edges()  const  { return ep_[num_nodes()]; }

    ulong num_edges(ulong p)  const;
    void get_edge_idx(ulong p, ulong &fe, ulong &en)  const
    // Setup fe and en so that the nodes reachable from p are
    //   e[fe], e[fe+1], ..., e[en-1].
    // Must have:  0<=p<ng
    {
        fe = ep_[p];   // (index of) First Edge
        en = ep_[p+1];  // (index of) first Edge of Next node
    }

    ulong edge_idx(ulong p, ulong pn)  const;

    bool  has_edge(ulong p, ulong pn)  const  // Return whether edge from p to pn exists
    { return (edge_idx(p, pn) < num_edges(p)); }

    ulong max_edges()  const;

    void  sort_edges(int rq=1);
    void  sort_edges(int (*cmp)(const ulong &, const ulong &));
    ulong test_edge_sorted(int (*cmp)(const ulong &, const ulong &))  const;
    bool is_edge_sorted(int (*cmp)(const ulong &, const ulong &))  const;

    void reverse_edge_order(ulong p0, ulong p1=0);
    void reverse_edge_order()  { reverse_edge_order(0, ng_-1); }

    void randomize_edge_order(ulong p0, ulong p1=0);
    void randomize_edge_order()  { randomize_edge_order(0, ng_-1); }


    void print(const char *bla=0)  const;
    void print_horiz(const char *bla=0)  const;

    ulong test()  const;
    bool OK()  const  { return (0==test()); }
};
// -------------------------



#endif  // !defined HAVE_DIGRAPH_H__
