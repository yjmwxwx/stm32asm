// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fft/fft.h"  // fourier_shift()

#include "aux1/copy.h"

#include "fxtalloca.h"

#include "fxttypes.h"
#include "complextype.h"  // Complex


static void
recursive_fft_dit2_core(const Complex *a, ulong n, Complex *x, int is)
{
    if ( n==1 )  { x[0] = a[0]; return; }

    ulong nh = n/2;
    ALLOCA(Complex, b, nh);
    ALLOCA(Complex, c, nh);
    ALLOCA(Complex, ev, nh);
    ALLOCA(Complex, od, nh);

    for (ulong k=0, j=0;  j<nh;  k+=2, j++)
    {
        ev[j] = a[k];
        od[j] = a[k+1];
    }

    recursive_fft_dit2_core(ev, nh, b, is);
    recursive_fft_dit2_core(od, nh, c, is);

    fourier_shift(c, nh, is*0.5);

    for (ulong k=0; k<nh; k++)
    {
        x[k]    = b[k] + c[k];
        x[k+nh] = b[k] - c[k];
    }
}
// -------------------------

void
recursive_fft_dit2(Complex *a, ulong ldn, int is)
//
// very inefficient, just to demonstrate the
// recursive fast fourier transform
//
{
    ulong n = (1UL<<ldn);
    ALLOCA(Complex, x, n);
    recursive_fft_dit2_core(a, n, x, is);
    acopy(x, a, n);
}
// -------------------------


static void
recursive_fft_dif2_core(const Complex *a, ulong n, Complex *x, int is)
{
    if ( n==1 )  { x[0] = a[0]; return; }

    ulong nh = n/2;
    ALLOCA(Complex, b, nh);
    ALLOCA(Complex, c, nh);
    ALLOCA(Complex, le, nh);
    ALLOCA(Complex, ri, nh);

    for (ulong j=0; j<nh; j++)
    {
        le[j] = a[j];
        ri[j] = a[nh+j];
    }

    for (ulong k=0; k<nh; k++)
    {
        Complex t =   (le[k] + ri[k]);
        ri[k] =       (le[k] - ri[k]);
        le[k] = t;
    }

    fourier_shift(ri, nh, is*0.5);

    recursive_fft_dif2_core(le, nh, b, is);
    recursive_fft_dif2_core(ri, nh, c, is);

    for (ulong k=0, j=0;  k<nh;  k++, j+=2)
    {
        x[j] =   b[k];
        x[j+1] = c[k];
    }
}
// -------------------------

void
recursive_fft_dif2(Complex *a, ulong ldn, int is)
//
// very inefficient, just to demonstrate the
// recursive fast fourier transform
//
{
    ulong n = (1UL<<ldn);
    ALLOCA(Complex, x, n);

    recursive_fft_dif2_core(a, n, x, is);
    acopy(x, a, n);
}
// -------------------------

