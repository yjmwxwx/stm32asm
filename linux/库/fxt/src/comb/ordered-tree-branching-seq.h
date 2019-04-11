#if !defined  HAVE_ORDERED_TREE_BRANCHING_SEQ_H__
#define       HAVE_ORDERED_TREE_BRANCHING_SEQ_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/comb-print.h"

#include "fxttypes.h"


// whether to use arrays instead of pointers:
//#define ORDERED_TREE_BRANCHING_SEQ_FIXARRAYS  // default is off
// small speedup with GCC 4.9.1


class ordered_tree_branching_seq
// Branching sequences for ordered rooted trees:
//   words [b(0), b(1), ..., b(n)] with b(n)=0, sum(j=0..n, b(j)) = n,
//   and sum(j=0..k, b(j)-1 ) >= 0 for k<n-1
//   (and necessarily sum(j=0..n-1, b(j)-1 ) = 0).
// Lexicographic order.
// The number of length-n RGS is (OEIS sequence A000108)
//   1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, ...
{
public:
#ifndef ORDERED_TREE_BRANCHING_SEQ_FIXARRAYS
    ulong *b_;  // branching sequence
#else
    ulong b_[60];  // > 10^33 trees
#endif
    ulong n_;  // number of non-root nodes
    ulong e_;  // index last nonzero value; set to 0 for n==0

private:  // have pointer data
    ordered_tree_branching_seq(const ordered_tree_branching_seq&);  // forbidden
    ordered_tree_branching_seq & operator = (const ordered_tree_branching_seq&);  // forbidden


public:
    explicit ordered_tree_branching_seq(ulong n)
    {
        n_ = n;
#ifndef ORDERED_TREE_BRANCHING_SEQ_FIXARRAYS
        b_ = new ulong[size()];
#endif
        first();
    }

    ~ordered_tree_branching_seq()
    {
#ifndef ORDERED_TREE_BRANCHING_SEQ_FIXARRAYS
        delete [] b_;
#endif
    }

    const ulong *data()  const  { return b_; }
    ulong size()  const  { return n_+1; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  b_[k] = 1;
        b_[n_] = 0;
        e_ = ( n_!=0 ? n_ - 1 : 0 );
    }

    ulong next()
    // Return  1 + position last nonzero value,
    // return zero when current is last.
    {
        ulong t = b_[e_] - 1;
        if ( e_ == 0 )  return 0;  // current is last

        // One unit moves to the left, rest are spread out
        //   as t - 1 ones at positions ending at n-1.
        b_[e_] = 0;
        b_[e_-1] += 1;
        if ( t==0 )  // easy case
        {
            --e_;
            return  e_ + 1;
        }
        else
        {
            ulong j = n_;
            do  { b_[--j] = 1; }  while ( --t );
            e_ = n_ - 1;
            return  e_ + 1;
        }
    }


    ulong branching_number(ulong j)  const
    // Out-degree of node[j].
    // Must have j <= n.
    { return b_[j]; }

    ulong max_branching_number()  const
    // Max out-degree.
    {
        ulong m = 0;
        for (ulong j=0; j<n_; ++j)
            if ( b_[j] > m )  m = b_[j];
        return m;
    }

    ulong min_branching_number()  const
    // Min out-degree of internal nodes.
    {
        ulong m = n_;
        for (ulong j=1; j<n_; ++j)
        {
            ulong d = b_[j];
            if ( d == 0 )  continue;  // skip leaves
            if ( d < m )  m = b_[j];
        }
        return m;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), size(), dfz); }

    void print_level_seq(const char *bla, bool dfz=false)  const;

    bool OK()  const
    {
        if ( b_[n_] != 0 )  return false;  // last is leaf

        ulong s = 0;  // sum must be == n:
        for (ulong j=0; j<n_; ++j)  s += b_[j];
        if ( s != n_ )  return false;

        ulong b = 0;  // branches left
        for (ulong j=0; j<n_; ++j)
        {
            ulong t = b_[j];
            b += t - 1;  // t new branches, minus one for present node
            if ( (long)b < 0 )  return false;
        }
        if ( b != 0 )  return false;

        return true;
    }
};
// -------------------------


#endif // !defined HAVE_ORDERED_TREE_BRANCHING_SEQ_H__
