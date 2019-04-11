// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fht/fht.h"

#include "aux0/sincos.h"

#include "aux1/copy.h"

#include "fxtalloca.h"
#include "fxttypes.h"
#include "complextype.h"

#include <cmath>


void
slow_ht(double *f, ulong n)
// (slow) Hartley transform.
{
    ALLOCA(double, res, n);

    const double ph0 = 2.0*M_PI/(double)n;
    for (ulong w=0; w<n; ++w)
    {
        double t=0.0;
        for (ulong k=0; k<n; ++k)
        {
            double c, s;
            SinCos(ph0*(double)k*(double)w, &s, &c);
//            SinCos(ph0*k*(w+sh, &s, &c));  // shifted ht
            t += ((c+s)*f[k]);
        }
        res[w] = t;
    }
    acopy(res, f, n);
}
// -------------------------

void
slow_ht(Complex *f, ulong n)
// (slow) Hartley transform.
{
    ALLOCA(Complex, res, n);

    const double ph0 = 2.0*M_PI/(double)n;
    for (ulong w=0; w<n; ++w)
    {
        Complex t=0.0;
        for (ulong k=0; k<n; ++k)
        {
            double c, s;
            SinCos(ph0*(double)k*(double)w, &s, &c);
//            SinCos(ph0*k*(w+sh, &s, &c));  // shifted ht
            t += ((c+s)*f[k]);
        }
        res[w] = t;
    }
    acopy(res, f, n);
}
// -------------------------


void
slow_row_column_ht(double *f, ulong nr, ulong nc)
{
    // HT over rows:
    ulong n = nr * nc;
    for (ulong k=0; k<n; k+=nc)  slow_ht(f+k, nc);


    // HT over columns:
    ALLOCA(double, w, nr);
    for (ulong k=0; k<nc; k++)
    {
        skip_copy(f+k, w, nr, nc);
        slow_ht(w, nr);
        skip_copy_back(w, f+k, nr, nc);
    }
}
// -------------------------

void
slow_twodim_ht(double *f, ulong nr, ulong nc)
// (slow) 2-dimensional Hartley transform.
{
    ulong n = nr * nc;
    ALLOCA(double, res, n);
    const double ph0r = 2.0*M_PI/(double)nr;
    const double ph0c = 2.0*M_PI/(double)nc;
    for (ulong wr=0; wr<nr; ++wr)
    {
        for (ulong wc=0; wc<nc; ++wc)
        {
            double t=0.0;
            for (ulong r=0; r<nr; ++r)
            {
                for (ulong c=0; c<nc; ++c)
                {
                    double cs, sn;
                    SinCos( ph0r*(double)r*(double)wr + ph0c*(double)c*(double)wc, &sn, &cs);
                    t += ((cs+sn) * f[r*nc+c]);
                }
            }
            res[wr*nc+wc] = t;
        }
    }
    acopy(res, f, n);
}
// -------------------------

