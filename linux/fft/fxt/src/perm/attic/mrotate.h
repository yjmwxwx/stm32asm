#if !defined HAVE_MROTATE_H__
#define      HAVE_MROTATE_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "restrict.h"


template <typename Type>
void mrotate(const Type * restrict f, ulong n, ulong r, Type * restrict g)
// for all i:  g[(i*r)%n] <- f[i]
// must have:  gcd(n,r)==1
//
// mrotate(f,n,1,g) =^= { acopy(f,g,n); }
// mrotate(f,n,n-1,g) =^= { acopy(f,g,n); reverse_0(g,n); }
{
    if ( r>=n )  r %= n;
//    if ( r==1 )  { acopy(f, n, g); return; }
//    if ( gcd(n,r)!=1 ) { panic(); }

    g[0] = f[0];
    for (ulong i=1, j=r;  i<n;  ++i)
    {
        g[j] = f[i];
        j += r;
        if ( j>=n )  j -= n;
    }
}
// -------------------------


template <typename Type>
void inverse_mrotate(const Type * restrict f, ulong n, ulong r, Type * restrict g)
// for all i:  g[i] <- f[(i*r)%n]
// must have:  gcd(n,r)==1
//
// inverse of mrotate(), i.e. the following is the identity on y[]:
// { acopy(y, x, n); mrotate(x, n, r, y); acopy(y, x, n); inverse_mrotate(x, n, r, y); }
{
    if ( r>=n )  r %= n;
//    if ( r==1 )  { acopy(f, n, g); return; }
//    if ( gcd(n,r)!=1 ) { panic(); }

    g[0] = f[0];
    for (ulong i=1, j=r;  i<n;  ++i)
    {
        g[i] = f[j];
        j += r;
        if ( j>=n )  j -= n;
    }
}
// -------------------------


template <typename Type>
ulong test_mrotate_eq(const Type *f, ulong n, ulong r, const Type *g)
// test whether:  for all i:  g[(i*r)%n] == f[i]
// Return zero if condition holds.
{
    if ( g[0] != f[0] )  return  n;
    if ( r>=n )  r %= n;
    for (ulong i=1, j=r;  i<n;  ++i)
    {
        if ( g[j] != f[i] )  return  n - i;
        j += r;
        if ( j>=n )  j -= n;
    }
}
// -------------------------


template <typename Type>
ulong test_inverse_mrotate_eq(const Type *f, ulong n, ulong r, const Type *g)
// test whether:  for all i:  g[i] == f[(i*r)%n]
// Return zero if condition holds.
{
    if ( g[0] != f[0] )  return  n;
    if ( r>=n )  r %= n;
    for (ulong i=1, j=r;  i<n;  ++i)
    {
        if ( g[i] != f[j] )  return  n - i;
        j += r;
        if ( j>=n )  j -= n;
    }
}
// -------------------------


#endif // !defined HAVE_MROTATE_H__
