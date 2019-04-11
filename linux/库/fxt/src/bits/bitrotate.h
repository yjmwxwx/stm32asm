#if !defined HAVE_BITROTATE_H__
#define      HAVE_BITROTATE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitasm.h"


static inline ulong bit_rotate_left(ulong x, ulong r)
// Return word rotated r bits to the left
// (i.e. toward the most significant bit)
//.
// GCC optimizes the function to asm 'roll %cl,%ebx'
{
#if defined  BITS_USE_ASM
    return asm_rol(x, r);
#else
//    r &= (BITS_PER_LONG-1);  // modulo wordlength
    return  (x<<r) | (x>>(BITS_PER_LONG-r));
#endif
}
// -------------------------


static inline ulong bit_rotate_right(ulong x, ulong r)
// Return word rotated r bits to the right
// (i.e. toward the least significant bit)
//.
// GCC optimizes the function to asm 'rorl %cl,%ebx'
{
#if defined  BITS_USE_ASM
    return asm_ror(x, r);
#else
//    r &= (BITS_PER_LONG-1);  // modulo wordlength
    return  (x>>r) | (x<<(BITS_PER_LONG-r));
#endif
}
// -------------------------


static inline ulong bit_rotate_sgn(ulong x, long r)
// Positive r --> shift away from element zero
{
    if ( r > 0 )  return  bit_rotate_left(x, (ulong)r);
    else          return  bit_rotate_right(x, (ulong)-r);
}
// -------------------------


static inline ulong bit_rotate_left(ulong x, ulong r, ulong n)
// Return n-bit word rotated r bits to the left
// (i.e. toward the most significant bit)
// Must have  0 <= r <= n
{
    ulong m = ~0UL >> ( BITS_PER_LONG - n );
    x &= m;
    x = (x<<r) | (x>>(n-r));
    x &= m;
    return  x;
}
// -------------------------


static inline ulong bit_rotate_right(ulong x, ulong r, ulong n)
// Return n-bit word rotated r bits to the right
// (i.e. toward the least significant bit)
// Must have  0 <= r <= n
{
    ulong m = ~0UL >> ( BITS_PER_LONG - n );
    x &= m;
    x = (x>>r) | (x<<(n-r));
    x &= m;
    return  x;
}
// -------------------------

static inline ulong bit_rotate_sgn(ulong x, long r, ulong n)
// Positive r --> shift away from element zero
{
    if ( r > 0 )  return  bit_rotate_left(x, (ulong)r, n);
    else          return  bit_rotate_right(x, (ulong)-r, n);
}
// -------------------------


#endif  // !defined HAVE_BITROTATE_H__
