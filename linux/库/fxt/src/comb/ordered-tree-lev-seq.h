#if !defined  HAVE_ORDERED_TREE_LEV_SEQ_H__
#define       HAVE_ORDERED_TREE_LEV_SEQ_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/tree-lev-seq-aux.h"

#include "comb/is-catalan-rgs.h"

#include "comb/comb-print.h"


#include "fxttypes.h"


class ordered_tree_lev_seq
// Level sequences for ordered rooted trees.
// Essentially the same as Catalan restricted growth strings (RGS).
// strings a[0,1,...,n] where a[0]=0, a[k] >=1 for k>=1,
//   and  a[k] <= a[k-1] + 1.
// Lexicographic order.
// The number of length-n RGS is (OEIS sequence A000108)
//  1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, ...
{
private:
    ulong n_;   // number of non-root nodes
    ulong *a_;  // level sequence: height of nodes in pre-order traversal
private:
    tree_lev_seq_aux aux;

private:  // have pointer data
    ordered_tree_lev_seq(const ordered_tree_lev_seq&);  // forbidden
    ordered_tree_lev_seq & operator = (const ordered_tree_lev_seq&);  // forbidden


public:
    explicit ordered_tree_lev_seq(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+1];
        first();
    }

    ~ordered_tree_lev_seq()
    { delete [] a_; }


    const ulong *data()  const  { return a_; }
    ulong size()  const  { return n_+1; }

    ulong lev(ulong k)  const { return ( k < size() ? a_[k] : 0 ); }

    void first()
    {
        a_[0] = 0;
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
    }

    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong j = n_;
        while ( j != 0 )
        {
            if ( a_[j] <= a_[j-1] ) //  break;
            {
                ++a_[j];
                return j;
            }

            a_[j] = 1;
            --j;
        }

        return 0;  // current is last
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


    bool is_balanced()  const
    // Return whether tree is balanced, that is,
    // all leafs are on the same height.
    // See OEIS sequences A079500 and A007059.
    // Use class balanced_tree_lev_seq for generating these efficiently.
    { return  aux.is_balanced(data(), size()); }

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


    bool OK()  const
    { return is_catalan_rgs(data(), size()); }
};
// -------------------------


#endif  // !defined HAVE_ORDERED_TREE_LEV_SEQ_H__
