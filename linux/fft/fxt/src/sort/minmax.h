#if !defined HAVE_MINMAX_H__
#define      HAVE_MINMAX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
inline Type min(const Type *f, ulong n)
// Return minimum of array.
{
    Type v = f[0];
    while ( n-- )  if ( f[n]<v )  v = f[n];
    return v;
}
// -------------------------


template <typename Type>
inline ulong min_idx(const Type *f, ulong n)
// Return index of minimum of array.
{
    ulong i = 0;
    Type v = f[i];
    while ( n-- )
    {
        if ( f[n]<v )
        {
            v = f[n];
            i = n;
        }
    }
    return  i;
}
// -------------------------


template <typename Type>
inline Type max(const Type *f, ulong n)
// Return maximum of array.
{
    Type v = f[0];
    while ( n-- )  if ( f[n]>v )  v = f[n];
    return v;
}
// -------------------------


template <typename Type>
inline ulong max_idx(const Type *f, ulong n)
// Return index of maximum of array.
{
    ulong i = 0;
    Type v = f[i];
    while ( n-- )
    {
        if ( f[n]>v )
        {
            v = f[n];
            i = n;
        }
    }
    return i;
}
// -------------------------


template <typename Type>
inline void min_max(const Type *f, ulong n, Type *mi, Type *ma)
// Set *mi to minimum of array
// and *ma to maximum of array.
{
    Type i = f[0];
    Type a = f[0];
    while ( n-- )
    {
        if ( f[n]<i )  i = f[n];
        if ( f[n]>a )  a = f[n];
    }
    *mi = i;
    *ma = a;
}
// -------------------------


//template <typename Type>
//inline void min_max_idx(const Type *f, ulong n, ulong *ii, ulong *ia)
//// Set *ii to index of minimum of array
//// and *ia to index of maximum of array.
//{
//    ulong idxi = 0, idxa =0;
//    Type mi, ma;
//    mi = ma = f[0];
//    while ( n-- )
//    {
//        if ( f[n]<mi )
//        {
//            mi = f[n];
//            idxi = n;
//        }
//
//        if ( f[n]>ma )
//        {
//            ma = f[n];
//            idxa = n;
//        }
//    }
//
//    *ii = idxi;
//    *ia = idxa;
//}
//// -------------------------
//
//
//template <typename Type>
//inline void update_min_max(const Type *f, ulong n, Type *mi, Type *ma)
//// Set *mi to minimum of array_min and *mi
//// and *ma to maximum of array_max and *ma.
//{
//    Type i, a;
//    min_max(f, n, &i, &a);
//    if ( *mi>i )  *mi = i;
//    if ( *ma<a )  *ma = a;
//}
//// -------------------------
//
//
//template <typename Type>
//ulong next_min5_idx(const Type *f, ulong n, ulong start=0)
//// Return index of first element (index >= start+2)
//// which is minimal wrt. its 2 left and 2 right neighbors.
//// If no such element is found, n is returned.
//{
//    if ( n<start+5 )  return n;
//
//    ulong i = start;
//    Type a, b=f[i], c=f[i+1], d=f[i+2], e=f[i+3];
//    for (  ; i+4<n; ++i)
//    {
//        a = b;
//        b = c;
//        c = d;
//        d = e;
//        e = f[i+4];
//
//        if ( c<a && c<b && c<d && c<e )  return i+2;
//    }
//
//    return  n;
//}
//// -------------------------
//
//
//template <typename Type>
//ulong next_max5_idx(const Type *f, ulong n, ulong start=0)
//// Return index of first element (index >= start+2)
//// which is maximal wrt. its 2 left and 2 right neighbors.
//// If no such element is found, n is returned.
//{
//    if ( n<start+5 )  return n;
//
//    ulong i = start;
//    Type a, b=f[i], c=f[i+1], d=f[i+2], e=f[i+3];
//    for (  ; i+4<n; ++i)
//    {
//        a = b;
//        b = c;
//        c = d;
//        d = e;
//        e = f[i+4];
//
//        if ( c>a && c>b && c>d && c>e )  return i+2;
//    }
//
//    return  n;
//}
//// -------------------------
//
//
//template <typename Type>
//ulong max_sumbox_idx(const Type *f, ulong n, ulong boxlen)
//// Find box of length boxlen for which sum of the elements is maximal.
//// Return index of first element of that box.
//{
//    if ( n<=boxlen )  return 0;
//
//    Type bv = 0;  // box value
//    for (ulong i=0; i<boxlen; ++i)  bv += f[i];  // value of box[0]
//    Type   mbv = bv;  // max box value
//    ulong  mbi = 0;   // max box index
//
//    for (ulong i=1; i<=n-boxlen; ++i)
//    {
//        bv = bv - f[i-1] + f[i+boxlen-1];  // value of box[i]
//        if ( bv>mbv )
//        {
//            mbv = bv;
//            mbi = i;
//        }
//    }
//
//    return mbi;
//}
//// -------------------------
//
//template <typename Type>
//ulong min_sumbox_idx(const Type *f, ulong n, ulong boxlen)
//// Find box of length boxlen for which sum of the elements is minimal.
//// Return index of first element of that box.
//{
//    if ( n<=boxlen )  return 0;
//
//    Type bv = 0;  // box value
//    for (ulong i=0; i<boxlen; ++i)  bv += f[i];  // value of box[0]
//    Type   mbv = bv;  // max box value
//    ulong  mbi = 0;   // max box index
//
//    for (ulong i=1; i<=n-boxlen; ++i)
//    {
//        bv = bv - f[i-1] + f[i+boxlen-1];  // value of box[i]
//        if ( bv<mbv )
//        {
//            mbv = bv;
//            mbi = i;
//        }
//    }
//
//    return mbi;
//}
//// -------------------------


#endif  // !defined HAVE_MINMAX_H__
