// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "realfft/realfft.h"
#include "aux0/sumdiff.h"
#include "perm/reverse.h"
#include "fxttypes.h"  // ulong

void
easy_ordering_real_complex_fft(double *f, ulong ldn, int is/*=+1*/)
//
// isign = +1
//
// ordering of output is:
// f[0]     = re[0]
// f[1]     = re[1]
//         ...
// f[n/2-1] = re[n/2-1]
// f[n/2]   = re[n/2] (==nyquist freq)
//
// f[n/2+1] = im[1]
// f[n/2+2] = im[2]
//         ...
// f[n-1]   = im[n/2-1]
//
// corresponding real and imag parts (with the exception of
// zero and nyquist freq) are found in f[i] and f[n/2+i]
//
{
    fht_real_complex_fft(f, ldn, is);

    if ( ldn>=2 )
    {
        ulong nh = (1UL<<ldn)/2;
        reverse(f+nh+1, nh-1);
    }
}
// -------------------------


void
easy_ordering_real_complex_fft0(double *f, ulong ldn, int is/*=+1*/)
//
// version for zero padded data
//
// ordering of output:
// see easy_ordering_real_complex_fft()
//
{
    fht_real_complex_fft0(f, ldn, is);

    if ( ldn>=2 )
    {
        ulong nh = (1UL<<ldn)/2;
        reverse(f+nh+1, nh-1);
    }
}
// -------------------------

void
easy_ordering_complex_real_fft(double *f, ulong ldn, int is/*=+1*/)
//
// isign = +1
//
// expected ordering of input:
// like the output of easy_ordering_real_complex_fft()
//
{
    if ( ldn>=2 )
    {
        ulong nh = (1UL<<ldn)/2;
        reverse(f+nh+1, nh-1);
    }

    fht_complex_real_fft(f, ldn, is);
}
// -------------------------
