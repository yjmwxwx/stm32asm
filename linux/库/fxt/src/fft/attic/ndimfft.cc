// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bit2pow.h"  // ld()
#include "fft/fft.h"

#include "jjassert.h"
// fixme: yucky code, should be redone

#include "fxttypes.h"  // ulong


static double *wr, *wi;  // workspace

// always call ndim_fft(), do not call e.g. fft_3dim() directly !

void fft_2dim(double *fr, double *fi, ulong d1, ulong d2, int is);
void fft_3dim(double *fr, double *fi, ulong d1, ulong d2, ulong d3, int is);
void fft_4dim(double *fr, double *fi, ulong d1, ulong d2, ulong d3, ulong d4, int is);
void fft_5dim(double *fr, double *fi, ulong d1, ulong d2, ulong d3, ulong d4, ulong d5, int is);

#define FFT(re, im, ldn, is)  fht_fft(re, im, ldn, is)


void
ndim_fft(double *fr, double *fi,
         ulong ndim, const ulong *ldn,
         int is)
// Compute n-dimensional FFT.
// ndim must be 1, 2, 3, 4, or 5
// ldn[] contains base 2 logarithms of dimensions
{
    jjassert( (ndim>=1) && (ndim<=5) );  // invalid ndim in ndim_fft().

    if (ndim==1)  // 1-dim FFT
    {
        FFT(fr, fi, ldn[0], is);
        return;
    }

    // find max(d2, d3, ..., dn):
    ulong nw=0;
    for (ulong k=0; k<ndim; ++k)  if ( ldn[k]>nw )  nw = ldn[k];
    nw = (1UL<<nw);

    wr = new double[2*nw];
    wi = wr + nw;

    ulong d1 = (1UL<<ldn[0]);
    ulong d2 = (1UL<<ldn[1]);
    if (ndim==2)  fft_2dim(fr, fi, d1, d2, is);
    else
    {
        ulong d3 = (1UL<<ldn[2]);
        if (ndim==3)  fft_3dim(fr, fi, d1, d2, d3, is);
        else
        {
            ulong d4 = (1UL<<ldn[3]);
            if (ndim==4)  fft_4dim(fr, fi, d1, d2, d3, d4, is);
            else
            {
                ulong d5 = (1UL<<ldn[4]);
                if (ndim==5)  fft_5dim(fr, fi, d1, d2, d3, d4, d5, is);
            }
        }
    }

    delete [] wr;
}
// -------------------------


void
fft_2dim(double *fr, double *fi,
         ulong d1, ulong d2,
         int is)
// Compute 2-dimensional FFT.
{
    ulong n = d1*d2;

    // rows:
    ulong ld1 = ld(d1);
    for (ulong k=0; k<n; k+=d1)  FFT(fr+k, fi+k, ld1, is);

    // columns:
    for (ulong k=0; k<d1; k++)  skip_fft(fr+k, fi+k, d2, d1, wr, wi, is);
}
// -------------------------



void
fft_3dim(double *fr, double *fi,
         ulong d1, ulong d2, ulong d3,
         int is)
// Compute 3-dimensional FFT.
{
    ulong d12 = d1*d2;
    ulong n = d12*d3;

    for (ulong k=0; k<n; k+=d12)  fft_2dim(fr+k, fi+k, d1, d2, is);

    for (ulong k=0; k<d12; k++)  skip_fft(fr+k, fi+k, d3, d12, wr, wi, is);
}
// -------------------------



void
fft_4dim(double *fr, double *fi,
         ulong d1, ulong d2, ulong d3, ulong d4,
         int is)
// Compute 4-dimensional FFT.
{
    ulong d123 = d1*d2*d3;
    ulong n = d123*d4;

    for (ulong k=0; k<n; k+=d123)  fft_3dim(fr+k, fi+k, d1, d2, d3, is);

    for (ulong k=0; k<d123; k++)  skip_fft(fr+k, fi+k, d4, d123, wr, wi, is);
}
// -------------------------



void
fft_5dim(double *fr, double *fi,
         ulong d1, ulong d2, ulong d3, ulong d4, ulong d5,
         int is)
// Compute 5-dimensional FFT.
{
    ulong d1234 = d1*d2*d3*d4;
    ulong n = d1234*d5;

    for (ulong k=0; k<n; k+=d1234)  fft_4dim(fr+k, fi+k, d1, d2, d3, d4, is);

    for (ulong k=0; k<d1234; k++)  skip_fft(fr+k, fi+k, d5, d1234, wr, wi, is);
}
// -------------------------

