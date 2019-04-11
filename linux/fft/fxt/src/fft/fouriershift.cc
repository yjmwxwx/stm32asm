// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "complextype.h"
#include "aux0/sincos.h"

#include <cmath>


void
fourier_shift(Complex *a, ulong n, double v)
// auxiliary routine for FFTs:
// used for recursive FFTs and matrix FFTs (MFA)
//
// n := length of array
//
// a[k] *= exp(k*v*sqrt(-1)*2*pi/n) for k = 0...n-1
{
//    if ( v==0.0 )  return;  // nothing to do

    const double phi0 = v * 2.0 * M_PI / (double)n;
    double ph = 0.0;
    for (ulong k=1; k<n; ++k)  // k==0 skipped
    {
        double s, c;
//        SinCos(phi0*k, &s, &c);
        ph += phi0;
        SinCos(ph, &s, &c);
        a[k] *= Complex(c, s);
    }
}
// -------------------------


void
fourier_shift(double *fr, double *fi, ulong n, double v)
// auxiliary routine for FFTs:
// used for recursive FFTs and matrix FFTs (MFA)
//
// n := length of array
//
// a[k] *= exp(k*v*sqrt(-1)*2*pi/n) for k = 0...n-1
{
//    if ( v==0.0 )  return;  // nothing to do

    const double phi0 = v * 2.0 * M_PI / (double)n;
    double ph = 0.0;
    for (ulong k=1; k<n; ++k)  // k==0 skipped
    {
        double s, c;
//        SinCos(phi0*k, &s, &c);
        ph += phi0;
        SinCos(ph, &s, &c);
        Complex t =  Complex(fr[k], fi[k]) * Complex(c, s);
        fr[k] = t.real();
        fi[k] = t.imag();
    }
}
// -------------------------


void
fourier_shift_imag0(double *fr, double *fi, ulong n, double v)
// auxiliary routine for FFTs:
// used for matrix FFTs (MFA)
//
// n := length of array
//
// (fr[k], fi[k]) *= exp(k*v*sqrt(-1)*2*pi/n) for k = 0...n-1
//
// assume fi[] is zero
{
//    if ( v==0.0 )  return;  // nothing to do

    const double phi0 = v * 2.0 * M_PI / (double)n;
    double ph = 0.0;
    for (ulong k=1; k<n; ++k)  // k==0 skipped
    {
        double s, c;
//        SinCos(phi0*k, &s, &c);
        ph += phi0;
        SinCos(ph, &s, &c);
        double t =  fr[k];
        fr[k] = c * t;
        fi[k] = s * t;
    }
}
// -------------------------


void
fourier_shift(double *fr, double *fi, ulong n, double v, ulong k0, ulong kn)
// auxiliary routine for FFTs
//
// (fr[k], fi[k]) *= exp((k0+k)*v*sqrt(-1)*2*pi/n) for k = 0...kn-1
// n := length of array
{
//    if ( v==0.0 )  return;  // nothing to do

    const double phi0 = v * 2.0 * M_PI / (double)n;
    double ph = phi0*(double)k0;
    for (ulong k=0; k<kn; ++k)
    {
        double s, c;
//        SinCos(phi0*(k0+k), &s, &c);
        SinCos(ph, &s, &c);
        ph += phi0;
        Complex t =  Complex(fr[k], fi[k]) * Complex(c, s);
        fr[k] = t.real();
        fi[k] = t.imag();
    }
}
// -------------------------


void
fourier_shift_imag0(double *fr, double *fi, ulong n, double v, ulong k0, ulong kn)
// auxiliary routine for FFTs
// (fr[k], fi[k]) *= exp((k0+k)*v*sqrt(-1)*2*pi/n) for k = 0...kn-1
// assume fi[] is zero
{
//    if ( v==0.0 )  return;  // nothing to do

    const double phi0 = v * 2.0 * M_PI / (double)n;
    double ph = phi0*(double)k0;
    for (ulong k=0; k<kn; ++k)
    {
        double s, c;
//        SinCos(phi0*(k0+k), &s, &c);
        SinCos(ph, &s, &c);
        ph += phi0;
        double t =  fr[k];
        fr[k] = c * t;
        fi[k] = s * t;
    }
}
// -------------------------
