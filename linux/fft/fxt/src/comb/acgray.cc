// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "comb/acgray.h"
#include "comb/delta2gray.h"
#include "perm/reverse.h"

#include "fxtalloca.h"
#include "fxttypes.h"

void
ac_gray_delta(uchar *d, ulong ldn)
// Generate a delta sequence for an adjacent-changes (AC) Gray code
//  of length n=2**ldn where ldn<=6.
// Example (ldn=4):
//    0:  .... 0    0
//    1:  ...1 1    1    0  ...1
//    2:  ..11 2    3    1  ..1.
//    3:  .111 3    7    2  .1..
//    4:  .1.1 2    5    1  ..1.
//    5:  .1.. 1    4    0  ...1
//    6:  .11. 2    6    1  ..1.
//    7:  ..1. 1    2    2  .1..
//    8:  1.1. 2   10    3  1...
//    9:  111. 3   14    2  .1..
//   10:  11.. 2   12    1  ..1.
//   11:  11.1 3   13    0  ...1
//   12:  1111 4   15    1  ..1.
//   13:  1.11 3   11    2  .1..
//   14:  1..1 2    9    1  ..1.
//   15:  1... 1    8    0  ...1
//
// For ldn>=7 the routine produces delta sequences with
//   2**(ldn-5) - 1  (ldn odd)
//   2**(ldn-5) - 2  (ldn even)
// non-AC transitions ("flaws"):
//   ldn =0..6  #non-ac = 0
//   ldn =  7   #non-ac = 3
//   ldn =  8   #non-ac = 6
//   ldn =  9   #non-ac = 15
//   ldn = 10   #non-ac = 30
//   ldn = 11   #non-ac = 63
//   ldn = 12   #non-ac = 126
//
// Near-AC Gray codes with fewer "flaws" may well exist.
{
    if ( ldn<=2 )  // standard Gray code
    {
        d[0] = 0;
        if ( ldn==2 ) { d[1] = 1; d[2] = 0; }
        return;
    }

    ac_gray_delta(d, ldn-1);  // recursion

    ulong n = 1UL<<ldn;
    ulong nh = n/2;
    if ( 0==(ldn&1) )
    {
        if ( ldn>=6 )
        {
            reverse(d, nh-1);
            for (ulong k=0;  k<nh;  ++k)  d[k] = (uchar)((ldn - 2) - d[k]);
        }

        for (ulong k=0, j=n-2;  k<j;  ++k, --j)  d[j] = d[k];
        d[nh-1] = (uchar)(ldn - 1);
    }
    else
    {
        for (ulong k=nh-2, j=nh-1;  0!=j;  --k, --j)  d[j] = (uchar)(d[k] + 1);
        for (ulong k=2, j=n-2;  k<j;  ++k, --j)  d[j] = d[k];
        d[0] = 0;
        d[nh] = 0;
    }
}
// -------------------------


ulong
test_ac_gray(ulong *g, ulong n)
// Count the number of non-AC transitions in a Gray path.
// If the returned value is zero, the Gray path is an AC-path.
{
    ulong ct = 0;
    for (ulong k=2; k<n; ++k)
    {
        ulong p0  = g[k],  p1 = g[k-1], p2 = g[k-2];
        ulong c0 = p0 ^ p1, c1 = p1 ^ p2;
        if ( c0 & (c1<<1) )  continue;
        if ( c1 & (c0<<1) )  continue;
        ++ct;
    }
    return ct;
}
// -------------------------

void
ac_gray(ulong *g, ulong ldn)
// Create an AC Gray code.
// (see ac_gray_delta())
{
    ulong n = 1UL<<ldn;
    ALLOCA(uchar, d, n);
    ac_gray_delta(d, ldn);
    delta2gray(d, ldn, g);
}
// -------------------------
