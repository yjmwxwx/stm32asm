#if !defined  HAVE_RADIX_M1PI_H__
#define       HAVE_RADIX_M1PI_H__
// This file is part of the FXT library.
// Copyright (C) 2011, 2012, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/radix-m4.h"
#include "bits/bitzip.h"

#include "fxttypes.h"
#include "bits/bitsperlong.h"

//: Conversion to and from (complex) radix(-1+i).


static inline ulong bin_real_to_radm1pi(ulong x)
// binary --> radix(-1+i)
{
    x = bin_to_radm4(x);

    // we have to replace:
    // 00 --> 0000
    // 01 --> 0001
    // 10 --> 1100
    // 11 --> 1101
    x = bit_zip0(x);  // first spread out

#if  BITS_PER_LONG == 64
    // mask in binary is ... 0100 0100 0100
    const ulong m = 0x4444444444444444UL;
#else
    const ulong m = 0x44444444UL;
#endif
    // the replacement to do now is:
    // 0000 --> 0000
    // 0001 --> 0001
    // 0100 --> 1100
    // 0101 --> 1101
    x |= (m & x) << 1;
    return x;
}
// -------------------------


static inline ulong bin_imag_to_radm1pi(ulong x)
// binary * i --> radix(-1+i)
{
    return  bin_real_to_radm1pi( x<<1 ) >> 2;
}
// -------------------------


static inline ulong add_radm1pi(ulong x, ulong y)
// Add radix(-1+i) representations x and y.
// Note that x + (x<<1) == x + (-1+i)*x == i*x
{
    // Recursive algorithm:
    while ( y )
    {
        ulong c = x & y;  // positions with carries
        x ^= y;  // positions without carries
        ulong c2 = c << 2,  c3 = c << 3;  // carries

#if 0  // move bits from c3 to c2 where possible (optional):
        ulong ca = c2 & c3;
        c2 ^= c3;  c2 |= ca;
        c3 = ca;
#endif
#if 0  // move bits from c3 to x where possible (optional):
        ulong m3 = ( c3 ^ x ) & c3;  x ^= m3;  c3 ^= m3;
#endif
#if 0  // move bits from c2 to x where possible (optional):
        ulong m2 = ( c2 ^ x ) & c2;  x ^= m2;  c2 ^= m2;
#endif

        y = add_radm1pi(c2, c3);  // add carries
    }
    return x;
}
// -------------------------


static inline ulong bin_to_radm1pi(ulong re, ulong im)
// binary ( re + i * im ) --> radix(-1+I)
{
    re = bin_real_to_radm1pi( re );
    im = bin_imag_to_radm1pi( im );
    return  add_radm1pi( re, im );
}
// -------------------------



static inline ulong radm1pi_to_bin_real(ulong x)
// convert radix(-1+i) number (which must be purely real) to binary.
{
#if  BITS_PER_LONG == 64
    // mask in binary is ... 1000 1000 1000
    const ulong m = 0x8888888888888888UL;
#else
    const ulong m = 0x88888888UL;
#endif
    x &= ~m;

    // Possibly wrong result if any bit in an odd position is set.
    x = bit_unzip0(x);
    x = radm4_to_bin(x);
    return x;
}
// -------------------------


static inline ulong radm1pi_to_bin_imag(ulong x)
// convert radix(-1+i) number (which must be purely imaginary) to binary.
{
#if 1

    ulong r = radm1pi_to_bin_real( x >> 2 );
    r <<= 1;
    r = -r;
    r |= (x & 1);
    return  r;

#else

    ulong r = radm1pi_to_bin_real( x << 2 );
//    return  r >> 1;
    return  ((long)r) >> 1;  // preserve highest bit

#endif
}
// -------------------------


static inline void radm1pi_to_bin(ulong z, ulong &re, ulong &im)
// radix(-1+i) --> binary ( re + i * im )
{
#if 1  // Use periodicity of real and imag part in powers of radix:

#if  BITS_PER_LONG == 64
    const ulong pr = 0x2929292929292929UL;  // positions where real part positive
    const ulong nr = 0x9292929292929292UL;  // positions where real part negative
    const ulong pi = 0x4a4a4a4a4a4a4a4aUL;  // positions where imag part positive
    const ulong ni = 0xa4a4a4a4a4a4a4a4UL;  // positions where imag part negative
    const ulong ev = 0x5555555555555555UL;  // even positions
    const ulong od = 0xaaaaaaaaaaaaaaaaUL;  // odd positions
#else
    const ulong pr = 0x29292929UL;
    const ulong nr = 0x92929292UL;
    const ulong pi = 0x4a4a4a4aUL;
    const ulong ni = 0xa4a4a4a4UL;
    const ulong ev = 0x55555555UL;
    const ulong od = 0xaaaaaaaaUL;
#endif

    const ulong zev = z & ev,  zod = z & od;

    ulong tpr = (zev & pr) | ( (zod & pr) >> 1 );
    ulong tnr = (zev & nr) | ( (zod & nr) >> 1 );
    tpr = bit_unzip0(tpr);
    tnr = bit_unzip0(tnr);
    re = tpr - tnr;

    ulong tpi = (zev & pi) | ( (zod & pi) >> 1 );
    ulong tni = (zev & ni) | ( (zod & ni) >> 1 );
    tpi = bit_unzip0(tpi);
    tni = bit_unzip0(tni);
    im = tpi - tni;

#else  // Expansion by powers of radix:

    ulong tr = 0,  ti = 0;
    ulong rdr = 1, rdi = 0;  // power of radix
    do
    {
        if ( z & 1 )  { tr += rdr;  ti += rdi; }
        // Next radix power,
        // use (a+i*b) * (-1+i) == ( -(a+b) + i*(a-b) ):
        ulong t = -(rdr+rdi);  rdi = rdr - rdi;  rdr = t;
        z >>= 1;
    }
    while ( z );
    re = tr;  im = ti;
#endif
}
// -------------------------


static inline bool radm1pi_is_real(ulong z)
// Return whether z is purely real.
{
#if  BITS_PER_LONG == 64
    // mask in binary is ... 0100 0100 0100
    const ulong m = 0x4444444444444444UL;
#else
    const ulong m = 0x44444444UL;
#endif
    ulong t = ( z ^ (z>>1) ) & m;  // pairs of bits must be equal
    t |= (z & (m>>1) );  // no purely imaginary bits
    return  ( t==0 );
}
// -------------------------


static inline bool radm1pi_is_imag(ulong z)
// Return whether z is purely imaginary.
{
#if  BITS_PER_LONG == 64
    // mask in binary is ... 0010 0010 0010
    const ulong m = 0x2222222222222222UL;
#else
    const ulong m = 0x22222222UL;
#endif
    ulong t = ( z ^ (z<<1) ) & m;  // pairs of bits must be equal
    t |= (z & (m<<2) );  // no purely real bits
    return  ( t==0 );
}
// -------------------------


#endif  // !defined HAVE_RADIX_M1PI_H__
