// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/delta2gray.h"

#include "fxtalloca.h"
#include "fxttypes.h"


void
monotonic_gray_delta(unsigned char *d, ulong ldn)
// Write the delta sequence for the Savage-Winkler monotonic Gray path
// into the array d[].
// Algorithm as given in Knuth, TAOCP vol.4
// (exercise 73, fascicle 2A, 7.2.1.1: "Generating all n-tuples").
{
    if ( 1>=ldn )
    {
        d[0] = 0;
        d[ldn] = 0;
        return;
    }

//    ALLOCA(uchar, p, ldn);
//    ALLOCA(uchar, pp, ldn);
    uchar * p = new uchar[ldn];
    uchar * pp = new uchar[ldn];

    const ulong nn = 1UL<<ldn;
//    ALLOCA(uchar, s, nn);
//    ALLOCA(uchar, t, nn);
//    ALLOCA(uchar, u, nn);
    uchar * s = new uchar[nn];
    uchar * t = new uchar[nn];
    uchar * u = new uchar[nn];

    uchar *sp = d;
//    ALLOCA(uchar, tp, nn);
//    ALLOCA(uchar, up, nn);
    uchar * tp = new uchar[nn];
    uchar * up = new uchar[nn];


    // R1:
    ulong n = 1;
    ulong n2 = 1UL << n;  // 2**n
    p[0] = 0;
    s[0] = t[0] = u[0] = 0;

 R2:
    // R2:
    {
        // S1:
        ulong j = 0,  k = 0,  l = 0;
        u[n2-1] = (uchar)-1;

    S2:
        // S2:
        while ( 0==u[j] )  { sp[l] = s[j];  up[l] = 0;  ++l;  ++j; }
        if ( (signed char)u[j] < 0 )  goto S5;  // jjcast

        // S3:
        sp[l] = s[j];  up[l] = 1;  ++l;  ++j;
        while ( 0==u[j] )  { sp[l] = s[j];  up[l] = 0;  ++l;  ++j; }
        sp[l] = (uchar)n;  up[l] = 0;  ++l;
        while ( 0==u[k] )  { sp[l] = p[t[k]];  up[l] = 0;  ++l;  ++k; }
        sp[l] = p[t[k]];  up[l] = 1;  ++l;  ++k;
        while ( 0==u[k] )  { sp[l] = p[t[k]];  up[l] = 0;  ++l;  ++k; }

        // S4:
        if ( (signed char)u[k] < 0 )  goto S6;  // jjcast
        sp[l] = (uchar)n;  up[l] = 0;  ++l;  ++k;  ++j;  goto S2;

    S5:
        // S5:
        sp[l] = (uchar)n;  up[l] = 1;  ++l;
        while ( 0==u[k] )  { sp[l] = p[t[k]];  up[l] = 0;  ++l;  ++k; }

    S6:
        // S6:
        j = k = l = 0;
        while ( 0==u[k] )  { tp[l] = t[k];  ++l;  ++k; }
        tp[l] = (uchar)n;  ++l;

    S7:
        // S7:
        while ( 0==u[j] )  { tp[l] = p[s[j]];  ++l;  ++j; }
        if ( (signed char)u[j] < 0 )   goto S_done;
        tp[l] = (uchar)n;  ++l;  ++j;  ++k;

        // S8:
        while ( 0==u[k] )  { tp[l] = t[k];  ++l;  ++k; }
        if ( (signed char)u[k] < 0 )   goto S10;  // jjcast

        // S9:
        tp[l] = t[k];  ++l;  ++k;
        while ( 0==u[k] )  { tp[l] = t[k];  ++l;  ++k; }
        tp[l] = (uchar)n;  ++l;
        while ( 0==u[j] )  { tp[l] = p[s[j]];  ++l;  ++j; }
        tp[l] = p[s[j]];  ++l;  ++j;
        goto S7;

    S10:
        // S10:
        tp[l] = (uchar)n;  ++l;
        while ( 0==u[j] )  { tp[l] = p[s[j]];  ++l;  ++j; }
    }
 S_done:
    ++n;  n2 = 1UL<<n;

    // R3
    // here sp[1...2**n-1] contains the delta sequence
    if ( n==ldn )
    {
        delete [] p;
        delete [] pp;
        delete [] s;
        delete [] t;
        delete [] u;
        delete [] tp;
        delete [] up;
        return;
    }

    // R4:
    pp[0] = (uchar)(n - 1);
    for (ulong j=1; j<n; ++j)  pp[j] = p[p[j-1]];

    // R5:
    for (ulong j=0; j<n; ++j)  p[j] = pp[j];
    for (ulong k=0; k<n2-1; ++k)  s[k] = sp[k];
    for (ulong k=0; k<n2-1; ++k)  t[k] = tp[k];
    for (ulong k=0; k<n2-1; ++k)  u[k] = up[k];
    goto R2;
}
// -------------------------


void
monotonic_gray(ulong *g, ulong ldn)
// Write the monotonic (Savage-Winkler) Gray path
// into g[0..N-1] (N=2**ldn).
{
    ulong n = 1UL<<ldn;
//    ALLOCA(uchar, d, n);
    uchar *d = new uchar[n];
    monotonic_gray_delta(d, ldn);
    delta2gray(d, ldn, g);
    delete [] d;
}
// -------------------------
