#if !defined  HAVE_TCRC64_H__
#define       HAVE_TCRC64_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
//#include "bits/bitsperlong.h"

//#if sizeof(uint64) < 8
//#error 'class crc64 needs sizeof(uint64)>=8'
//#endif


#define LOG_TSIZE 8  // 4 or 8
// size of the lookup table (16 or 256):
#define TSIZE (1ULL<<LOG_TSIZE)  // do not modify

class tcrc64
// 64-bit CRC (cyclic redundancy check) with lookup table
{
public:
    uint64 a_;  // internal state (polynomial modulo c)
    uint64 c_;  // a binary primitive polynomial
    // (non-primitive c lead to smaller periods)
    // The leading coefficient needs not be present.
    // After initialization c is shifted to the right.
    uint64 t_[TSIZE];  // lookup table

public:
    explicit tcrc64(uint64 c=0)
    {
        if ( 0==c )  c = 0x1bULL;  // =^= 64,4,3,1,0 (default)
        init(c);
    }

    ~tcrc64()  {;}

    void init(uint64 c)
    {
        c_ = c;
        c_ >>= 1;
        uint64 h = 1ULL<<63;
        c_ |= h;  // leading coefficient

        // create lookup table:
        for (ulong w=0; w<TSIZE; ++w)
        {
            set_a(0);
            for (ulong k = 0; k<LOG_TSIZE; ++k)   bit_in( (uchar)(w>>k) );
            t_[w] = a_;
        }
        reset();
    }

    void reset()  { set_a(~0ULL); }  // all ones
    void set_a(uint64 a)  { a_=a; }

    uint64 get_a()  const  { return a_; }

    void shift()
    {
        bool s = (a_ & 1);
        a_ >>= 1;
        if ( 0!=s )  a_ ^= c_;
    }

    void bit_in(uchar b)
    {
        a_ ^= (b&1);
        shift();
    }

    void nibble_in(uchar b)
    {
        uint64 x;
        a_ ^= b;
        x =  t_[a_ & 15];
        a_ >>= 4;
        a_ ^= x;
    }

    uint64 byte_in(uchar b)
    {
#if  ( LOG_TSIZE == 4 )
        nibble_in(b&15);
        b>>=4;
        nibble_in(b&15);
#else
        a_ ^= b;
        uint64 x =  t_[a_ & 255];
        a_ >>= 8;
        a_ ^= x;
#endif
        return  a_;
    }

    uint64 word_in(uint64 w)
    {
        uint k = 8;  // BYTES_PER_LONG_LONG;
        while ( k-- )  { byte_in( (uchar)w );  w>>=8; }
        return  a_;
    }
};
// -------------------------

#undef LOG_TSIZE
#undef TSIZE


#endif  // !defined HAVE_TCRC64_H__
