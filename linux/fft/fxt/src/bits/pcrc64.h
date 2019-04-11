#if !defined  HAVE_PCRC64_H__
#define       HAVE_PCRC64_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

template <typename Type>
class pcrc64
// Parallel computation of 64-bit CRCs for each bit of the input words.
// Primitive polynomial used is x^64 + x^4 + x^3 + x^2 + 1
{
public:
    Type x_[64];    // CRC data
    // bit(i) of x_[0], x_[1], ..., x_[63] is a 64-bit CRC
    //   of bit(i) of all input words
    uint pos_;      // position of constant polynomial term
    const uint m_;  // mask to compute mod 64

public:
    explicit pcrc64()
        : m_(63)
    {
        reset();
    }

    ~pcrc64()  { ; }

    void reset()
    {
        pos_ = 0;
        Type ff = 0;
        ff = (Type)~ff;  // compiler wants cast here
        for (uint k=0; k<64; ++k)  x_[k] = ff;
    }

    void word_in(Type w)
    {  // Fibonacci setup
        uint p = pos_;
        pos_ = (p+1) & m_;
        uint h = (p-1) & m_;
        Type a = x_[p & m_];  // 0
        p += 2;
        a ^= x_[p & m_];  // 2
        ++p;
        a ^= x_[p & m_];  // 3
        ++p;
        a ^= x_[p & m_];  // 4
        x_[h] = a ^ w;
    }

    void words_in(Type *w, ulong n)
    {
        if ( n&1 )  { word_in(w[0]); ++w; }
        n >>= 1;

        if ( n&1 )  { word_in(w[0]); word_in(w[1]); w+=2; }
        n >>= 1;

        for (ulong k=0; k<n; ++k)
        {
            word_in(w[0]);
            word_in(w[1]);
            word_in(w[2]);
            word_in(w[3]);
            w += 4;
        }
    }

    void zero_pos()
    {  // move constant term to position zero
        rotate_left(x_, 64, pos_);
        pos_ = 0;
    }

    Type sum()
    {  // Return sum (XOR) of all CRC words
        Type s = 0;
        for (uint k=0; k<64; ++k)  s ^= x_[k];
        return s;
    }
};
// -------------------------

#endif  // !defined HAVE_PCRC64_H__
