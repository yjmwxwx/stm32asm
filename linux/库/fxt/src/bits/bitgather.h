#if !defined  HAVE_BITGATHER_H__
#define       HAVE_BITGATHER_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"


static inline ulong bit_gather(ulong w, ulong m)
// Return  word with bits of w collected as indicated by m:
// Example:
//  w = 00A0BC00
//  m = 00101100
//  ==> 00000ABC
// This is the inverse of bit_scatter()
{
    ulong z = 0;
    ulong b = 1;
    while ( m )
    {
        ulong i = m & -m;  // lowest bit
        m ^= i;  // clear lowest bit in m
        z += (i&w ? b : 0);
        b <<= 1;
    }
    return  z;
}
// -------------------------

static inline ulong bit_scatter(ulong w, ulong m)
// Return  word with bits of w distributed as indicated by m:
// Example:
//  w = 00000ABC
//  m = 00101100
//  ==> 00A0BC00
// This is the inverse of bit_gather()
{
    ulong z = 0;
    ulong b = 1;
    while ( m )
    {
        ulong i = m & -m;  // lowest bit
        m ^= i;
        z += (b&w ? i : 0);
        b <<= 1;
    }
    return  z;
}
// -------------------------


#endif  // !defined HAVE_BITGATHER_H__
