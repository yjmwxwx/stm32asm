#if !defined  HAVE_CRC32_H__
#define       HAVE_CRC32_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
//#include "bits/bitsperlong.h"

//#if sizeof(uint) < 4
//#error 'class crc32 needs sizeof(uint)>=4'
//#endif


class crc32
// 32-bit CRC (cyclic redundancy check)
{
public:
    uint a_;  // internal state (polynomial modulo c)
    uint c_;  // a binary primitive polynomial
    // (non-primitive c lead to smaller periods)
    // The leading coefficient does not need to be present.
    // After initialization c is shifted to the right.

    static const uint cc[];  // 16 "random" 32-bit primitive polynomials

public:
    explicit crc32(uint c=0)
    {
        if ( 0==c )  c = 0xaf;  // =^= 32,7,5,3,2,1,0 (default)
        init(c);
    }

//    virtual
    ~crc32()  {;}

    void init(uint c)
    {
        c_ = c;
        c_ >>= 1;
        uint h = 1ULL<<31;
        c_ |= h;  // leading coefficient
        reset();
    }

    void reset()  { set_a(0U); }  // all ones
    void set_a(uint a)  { a_=a; }

    uint get_a()  const  { return a_; }

    void shift()
    {
        bool s = (a_ & 1);
        a_ >>= 1;
        if ( 0!=s )  a_ ^= c_;
    }

    uint bit_in(uchar b)
    {
        a_ ^= (b&1);
        shift();
        return  a_;
    }

    uint byte_in(uchar b)
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

    uint word_in(uint w)
    {
        uint k = 4;  // BYTES_PER_INT;
        while ( k-- )  { byte_in( (uchar)w );  w>>=8; }
        return  a_;
    }

    uint bits_in(uint w, uchar k)
    // Feed in the k lowest bits of w
    {
        // VERSION 1:   (OK but suboptimal)
//        while ( k-- )  { bit_in( (uchar)w );  w>>=1; }

        // VERSION 2:   (optimized)
        if ( k&1 )  { a_ ^= (w&1); w >>= 1;  shift(); }
//        k >>= 1;
        k = (uchar)(k>>1);  // cast to avoid pedantic compiler warning

        if ( k&1 )  { a_ ^= (w&3); w >>= 2; shift(); shift(); }
//        k >>= 1;
        k = (uchar)(k>>1);  // cast to avoid pedantic compiler warning

        if ( k&1 )  { a_ ^= (w&15); w >>= 4; shift(); shift(); shift(); shift(); }
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



#endif  // !defined HAVE_CRC32_H__
