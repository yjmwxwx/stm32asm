#if !defined HAVE_BIT_SL_GRAY_H__
#define      HAVE_BIT_SL_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

//#include "jjassert.h"


// Cf. comb/binary-sl-gray.h for generation in an array.
// Cf. bits/bitlex.h for subset-lex order.

// alternative detection of last word:
//#define  BIT_SL_GRAY_ALT  // default off (slight slowdown)


class bit_sl_gray
// Binary words in a minimal-change order
//   related so subset-lex order ("SL-Gray" order).
// Successive transitions are mostly adjacent (one-close),
//   and otherwise have distance 3 (three-close).
// Loopless algorithm.
{
public:
    ulong x_;   // Gray code word
    ulong tr_;  // current track (a one-bit word)
    ulong h_;   // highest allowed track
    bool dt_;   // direction track tries to move in: true== try move right

public:
    explicit bit_sl_gray(ulong n)  { first(n); }
    ~bit_sl_gray()  { ; }

    void first(ulong n)
    {
        tr_ = 1UL << (n-1);
        h_ = tr_;
        dt_ = true;
        x_ = 0;

        if ( n == 0 )  // make things work for n==0
        {
            h_ = 0;
            tr_ = 1;
            dt_ = false;
        }

#ifdef  BIT_SL_GRAY_ALT
        if ( n == 1 )  h_ = 2;  // simplify for n==1
#endif
    }

    ulong data()  const  { return x_; }

    ulong next()
    // Loopless algorithm.
    {
#ifdef  BIT_SL_GRAY_ALT
        if ( (x_<<1) == h_ )  return 0;  // current is last
#endif
        if ( dt_ )  // try to append trailing ones
        {
            if ( (x_ & tr_) == 0 )  // bit not set?
            {
                x_ ^= tr_;  // set bit
                if ( tr_>>1 )  tr_ >>= 1;  // move right unless already at end
            }
            else  // change bit one track left
            {
                dt_ = false;
//                jjassert( tr_ == 1 );
//                tr_ = 1;
                x_ ^= (tr_<<1);
#ifndef  BIT_SL_GRAY_ALT
                if ( tr_ >= h_ )  return  0;  // current is last (only for n_ == 1)
#endif
            }
        }
        else  // try to remove trailing ones
        {
            if ( (x_ & (tr_<<1)) != 0 )  // left bit set?
            {
                x_ ^= tr_;  // remove bit on track
                tr_ <<= 1;  // move left
            }
            else  // change bit three tracks left, move right
            {
#ifndef  BIT_SL_GRAY_ALT
                if ( h_ <= tr_<<1 )  return 0;  // current is last
#endif
                dt_ = true;
                x_ ^= (tr_ << 2);
                if ( tr_>>1 )  tr_ >>= 1;
            }
        }
        return x_;
    }
};
// -------------------------


#endif  // !defined HAVE_BIT_SL_GRAY_H__
