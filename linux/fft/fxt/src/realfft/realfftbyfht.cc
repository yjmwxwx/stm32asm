// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fht/fht-default.h"
#include "aux0/sumdiff.h"

#include "fxttypes.h"  // ulong
//#include "complextype.h"

void
fht_real_complex_fft(double *f, ulong ldn, int is/*=+1*/)
// Real to complex FFT.
//
// Ordering of output:
// f[0]     = re[0]
// f[1]     = re[1]
//         ...
// f[n/2-1] = re[n/2-1]
// f[n/2]   = re[n/2](==nyquist freq)
//
// f[n/2+1] = im[n/2-1]  (wrt. complex FFT with is=+1)
// f[n/2+2] = im[n/2-2]
//         ...
// f[n-1]   = im[1]
//
// corresponding real and imag parts (with the exception of
// zero and nyquist freq) are found in f[i] and f[n-i]
//
// note that the order of imaginary parts
// is reversed wrt. fft_real_complex_fft()
//
{
    fht(f, ldn);

    const ulong n = (1UL<<ldn);

    if ( is>0 )  for (ulong i=1, j=n-1;  i<j;  i++, j--)  sumdiff05(f[i], f[j]);
    else         for (ulong i=1, j=n-1;  i<j;  i++, j--)  sumdiff05_r(f[i], f[j]);
}
// -------------------------


void
fht_real_complex_fft0(double *f, ulong ldn, int is/*=+1*/)
// Real to complex FFT.
//
// Version for zero padded data
// Ordering of output as with fht_real_complex_fft()
{
    fht0(f, ldn);

    const ulong n = (1UL<<ldn);

    if ( is>0 )  for (ulong i=1, j=n-1;  i<j;  i++, j--)  sumdiff05(f[i], f[j]);
    else         for (ulong i=1, j=n-1;  i<j;  i++, j--)  sumdiff05_r(f[i], f[j]);
}
// -------------------------


void
fht_complex_real_fft(double *f, ulong ldn, int is/*=+1*/)
// Complex to real FFT.
// Inverse of fht_real_complex_fft() for _same_ sign of transform (is).
//
// Ordering of input like the output of fht_real_complex_fft()
{
    const ulong n = (1UL<<ldn);

    if ( is>0 )  for (ulong i=1, j=n-1;  i<j;  i++, j--)  sumdiff(f[i], f[j]);
    else         for (ulong i=1, j=n-1;  i<j;  i++, j--)  diffsum(f[i], f[j]);

    fht(f, ldn);
}
// -------------------------


void
realisator(double *gr, const double *gi, ulong n, int is)
// Let gr[], gi[] be the FFT of a complex sequence.
// realisator() isolates the part of the data corresponding
// to the real part of the original sequence in gr[]
//
// Using the code fragment:
// { realisator(gr, gi, n, is); fht_complex_real_fft(gr, ldn); }
// one would get (only) the real part of the original sequence in gr[]
//
{
    if ( is>0 )
    {
        for (ulong i=1, j=n-1;  i<j;  ++i, --j)
        {
            double rs = 0.5*(gr[i]+gr[j]);
            double ia = 0.5*(gi[i]-gi[j]);
            gr[i] = rs;
            gr[j] = ia;
        }
    }
    else
    {
        for (ulong i=1, j=n-1;  i<j;  ++i, --j)
        {
            double rs  = 0.5*(gr[i]+gr[j]);
            double mia = 0.5*(gi[j]-gi[i]);  // note the swapped indices
            gr[i] = rs;
            gr[j] = mia;
        }
    }
}
// -------------------------


void
imaginator(const double *gr, double *gi, ulong n, int is)
// Let gr[], gi[] be the FFT of a complex sequence.
// imaginator() isolates the part of the data corresponding
// to the imag part of the original sequence in gi[]
//
// Using the code fragment:
// { imaginator(gr, gi, n, is); fht_complex_real_fft(gi, ldn); }
// one gets (only) the imag part of the original sequence in gi[]
{
    realisator(gi, gr, n, -is);  // note the swapped real/imag part
}
// -------------------------


void
separator(double *gr, double *gi, ulong n, int is)
// Let gr[], gi[] be the FFT of a complex sequence.
// separator() isolates the parts of the data corresponding
// to the real/imag part of the original sequence in gr[]/gi[]
//
// Using the code fragment:
// { separator(gr, gi, n, is);
//  fht_complex_real_fft(gr, ldn); fht_complex_real_fft(gi, ldn); }
// one would get the real/imag parts of the original sequence in gr[]/gi[]
//
{
    if ( is>0 )
    {
        for (ulong i=1, j=n-1;  i<j;  ++i, --j)
        {
            double sr, ar;
            sumdiff05(gr[i], gr[j], sr, ar);

            double si, ai;
            sumdiff05(gi[i], gi[j], si, ai);

            gr[i] = sr;
            gr[j] = ai;

            gi[i] = si;
            gi[j] = -ar;
        }
    }
    else
    {
        for (ulong i=1, j=n-1;  i<j;  ++i, --j)
        {
            double sr, ar;
            sumdiff05(gr[i], gr[j], sr, ar);

            double si, ai;
            sumdiff05(gi[i], gi[j], si, ai);

            gr[i] = sr;
            gr[j] = -ai;

            gi[i] = si;
            gi[j] = ar;
        }
    }
}
// -------------------------
