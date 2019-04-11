#if !defined  HAVE_CSWAP_H__
#define       HAVE_CSWAP_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitasm.h"
#include "fxttypes.h"


static inline void cswap_lt(ulong &a, ulong &b)
// Branchless equivalent to:
// if ( a<b )   { ulong t=a; a=b; b=t; }  // swap if a < b
// NOTE: Whether this routine is faster depends both
// on the machine used and the surrounding code.
{
#ifdef BITS_USE_ASM_AMD64
    asm volatile("movq %0, %%r15 \n"   // t=a
                 "cmpq %0, %1 \n"      // cmp a, b
                 "cmovae %1, %0 \n"    // cond a=b
                 "cmovae %%r15, %1 \n"  // cond b=t
                 ""
                 : "=r" (a), "=r" (b)  // output
                 : "0" (a), "1" (b)   // input
                 : "r15"  // clobber
                 );
#else
//    ulong x=a^b;  if (a>=b) { x=0;  a^=x;  b^=x; }  // XOR trick
    if ( a < b )  { ulong t=a; a=b; b=t; }  // plain
#endif
    // here: a>=b
}
// -------------------------

static inline void cswap_gt(ulong &a, ulong &b)
// Branchless equivalent to:
// if ( a>b )   { ulong t=a; a=b; b=t; }  // swap if a > b
{
    cswap_lt(b, a);
    // here: a<=b
}
// -------------------------


#endif  // !defined HAVE_CSWAP_H__
