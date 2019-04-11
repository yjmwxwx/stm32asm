// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "restrict.h"
#include "aux1/arith1.h"
#include "ntt/ntt.h"

#include "jjassert.h"


void
ntt_auto_convolution(mod *f, ulong ldn)
// Cyclic self-convolution.
// Use zero padded data for linear convolution.
{
    jjassert( mod::modulus & 1 );  // need odd modulus, so we can normalize later

    const int is = +1;

    ntt_dif4_core(f, ldn, is);  // transform

    const ulong n = (1UL<<ldn);
    for (ulong i=0; i<n; ++i)  f[i] *= f[i];  // multiply element-wise

    ntt_dit4_core(f, ldn, -is);  // inverse transform

    multiply_val(f, n, (mod(n)).inv() );  // normalize
}
// -------------------------


void
ntt_convolution(mod * restrict f, mod * restrict g, ulong ldn)
// Cyclic convolution.
// Use zero padded data for linear convolution.
// Result in g[].
{
    jjassert( mod::modulus & 1 );  // need odd modulus, so we can normalize later

//    jjassert( f!=g );

    const int is=+1;

    ntt_dif4_core(f, ldn, is);
    ntt_dif4_core(g, ldn, is);

    const ulong n = (1UL<<ldn);
    for (ulong i=0; i<n; ++i)  g[i] *= f[i];

    ntt_dit4_core(g, ldn, -is);

    multiply_val(g, n, (mod(n)).inv() );  // normalize
}
// -------------------------



// These are for the interface of fxtmult/hfloat:

void
ntt_convolution(double *f, double *g, ulong ldn)
{
    ntt_convolution((mod *)f, (mod *)g, ldn);  // jjcast
}
// -------------------------

void
ntt_auto_convolution(double *f, ulong ldn)
{
    ntt_auto_convolution((mod *)f, ldn);  // jjcast
}
// -------------------------
