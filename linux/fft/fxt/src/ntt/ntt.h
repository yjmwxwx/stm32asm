#if !defined HAVE_NTT_H__
#define      HAVE_NTT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/mod.h"
#include "fxttypes.h"
#include "restrict.h"


// ntt/nttdit4.cc:
void ntt_dit4_core(mod *f, ulong ldn, int is);
void ntt_dit4(mod *f, ulong ldn, int is);

// ntt/nttdif4.cc:
void ntt_dif4_core(mod *f, ulong ldn, int is);
void ntt_dif4(mod *f, ulong ldn, int is);


// ntt/nttdit2.cc:
void ntt_dit2_core(mod *f, ulong ldn, int is);
void ntt_dit2(mod *f, ulong ldn, int is);

// ntt/nttdif2.cc:
void ntt_dif2_core(mod *f, ulong ldn, int is);
void ntt_dif2(mod *f, ulong ldn, int is);

// ntt/nttcnvl.cc:
void ntt_auto_convolution(mod *f, ulong ldn);
void ntt_convolution(mod *f, mod *g, ulong ldn);
void ntt_convolution(double * restrict f, double * restrict g, ulong ldn);
void ntt_auto_convolution(double *f, ulong ldn);

// ntt/slownttcnvl.cc:
void slow_mod_convolution(mod *f, mod *g, ulong n);
void slow_mod_convolution(double *f, double *g, ulong n);


// ntt/nttlearn.cc:
void ntt_dit2l(mod *f, ulong ldn, int is);
void ntt_dif2l(mod *f, ulong ldn, int is);


// ntt/slowntt.cc:
void slow_ntt(mod *f, ulong n, int is);


#endif  // !defined HAVE_NTT_H__
