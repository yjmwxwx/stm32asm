#if !defined  HAVE_BITPOL_DEGREE_H__
#define       HAVE_BITPOL_DEGREE_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bithigh.h"
#include "fxttypes.h"  // ulong

inline ulong bitpol_deg(ulong c)
// Return degree of binary polynomial C.
// Return zero if C is the zero polynomial.
{
    if ( 0==c )  return 0;
    return  highest_one_idx(c);
}
// -------------------------

inline ulong bitpol_h(ulong c)
// Return 1-bit mask needed with modular computations.
{
    if ( c<=1 )  return 0;
    return  highest_one(c) >> 1;
}
// -------------------------

inline void bitpol_hdeg(ulong c, ulong &d, ulong &h)
// Compute both degree and mask.
{
    d = bitpol_deg(c);
    h = 0;
    if ( d )  h = 1UL << (d-1);
}
// -------------------------


#endif  // !defined HAVE_BITPOL_DEGREE_H__
