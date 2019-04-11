#if !defined  HAVE_CRC64_H__
#define       HAVE_CRC64_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
//#include "bits/bitsperlong.h"

//#if sizeof(uint64) < 8
//#error 'class crc64 needs sizeof(uint64)>=8'
//#endif


class crc64
// 64-bit CRC (cyclic redundancy check)
{
public:
    uint64 a_;  // internal state (polynomial modulo c)
    uint64 c_;  // a binary primitive polynomial
    // (non-primitive c lead to smaller periods)
    // The leading coefficient does not need to be present.
    // After initialization c is shifted to the right.

    static const uint64 cc[];  // 16 "random" 64-bit primitive polynomials

public:
    explicit crc64(uint64 c=0)
    {
        if ( 0==c )  c = 0x1bULL;  // =^= 64,4,3,1,0 (default)
        init(c);
    }

    //virtual
    ~crc64()  {;}

    void init(uint64 c)
    {
        c_ = c;
        c_ >>= 1;
        uint64 h = 1ULL<<63;
        c_ |= h;  // leading coefficient
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

    uint64 bit_in(uchar b)
    {
        a_ ^= (b&1);
        shift();
        return  a_;
    }

    uint64 byte_in(uchar b)
    {
#if 1
        a_ ^= b;
        shift();  shift();  shift();  shift();
        shift();  shift();  shift();  shift();
#else  // identical but slower:
        bit_in(b);  b>>=1;  // bit 0
        bit_in(b);  b>>=1;  // bit 1
        bit_in(b);  b>>=1;  // bit 2
        bit_in(b);  b>>=1;  // bit 3
        bit_in(b);  b>>=1;  // bit 4
        bit_in(b);  b>>=1;  // bit 5
        bit_in(b);  b>>=1;  // bit 6
        bit_in(b);  b>>=1;  // bit 7
#endif
        return  a_;
    }

    uint64 word_in(uint64 w)
    {
        uint k = 8;  // BYTES_PER_LONG_LONG;
        while ( k-- )  { byte_in( (uchar)w );  w>>=8; }
        return  a_;
    }

    uint64 bits_in(uint64 w, uchar k)
    // Feed in the k lowest bits of w
    {
        // VERSION 1:   (OK but suboptimal)
//        while ( k-- )  { bit_in( (uchar)w );  w>>=1; }

        // VERSION 2:   (optimized)
        if ( k&1 )  { a_ ^= (w&1);  w >>= 1;  shift(); }
//        k >>= 1;
        k = (uchar)(k>>1);  // cast to avoid pedantic compiler warning

        if ( k&1 )  { a_ ^= (w&3);  w >>= 2;  shift();  shift(); }
//        k >>= 1;
        k = (uchar)(k>>1);  // cast to avoid pedantic compiler warning

        if ( k&1 )  { a_ ^= (w&15);  w >>= 4;  shift();  shift();  shift();  shift(); }
//        k >>= 1;
        k = (uchar)(k>>1);  // cast to avoid pedantic compiler warning

        while ( k-- )  { byte_in( (uchar)w );  w>>=8; }

        // VERSION 3:   (optimized)
//        if ( k & 7 )
//        {
//            uchar z = k & 7;
//            while ( z-- )  { bit_in( (uchar)w );  w>>=1; }
//        }
//        k >>= 3;
//        while ( k-- )  { byte_in( (uchar)w );  w>>=8; }

        return  a_;
    }
};
// -------------------------



#endif  // !defined HAVE_CRC64_H__
