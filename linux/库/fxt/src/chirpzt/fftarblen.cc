// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/complexconvolution.h"
#include "chirpzt/chirpzt.h"

//#include "aux1/aux1double.h"
#include "aux1/arith1.h"   // multiply(), add(), subtract()
#include "bits/bit2pow.h"  // ld()

#include "aux0/csincos.h"

#include "aux1/copy.h"

#include "fxttypes.h"  // ulong
#include "complextype.h"  // Complex


static inline void
make_fft_chirp(Complex *w, ulong n, ulong nn, int is)
// For k=0..n-1:   w[k] := exp( is * k*k * (i*2*PI/n)/2 )  where i = sqrt(-1)
// For k=n..nn-1:  w[k] = 0
{
//    double phi = 1.0*is*M_PI/n;  // == (i*2*Pi/n)/2
    double phi = (double)is*M_PI/(double)n;  // == (i*2*Pi/n)/2
    ulong k2 = 0,  n2 = 2*n;
    for (ulong k=0; k<n; ++k)
    {
        w[k] = SinCos(phi*(double)k2);
        k2 += (2*k+1);
        if ( k2>n2 )  k2 -= n2;
        // here:  k2 == (k*k) mod 2*n;
    }
    null(w+n, nn-n);
}
// -------------------------

void
fft_arblen(Complex *x, ulong n, int is)
// Arbitrary length FFT.
{
    const ulong ldnn = 1 + ld( (n << 1) - 1 );
    const ulong nn = (1UL<<ldnn);  // smallest power of 2 >= 2*n

    Complex *f = new Complex[nn];
    acopy(x, f, n);
    null(f+n, nn-n);

    Complex *w = new Complex[nn];
    make_fft_chirp(w, n, nn, is);
    multiply(f, n, w);

    double *dw = (double *)w;  // jjcast
    for (ulong k=1; k<2*n; k+=2)  dw[k] = -dw[k];  // =^= make_fft_chirp(w, n, nn, -is);

    fft_complex_convolution(w, f, ldnn);

    if ( n & 1 )  subtract(f, n, f+n);  // odd n:  negacyclic convolution
    else          add(f, n, f+n);       // even n:  cyclic convolution

    make_fft_chirp(w, n, nn, is);
    multiply(w, n, f);

    acopy(w, x, n);
    delete [] w;
    delete [] f;
}
// -------------------------

