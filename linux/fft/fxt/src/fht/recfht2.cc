// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fht/hartleyshift.h"  // hartley_shift_05()

#include "aux1/copy.h"

#include "fxtalloca.h"
#include "fxttypes.h"


static void
recursive_fht_dit2_core(const double *a, ulong n, double *x)
{
    if ( n==1 )  { x[0] = a[0]; return; }

    ulong nh = n/2;
    ALLOCA(double, b, nh);
    ALLOCA(double, c, nh);
    ALLOCA(double, ev, nh);
    ALLOCA(double, od, nh);

    for (ulong k=0, j=0;  j<nh;  k+=2, j++)
    {
        ev[j] = a[k];
        od[j] = a[k+1];
    }

    recursive_fht_dit2_core(ev, nh, b);
    recursive_fht_dit2_core(od, nh, c);

    hartley_shift_05(c, nh);
    for (ulong k=0; k<nh; k++)
    {
        x[k]    = b[k] + c[k];
        x[k+nh] = b[k] - c[k];
    }
}
// -------------------------

void
recursive_fht_dit2(double *a, ulong ldn)
// Very inefficient, just to demonstrate the
// recursive fast Hartley transform
{
    ulong n = (1UL<<ldn);
    ALLOCA(double, x, n);
    recursive_fht_dit2_core(a, n, x);
    acopy(x, a, n);
}
// -------------------------


static void
recursive_fht_dif2_core(const double *a, ulong n, double *x)
{
    if ( n==1 )  { x[0] = a[0]; return; }

    ulong nh = n/2;
    ALLOCA(double, b, nh);
    ALLOCA(double, c, nh);
    ALLOCA(double, le, nh);
    ALLOCA(double, ri, nh);

    for (ulong j=0; j<nh; j++)
    {
        le[j] = a[j];
        ri[j] = a[nh+j];
    }

    for (ulong k=0; k<nh; k++)
    {
        double t =   (le[k] + ri[k]);
        ri[k] =       (le[k] - ri[k]);
        le[k] = t;
    }

    hartley_shift_05(ri, nh);

    recursive_fht_dif2_core(le, nh, b);
    recursive_fht_dif2_core(ri, nh, c);

    for (ulong k=0, j=0;  k<nh;  k++, j+=2)
    {
        x[j]   = b[k];
        x[j+1] = c[k];
    }
}
// -------------------------

void
recursive_fht_dif2(double *a, ulong ldn)
// Very inefficient, just to demonstrate the
// recursive fast Hartley transform
{
    ulong n = (1UL<<ldn);
    ALLOCA(double, x, n);
    recursive_fht_dif2_core(a, n, x);
    acopy(x, a, n);
}
// -------------------------

