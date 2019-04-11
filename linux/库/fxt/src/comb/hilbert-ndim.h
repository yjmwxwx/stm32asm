#if !defined  HAVE_HILBERT_NDIM_H__
#define       HAVE_HILBERT_NDIM_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/graycode.h"
#include "bits/bitlow.h"
#include "bits/bithigh.h"
#include "aux0/swap.h"
#include "fxttypes.h"


// define to unroll init loop:
#define HILBERT_NDIM_UNROLL  // default on

class hilbert_ndim
// Fred Lunnon's iterative algorithm to convert linear coordinate
// into coordinates of d-dimensional Hilbert curve.
{
public:
    ulong d;  // number of dimensions 2<=d<=32
    ulong P[32];  // size == max dim

private:
    hilbert_ndim(const hilbert_ndim&);  // forbidden
    hilbert_ndim & operator = (const hilbert_ndim&);  // forbidden

public:
    explicit hilbert_ndim(ulong dd)
    // Must have: 2<=dd<=32
    { d = dd; }

    ~hilbert_ndim()  { ; }

    const ulong *data()  const  { return &P[0]; }

    void lin2hilbert(ulong n)
    {
#ifndef HILBERT_NDIM_UNROLL
        for (ulong e=0; e<d; ++e)  P[e] = 0;
#else
        for (ulong e=0; e<d; e+=4)
        { P[e] = 0; P[e+1] = 0; P[e+2] = 0; P[e+3] = 0; }
//        for (ulong e=0; e<d; e+=2)  { P[e] = 0; P[e+1] = 0; }
#endif

        const ulong d2 = (1UL << d) - 1;  // mask for computing mod 2**d

        ulong h = 1;  // cell diameter 2**lv
        ulong m = n;
        ulong lv;
        for (lv=0;  m!=0;  ++lv)
        {
            const ulong j = m & d2;  // j mod 2**d
            m -=j;  m >>= d;         // m = (m-j)/(2**d)

            if ( j != 0 )  // unless just entering cell
            {
                if ( j == d2 )  // divert path to exit cell at final step
                {
                    P[0] = h-1 - P[0];
                    P[d-1] = h+h-1 - P[d-1];
                }
                else
                {
                    ulong J = gray_code(j);
                    ulong J1 = gray_code(j-1);

                    // permute axes P[1], P[0], P[k+1] cyclically (incl. case k = 0):
                    {
                        const ulong k = lowest_one_idx(J);
                        const ulong P0 = P[0];  P[0] = P[1];  P[1] = P[k+1];  P[k+1] = P0;
                    }

                    // ----- i==0:
                    if ( 0==(J & 1) )  P[0] = h-1 - P[0];  // reverse axis
                    else               P[0] = h + P[0];    // translate axis

                    // ----- i==1:
                    J >>= 1;
                    J1 >>= 1;
                    if ( J1 & 1 )  P[1] = h-1 - P[1];  // reverse axis
                    if ( J & 1 )   P[1] = h + P[1];    // translate axis

                    // ----- i==2,3,...,d-1:
                    for (ulong i=2; i<d; ++i)
                    {
                        J >>= 1;
                        J1 >>= 1;
                        if ( J1 & 1 )  P[i] = h-1 - P[i];  // reverse axis
                        if ( J & 1 )   P[i] = h + P[i];    // translate axis
                    }
                }
            }

            swap2( P[0], P[d-1] );  // transpose so P[0] active
            h <<= 1;
        }

        if ( lv & 1 )  swap2(P[0], P[d-1]);  // stabilize odd with even levels
    }
};
// -------------------------


#undef HILBERT_NDIM_UNROLL


#endif  // !defined HAVE_HILBERT_NDIM_H__
