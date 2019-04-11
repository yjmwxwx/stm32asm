#if !defined  HAVE_RADIX_2I_H__
#define       HAVE_RADIX_2I_H__
// This file is part of the FXT library.
// Copyright (C) 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/radix-m4.h"
#include "bits/bitzip-pairs.h"
//#include "bits/bitzip.h"

#include "fxttypes.h"
#include "bits/bitsperlong.h"

//: Conversion to and from radix(2*i), "quater-imaginary base".
//: The radix(2*i) representation for complex integers needs
//: one digit (i.e., two bits) after the point.


static inline ulong bin_real_to_rad2i(ulong x)
// binary --> radix(2*i)
{
    x = bin_to_radm4(x);

#if 1
    x = bit_zip0_pairs(x);

#else
    // Version using bit_zip0() (slower):
    x = bit_zip0(x);  // spread out

#if  BITS_PER_LONG == 64
    const ulong m = 0x4444444444444444UL;
#else
    const ulong m = 0x44444444UL;
#endif
    ulong t = m & x;
    x |= t >> 1;
    x ^= t;
#endif

    return x << 2;  // one digit after point
}
// -------------------------


static inline ulong bin_imag_to_rad2i(ulong x)
// binary * i --> radix(2*i)
{
#if 1
    x = -x;
    return  bin_real_to_rad2i( x<<1 ) >> 2;
#else
    return  bin_real_to_rad2i( x<<3 ) >> 6;
#endif
}
// -------------------------


static inline ulong bin_to_rad2i(ulong re, ulong im)
// binary ( re + i * im ) --> radix(2*i)
{
    re = bin_real_to_rad2i( re );
    im = bin_imag_to_rad2i( im );
    return  re + im;  // digits are disjoint
}
// -------------------------



static inline ulong rad2i_to_bin_real(ulong x)
// radix(2*i) (must be purely real) --> binary
{
    x >>=2;  // ignore digit after point
    x = bit_unzip0_pairs(x);
    x = radm4_to_bin(x);
    return x;
}
// -------------------------


static inline ulong rad2i_to_bin_imag(ulong x)
// radix(2*) (must be purely imaginary) --> binary
{
    ulong fd = x & 3;  // final digit
    x >>= 4;  // remove final and first real digit
    x = bit_unzip0_pairs(x);
    x = radm4_to_bin(x) << 1;
    x -= (fd>>1);  // final digit
    return x;
}
// -------------------------



static inline void rad2i_to_bin(ulong z, ulong &re, ulong &im)
// radix(2*i) --> binary ( re + i * im )
{
#if 1
    // Use periodicity of real and imag part in powers of radix:

#if  BITS_PER_LONG == 64
    const ulong pr = 0x3333333333333333UL;
#else
    const ulong pr = 0x33333333UL;
#endif

    ulong fd = z & 3;  // final digit
    z >>= 2;  // remove final digit

    ulong tr = z & pr;
    tr = bit_unzip0_pairs(tr);
    re = radm4_to_bin(tr);

    z >>= 2;  // remove first real digit
    ulong ti = z & pr;
    ti = bit_unzip0_pairs(ti);
    ti = radm4_to_bin(ti) << 1;
    ti -= (fd>>1);  // final digit
    im = ti;

#else
    // Expansion by powers of radix:

    ulong fd = z & 3;  // final digit
    z >>= 2;  // remove final digit

    ulong tr = 0,  ti = 0;
    ulong rdr = 1, rdi = 2;  // power of radix
    do
    {
        tr += rdr * (z&3);
        z >>= 2;
        ti += rdi * (z&3);
        z >>= 2;
        // Next radix power, two steps at once,
        // use (a+i*b) * (2*i)^2 == ( - 4*b - 4*i*a ):
        rdr = -(rdr<<2);
        rdi = -(rdi<<2);
    }
    while ( z );
    ti -= fd>>1;  // if final digit set (then fd==2), subtract i

    re = tr;  im = ti;
#endif
}
// -------------------------


static inline bool rad2i_is_real(ulong z)
// Return whether z is purely real.
{
#if  BITS_PER_LONG == 64
    const ulong m = 0x3333333333333333UL;
#else
    const ulong m = 0x33333333UL;
#endif
    return  ( (z & m)==0 );
}
// -------------------------


static inline bool rad2i_is_imag(ulong z)
// Return whether z is purely imaginary.
{
#if  BITS_PER_LONG == 64
    const ulong m = 0xccccccccccccccccUL;
#else
    const ulong m = 0xccccccccUL;
#endif
    return  ( (z & m)==0 );
}
// -------------------------


#endif  // !defined HAVE_RADIX_2I_H__
