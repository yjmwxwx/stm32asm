// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "realfft/realfft.h"
#include "fft/fft.h"

#include "bits/bit2pow.h"  // ld()
#include "aux1/copy.h"

#include "fxttypes.h"  // ulong
#include "complextype.h"  // Complex


#define  FFT(re, im, ldn, is)   fht_fft(re, im, ldn, is)
#define  FFT0(re, im, ldn, is)  fht_fft0(re, im, ldn, is)

#define  FFTC(f, ldn, is)   fht_fft(f, ldn, is)
#define  FFT0C(f, ldn, is)  fht_fft0(f, ldn, is)


void
column_ffts(double *fr, double *fi, ulong nr, ulong nc, int is,
            int zp, double *tmpr, double *tmpi)
//
// nr x nc matrix (nr rows, nc columns)
// length of each col is nr
// length of each row is nc
//
{
    double *wr, *wi;
    if ( tmpr )  wr = tmpr;
    else         wr = new double[nr];
    if ( tmpi )  wi = tmpi;
    else         wi = new double[nr];

    ulong rh = (nr>>1);
    ulong ldr = ld(nr);
    double *pr = fr,  *pi = fi;
    for (ulong k=0; k<nc; ++k)
    {
        if ( zp )  //  skip_fft0(pr, pi, nr, nc, wr, wi, is);
        {
            skip_copy(pr, wr, rh, nc);
            skip_copy(pi, wi, rh, nc);
            null(wr+rh, rh);
            null(wi+rh, rh);
            FFT0(wr, wi, ldr, is);
        }
        else  // skip_fft(pr, pi, nr, nc, wr, wi, is);
        {
            skip_copy(pr, wr, nr, nc);
            skip_copy(pi, wi, nr, nc);
            FFT(wr, wi, ldr, is);
        }

        skip_copy_back(wr, pr, nr, nc);
        skip_copy_back(wi, pi, nr, nc);

        pr++;
        pi++;
    }

    if ( !tmpr )  delete [] wr;
    if ( !tmpi )  delete [] wi;
}
// -------------------------


void
column_ffts(Complex *f, ulong nr, ulong nc, int is, int zp, Complex *tmp)
//
// nr x nc matrix (nr rows, nc columns)
// length of each col is nr
// length of each row is nc
//
{
    Complex*w;
    if ( tmp )  w = tmp;
    else        w = new Complex[nr];

    ulong rh = (nr>>1);
    ulong ldr = ld(nr);
    Complex *p = f;
    for (ulong k=0; k<nc; ++k)
    {
        if ( zp )  //  skip_fft0(p, nr, nc, wr, wi, is);
        {
            skip_copy(p, w, rh, nc);
            null(w+rh, rh);
            FFT0C(w, ldr, is);
        }
        else  // skip_fft(pr, pi, nr, nc, wr, wi, is);
        {
            skip_copy(p, w, nr, nc);
            FFTC(w, ldr, is);
        }

        skip_copy_back(w, p, nr, nc);

        p++;
    }

    if ( !tmp )  delete [] w;
}
// -------------------------


void
column_real_complex_ffts(double *f, ulong nr, ulong nc, int zp, double *tmp)
//
// nr x nc matrix (nr rows, nc columns)
// length of each col is nr
// length of each row is nc
//
{
    double *tr;
    if ( tmp )  tr = tmp;
    else        tr = new double[nr];

    for (ulong k=0; k<nc; ++k)
    {
        if ( zp ) skip_real_complex_fft0(f, nr, nc, tr);
        else      skip_real_complex_fft(f, nr, nc, tr);
        f++;
    }

    if ( !tmp )  delete [] tr;
}
// -------------------------


void
column_complex_real_ffts(double *f, ulong nr, ulong nc, double *tmp)
//
// nr x nc matrix (nr rows, nc columns)
// length of each col is nr
// length of each row is nc
//
{
    double *tr;
    if ( tmp )  tr = tmp;
    else        tr = new double[nr];

    ulong ldr = ld(nr);
    for (ulong k=0; k<nc; ++k)
    {
//        skip_complex_real_fft(f, nr, nc, tr);
        //  ==
        skip_copy(f, tr, nr, nc);
        fht_complex_real_fft(tr, ldr);
        skip_copy_back(tr, f, nr, nc);

        f++;
    }

    if ( !tmp )  delete [] tr;
}
// -------------------------


void
column_complex_imag_ffts(const double *fr, double *fi, ulong nr, ulong nc, double *tmp)
//
// nr x nc matrix (nr rows, nc columns)
// length of each col is nr
// length of each row is nc
//
// only the imag part of the result is computed
//
{
    double *tr;
    if ( tmp )  tr = tmp;
    else        tr = new double[2*nr];
    double *ti = tr + nr;

    ulong ldr = ld(nr);
    for (ulong k=0; k<nc; ++k)
    {
        skip_copy(fr, tr, nr, nc);
        skip_copy(fi, ti, nr, nc);

        imaginator(tr, ti, nr, +1);  // note: isign dependence
        fht_complex_real_fft(ti, ldr);

        skip_copy_back(ti, fi, nr, nc);

        fr++;
        fi++;
    }

    if ( !tmp )  delete [] tr;
}
// -------------------------

