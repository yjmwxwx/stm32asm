// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "chirpzt/chirpzt.h"
#include "convolution/complexconvolution.h"

#include "bits/bit2pow.h"  // ld()
#include "aux1/arith1.h"    // negate()

//#include "aux1/aux1double.h"  // ri_multiply()
#include "aux0/cmult.h"  // cmult(), used in ri_multiply()

#include "aux0/sincos.h"
#include "aux0/csincos.h"

#include "aux1/copy.h"

#include "fxttypes.h"  // ulong
#include "complextype.h"  // Complex

#include <cmath>  // M_PI



static inline void
make_fft_fract_chirp(Complex *w, double v, ulong n, ulong nn)
// For k=0..nn-1:   w[k] == exp(v*sqrt(-1)*k*k*2*pi*/n/2)
{
//    const double phi = v*2.0*M_PI/(double)n/2.0;
    const double phi = v*M_PI/(double)n;
    ulong n2 = 2*n;
    ulong np = 0;
    for (ulong k=0; k<nn; ++k)
    {
        w[k] = SinCos(phi*(double)np);

        np += ((k<<1)+1);  // np == (k*k)%n2
        if ( np>=n2 )  np -= n2;
    }
}
// -------------------------


void
fft_fract(Complex *x, ulong n, double v)
// Fractional (fast) Fourier transform.
//
// For complex array c[0...n]
// compute \sum_{x=0}^{n}{c_x*exp(is*v*2*i*\pi*x*k/n)}
//  (for v==1.0 this is just the usual FFT)
//
// Use n*k == n^2/2 + k^2/2 - (k-n)^2/2
// See: Nussbaumer: "Fast Fourier Transform and Convolution Algorithms", chap.5, p.113ff
// Could use n*k == - n^2/2 - k^2/2 + (k+n)^2/2 instead.
//
// Worst case if n=2^x+1:
//   then nn=2*2^x
//   work is about 6 times of an FFT of length 2^x
//   and allocated workspace =2*nn
{
    const ulong ldnn = 1 + ld((n<<1)-1);
    const ulong nn = (1UL<<ldnn);  // smallest power of 2 >= 2*n

    Complex *f = new Complex[nn];
    acopy(x, f, n);
    null(f+n, nn-n);

    Complex *w = new Complex[nn];
    make_fft_fract_chirp(w, v, n, nn);

//    multiply(w, f, n);
    for (ulong j=0; j<n; ++j)  f[j] *= w[j];

//    negate(wi, nn);
    for (ulong j=0; j<nn; ++j)  w[j] = conj(w[j]);

    fft_complex_convolution(w, f, ldnn);

    make_fft_fract_chirp(w, v, n, nn);

//    multiply(f, w, nn);
    for (ulong j=0; j<n; ++j)  w[j] *= f[j];

    acopy(w+n, x, n);
    delete [] w;
    delete [] f;
}
// -------------------------



static inline void
make_fft_fract_chirp(double *wr, double *wi, double v, ulong n, ulong nn)
// For k=0..nn-1:   Complex(wr[k], wi[k]) == exp(v*sqrt(-1)*k*k*2*pi*/n/2)
{
//    const double phi = v*2.0*M_PI/n/2;
    const double phi = v*M_PI/(double)n;
    ulong n2 = 2*n;
    ulong np=0;
    for (ulong k=0; k<nn; ++k)
    {
        double c, s;
        SinCos(phi*(double)np, &s, &c);
        wr[k] = c;
        wi[k] = s;

        np += ((k<<1)+1);  // np == (k*k)%n2
        if ( np>=n2 )  np -= n2;
    }
}
// -------------------------



static void ri_multiply(const double *fr, const double *fi,
                        double *gr, double *gi, ulong n)
// complex multiply array g[] by f[]:
//  Complex(gr[], gi[]) *= Complex(fr[], fi[])
{
    while ( n-- )  cmult(fr[n], fi[n], gr[n], gi[n]);
}
// -------------------------

void
fft_fract(double *x, double *y, ulong n, double v)
// Fractional (fast) fourier transform.
//
// For complex array c[0...n]
// compute \sum_{x=0}^{n}{c_x*exp(is*v*2*i*\pi*x*k/n)}
//  (for v==1.0 this is just the usual fft)
//
// Use n*k == n^2/2 + k^2/2 - (k-n)^2/2
// See: Nussbaumer: "Fast Fourier Transform and Convolution Algorithms", chap.5, p.113ff
// Could use n*k == - n^2/2 - k^2/2 + (k+n)^2/2 instead.
//
// Worst case if n=2^x+1:
//   then nn=4*2^x
//   work is about 12 times of an FFT of length 2^x
//   and allocated workspace =4*nn
{
    const ulong ldnn = 1 + ld((n<<1)-1);
    const ulong nn = (1UL<<ldnn);  // smallest power of 2 >= 2*n

    double *fr = new double[2*nn];
    double *fi = fr + nn;

    acopy(x, fr, n);
    acopy(y, fi, n);

    null(fr+n, nn-n);
    null(fi+n, nn-n);

    double *wr = new double[2*nn];
    double *wi = wr + nn;

    make_fft_fract_chirp(wr, wi, v, n, nn);

    ri_multiply(wr, wi, fr, fi, n);

    negate(wi, nn);
    fft_complex_convolution(wr, wi, fr, fi, ldnn);

    make_fft_fract_chirp(wr, wi, v, n, nn);

    ri_multiply(fr, fi, wr, wi, nn);


    acopy(wr+n, x, n);
    acopy(wi+n, y, n);

    delete [] wr;
    delete [] fr;
}
// -------------------------
