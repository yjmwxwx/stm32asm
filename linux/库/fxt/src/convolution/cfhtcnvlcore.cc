
// MACHINE GENERATED FILE, DO NOT EDIT !
// this file was generated from fhtcnvlcore.cc
#include "complextype.h"
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/fhtmulsqr.h"  // fht_mul()
#include "restrict.h"
#include "fxttypes.h"  // ulong


void
fht_convolution_core(const Complex * restrict f, Complex * restrict g, ulong ldn,
                     double v/*=0.0*/)  // jjkeep
// Auxiliary routine for the computation of convolutions
//   via Fast Hartley Transforms.
// ldn := base-2 logarithm of the array length.
// v!=0.0 chooses alternative normalization.
{
    const ulong n = (1UL<<ldn);
    if ( v==0.0 )  v = 1.0/(double)n;  // jjkeep
    g[0]  *=  (v * f[0]);
    const ulong  nh = n/2;

    if ( nh>0 )
    {
        g[nh] *= (v * f[nh]);
        v *= 0.5;
        for (ulong i=1, j=n-1;  i<j;  i++, j--)  fht_mul(f[i], f[j], g[i], g[j], v);
    }
}
// -------------------------


void
fht_convolution_revbin_permuted_core(const Complex * restrict f,
                                     Complex * restrict g,
                                     ulong ldn,
                                     double v/*=0.0*/)  // jjkeep
// Auxiliary routine for the computation of convolutions
//   via Fast Hartley Transforms.
//
// ldn := base-2 logarithm of the array length.
//
// v!=0.0 chooses alternative normalization.
//
// Same as fht_convolution_core() but with data access in revbin order.
// This version avoids calls to revbin_permute().
//
// Same as:
//    revbin_permute(f, n);
//    revbin_permute(g, n);
//    fht_convolution_core(f, g, ldn);
//    revbin_permute(g, n);
{
    const ulong n = (1UL<<ldn);

    if ( v==0.0 )  v = 1.0/(double)n;  // jjkeep

    g[0] *= (v * f[0]);  // 0 == revbin(0)
    if ( n>=2 )  g[1] *= (v * f[1]);  // 1 == revbin(nh)

    if ( n<4 )  return;

    v *= 0.5;
    const ulong nh = (n>>1);

    ulong r=nh, rm=n-1;  // nh == revbin(1),  n1-1 == revbin(n-1)
    fht_mul(f[r], f[rm], g[r], g[rm], v);

    ulong k=2, km=n-2;
    while ( k<nh  )
    {
        // k even:
        rm -= nh;
        ulong tr = r;
        r^=nh;  for (ulong m=(nh>>1); !((r^=m)&m); m>>=1)  {;}
        fht_mul(f[r], f[rm], g[r], g[rm], v);
        --km;
        ++k;

        // k odd:
        rm += (tr-r);
        r += nh;
        fht_mul(f[r], f[rm], g[r], g[rm], v);
        --km;
        ++k;
    }
}
// -------------------------
