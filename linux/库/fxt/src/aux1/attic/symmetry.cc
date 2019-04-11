// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>  // fabs()

#include "fxttypes.h"
#include "aux0/sumdiff.h"
#include "aux1/arith1.h"
//#include "jjassert.h"

#include "aux1/copy.h"


int
symm_q(const double *f, ulong n, double eps/*=1e-5*/)
//
// check symmetry  k <--> n-1-k  (k=0..n-1)
// return:
//    0: no symmetry
//    1: symmetry
//   -1: neg. symm.
//
{
    ulong k, nh = n/2;
    for (k=0; k<nh; ++k)  if ( fabs(f[k]-f[n-1-k]) > eps ) break;
    if ( k==nh )  return +1;
    else
    {
        for (k=0; k<nh; ++k)  if ( fabs(f[k]+f[n-1-k]) > eps ) break;
        if ( k==nh )  return -1;
    }
    return  0;
}
// -------------------------


int
symm_0_q(const double *f, ulong n, double eps/*=1e-5*/)
// check symmetry  k <--> n-k  (k=1..n/2-1)
{
    ulong k, nh = n/2;
    for (k=1; k<nh; ++k)  if ( fabs(f[k]-f[n-k]) > eps ) break;

    if ( k==nh )  return +1;

    for (k=1; k<nh; ++k)  if ( fabs(f[k]+f[n-k]) > eps )   break;

    if ( k==nh )
    {
        if ( (fabs(f[nh])<eps) && (fabs(f[0])<eps) )  return -1;
    }

    return 0;
}
// -------------------------


int
any_symm_q(const double *f, ulong n, double eps/*=1e-5*/)
{
    return  symm_q(f, n, eps) + 2 * symm_0_q(f, n, eps);
}
// -------------------------


void
symm_0(double *f, ulong n, int s=+1)
// make symmetric  k <--> n-k  (k=1..n/2-1)
{
    ulong nh = n/2;

    for (ulong k=1, j=n-1;  k<j;  ++k, --j)  sumdiff(f[k],f[j]);

    if ( s>0 )
    {
        copy_reverse(f+1, f+nh+1, nh-1);
        f[0] *= 2;
        if ( 0==(n&1) )  f[nh] *= 2;  // only for n even
    }
    else
    {
        copy_reverse(f+nh+1, f+1, nh-1);
        negate(f+1, nh-1);
        if ( 0==(n&1) )  f[nh] = 0.0;  // only for n even
        f[0] = 0.0;
    }

//    jjassert( s == symm_0_q(f, n) );
}
// -------------------------


void
symm(double *f, ulong n, int s=+1)
// make symmetric  k <--> n-1-k  (k=1..n/2-1)
{
    ulong nh = n/2;

    for (ulong k=0, j=n-1;  k<j;  ++k, --j)  sumdiff(f[k],f[j]);

    if ( s>0 )
    {
        copy_reverse(f, f+nh, nh);
        if ( n & 1 )  f[nh] *= 2.0;  // only for n odd
    }
    else
    {
        copy_reverse(f+nh, f, nh);
        negate(f, nh);
        if ( n & 1 )  f[nh] = 0.0;  // only for n odd
    }

//    jjassert( s == symm_q(f, n) );
}
// -------------------------
