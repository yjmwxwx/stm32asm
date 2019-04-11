#if !defined HAVE_SHIFT_H__
#define      HAVE_SHIFT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template <typename Type>
inline void shift_right(Type *f, ulong n, ulong s)
// Shift elements s positions away from element zero.
{
    if ( s==0 )  return;
    if ( n==0 )  return;

    ulong k = n - 1;
    if ( n>s )  for (  ; k>=s; --k)  f[k] = f[k-s];
    do  { f[k]=0; }  while ( k-- );
}
// -------------------------


template <typename Type>
inline void shift_left(Type *f, ulong n, ulong s)
// Shift elements s positions towards element zero.
{
    if ( s==0 )  return;
    if ( n==0 )  return;

    ulong k = 0;
    if ( n>s )  for (  ; k<n-s; ++k)  f[k] = f[k+s];
    for (  ; k<n; ++k)    f[k] = 0;
}
// -------------------------



//template <typename Type>
//inline void shift_sgn(Type *f, ulong n, long s)
//// positive s --> shift away from element zero
//{
//    if ( s>0 )  shift_right(f,n, (ulong)s);
//    else        shift_left(f,n, (ulong)-s);
//}
//// -------------------------

template <typename Type>
inline void shift_right1(Type *f, ulong n)
// Shift elements 1 position away from element zero.
{
    if ( n==0 )  return;
    for (ulong k=n-1; k!=0; --k)  f[k] = f[k-1];
    f[0] = 0;
}
// -------------------------

template <typename Type>
inline void shift_left1(Type *f, ulong n)
// Shift elements 1 position towards element zero.
{
    if ( n==0 )  return;
    for (ulong k=0; k<n-1; ++k)  f[k] = f[k+1];
    f[n-1] = 0;
}
// -------------------------


#endif  // !defined HAVE_SHIFT_H__
