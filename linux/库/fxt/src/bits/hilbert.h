#if !defined HAVE_HILBERT_H__
#define      HAVE_HILBERT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/parity.h"


// bits/lin2hilbert.cc:
void  lin2hilbert(ulong t, ulong &x, ulong &y);
ulong hilbert2lin(ulong x, ulong y);
ulong hilbert_gray_code(ulong t);
ulong inverse_hilbert_gray_code(ulong g);


static inline ulong hilbert_p(ulong t)
// Let (dx,dy) be the (horizontal,vertical) move
//   with step t of the Hilbert curve.
// Return  zero if (dx+dy)==-1, else one (then: (dx+dy)==+1).
// Used in hilbert_dir()
// Algorithm: count number of threes in radix 4 expansion of t.
{
#if 0
#if ( BITS_PER_LONG<=32 )
    ulong d = (t & 0x55555555UL) & ((t & 0xaaaaaaaaUL) >> 1);
#else
    ulong d = (t & 0x5555555555555555UL) & ((t & 0xaaaaaaaaaaaaaaaaUL) >> 1);
#endif
    return  parity( d );

#else  // optimized version:

#if ( BITS_PER_LONG<=32 )
    t &= ((t & 0xaaaaaaaaUL) >> 1);
#else
    t &= ((t & 0xaaaaaaaaaaaaaaaaUL) >> 1);
#endif

    t ^= t>>2;  // gray ** 2
    t ^= t>>4;  // gray ** 4
    t ^= t>>8;  // gray ** 8
    t ^= t>>16;  // gray ** 16
#if  BITS_PER_LONG > 32
    t ^= t>>32;  // for 64bit words
#endif

    return  t & 1;
#endif
}
// -------------------------


static inline ulong hilbert_m(ulong t)
// Let (dx,dy) be the (horizontal,vertical) move
//   with step t of the Hilbert curve.
// Return  zero if (dx-dy)==-1, else one (then: (dx-dy)==+1).
// Used in hilbert_dir()
{
    return  hilbert_p( -t );
}
// -------------------------


static inline ulong hilbert_dir(ulong t)
// Return encoding of the the next move with the Hilbert curve.
//
// d \in {0,1,2,3} as follows:
//   d : direction
//   0 : right (+x:  dx=+1, dy= 0)
//   1 : down  (-y:  dx= 0, dy=-1)
//   2 : up    (+y:  dx= 0, dy=+1)
//   3 : left  (-x:  dx=-1, dy= 0)
//
// To print symbollically:  cout << (">v^<")[ d ];
//
// dx+dy: ++-+++-+++----++++-+++-+++----++++-+++-+++----+---+---+---++++-
// dx-dy: +----+++-+++-+++-++++---+---+----++++---+---+----++++---+---+--
//   dir: >^<^^>v>^>vv<v>>^>v>>^<^>^<<v<^^^>v>>^<^>^<<v<^<<v>vv<^<v<^^>^<
{
    ulong p = hilbert_p(t);
    ulong m = hilbert_m(t);
    ulong d = p ^ (m<<1);
    return  d;
}
// -------------------------


static inline int hilbert_turn(ulong t)
// Return the turn (left or right) with the steps
//   t and t-1 of the Hilbert curve.
// Returned value is
//   0 for no turn
//  +1 for right turn
//  -1 for left turn
//
// To print symbollically:  cout << ("-0+")[ u ];
//   dir: >^<^^>v>^>vv<v>>^>v>>^<^>^<<v<^^^>v>>^<^>^<<v<^<<v>vv<^<v<^^>^<
//  turn: 0--+0++--++0+--0-++-0--++--0-++00++-0--++--0-++-0--+0++--++0+--
{
    ulong d1 = hilbert_dir(t);
    ulong d2 = hilbert_dir(t-1);
    d1 ^= (d1>>1);
    d2 ^= (d2>>1);
    ulong u = d1 - d2;
    // at this point, symbolically:  cout << ("+.-0+.-")[ u + 3 ];
    if ( 0==u )  return 0;
    if ( (long)u < 0 )  u += 4;
    return  (1==u ? +1 : -1);
}
// -------------------------


#endif  // !defined HAVE_HILBERT_H__
