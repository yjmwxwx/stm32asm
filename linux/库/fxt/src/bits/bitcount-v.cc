// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitcount.h"
#include "fxttypes.h"

//#include "bits/print-bin.h"
//#include "fxtio.h"

static inline ulong bit_count_v15(const ulong *x)
// Return sum(j=0, 14, bit_count(x[j]) )
// Technique is "vertical" addition.
{
//#define PP(k) { cout << "x[" << setw(2) << k << "]="; print_bin("", x[k], 8); print_bin("  a0=", a0, 8); print_bin("  a1=", a1, 8); print_bin("  a2=", a2, 8); print_bin("  a3=", a3, 8); cout << endl; }
#define PP(k)

#define VV(A) { ulong t = A & cy;  A ^= cy;  cy = t; }
    ulong a1, a2, a3;
//    a1= a2 = a3 = 0;  // initialization only needed with printing
    ulong a0=x[0]; PP(0);
    { ulong cy = x[ 1];  VV(a0);  a1 = cy; }  PP(1);
    { ulong cy = x[ 2];  VV(a0);  a1 ^= cy; }  PP(2);
    { ulong cy = x[ 3];  VV(a0);  VV(a1);  a2 = cy; }  PP(3);
    { ulong cy = x[ 4];  VV(a0);  VV(a1);  a2 ^= cy; }  PP(4);
    { ulong cy = x[ 5];  VV(a0);  VV(a1);  a2 ^= cy; }  PP(5);
    { ulong cy = x[ 6];  VV(a0);  VV(a1);  a2 ^= cy; }  PP(6);
    { ulong cy = x[ 7];  VV(a0);  VV(a1);  VV(a2);  a3 = cy; }  PP(7);
    { ulong cy = x[ 8];  VV(a0);  VV(a1);  VV(a2);  a3 ^= cy; }  PP(8);
    { ulong cy = x[ 9];  VV(a0);  VV(a1);  VV(a2);  a3 ^= cy; }  PP(9);
    { ulong cy = x[10];  VV(a0);  VV(a1);  VV(a2);  a3 ^= cy; }  PP(10);
    { ulong cy = x[11];  VV(a0);  VV(a1);  VV(a2);  a3 ^= cy; }  PP(11);
    { ulong cy = x[12];  VV(a0);  VV(a1);  VV(a2);  a3 ^= cy; }  PP(12);
    { ulong cy = x[13];  VV(a0);  VV(a1);  VV(a2);  a3 ^= cy; }  PP(13);
    { ulong cy = x[14];  VV(a0);  VV(a1);  VV(a2);  a3 ^= cy; }  PP(14);
#undef VV
#undef PP

    ulong b = bit_count(a0);
    b += (bit_count(a1)<<1);
    b += (bit_count(a2)<<2);
    b += (bit_count(a3)<<3);
    return  b;
}
// -------------------------

ulong
bit_count_v(const ulong *x, ulong n)
// Return sum(j=0, n-1, bit_count(x[j]) )
{
    ulong b = 0;
    const ulong *xe = x + n + 1;
    while ( x+15 < xe )  // process blocks of 15 elements
    {
        b += bit_count_v15(x);
        x += 15;
    }

    // process remaining elements:
    const ulong r = (ulong)(xe-x-1);
    for (ulong k=0; k<r; ++k)  b+=bit_count(x[k]);

    return  b;
}
// -------------------------
