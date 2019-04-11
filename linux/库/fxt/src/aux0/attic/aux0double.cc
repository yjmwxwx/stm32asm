// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "aux0/sincos.h"

#include <cmath>


double
pythag(double a, double b)
// return sqrt(a*a+b*b) avoiding overflow.
// Shouldn't be necessary with type double and sane algorithms/code
{
    a = fabs(a);
    b = fabs(b);
    if ( a>b )
    {
        double v = b / a;
        return  a * sqrt(1.0+v*v);
    }
    else
    {
        if ( b==0.0 )  return 0.0;
        double v = a / b;
        return  b * sqrt(1.0+v*v);
    }
}
// -------------------------


double
extr3_estimate(const double *f)
// return extremum (y-value) of parabola through
// the points (-1,a), (0,b), (+1,c)
{
    double a = f[-1],  b = f[0],  c = f[1];
    double xval = 0.5*(a-c) / (a+c-b*2);   // position of maximum
    double yval = b - 0.25*(a-c)*xval;  // value of maximum
    return  yval;
}
// -------------------------

double
extr3_estimate(const double *f, double &xval)
// return extremum (y-value) of parabola through
// the points (-1,a), (0,b), (+1,c)
// Put get the corrsponding x-value into xval
{
    double a = f[-1],  b = f[0],  c = f[1];
    xval = 0.5*(a-c) / (a+c-b*2);   // position of maximum
    double yval = b - 0.25*(a-c)*xval;  // value of maximum
    return  yval;
}
// -------------------------


double
sinc(double x)
// return sin(pi*x)/(pi*x)
{
    if ( x==0 )  return  1.0;
    else
    {
        x *= M_PI;
        return  sin(x) / x;
    }
}
// -------------------------

void
chop(double &x, double eps=1e-6)
// set to zero if tiny
{
    if ( fabs(x)<eps )  x = 0.0;
}
// -------------------------
