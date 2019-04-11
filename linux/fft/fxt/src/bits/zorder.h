#if !defined  HAVE_ZORDER_H__
#define       HAVE_ZORDER_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitzip.h"
#include "fxttypes.h"

//: Z-order (or Morton order), a non self-intersecting space filling curve.


static inline void lin2zorder(ulong t, ulong &x, ulong &y)  { bit_unzip2(t, x, y); }
static inline ulong zorder2lin(ulong x, ulong y)  { return bit_zip2(x, y); }

static inline void zorder_next(ulong &x, ulong &y)
{
    ulong b = 1;
    do
    {
        x ^= b;  b &= ~x;
        y ^= b;  b &= ~y;
        b <<= 1;
    }
    while ( b );
}
// -------------------------

static inline void zorder_prev(ulong &x, ulong &y)
{
    ulong b = 1;
    do
    {
        x ^= b;  b &= x;
        y ^= b;  b &= y;
        b <<= 1;
    }
    while ( b );
}
// -------------------------


static inline void zorder3d_next(ulong &x, ulong &y, ulong &z)
{
    ulong b = 1;
    do
    {
        x ^= b;  b &= ~x;
        y ^= b;  b &= ~y;
        z ^= b;  b &= ~z;
        b <<= 1;
    }
    while ( b );
}
// -------------------------

static inline void zorder3d_prev(ulong &x, ulong &y, ulong &z)
{
    ulong b = 1;
    do
    {
        x ^= b;  b &= x;
        y ^= b;  b &= y;
        z ^= b;  b &= z;
        b <<= 1;
    }
    while ( b );
}
// -------------------------

#endif  // !defined HAVE_ZORDER_H__
