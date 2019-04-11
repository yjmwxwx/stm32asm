// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux0/sincos.h"

#include <cstdlib>  // rand(), random(), srandom()
#include <cmath>  // sin(), cos(), sqrt(), log()

#include <sys/time.h>  // gettimeofday()


uint
rseed(uint s/*=0*/)
{
    struct timeval tv;
    if ( 0==s )
    {
        gettimeofday(&tv, 0);  // #ifdef _BSD_SOURCE
        ulong t = (ulong)tv.tv_sec ^ (ulong)tv.tv_usec;
//        t ^= (t>>32);
        s = (uint)t;
    }
    srandom(s);
    return s;
}
// -------------------------


double
rnd01()
// Random number in [0,1[
{
    return  (double)random() * (1.0/(RAND_MAX-1));
}
// -------------------------

void
rnd01(double *f, ulong n)
// Fill with random numbers in [0,1[
{
    for (ulong k=0; k<n; ++k)  f[k] = (double)random() * (1.0/(RAND_MAX-1));
}
// -------------------------


double
white_noise()
// Return one sample of white noise (with mean=0, sigma=1).
{
    static double z2;
    static unsigned ct = 0;

    ++ct;
    if ( ct & 1 )  // compute two independent samples:
    {
        double r1 = sqrt( -2.0 * log(1.0-rnd01()) );  // arg of log != 0
        double r2 = 2.0 * M_PI * rnd01();
        double z1;
        SinCos(r2, &z1, &z2);
        z1 *= r1;  // z1 = r1 * sin(r2)
        z2 *= r1;  // z2 = r1 * cos(r2)
        return  z1;
    }
    else  // ... next time there is one for free:
    {
        return  z2;
    }
}
// -------------------------


void
white_noise(double *f, ulong n)
// Fill array with samples of white noise (with mean=0, sigma=1).
{
    ulong k = 0;
    if ( n & 1 )  f[k++] = white_noise();

    for (  ; k<n-1; k+=2)
    {
        // compute two independent samples:
        double r1 = sqrt( -2.0 * log(1.0-rnd01()) );  // arg of log != 0
        double r2 = 2.0 * M_PI * rnd01();
        double z1, z2;
        SinCos(r2, &z1, &z2);
        z1 *= r1;  // z1 = r1 * sin(r2)
        z2 *= r1;  // z2 = r1 * cos(r2)
        f[k] = z1;
        f[k+1] = z2;
    }
}
// -------------------------

