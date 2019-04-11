#if !defined HAVE_BITCYCLIC_XOR_H__
#define      HAVE_BITCYCLIC_XOR_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitrotate.h"
#include "bits/graycode.h"
#include "bits/revgraycode.h"


static inline ulong bit_cyclic_rxor(ulong x)
// Similar to Gray code, but the bit shifted
// out at the right is moved to the highest bit.
// The returned word has an even number of bits set.
{
    return x ^ bit_rotate_right(x, 1);
}
// -------------------------

static inline ulong bit_cyclic_rxor(ulong x, ulong n)
// Version for n-bit words
{
    return x ^ bit_rotate_right(x, 1, n);
}
// -------------------------

static inline ulong bit_cyclic_inv_rxor(ulong x)
// Return v so that bit_cyclic_rxor(v) == x.
// The same relation holds for ~v.
// x must have an even number of bits.
// Lowest bit of result is zero for valid inputs.
// Also the inverse of bit_cyclic_rxor(x,n) for any n.
{
    return  inverse_gray_code(x);
}
// -------------------------


static inline ulong bit_cyclic_lxor(ulong x)
// Similar to reversed Gray code, but the bit shifted
// out at the left is moved to the lowest bit.
// The returned word has an even number of bits set.
{
    return x ^ bit_rotate_left(x, 1);
}
// -------------------------

static inline ulong bit_cyclic_lxor(ulong x, ulong n)
// Version for n-bit words
{
    return x ^ bit_rotate_left(x, 1, n);
}
// -------------------------

static inline ulong bit_cyclic_inv_lxor(ulong x)
// Return v so that bit_cyclic_lxor(v) == x.
// The same relation holds for ~v.
// x must have an even number of bits.
// Highest bit of result is zero for valid inputs.
// Also the inverse of bit_cyclic_lxor(x,n) for any n.
{
    return  inverse_rev_gray_code(x);
}
// -------------------------


#endif  // !defined HAVE_BITCYCLIC_XOR_H__
