#if !defined  HAVE_PRINT_ARRANGEMENT_RGS_PERM_H__
#define       HAVE_PRINT_ARRANGEMENT_RGS_PERM_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// comb/print-arrangement-rgs-perm.cc:
void print_arrangement_rgs_perm(const char *bla,
                                const ulong *a, ulong n,
                                ulong *rfc,
                                ulong *p,
                                bool zb=false);

#endif  // !defined HAVE_PRINT_ARRANGEMENT_RGS_PERM_H__
