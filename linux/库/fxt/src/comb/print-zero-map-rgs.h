#if !defined  HAVE_PRINT_ZERO_MAP_RGS_H__
#define       HAVE_PRINT_ZERO_MAP_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// comb/print-zero-map-rgs.cc:
void print_zero_map_rgs_as_zero_dist_rgs(const char *bla,
                                         const ulong *a, ulong n,
                                         bool dfz=true);

void print_zero_map_rgs_as_fp_rgs(const char *bla,
                                  const ulong *a, ulong n,
                                  bool dfz=true,
                                  bool zb=true);

void print_zero_map_rgs_as_fp_dist_rgs(const char *bla,
                                       const ulong *a, ulong n,
                                       bool dfz=true,
                                       bool zb=true);

void print_zero_map_rgs_setpart(const char *bla,
                                const ulong *a, ulong n,
                                bool zb=false,
                                bool iq=false);

#endif  // !defined HAVE_PRINT_ZERO_MAP_RGS_H__
