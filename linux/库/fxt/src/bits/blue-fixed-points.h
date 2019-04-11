#if !defined  HAVE_BLUE_FIXED_POINTS_H__
#define       HAVE_BLUE_FIXED_POINTS_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/revgraycode.h"


static inline ulong blue_fixed_point(ulong s)
// Return unique fixed point of blue_code() for each argument.
//.
// The first few fixed points (bfp) are:
//  arg = arg_2 :     bfp_2     =      bfp
//   0 = ...... :    .......... =        0
//   1 = .....1 :    .........1 =        1
//   2 = ....1. :    .......11. =        6
//   3 = ....11 :    .......111 =        7
//   4 = ...1.. :    .....1.1.. =       20
//   5 = ...1.1 :    .....1..1. =       18
//   6 = ...11. :    .....1.1.1 =       21
//   7 = ...111 :    .....1..11 =       19
//   8 = ..1... :    ...1111... =      120
//   9 = ..1..1 :    ...11.11.. =      108
//  10 = ..1.1. :    ...111111. =      126
//  11 = ..1.11 :    ...11.1.1. =      106
//  12 = ..11.. :    ...1111..1 =      121
//  13 = ..11.1 :    ...11.11.1 =      109
//  14 = ..111. :    ...1111111 =      127
//  15 = ..1111 :    ...11.1.11 =      107
//  16 = .1.... :    .1...1.... =      272
//  17 = .1...1 :    .1.11.1... =      360
{
    if ( 0==s )  return 0;
    ulong f = 1;
    while ( s>1 )
    {
        f ^= (f<<1);
        f <<= 1;
        f |= (s&1);
        s >>= 1;
    }
    return f;
}
// -------------------------


static inline ulong blue_fixed_point_idx(ulong f)
// Inverse of blue_fixed_point()
{
    ulong s = 1;
    while ( f )
    {
        s <<= 1;
        s ^= (f & 1);
        f >>= 1;
        f = inverse_rev_gray_code(f);  // == bitpol_div(f, 3);
    }
    return s >> 1;
}
// -------------------------


#endif  // !defined HAVE_BLUE_FIXED_POINTS_H__
