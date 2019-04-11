#if !defined  HAVE_HILBERT_NDIM_REC_H__
#define       HAVE_HILBERT_NDIM_REC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/graycode.h"
#include "bits/bitlow.h"
#include "bits/bithigh.h"
#include "aux0/swap.h"
#include "fxttypes.h"

//#include "jjassert.h"

// define to unroll copy and init loops:
#define HILBERT_NDIM_UNROLL  // default on

class hilbert_ndim_rec
// Fred Lunnon's recursive algorithm to convert linear coordinate
// into coordinates of d-dimensional Hilbert curve.
// Note: the iterative version (class hilbert_ndim) is much faster.
{
public:
    ulong d;  // number of dimensions 2<=d<=32
    ulong P[32];  // size == max dim
    ulong Q[32];  // size == max dim

private:
    hilbert_ndim_rec(const hilbert_ndim_rec&);  // forbidden
    hilbert_ndim_rec & operator = (const hilbert_ndim_rec&);  // forbidden

public:
    explicit hilbert_ndim_rec(ulong dd)
    // Must have: 2<=dd<=32
    { d = dd; }

    ~hilbert_ndim_rec()  { ; }

    const ulong *data()  const  { return &P[0]; }

    void lin2hilbert(ulong n)
    {
#ifndef HILBERT_NDIM_UNROLL
        for (ulong e=0; e<d; ++e)  P[e] = 0;
#else
        for (ulong e=0; e<d; e+=4)
        { P[e] = 0; P[e+1] = 0; P[e+2] = 0; P[e+3] = 0; }
#endif
        lin2hilbert_rec(n);
    }

private:
    void lin2hilbert_rec(ulong n)
    {
        const ulong l = highest_one_idx(n) / d;  // sub-cell generation
        const ulong h = 1UL << l;  // sub-cell diameter  h=2^l
        const ulong hds = l*d;  // aux: shift for divide and mult with h^d
        //    jjassert( hds == highest_one_idx(n) - (highest_one_idx(n)%d) );  // OK
        const ulong j = (n >> hds);  // sub-cell step  j = floor(n/h^d)
        const ulong m = n - (j<<hds);  // move within sub-cell:  m = n - j*h^d = n - j*hd

        if ( m!=0 )  lin2hilbert_rec(m);  // initial sub-cell via recursion

        if ( j != 0 )
        {
#ifndef HILBERT_NDIM_UNROLL
            for (ulong e=0; e<d; ++e)  Q[e] = P[e];
#else
            for (ulong e=0; e<d; e+=4)
            { Q[e] = P[e];  Q[e+1] = P[e+1];  Q[e+2] = P[e+2];  Q[e+3] = P[e+3]; }
//            for (ulong e=0; e<d; e+=2)
//            { Q[e] = P[e];  Q[e+1] = P[e+1]; }
#endif

            if ( 0==(l&1) )  // odd generation: Q[d-1] and P[0] active
            {
                swap2( Q[0], Q[d-1] );  // transpose end components
            }
            // else  //  even generation: Q[0] and P[d-1] active, nothing to do

            if ( j == (1UL<<d)-1 )  // bend path to exit cell at finish
            {
                P[0] = h-1-Q[0];  P[d-1] = 2*h-1-Q[d-1];
            }
            else
            {
                const ulong J = gray_code(j);
                const ulong J1 = gray_code(j-1);
                const ulong k = lowest_one_idx(J);

                // ----- i==0:
                // P[i] = Q[1];  // permute axes
                // if ( Ji == 0 )  { P[i] = h-1 - P[i]; }  // reverse axis
                // if ( Ji == 1 )  { P[i] = h + P[i]; }  // translate axis
                P[0] = ( (J&1)==0 ? h-1-Q[1] : h+Q[1] );

                // ----- i==1:
                P[1] = ( k==0 ? Q[0] : Q[k+1]);  // permute axes
                if ( J1&2 )  P[1] = h-1-P[1];  // reverse axis
                if ( J&2 )  P[1] = h+P[1];  // translate axis

                // ----- i>=2:
                for (ulong i=2; i<d; ++i)
                {
                    P[i] = ( i==k+1 ? Q[0] : Q[i]);  // permute axes
                    const ulong Ji = (J>>i) & 1;
                    const ulong J1i = (J1>>i) & 1;
                    if ( J1i==1 )  P[i] = h-1-P[i];  // reverse axis
                    if ( Ji==1 )  P[i] = h+P[i];  // translate axis
                }
            }

            if ( 0==(l&1) )  // odd generation: Q[d-1] and P[0] active
            {
                swap2( P[0], P[d-1] );  // transpose end components
            }
            // else  // even generation: Q[0] and P[d-1] active, nothing to do
        }
    }
};
// -------------------------


#undef HILBERT_NDIM_UNROLL


#endif  // !defined HAVE_HILBERT_NDIM_REC_H__
