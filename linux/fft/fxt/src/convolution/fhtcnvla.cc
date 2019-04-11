// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/realconvolution.h"  // fht_auto_convolution_core()
#include "fht/fht-default.h"
#include "fxttypes.h"  // ulong


// tuning parameter:
#define  USE_REVBIN_CORE
//
#ifdef  USE_REVBIN_CORE
//#warning 'FYI: fht_auto_convolution(double *, ulong) using revbin_permuted_core'
#else
#warning 'fht_auto_convolution(double *, ulong) using normal core'
#endif

#define  ZP_USE_REVBIN_CORE  // default: yes


void
fht_auto_convolution(double *f, ulong ldn)
// (cyclic, real) self-convolution:  f[] :=  f[] (*) f[]
// ldn := base-2 logarithm of the array length
{
#ifdef  USE_REVBIN_CORE
    fht_dif_core(f, ldn);
    fht_auto_convolution_revbin_permuted_core(f, ldn);
    fht_dit_core(f, ldn);
#else
    fht(f, ldn);
    fht_auto_convolution_core(f, ldn);
    fht(f, ldn);
#endif
}
// -------------------------


void
fht_auto_convolution0(double *f, ulong ldn)
// (linear, real) self-convolution:  f[] :=  f[] (*0) f[]
// ldn := base-2 logarithm of the array length
// version for zero padded data:
//   f[k] == 0 for k=n/2 ... n-1
// n = 2**ldn  must be >=2
{
//    if ( ldn<=1 )  { fr[0] *= fr[0]; return; }

#ifdef  ZP_USE_REVBIN_CORE
    fht0(f, ldn);
    fht_auto_convolution_core(f, ldn);
    fht(f, ldn);
#else
    fht_dif_core(f, ldn);
    fht_auto_convolution_revbin_permuted_core(f, ldn);
    fht_dit_core(f, ldn);
#endif
}
// -------------------------
