#if !defined HAVE_BIN_TO_SL_GRAY_H__
#define      HAVE_BIN_TO_SL_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


static inline ulong bin_to_sl_gray(ulong k, ulong ldn)
// Unranking for binary SL-Gray:
// Convert binary number to corresponding word in SL-Gray order.
// Successive transitions are adjacent (one-close) or three-close.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
    if ( ldn==0 )  return 0;

    ulong b = 1UL << (ldn-1);  // highest bit
    ulong m = (b<<1) - 1;  // mask for reversing direction
    ulong z = b;  // Gray code
    k -= 1;  // move all-zero word to begin
//    ulong z = 0;  ++k;  // reverse order

    while ( b != 0 )
    {
        const ulong h = k & b;  // bit under consideration
        z ^= h;  // with one, switch bit in Gray code

        if ( !h )  k ^= m;  // reverse direction with zero
//        if ( h )  k ^= m;  // reverse direction with one
//        if ( (!h) ^ (ldn & 1)  )  k ^= m;  //
//        if ( (!!h) ^ (ldn & 1)  )  k ^= m;  //

        k += 1;  // SL-Gray

//        k = -k - 2;  // complement of SL-Gray
//        k = -k - 1;  // binary reflected Gray code
        // when k is not  changed here ==> complement of binary reflected Gray code
//        k += m/4;  // rotated SL-Gray
//        k -= 1;  // another Gray code
//        k = -k;  // complement of the above
//        k += 0x55555555UL ;  // another Gray code

        b >>= 1;  // next lower bit
        m >>= 1;  // next smaller mask
    }

    return z;
}
// -------------------------


static inline ulong sl_gray_to_bin(ulong k, ulong ldn)
// Ranking for binary SL-Gray:
// Convert binary word in SL-Gray order to binary number.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
    if ( k==0 )  return 0;

    ulong b = 1UL << (ldn-1);  // mask for bit at end
    ulong h = k & b;  // bit at end
    k ^= h;  // remove bit

    ulong z = sl_gray_to_bin( k, ldn-1 );  // recursion
    if ( h==0 )  return (b<<1) - z;
    else         return 1 + z;
}
// -------------------------


#endif  // !defined HAVE_BIN_TO_SL_GRAY_H__
