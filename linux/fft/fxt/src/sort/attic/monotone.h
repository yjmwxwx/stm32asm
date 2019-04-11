#if !defined HAVE_MONOTONE_H__
#define      HAVE_MONOTONE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template  <typename Type>
int is_monotone(const Type *f, ulong n)
// Return
//   +1 for ascending order
//   -1 for descending order
//   else 0
// Note: a constant sequence is also monotone
{
    if ( 1>=n )  return  +1;

    ulong k;
    for (k=1; k<n; ++k)  // skip constant start
    {
        if ( f[k] != f[k-1] )  break;
    }

    if ( k==n )  return +1;  // constant is considered ascending here

    int s = ( f[k] > f[k-1] ? +1 : -1 );

    if ( s>0 )  // was: ascending
    {
        // scan for descending pair:
        for (  ; k<n; ++k)  if ( f[k] < f[k-1] )  return 0;
    }
    else  // was: descending
    {
        // scan for ascending pair:
        for (  ; k<n; ++k)  if ( f[k] > f[k-1] )  return 0;
    }

    return  s;
}
// -------------------------


template  <typename Type>
int is_strictly_monotone(const Type *f, ulong n)
// Return
//   +1 for strictly ascending order
//   -1 for strictly descending order
//   else 0
{
    if ( 1>=n )  return  +1;

    ulong k = 1;
    if ( f[k] == f[k-1] )  return 0;

    int s = ( f[k] > f[k-1] ? +1 : -1 );

    if ( s>0 )  // was: ascending
    {
        // scan for descending pair:
        for (  ; k<n; ++k)  if ( f[k] <= f[k-1] )  return 0;
    }
    else  // was: descending
    {
        // scan for ascending pair:
        for (  ; k<n; ++k)  if ( f[k] >= f[k-1] )  return 0;
    }

    return  s;
}
// -------------------------


#endif  // !defined HAVE_MONOTONE_H__
