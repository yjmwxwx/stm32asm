#if !defined  HAVE_IS_SORTS_IN_RUNS_SORTED_H__
#define       HAVE_IS_SORTS_IN_RUNS_SORTED_H__
// This file is part of the FXT library.
// Copyright (C) 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


inline bool is_sorts_in_runs_sorted_asc(const ulong *A, const ulong *S, ulong m)
// For compositions and partitions with parts A[] of sorts S[],
// return whether for all runs of equal parts
// the sorts of parts are sorted (ascending order).
{
    if ( m <= 1 )  return true;  // nothing to do

    ulong j = 0, aj = A[j], sj=S[j];
    while ( j < m )
    {
        if ( A[j] == aj )
        {
            if ( S[j] < sj )  return false;
        }
        else
        {
            aj = A[j];
        }
        sj = S[j];
        ++j;
    }
    return true;
}
// -------------------------


inline bool is_sorts_in_runs_sorted_desc(const ulong *A, const ulong *S, ulong m)
// For compositions and partitions with parts A[] of sorts S[],
// return whether for all runs of equal parts
// the sorts of parts are sorted (descending order).
{
    if ( m <= 1 )  return true;  // nothing to do

    ulong j = 0, aj = A[j], sj=S[j];
    while ( j < m )
    {
        if ( A[j] == aj )
        {
            if ( S[j] > sj )  return false;
        }
        else
        {
            aj = A[j];
        }
        sj = S[j];
        ++j;
    }
    return true;
}
// -------------------------


#endif // !defined HAVE_IS_SORTS_IN_RUNS_SORTED_H__
