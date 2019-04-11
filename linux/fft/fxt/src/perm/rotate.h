#if !defined HAVE_ROTATE_H__
#define      HAVE_ROTATE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "perm/reverse.h"


template <typename Type>
void rotate_left(Type *f, ulong n, ulong s)
// Rotate towards element #0
// Shift is taken modulo n
{
    if ( n<=1 )  return;  // nothing to do
    if ( s>=n )  s %= n;
    if ( s==0 )  return;  // nothing to do

    reverse(f,   s);
    reverse(f+s, n-s);
    reverse(f,   n);
}
// -------------------------


template <typename Type>
void rotate_right(Type *f, ulong n, ulong s)
// Rotate away from element #0
// Shift is taken modulo n
{
    if ( n<=1 )  return;  // nothing to do
    if ( s>=n )  s %= n;
    if ( s==0 )  return;  // nothing to do

    reverse(f,     n-s);
    reverse(f+n-s, s);
    reverse(f,     n);
}
// -------------------------

template <typename Type>
void rotate_left1(Type *f, ulong n)
// Rotate towards element #0, by one position.
// =^= rotate_left(f, n, 1);
{
    if ( n<=1 )  return;  // nothing to do
    ulong f0 = f[0];
    for (ulong k=0; k<n-1; ++k)  f[k] = f[k+1];
    f[n-1] = f0;
}
// -------------------------

template <typename Type>
void rotate_right1(Type *f, ulong n)
// Rotate away from element #0, by one position.
// =^= rotate_right(f, n, 1);
{
    if ( n<=1 )  return;  // nothing to do
    ulong fl = f[n-1];
    for (ulong k=n-1; k>0; --k)  f[k] = f[k-1];
    f[0] = fl;
}
// -------------------------



template <typename Type>
void rotate_sgn(Type *f, ulong n, long s)
// Positive s --> shift away from element zero
{
    if ( s>0 )  rotate_right(f, n, (ulong)s);
    else        rotate_left(f, n, (ulong)-s);
}
// -------------------------


#endif  // !defined HAVE_ROTATE_H__
