// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>

#include "fxttypes.h"
#include "complextype.h"
#include "aux0/csincos.h"
#include "aux0/cmult.h"

#include "aux1/copy.h"

#include "fxtalloca.h"


void
slow_ft(Complex *f, ulong n, int is)
//
// Fourier transform by definition (slow!)
//
{
    ALLOCA(Complex, h, n);
    const double ph0 = (double)is * 2.0 * M_PI / (double)n;
    for (ulong w=0; w<n; ++w)
    {
        Complex t = 0.0;
        for (ulong k=0; k<n; ++k)
        {
            t +=  f[k] * SinCos( ph0 * (double)k * (double)w );
        }
        h[w] = t;
    }
    acopy(h, f, n);
}
// -------------------------


void
slow_ft(double *fr, double *fi, ulong n, int is)
//
// Fourier transform by definition (slow!)
//
{
    ALLOCA(double, hr, n);
    ALLOCA(double, hi, n);
    const double ph0 = (double)is * 2.0 * M_PI / (double)n;
    for (ulong w=0; w<n; ++w)
    {
        double sr=0.0, si=0.0;
        for (ulong k=0; k<n; ++k)
        {
            double c, s;
            SinCos(ph0*(double)k*(double)w, &s, &c);
//            SinCos(ph0*k*(w+sh), &s, &c);  // shifted ft

            double r, i;
            cmult(c, s, fr[k], fi[k], r, i);

            sr += r;
            si += i;
        }
        hr[w] = sr;
        hi[w] = si;
    }
    acopy(hr, fr, n);
    acopy(hi, fi, n);
}
// -------------------------


void
slow_twodim_ft(Complex *f, ulong nr, ulong nc, int is)
{
    ulong n = nr * nc;

    // ft over rows:
    for (ulong k=0; k<n; k+=nc)  slow_ft(f+k, nc, is);

    // ft over columns:
    ALLOCA(Complex, w, nr);
    for (ulong k=0; k<nc; k++)
    {
        skip_copy(f+k, w, nr, nc);

        slow_ft(w, nr, is);

        skip_copy_back(w, f+k, nr, nc);
    }
}
// -------------------------


void
slow_twodim_ft(double *fr, double *fi, ulong nr, ulong nc, int is)
{
    ulong n = nr * nc;

    // ft over rows:
    for (ulong k=0; k<n; k+=nc)  slow_ft(fr+k, fi+k, nc, is);

    // ft over columns:
    ALLOCA(double, wr, nr);
    ALLOCA(double, wi, nr);
    for (ulong k=0; k<nc; k++)
    {
        skip_copy(fr+k, wr, nr, nc);
        skip_copy(fi+k, wi, nr, nc);

        slow_ft(wr, wi, nr, is);

        skip_copy_back(wr, fr+k, nr, nc);
        skip_copy_back(wi, fi+k, nr, nc);
    }
}
// -------------------------

