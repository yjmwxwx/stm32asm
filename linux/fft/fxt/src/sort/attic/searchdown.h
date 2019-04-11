#if !defined  HAVE_SEARCHDOWN_H__
#define       HAVE_SEARCHDOWN_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
inline ulong search_down(const Type *f, const Type v, ulong &i)
// Search v in f[], starting at i (so i must be < length).
// f[i] must be greater or equal v.
// f[] must be sorted in ascending order.
// Return index k if f[k]==v or ~0 if no such k is found.
// i is updated so that it can be used for a following
// search for an element u where u < v
{
    while ( (f[i]>v) && (i>0) )  --i;

    if ( f[i]==v )  return i;
    else            return ~0UL;
}
// -------------------------


template <typename Type>
inline ulong search_down(const Type *f, const Type v, ulong &i,
                         int (*cmp)(const Type &, const Type &))
// Search v in f[], starting at i (so i must be < length).
// f[i] must be greater or equal v.
// f[] must be sorted in ascending order.
// Return index k if f[k]==v or ~0 if no such k is found.
// i is updated so that it can be used for a following
// search for an element u where u < v
{
//    while ( (f[i]>v) && (i>0) )  --i;
    while ( (cmp(f[i],v)>0) && (i>0) )  --i;

//    if ( f[i]==v )  return i;
    if ( cmp(f[i],v)==0 )  return i;
    else                   return ~0UL;
}
// -------------------------



#endif  // !defined HAVE_SEARCHDOWN_H__
