#if !defined  HAVE_NEXTGRAY_H__
#define       HAVE_NEXTGRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitlow.h"  // lowest_one()
#include "fxttypes.h"


static inline ulong next_gray2(ulong x)
// With input x==gray_code(2*k) the return is gray_code(2*k+2).
// Let x1 be the word x shifted right once
// and i1 its inverse Gray code.
// Let r1 be the return r shifted right once.
// Then r1 = gray_code(i1+1).
// That is, we have a Gray code counter.
// The argument must have an even number of bits.
//
//   k:     g(k)      g(2*k)     g(k) p
//   0:   .......    .......   ...... .   ...... .
//   1:   ......1    .....11   .....1 1   .....+ 1
//   2:   .....11    ....11.   ....11 .   ....+1 .
//   3:   .....1.    ....1.1   ....1. 1   ....1- 1
//   4:   ....11.    ...11..   ...11. .   ...+1. .
//   5:   ....111    ...1111   ...111 1   ...11+ 1
//   6:   ....1.1    ...1.1.   ...1.1 .   ...1-1 .
//   7:   ....1..    ...1..1   ...1.. 1   ...1.- 1
//   8:   ...11..    ..11...   ..11.. .   ..+1.. .
//   9:   ...11.1    ..11.11   ..11.1 1   ..11.+ 1
//  10:   ...1111    ..1111.   ..1111 .   ..11+1 .
//  11:   ...111.    ..111.1   ..111. 1   ..111- 1
//  12:   ...1.1.    ..1.1..   ..1.1. .   ..1-1. .
//  13:   ...1.11    ..1.111   ..1.11 1   ..1.1+ 1
//  14:   ...1..1    ..1..1.   ..1..1 .   ..1.-1 .
//  15:   ...1...    ..1...1   ..1... 1   ..1..- 1
//  16:   ..11...    .11....   .11... .   .+1... .
//  17:   ..11..1    .11..11   .11..1 1   .11..+ 1
//
// Note that the changes with increment always
// happen one position left of the rightmost bit.
//
// Convert an arbitrary (Gray code) word g to
//   x = (g<<1) ^ parity(g)
// in order to use this routine.
{
    x ^= 1;
    x ^= (lowest_one(x) << 1);
    return x;
}
// -------------------------


#endif  // !defined HAVE_NEXTGRAY_H__
