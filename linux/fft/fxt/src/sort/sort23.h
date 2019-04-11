#if !defined  HAVE_SORT23_H__
#define       HAVE_SORT23_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "fxttypes.h"


//: Sorting 2 or 3 elements

template <typename Type>
static inline void sort2(Type &x1, Type &x2)
// sort x1, x2
{ if ( x1>x2 )  swap2(x1, x2); }

template <typename Type>
static inline void sort3(Type &x0, Type &x1, Type &x2)
// sort x0, x1, x2
//{ sort2(x0, x1); sort2(x1, x2); sort2(x0, x1); }
{ sort2(x0, x1);  if ( x1>x2 ) {swap2(x1, x2); sort2(x0, x1);} }


//template <typename Type>
//static inline void idx_sort2(const Type *f, ulong *x)
//// sort index x[] so that f[x[0]]<=f[x[1]]
//{ if ( f[x[0]]>f[x[1]] )  swap2(x[0], x[1]); }
//
//template <typename Type>
//static inline void idx_sort2(Type f0, Type f1, ulong &x0, ulong &x1)
//// sort x0, x1 according to order of f0, f1
//{ if ( f0>f1 )  swap2(x0, x1); }
//
//template <typename Type>
//static inline void idx_sort3(const Type *f, ulong *x)
//// sort index x[] so that f[x[0]]<=f[x[1]]<=f[x[2]]
//{ sort2_idx(f, x); sort2_idx(f+1, x+1); sort2_idx(f, x); }
//
//template <typename Type>
//static inline void idx_sort3(Type f0, Type f1, Type f2,
//                             ulong &x0, ulong &x1, ulong &x2)
//// sort x0, x1, x2 according to order of f0, f1, f2
//{
//    if ( f0>f1 )  { swap2(x0, x1); swap2(f0, f1); }
//    if ( f1>f2 )  { swap2(x1, x2); swap2(f1, f2); }
//    if ( f0>f1 )  { swap2(x0, x1); }
//}
//
//template <typename Type>
//static inline void ptr_sort2(const Type *dummy, Type *x)
//// sort x[] so that f[x[0]]<=f[x[1]]
//{ if ( *x[0]>*x[1] )  swap2(x[0], x[1]); }
//
//template <typename Type>
//static inline void ptr_sort2(const Type *dummy, Type *&x0, ulong *&x1)
//// sort x0, x1 according to order of f0, f1
//{ if ( *x0>*x1 )  swap2(x0, x1); }


#endif  // !defined HAVE_SORT23_H__
