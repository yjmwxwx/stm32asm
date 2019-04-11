#if !defined  HAVE_TREE_LEV_SEQ_BRANCHING_NUM_H__
#define       HAVE_TREE_LEV_SEQ_BRANCHING_NUM_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


inline ulong tree_lev_seq_branching_number(const ulong *a, ulong n, ulong j)
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
// -------------------------


inline void tree_lev_seq_branching_numbers(const ulong *a, ulong n, ulong *b, ulong *s)
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
// -------------------------


inline ulong tree_lev_seq_max_branching_number(const ulong *a, ulong n)
// Max out-degree.
{
    // note: use tree_lev_seq_branching_numbers() to make cost linear
    ulong r = 0;
    for (ulong j=0; j<n; ++j)
    {
        const ulong b = tree_lev_seq_branching_number(a, n, j);
        if ( b > r )  r = b;
    }
    return r;
}
// -------------------------


inline ulong tree_lev_seq_min_branching_number(const ulong *a, ulong n)
// Min out-degree of internal nodes.
{
    // note: use tree_lev_seq_branching_numbers() to make cost linear
    if ( n <= 1 )  return 0;
    ulong r = n;
    for (ulong j=0; j<n; ++j)
    {
        const ulong b = tree_lev_seq_branching_number(a, n, j);
        if ( b == 0 )  continue;  // ignore terminal nodes
        if ( b < r )  r = b;
    }
    return r;
}
// -------------------------


#endif // !defined HAVE_TREE_LEV_SEQ_BRANCHING_NUM_H__
