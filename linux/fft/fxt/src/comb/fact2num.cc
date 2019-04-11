// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

ulong
ffact2num(const ulong *fc, ulong n)
// Convert (falling) factorial in fc[] to number.
// Note: n!-1 must fit into a ulong ==> only good for _tiny_ n
{
    ulong r = 0;
#if 1
    ulong p = 1;  // multiplier
    ulong x = n+1;  // radix
    for (ulong k=0; k<n; ++k)
    {
        ulong t = fc[k];
        r += p*t;
        p *= x;
        --x;
    }
#else
    ulong p = 1;  // multiplier
    for (ulong k=0; k<n; ++k)
    {
        ulong t = fc[n-1-k];
        r += p*t;
        p *= (k+2);
    }
#endif

    return r;
}
// -------------------------


bool
num2ffact(ulong x, ulong *fc, ulong n)
// Convert number x to (falling) factorial in fc[0,...,n-1].
// Return whether x fits into fc[]
{
    ulong rx = n+1;  // radix
    for (ulong k=0; k<n; ++k)
    {
        ulong f = x % rx;
        fc[k] = f;
        x /= rx;
        --rx;
    }

//    for (ulong k=0; k<n; ++k)  // wrong: reversed rfact
//    {
//        ulong f = x % (k+2);
//        x /= (k+2);
//        fc[n-1-k] = f;
//    }
    return  ( 0==x );
}
// -------------------------



ulong
rfact2num(const ulong *fc, ulong n)
// Convert (rising) factorial in fc[] to number.
// Note: n!-1 must fit into a ulong ==> only good for _tiny_ n
{
//    ulong x = 0;
//    for (ulong k=0; k<n; ++k)  { x*=(k+2); x+=fc[k]; }
//    return x;

    ulong r = 0;
    ulong p = 1;  // multiplier
    for (ulong k=0; k<n; ++k)
    {
        ulong t = fc[k];
        r += p*t;
        p *= (k+2);  // == m1[k]+1;
    }
    return r;
}
// -------------------------


bool
num2rfact(ulong x, ulong *fc, ulong n)
// Convert number x to (rising) factorial in fc[0,...,n-1].
// Return whether x fits into fc[]
{
    for (ulong k=0; k<n; ++k)
    {
        ulong f = x % (k+2);
        x /= (k+2);
        fc[k] = f;
    }
    return  ( 0==x );
}
// -------------------------
