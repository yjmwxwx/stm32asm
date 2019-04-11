#if !defined  HAVE_ENDO_ENUP_H__
#define       HAVE_ENDO_ENUP_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


static inline ulong next_endo(ulong x, ulong m)
// Return next number in endo order
// (endo := "Even Numbers DOwn, odd numbers up")
// m := max digit
//  m:   endo sequence
//  1:   1 0
//  2:   1 2 0
//  3:   1 3 2 0
//  4:   1 3 4 2 0
//  5:   1 3 5 4 2 0
//  6:   1 3 5 6 4 2 0
//  7:   1 3 5 7 6 4 2 0
//  8:   1 3 5 7 8 6 4 2 0
//  9:   1 3 5 7 9 8 6 4 2 0
// The routine computes one for the input zero (wrap around).
{
    if ( x & 1 )  // x odd
    {
        x += 2;
        if ( x>m )  x = m - (m&1);  // == max even <= m
    }
    else  // x even
    {
//        x -= 2;
//        if ( x>m )  x = 1;  // == min odd

        x = ( x==0 ? 1 : x-2 );
    }
    return x;
}
// -------------------------

static inline ulong next_enup(ulong x, ulong m)
// Return next number in enup order
// (enup := "Even Numbers UP, odd numbers down")
// enup order is reversed endo order.
// m := max digit
//  m:   enup sequence
//  1:   0 1
//  2:   0 2 1
//  3:   0 2 3 1
//  4:   0 2 4 3 1
//  5:   0 2 4 5 3 1
//  6:   0 2 4 6 5 3 1
//  7:   0 2 4 6 7 5 3 1
//  8:   0 2 4 6 8 7 5 3 1
//  9:   0 2 4 6 8 9 7 5 3 1
// The routine computes zero for the input one (wrap around).
{
    if ( x & 1 )  // x odd
    {
//        x -= 2;
//        if ( x>m )  x = 0;  // == min even

//        x += (x==1);
//        x -= 2;

        x = ( x==1 ? 0 : x-2 );
    }
    else  // x even
    {
        x += 2;
        if ( x>m )  x = m - !(m&1);  // max odd <=m
    }
    return x;
}
// -------------------------

static inline ulong prev_endo(ulong x, ulong m)
// Return previous number in endo order
// Inverse of next_endo()
{ return next_enup(x, m); }

static inline ulong prev_enup(ulong x, ulong m)
// Return previous number in enup order
// Inverse of next_enup()
{ return next_endo(x, m); }

static inline ulong endo_num(ulong x, ulong m)
// Return the x-th number in endo order.
// m := max digit
// For example, with m=5:
//  x:   0 1 2 3 4 5
//  r:   1 3 5 4 2 0
// Must have  x<=m.
{
    // return enup_num(m-x, m);
    x = m - x;
    ulong r = 2*x;
    if  ( r>m )  r = 2*m+1 - r;
    return  r;
}
// -------------------------

static inline ulong endo_idx(ulong x, ulong m)
// Inverse of endo_num()
// For example, with m=5:
//  x:   0 1 2 3 4 5
//  r:   5 0 4 1 3 2
// Must have  x<=m.
{
    const ulong b = x & 1;
    x >>= 1;
    return  ( b ? x : m-x );
}
// -------------------------


static inline ulong enup_num(ulong x, ulong m)
// Return the x-th number in enup order.
// m := max digit
// For example, with m=5:
//  x:   0 1 2 3 4 5
//  r:   0 2 4 5 3 1
// Must have  x<=m.
{
    ulong r = 2*x;
    if  ( r>m )  r = 2*m+1 - r;
    return r;
}
// -------------------------

static inline ulong enup_idx(ulong x, ulong m)
// Inverse of enup_num()
// m := max digit
// For example, with m=5:
//  x:   0 1 2 3 4 5
//  r:   0 5 1 4 2 3
// Must have  x<=m.
{
    const ulong b = x & 1;
    x >>= 1;
    return  ( b ? m-x : x );
}
// -------------------------

#endif  // !defined HAVE_ENDO_ENUP_H__
