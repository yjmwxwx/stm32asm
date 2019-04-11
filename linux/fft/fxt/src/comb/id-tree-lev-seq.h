#if !defined  HAVE_ID_TREE_LEV_SEQ_H__
#define       HAVE_ID_TREE_LEV_SEQ_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/tree-lev-seq-aux.h"

#include "comb/comb-print.h"

#include "comb/is-catalan-rgs.h"

#include "fxttypes.h"

//#include "jjassert.h"
//#include "fxtio.h"


class id_tree_lev_seq
// Level sequences for unordered rooted identity trees.
// Cf. OEIS sequence A004111.
{
private:
    ulong n_;   // number of non-root nodes
    ulong *a_;  // level sequence: height of nodes in pre-order traversal
private:
    tree_lev_seq_aux aux;

public:
    id_tree_lev_seq(ulong n)
    {
        n_ = n;
        a_ = new ulong[size()];
        first();
    }

    ~id_tree_lev_seq()
    { delete [] a_; }

    void first()
    {
        a_[0] = 0;
        for (ulong j=1; j<size(); ++j)  a_[j] = j;
    }

    const ulong *data()  const  { return a_; }
    ulong size()  const  { return n_ + 1; }

    ulong lev(ulong k)  const { return ( k < size() ? a_[k] : 0 ); }

private:
    ulong next_rec(ulong p)
    {
        if ( p <= 3 )  return 0;  // current is last

#if 0
        while ( a_[p] == 1 )  { --p; }
#else  // can happen at most twice:
        if ( a_[p] == 1 )  { --p; }
        if ( a_[p] == 1 )  { --p; }
#endif
        // here a[p] != 1
//        jjassert( a_[p] != 1 );

        const ulong ap1 = a_[p] - 1;

        // scan for a[p] - 1:
        ulong q = p;
        do  { --q; }  while ( a_[q] != ap1 );
        // here q != 0
//        jjassert( q!=0 );

        // Periodic copying:
        const ulong d = p - q;

        ulong e = d + p;  // copying range end at e-1
        const bool done = ( e > size() );  // done when period extends beyond end

        if ( done )  e = size();

        for (ulong j=p; j<e; ++j)  a_[j] = a_[j-d];

        // fixme: find a faster method
//        cout << " :: next_rec(" << p << ") :";
//        print("  ");
//        cout << endl;

        if ( done )  return p;

        return  next_rec( e - 1 );  // recursion
    }

public:
    ulong next()
    // Return position of leftmost change.
    // Return zero if current sequence is last.
    {
        ulong p = size() - 1;

        ulong z = a_[p] - 1;
        if ( z != 0 )  // easy case: only change rightmost value
        {
            if ( size() <= 3 )  return 0;
            z -= ( z == a_[p-1] );  // back up on [x-1, x]
            if ( z != 0 )
            {
                a_[p] = z;
                return p;
            }
        }

        return  next_rec(p - 1);
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

//    bool is_balanced()  const;  // only the first tree is balanced (for all n)


    bool is_branch(ulong j)  const
    // Return whether node j is a branch.
//    { return  ( aux.branching_number(data(), size(), j) > 1 ); }
    { return  aux.is_branch(data(), size(), j); }

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
    {
//        return  aux.height(data(), size());  // less efficient
        ulong h = size();
        do  { h -= 1; }  while ( a_[h] != h );  // last fixed point is height
        return h;
    }


    void print(const char *bla)  const
    { print_vec(bla, data(), size()); }

    void print_aa(const char *bla)  const
    { aux.print_aa(bla, data(), size()); }

    void print_branching_numbers(const char *bla, bool dfz=true)  const
    {
        // note: use tree_lev_seq_aux::all_branching_numbers() to make cost linear
        aux.print_branching_numbers(bla, data(), size(), dfz);
    }

    void print_base_seq(const char *bla, bool dfz=true)  const
    { aux.print_base_seq(bla, data(), size(), dfz); }

    void print_paren_word(const char *bla, const char * s="()")  const
    { aux.print_paren_word(bla, data(), size(), s); }


    bool OK()  const
    {
        if ( ! is_catalan_rgs(data(), size()) )  return false;
        if ( ! aux.is_identity_tree(data(), size()) )  return false;
        return true;
    }
};
// -------------------------

#endif // !defined HAVE_ID_TREE_LEV_SEQ_H__
