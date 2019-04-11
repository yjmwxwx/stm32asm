// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitcount.h"
#include "bits/graycode.h"
//#include "bits/revgraycode.h"
#include "bits/bitlex.h"
#include "bits/revbin.h"
#include "bits/bitlow.h"
#include "bits/bithigh.h"
#include "bits/bitsequency.h"
#include "bits/bittransforms.h"

#include "fxttypes.h"

// ==================================
//
// The functions CF quickly lead to Gray codes
// for sizes P as follows:
//
// CF:  P =
//  0:  3   5   7   11   13
//  1:  3   5   7   11        17   19
//  2:  3   5   7   11   13   17
//  3:  3   5   7   11   13   17   19   23
//  4:  3   5   7   11   13
//  5:  3   5   7   11   13        19   23
//  6:  3   5   7   11   13   17   19
//  7:  3   5   7   11   13   17   19   23  (29  31)
//
// ==================================

int
lyndon_cmp0(const ulong &a, const ulong &b)
{
    int bc = bit_count_cmp(a, b);
    if ( bc )  return  -bc;  // more bits first
    else
    {
        if ( a==b )  return 0;
        return  (a>b ?  +1 : -1);  // greater numbers last
    }
}
// -------------------------

int
lyndon_cmp1(const ulong &a, const ulong &b)
{
    if ( a==b )  return 0;
#define CODE(x) gray_code(blue_code(x))
    ulong ta = CODE(a), tb = CODE(b);
    return  ( ta<tb ? +1 : -1);
#undef CODE
}
// -------------------------

int
lyndon_cmp2(const ulong &a, const ulong &b)
{
    if ( a==b )  return 0;
#define CODE(x) gray_code(x)
    ulong ta = CODE(a), tb = CODE(b);
    return  ( ta<tb ? +1 : -1);
#undef CODE
}
// -------------------------

int
lyndon_cmp3(const ulong &a, const ulong &b)
{
    if ( a==b )  return 0;
#define CODE(x) inverse_gray_code(x)
    ulong ta = CODE(a), tb = CODE(b);
    return  ( ta<tb ? +1 : -1);
#undef CODE
}
// -------------------------

int
lyndon_cmp4(const ulong &a, const ulong &b)
{
    if ( a==b )  return 0;
    int bc = bit_count_cmp(a, b);
    if ( bc )  return  -bc;
#define CODE(x) inverse_gray_code( inverse_gray_code(x))
    ulong ta = CODE(a),  tb = CODE(b);
    return  ( ta<tb ? +1 : -1);
#undef CODE
}
// -------------------------

int
lyndon_cmp5(const ulong &a, const ulong &b)
{
    if ( a==b )  return 0;
#define CODE(x) inverse_gray_code( inverse_gray_code(x) )
    ulong ta = CODE(a),  tb = CODE(b);
    return  ( ta<tb ? +1 : -1);
#undef CODE
}
// -------------------------

int
lyndon_cmp6(const ulong &a, const ulong &b)
{
    if ( a==b )  return 0;
#define CODE(x) inverse_gray_code( negidx2lexrev(x) )
    ulong ta = CODE(a),  tb = CODE(b);
    return  ( ta<tb ? +1 : -1);
#undef CODE
}
// -------------------------

static inline ulong g21(ulong x)
// Gray code to the 21. power
{
    x ^= x>>1;  // gray ** 1
    x ^= x>>4;  // gray ** 4
    x ^= x>>16;  // gray ** 16
    return  x;
}
// -------------------------
// used for:
int
lyndon_cmp7(const ulong &a, const ulong &b)
{
    if ( a==b )  return 0;
#define CODE(x) g21(x)
    ulong ta = CODE(a),  tb = CODE(b);
    return  ( ta<tb ? +1 : -1);
#undef CODE
}
// -------------------------
