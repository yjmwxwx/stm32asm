#if !defined  HAVE_TREE_LEV_SEQ_H__
#define       HAVE_TREE_LEV_SEQ_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/tree-lev-seq-aux.h"

#include "comb/comb-print.h"

#include "comb/is-catalan-rgs.h"

#include "fxttypes.h"

// Cf. comb/id-tree-lev-seq.h for identity trees
// Cf. comb/balanced-tree-lev-seq.h for balanced trees
// Cf. comb/ordered-tree-lev-seq.h for ordered trees
// Cf. comb/ordered-tree-branching-seq.h for ordered trees (as branching sequences)


class tree_lev_seq
// Level sequences for unordered rooted trees.
// Cf. OEIS sequence A000081
{
private:
    ulong n_;   // number of non-root nodes
    ulong *a_;  // level sequence: height of nodes in pre-order traversal
private:
    tree_lev_seq_aux aux;

public:
    tree_lev_seq(ulong n)
    {
        n_ = n;
        a_ = new ulong[size()];
        first();
    }

    ~tree_lev_seq()
    { delete [] a_; }


    const ulong *data()  const  { return a_; }
    ulong size()  const  { return n_ + 1; }

    ulong lev(ulong k)  const { return ( k < size() ? a_[k] : 0 ); }


    void first()
    {
        a_[0] = 0;
        for (ulong j=1; j<size(); ++j)  a_[j] = j;
    }

    ulong next()
    // Return position of leftmost change.
    // Return zero if current sequence is last.
    {
        // Cf. Wilf, Combinatorial Algorithms, p.25
        // find rightmost index p such that a[p] not minimal:
        ulong p = size() - 1;
#if 1  // easy case optimization, significant speedup
        if ( a_[p] != 1 )  { --a_[p];  return p; }
        do { --p; }  while ( a_[p] == 1 );
#else
        while ( a_[p] == 1 )  --p;
#endif

        if ( p==0 )  return 0;  // current is last

        // find rightmost index q such that a[q] == a[p] - 1:
        const ulong ap1 = a_[p] - 1;

        ulong q = p - 1;
        while ( a_[q] != ap1 )  --q;
        // Here  q == base_idx(p)

        // Periodic copying:
        const ulong d = p - q;
        for (ulong j=p; j<size(); ++j)  a_[j] = a_[j-d];

        return p;
    }

    ulong branching_number(ulong j)  const
    // Out-degree of node[j].
    // Must have j < n.
    { return aux.branching_number(data(), size(), j); }

    ulong max_branching_number()  const
    // Max out-degree.
    { return aux.max_branching_number(data(), size()); }

    ulong min_branching_number()  const
    // Min out-degree of internal nodes.
    { return aux.min_branching_number(data(), size()); }

    ulong valency(ulong j)  const
    // return number of edges connected to node j
    { return aux.valency(a_, size(), j); }


    ulong num_leaves()  const
    { return aux.num_leaves(data(), size()); }


    bool is_branch(ulong j)  const
    // Return whether node j is a branch.
    { return  ( aux.branching_number(data(), size(), j) > 1 ); }

    bool is_leaf(ulong j)  const
    // Return whether node j is a leaf.
    { return  aux.is_leaf(data(), size(), j); }

    ulong limb_length(ulong j)  const
    // A limb is a path (towards the root) from a leaf to
    //   the nearest branching point.
    // The length is the number of edges in the path.
    // Return the length, or zero for non-leaves.
    { return  aux.limb_length(data(), size(), j); }

    ulong min_limb_length()  const
    { return  aux.min_limb_length(data(), size()); }

    ulong max_limb_length()  const
    { return  aux.max_limb_length(data(), size()); }

    ulong height()  const
    { return  aux.height(data(), size()); }

    bool is_identity_tree()  const
    // Return whether tree has no two identical sub-trees based on the same node.
    // Such trees are called identity trees, see OEIS sequence A004111.
    // Complexity is O(n^3).
    // Use class id_tree_lev_seq for generating these efficiently.
    { return  aux.is_identity_tree(data(), size()); }

    bool is_balanced()  const
    // Return whether tree is balanced, that is, all leafs are on the same height.
    // See OEIS sequence A048816.
    // Use class fixme:todo for generating these efficiently.
    { return  aux.is_balanced(data(), size()); }

    void print(const char *bla)  const
    { print_vec(bla, data(), size()); }

    void print_aa(const char *bla)  const
    { aux.print_aa(bla, data(), size()); }

    void print_branching_numbers(const char *bla, bool dfz=true)  const
    { aux.print_branching_numbers(bla, data(), size(), dfz); }

    void print_base_seq(const char *bla, bool dfz=true)  const
    { aux.print_base_seq(bla, data(), size(), dfz); }

    void print_paren_word(const char *bla, const char * s="()")  const
    { aux.print_paren_word(bla, data(), size(), s); }

    bool OK()  const  // test is incomplete
    { return is_catalan_rgs(data(), size()); }
};
// -------------------------

#endif // !defined HAVE_TREE_LEV_SEQ_H__
