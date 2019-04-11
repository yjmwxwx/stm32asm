#if !defined HAVE_LDN2RC_H__
#define      HAVE_LDN2RC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

static inline void ldn2rc(ulong ldn, ulong &nr, ulong &nc)
// Input ldn := log_2(n)
// nr, nc are set so that nr*nc = n and ldr>=ldc
// Used in matrix-fft based convolution.
{
    ulong ldc = (ldn>>1);
    ulong ldr = ldn-ldc;
    nc = (1UL<<ldc);
    nr = (1UL<<ldr);  // nrow >= ncol
}
// -------------------------


#endif  // !defined HAVE_LDN2RC_H__
