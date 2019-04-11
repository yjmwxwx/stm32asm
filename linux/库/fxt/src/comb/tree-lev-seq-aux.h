#if !defined  HAVE_TREE_LEV_SEQ_AUX_H__
#define       HAVE_TREE_LEV_SEQ_AUX_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


class tree_lev_seq_aux
// Auxiliary class for classes *tree_lev_seq*
{
private:
    // no data

public:
    ulong height(const ulong *a, ulong n)  const
    {
        ulong h = 0;
        for (ulong j=1; j<n; ++j)
            if ( a[j] > h )  h = a[j];
        return h;
    }

    ulong is_leaf(const ulong *a, ulong n, ulong j)  const
    {
        if ( j==0 )  return  false;  // root node
        if ( j >= n - 1 )  return true;   // end node
        return  ( a[j] + 1 != a[j+1] );
    }

    ulong num_leaves(const ulong *a, ulong n)  const
    {
        if ( n <= 1 )  return n;  // root is not a leaf
        ulong r = 1;  // final node is leaf
        for (ulong j=1; j<n; ++j)
            r += ( a[j-1] + 1 != a[j] );
        return r;
    }


    ulong limb_length(const ulong *a, ulong n, ulong j)  const
    // A limb is a path (towards the root) from a leaf to
    //   the nearest branching point.
    // The length is the number of edges in the path.
    // Return the length, or zero for non-leaves.
    {
        if ( ! is_leaf(a, n, j) )  return 0;
        ulong i = j;
        ulong h = a[j];
        while ( --i != 0 )  // follow path until either a leaf or a branch is found
        {
            h -= 1;
            if ( a[i] != h )  break;
            if ( is_branch(a, n, i) )  break;
        }
        return  j - i;

    }

    ulong min_limb_length(const ulong *a, ulong n)  const
    {
        if ( n <= 1 )  return 0;
        ulong m = ~0UL;
        for (ulong j=1; j<n; ++j)
        {
            if ( is_leaf(a, n, j) )
            {
                ulong t = limb_length(a, n, j);
                if ( t < m )  m = t;
            }
        }
        return m;
    }

    ulong max_limb_length(const ulong *a, ulong n)  const
    {
        if ( n <= 1 )  return 0;
        ulong m = 0;
        for (ulong j=1; j<n; ++j)
        {
            if ( is_leaf(a, n, j) )
            {
                ulong t = limb_length(a, n, j);
                if ( t > m )  m = t;
            }
        }
        return m;
    }


    ulong branching_number(const ulong *a, ulong n, ulong j)  const
    // Out-degree of node[j].
    {
        if ( j >= n )  return 0;  // error

        const ulong t = a[j];  // height at position j
        ulong r = 0;  // out-degree: number of heights t+1 before next occurrence of t
        for (ulong k=j+1; k<n; ++k)
        {
            const ulong d = a[k];
            if ( d <= t )  break;  // back at level of node j
            r += ( d == t+1 );
        }
        return r;
    }


    ulong is_branch(const ulong *a, ulong n, ulong j)  const
    { return  ( branching_number(a, n, j) > 1 ); }

    ulong valency(const ulong *a, ulong n, ulong j)  const
    // return number of edges connected to node j
    { return branching_number(a, n, j) + (j!=0); }


    void all_branching_numbers(const ulong *a, ulong n, ulong *b, ulong *s)  const
    // Write out-degree of node[j] to b[j] for all j.
    // s[] is scratch space, s[j] holds the index where the value j was last seen.
    {
        for (ulong j=0; j<n; ++j)  b[j] = 0;
        s[0] = 0;
        for (ulong j=1; j<n; ++j)
        {
            b[ s[ a[j] - 1 ] ] += 1;
            s[ a[j] ] = j;
        }
    }

    ulong max_branching_number(const ulong *a, ulong n)  const
    // Max out-degree.
    {
        // note: use all_branching_numbers() to make cost linear
        ulong r = 0;
        for (ulong j=0; j<n; ++j)
        {
            const ulong b = branching_number(a, n, j);
            if ( b > r )  r = b;
        }
        return r;
    }

    ulong min_branching_number(const ulong *a, ulong n)  const
    // Min out-degree of internal nodes.
    {
        // note: use all_branching_numbers() to make cost linear
        if ( n <= 1 )  return 0;
        ulong r = n;
        for (ulong j=0; j<n; ++j)
        {
            const ulong b = branching_number(a, n, j);
            if ( b == 0 )  continue;  // ignore terminal nodes
            if ( b < r )  r = b;
        }
        return r;
    }

    bool is_balanced(const ulong *a, ulong n)  const
    {
        if ( n <= 2 )  return true;
        const ulong f = a[n-1];  // final height is a leaf
        for (ulong j=1; j+1 < n; ++j)
        {
            if ( a[j] < a[j+1] )  continue;  // not a leaf
            if ( a[j] != f )  return false;
        }
        return true;
    }

private:
    ulong base_idx(const ulong *a, ulong j)  const
    // Return index of base of subtree containing node j.
    {
        if ( j==0 )  return 0;
        ulong b = a[j] - 1;
        do  { --j; }  while ( a[j] != b );
        return j;
    }

    bool sub_tree_cmp(const ulong *a, ulong f, ulong k)  const
    // Return whether subtrees in
    //   [f, f+1, ..., f+s-1] and [k, k+1, ..., k+s-1]
    // where s := k - f  are identical (and have same base).
    {
        if ( base_idx(a, f) != base_idx(a, k) )  return false;
        const ulong s = k - f;
        for (ulong j=0; j<s; ++j)
        {
            if ( a[f] != a[k] )  return false;
            ++f;  ++k;
        }
        return true;
    }
public:
    bool is_identity_tree(const ulong *a, ulong n)  const
    // Return whether tree has no two identical
    //   sub-trees based on same node.
    // Such trees are called identity trees, cf. A004111.
    // Complexity is O(n^3).
    // Use class id_tree_lev_seq for generating these efficiently.
    {
        for (ulong j=1; j+1 < n; ++j)  // case s==1 (see below)
            if ( a[j] == a[j+1] )  return false;

        for (ulong s=2; s<=n/2; ++s)  // length-s runs
            for (ulong f=1, k=f+s;  k+s <= n;  ++f, ++k)
                if ( sub_tree_cmp(a, f, k) )  return false;

        return true;
    }


public:
    // printing:

    void print_aa(const char *bla, const ulong *a, ulong n)  const;

    void print_branching_numbers(const char *bla,
                                 const ulong *a, ulong n,
                                 bool dfz)  const;

    void print_base_seq(const char *bla,
                        const ulong *a, ulong n,
                        bool dfz=true)  const;

    void print_paren_word(const char *bla,
                          const ulong *a, ulong n,
                          const char * s="()")  const;

    // only for balanced trees:
    void print_balanced_composition(const char *bla,
                                    const ulong *a, ulong n)  const;


//    //: functions using branching sequence a[]:
//    void print_tree_branching_seq_levels(const char *bla,
//                                         const ulong *a, ulong n,
//                                         bool dfz=false)  const;
//
};
// -------------------------


#endif // !defined HAVE_TREE_LEV_SEQ_AUX_H__
