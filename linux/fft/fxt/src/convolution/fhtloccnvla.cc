// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/realconvolution.h"  // fht_auto_convolution_core()
#include "fht/fhtloc2.h"
#include "fxttypes.h"  // ulong


// tuning parameter:
#define  USE_REVBIN_CORE  // default: yes
#define  ZP_USE_REVBIN_CORE  // default: yes


void
loc_fht_auto_convolution(double *f, ulong ldn)
// (cyclic, real) self-convolution:  f[] :=  f[] (*) f[]
// ldn := base-2 logarithm of the array length
{
//    if ( ldn<=1 )  { f[0] *= f[0]; return; }

#ifdef  USE_REVBIN_CORE
    fht_loc_dif2_core(f, ldn);
    fht_auto_convolution_revbin_permuted_core(f, ldn);
    fht_loc_dit2_core(f, ldn);
#else
    fht_loc(f, ldn);
    fht_auto_convolution_core(f, ldn);
    fht_loc(f, ldn);
#endif
}
// -------------------------


void
loc_fht_auto_convolution0(double *f, ulong ldn)
// (linear, real) self-convolution:  f[] :=  f[] (*0) f[]
// ldn := base-2 logarithm of the array length
// version for zero padded data:
//   f[k] == 0 for k=n/2 ... n-1
// n = 2**ldn  must be >=2
{
//    if ( ldn<=1 )  { f[0] *= f[0]; return; }

#ifdef  ZP_USE_REVBIN_CORE
    fht_loc_dif2_core(f, ldn);
    fht_auto_convolution_revbin_permuted_core(f, ldn);
    fht_loc_dit2_core(f, ldn);
#else
    fht_loc_0(f, ldn);
    fht_auto_convolution_core(f, ldn);
    fht_loc(f, ldn);
#endif
}
// -------------------------
