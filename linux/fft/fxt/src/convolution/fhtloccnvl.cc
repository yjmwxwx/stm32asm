// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/realconvolution.h"  // fht_convolution_core()
#include "fht/fht.h"
#include "fht/fhtloc2.h"
#include "restrict.h"
#include "fxttypes.h"  // ulong


// tuning parameter:
#define  USE_REVBIN_CORE  // default: yes
#define  ZP_USE_REVBIN_CORE  // default: yes


void
loc_fht_convolution(double * restrict f, double * restrict g, ulong ldn)
// (cyclic, real) convolution:  g[] :=  f[] (*) g[]
// ldn := base-2 logarithm of the array length
{
#ifdef  USE_REVBIN_CORE
    fht_loc_dif2_core(f, ldn);
    fht_loc_dif2_core(g, ldn);
    fht_convolution_revbin_permuted_core(f, g, ldn);
    fht_loc_dit2_core(g, ldn);
#else
    fht_loc(f, ldn);
    fht_loc(g, ldn);
    fht_convolution_core(f, g, ldn);  // n>=2
    fht_loc(g, ldn);
#endif
}
// -------------------------


void
loc_fht_convolution0(double * restrict f, double * restrict g, ulong ldn)
// (linear, real) convolution:  g[] :=  f[] (*) g[]
// ldn := base-2 logarithm of the array length
// input data must be zero padded:
//   f[n/2] .. f[n-1] == 0 and g[n/2] .. g[n-1] == 0
// n = 2**ldn  must be >=2
{
#ifdef  ZP_USE_REVBIN_CORE
    fht_loc_dif2_core(f, ldn);
    fht_loc_dif2_core(g, ldn);
    fht_convolution_revbin_permuted_core(f, g, ldn);
    fht_loc_dit2_core(g, ldn);
#else
    fht_loc_0(f, ldn);
    fht_loc_0(g, ldn);
    fht_convolution_core(f, g, ldn);
    fht_loc(g, ldn);
#endif
}
// -------------------------

