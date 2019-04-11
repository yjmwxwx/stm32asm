#if !defined  HAVE_DYADICCNVL_H__
#define       HAVE_DYADICCNVL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "walsh/walshwak.h"
#include "restrict.h"

// define to use walsh_gray() for convolution (default: not defined)
//#define USE_WALSH_GRAY
// See end of file
#ifdef USE_WALSH_GRAY
#include "walsh/walshgray.h"
#include "bits/grsnegative.h"
#endif


template <typename Type>
void dyadic_convolution(Type * restrict f, Type * restrict g, ulong ldn)
// Dyadic convolution (XOR-convolution):  h[] of f[] and g[]:
//   h[k] = sum( i XOR j == k,  f[i]*g[k] )
// Result is written to g[].
// ldn := base-2 logarithm of the array length
//.
// Convolution diagram:
//   +--   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
//   |
//   0:    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
//   1:    1  0  3  2  5  4  7  6  9  8 11 10 13 12 15 14
//   2:    2  3  0  1  6  7  4  5 10 11  8  9 14 15 12 13
//   3:    3  2  1  0  7  6  5  4 11 10  9  8 15 14 13 12
//   4:    4  5  6  7  0  1  2  3 12 13 14 15  8  9 10 11
//   5:    5  4  7  6  1  0  3  2 13 12 15 14  9  8 11 10
//   6:    6  7  4  5  2  3  0  1 14 15 12 13 10 11  8  9
//   7:    7  6  5  4  3  2  1  0 15 14 13 12 11 10  9  8
//   8:    8  9 10 11 12 13 14 15  0  1  2  3  4  5  6  7
//   9:    9  8 11 10 13 12 15 14  1  0  3  2  5  4  7  6
//  10:   10 11  8  9 14 15 12 13  2  3  0  1  6  7  4  5
//  11:   11 10  9  8 15 14 13 12  3  2  1  0  7  6  5  4
//  12:   12 13 14 15  8  9 10 11  4  5  6  7  0  1  2  3
//  13:   13 12 15 14  9  8 11 10  5  4  7  6  1  0  3  2
//  14:   14 15 12 13 10 11  8  9  6  7  4  5  2  3  0  1
//  15:   15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
{
#ifdef USE_WALSH_GRAY

    walsh_gray(f, ldn);
    walsh_gray(g, ldn);
    const ulong n = (1UL<<ldn);
    for (ulong k=0; k<n; ++k)
    {
        Type t = g[k] * f[k];
        if ( grs_negative_q(k) )  t = -t;
        g[k] = t;
    }
    inverse_walsh_gray(g, ldn);

#else  // def USE_WALSH_GRAY

    walsh_wak(f, ldn);
    walsh_wak(g, ldn);
    const ulong n = (1UL<<ldn);
    for (ulong k=0; k<n; ++k)  g[k] *= f[k];
    walsh_wak(g, ldn);

#endif  // def USE_WALSH_GRAY
}
// -------------------------


template <typename Type>
void dyadic_auto_convolution(Type *f, ulong ldn)
// Dyadic self-convolution.
// ldn := base-2 logarithm of the array length
{
#ifdef USE_WALSH_GRAY

    walsh_gray(f, ldn);
    const ulong n = (1UL<<ldn);
    for (ulong k=0; k<n; ++k)
    {
        Type t = f[k] * f[k];
        if ( grs_negative_q(k) )  t = -t;
        f[k] = t;
    }
    inverse_walsh_gray(f, ldn);

#else  // def USE_WALSH_GRAY

    walsh_wak(f, ldn);
    const ulong n = (1UL<<ldn);
    for (ulong k=0; k<n; ++k)  f[k] *= f[k];
    walsh_wak(f, ldn);

#endif  // def USE_WALSH_GRAY
}
// -------------------------

#undef USE_WALSH_GRAY


// Whether Gray-variant is advantageous depends on used machine:
// timings for radix-2 wak transform:

// AMD K6/2 366 MHz with 66 MHz EDO-RAM:
//  ldn=20  n=1048576 repetitions: m=5 memsize=16384 kiloByte
//                   reverse(f,n2);     dt=0.0418339      rel=       1
//                 walsh_wak(f,ldn);    dt=0.505863       rel= 12.0922
//                walsh_gray(f,ldn);    dt=0.378223       rel= 9.04108
//    dyadic_convolution(f, g, ldn);    dt= 1.54834       rel= 37.0117 << wak
//    dyadic_convolution(f, g, ldn);    dt= 1.19474       rel= 28.5436 << gray
//
//  ldn=21  n=2097152 repetitions: m=5 memsize=32768 kiloByte
//                   reverse(f,n2);     dt=0.0838011     rel=       1
//                 walsh_wak(f,ldn);    dt=1.07741       rel= 12.8567
//                walsh_gray(f,ldn);    dt=0.796644      rel= 9.50636
//    dyadic_convolution(f, g, ldn);    dt=3.28062       rel= 39.1477 << wak
//    dyadic_convolution(f, g, ldn);    dt=2.49583       rel= 29.7401 << gray

// AMD Athlon 2000 MHz with 133 MHz DDR-RAM:
// Gray-variant consistently 20% _slower_


#endif  // !defined HAVE_DYADICCNVL_H__
