
// MACHINE GENERATED FILE, DO NOT EDIT !
// this file was generated from fhtcnvlacore.cc
#include "complextype.h"
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/fhtmulsqr.h"  // fht_sqr()
#include "restrict.h"
#include "fxttypes.h"  // ulong


void
fht_auto_convolution_core(Complex *f, ulong ldn,
                          double v/*=0.0*/)  // jjkeep
// Auxiliary routine for the computation of self-convolutions
// via Fast Hartley Transforms.
// ldn := base-2 logarithm of the array length
// v!=0.0 chooses alternative normalization
{
    const ulong  n  = (1UL<<ldn);

    if ( v==0.0 )  v = 1.0/(double)n;  // jjkeep

    f[0] *= (v * f[0]);

    if ( n>=2 )
    {
        const ulong  nh = n/2;
        f[nh] *= (v * f[nh]);
        v *= 0.5;
        for (ulong i=1, j=n-1;  i<j;  i++, j--)  fht_sqr(f[i], f[j], v);
    }
}
// -------------------------


void
fht_auto_convolution_revbin_permuted_core(Complex *f, ulong ldn,
                                          double v/*=0.0*/)  // jjkeep
// Auxiliary routine for the computation of convolutions
// via Fast Hartley Transforms.
//
// ldn := base-2 logarithm of the array length
// v!=0.0 chooses alternative normalization
//
// Same as fht_auto_convolution_core() but with data access in revbin order.
// This version avoids two calls to revbin_permute().
{
    const ulong n = (1UL<<ldn);

    if ( v==0.0 )  v = 1.0/(double)n;  // jjkeep
    f[0] *= (v * f[0]);  // == [0]
    if ( n>=2 )  f[1] *= (v * f[1]);  // == [nh]

    if ( n<4 )  return;

    v *= 0.5;
    const ulong nh = (n>>1);

    ulong r=nh, rm=n-1;
    fht_sqr(f[r], f[rm], v);

    ulong k=2, km=n-2;
    while ( k<nh  )
    {
        // k even:
        rm -= nh;
        ulong tr = r;
        r^=nh;  for (ulong m=(nh>>1); !((r^=m)&m); m>>=1)  {;}
        fht_sqr(f[r], f[rm], v);
        --km;
        ++k;

        // k odd:
        rm += (tr-r);
        r += nh;
        fht_sqr(f[r], f[rm], v);
        --km;
        ++k;
    }
}
// -------------------------

