#if !defined  HAVE_POLY_TAB_H__
#define       HAVE_POLY_TAB_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong

// bpol/primpoly-minweight.cc:
extern const ulong minweight_primpoly[];

// bpol/primpoly-lowbit.cc:
extern const ulong lowbit_primpoly[];

// bpol/primpoly-rand.cc:
extern const ulong rand_primpoly[];


// bpol/normal-irredpoly.cc:
extern const ulong highbit_normal_irredpoly[];

// bpol/normal-primpoly.cc:
extern const ulong highbit_normal_primpoly[];

#endif  // !defined HAVE_POLY_TAB_H__
