#if !defined  HAVE_BALANCED_ORDERED_TREE_LEV_SEQ_H__
#define       HAVE_BALANCED_ORDERED_TREE_LEV_SEQ_H__
// This file is part of the FXT library.
// Copyright (C) 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/tree-lev-seq-aux.h"

#include "comb/is-catalan-rgs.h"

#include "comb/comb-print.h"


#include "fxttypes.h"


// Cf. comb/composition-nz-first-max.h



class balanced_ordered_tree_lev_seq
// Level sequences for ordered balanced rooted trees.
// Lexicographic order.
// See OEIS sequences A079500 and A007059.
{
private:
    ulong n_;   // number of non-root nodes
    ulong *a_;  // level sequence: height of nodes in pre-order traversal
private:
    tree_lev_seq_aux aux;

private:  // have pointer data
    balanced_ordered_tree_lev_seq(const balanced_ordered_tree_lev_seq&);  // forbidden
    balanced_ordered_tree_lev_seq & operator = (const balanced_ordered_tree_lev_seq&);  // forbidden


public:
    explicit balanced_ordered_tree_lev_seq(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+1];
        first();
    }

    ~balanced_ordered_tree_lev_seq()
    { delete [] a_; }


    const ulong *data()  const  { return a_; }
    ulong size()  const  { return n_+1; }

    ulong lev(ulong k)  const { return ( k < size() ? a_[k] : 0 ); }

    void first()
    {
        a_[0] = 0;
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
    }

private:
    void write_tail(ulong j)
    {
        ulong h = a_[n_];  // height of tree
        ulong v = a_[j] + 1;

        while ( j < n_ )  // last element unchanged
        {
            a_[j] = v;
            v += 1;
            if ( v > h )
            {
                if ( n_ - j >= h )  v = 1;
                else                v = 1 + h - (n_ - j);
            }
            ++j;
        }
    }
public:
    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong h = a_[n_];  // height of tree
        if ( h == n_ )  return 0;  // current is last

        ulong j = n_;
        while ( --j > h )
        {
            if ( a_[j] < a_[j-1] )
            {
                write_tail(j);
                return j;
            }
        }

        // Need to increase height:
        h += 1;
        a_[n_] = h;
        write_tail(h);
        return h;
    }

public:
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
    { return  aux.height(data(), size()); }


    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), size(), dfz); }

    void print_aa(const char *bla)  const
    { aux.print_aa(bla, data(), size()); }

    void print_branching_numbers(const char *bla, bool dfz=true)  const
    { aux.print_branching_numbers(bla, data(), size(), dfz); }

    void print_paren_word(const char *bla, const char * s="()")  const
    { aux.print_paren_word(bla, data(), size(), s); }

    void print_composition(const char *bla)  const
    { aux.print_balanced_composition(bla, data(), size()); }

private:
    bool is_balanced()  const
    { return  aux.is_balanced(data(), size()); }

public:
    bool OK()  const
    {
        if ( ! is_catalan_rgs(data(), size()) )  return false;
        if ( ! is_balanced() )  return false;
        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_BALANCED_ORDERED_TREE_LEV_SEQ_H__
