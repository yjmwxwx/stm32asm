// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>  // M_PI

#include "fft/fft.h"
#include "complextype.h"
#include "aux0/cmult.h"
#include "aux0/sumdiff.h"
#include "perm/zip.h"
#include "aux0/sincos.h"
#include "perm/reverse.h"  // reverse_0()
#include "fxttypes.h"  // ulong


void
wrap_real_complex_fft(double *f, ulong ldn/*, int is=+1*/)
// Real to complex FFT (R2CFT)
// Sign hard-coded to is=+1
//
// Ordering of output:
// f[0]     = re[0]   (DC part, purely real)
// f[1]     = re[n/2] (nyquist freq, purely real)
// f[2]     = re[1]
// f[3]     = im[1]
// f[4]     = re[2]
// f[5]     = im[2]
//         ...
// f[2*i]   = re[i]
// f[2*i+1] = im[i]
//         ...
// f[n-2]   = re[n/2-1]
// f[n-1]   = im[n/2-1]
//
// Equivalent to:
// { fht_real_complex_fft(f, ldn, is); zip(f, n); }
//
{
    if ( ldn==0 )  return;

    fht_fft((Complex *)f, ldn-1, +1);  // jjcast

    const ulong n = 1UL<<ldn;
    const ulong nh = n/2, n4 = n/4;
    const double phi0 = M_PI / (double)nh;
    for (ulong i=1; i<n4; i++)
    {
        ulong i1 = 2 * i;   // re low [2, 4, ..., n/2-2]
        ulong i2 = i1 + 1;  // im low [3, 5, ..., n/2-1]

        ulong i3 = n - i1;  // re hi  [n-2, n-4, ..., n/2+2]
        ulong i4 = i3 + 1;  // im hi  [n-1, n-3, ..., n/2+3]

        double f1r, f2i;
        sumdiff05(f[i3], f[i1], f1r, f2i);

        double f2r, f1i;
        sumdiff05(f[i2], f[i4], f2r, f1i);

        double c, s;
        double phi = (double)i * phi0;
        SinCos(phi, &s, &c);

        double tr, ti;
        cmult(c, s, f2r, f2i, tr, ti);

        // f[i1] = f1r + tr;  // re low
        // f[i3] = f1r - tr;  // re hi
        // =^=
        sumdiff(f1r, tr, f[i1], f[i3]);


        // f[i4] = is * (ti + f1i);  // im hi
        // f[i2] = is * (ti - f1i);  // im low
        // =^=
        sumdiff( ti,  f1i, f[i4], f[i2]);

//        if ( is>0 )  sumdiff( ti,  f1i, f[i4], f[i2]);
//        else         sumdiff(-ti,  f1i, f[i2], f[i4]);
    }
    sumdiff(f[0], f[1]);

//    if ( nh>=2 )  f[nh+1] *= is;
}
// -------------------------


void
wrap_complex_real_fft(double *f, ulong ldn/*, int is=+1*/)
// Complex to real FFT (C2RFT).
// Sign hard-coded to is=+1
//
// Inverse of wrap_real_complex_fft().
// Ordering of input is same as for
//   the output of wrap_real_complex_fft()
{
    if ( ldn==0 )  return;

    const ulong n = 1UL<<ldn;
    const ulong nh = n/2, n4 = n/4;
    const double phi0 = -M_PI / (double)nh;
    for (ulong i=1; i<n4; i++)
    {
        ulong i1 = 2 * i;   // re low [2, 4, ..., n/2-2]
        ulong i2 = i1 + 1;  // im low [3, 5, ..., n/2-1]

        ulong i3 = n - i1;  // re hi  [n-2, n-4, ..., n/2+2]
        ulong i4 = i3 + 1;  // im hi  [n-1, n-3, ..., n/2+3]

        double f1r, f2i;
        // double f1r =  f[i1] + f[i3];  // re symm
        // double f2i =  f[i1] - f[i3];  // re asymm
        // =^=
        sumdiff(f[i1], f[i3], f1r, f2i);

        double f2r, f1i;
        // double f2r = -f[i2] - f[i4];  // im symm
        // double f1i =  f[i2] - f[i4];  // im asymm
        // =^=
        sumdiff(-f[i4], f[i2], f1i, f2r);

        double c, s;
        double phi = (double)i * phi0;
        SinCos(phi, &s, &c);

        double tr, ti;
        cmult(c, s, f2r, f2i, tr, ti);

        // f[i1] = f1r + tr;  // re low
        // f[i3] = f1r - tr;  // re hi
        // =^=
        sumdiff(f1r, tr, f[i1], f[i3]);

        // f[i2] = ti - f1i;  // im low
        // f[i4] = ti + f1i;  // im hi
        // =^=
        sumdiff(ti, f1i, f[i4], f[i2]);
    }
    sumdiff(f[0], f[1]);

    if ( nh>=2 )  { f[nh] *= 2.0; f[nh+1] *= 2.0; }

    fht_fft((Complex *)f, ldn-1, -1);  // jjcast
//    if ( is<0 )  reverse_0(f, n);
}
// -------------------------
