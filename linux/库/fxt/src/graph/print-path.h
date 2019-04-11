#if !defined  HAVE_PRINT_PATH_H__
#define       HAVE_PRINT_PATH_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// graph/print-path.cc:
void print_path(const ulong *rv, ulong ng);
void print_bin_path(const ulong *rv, ulong ng, ulong ngbits);
void print_bin_horiz_path(const ulong *rv, ulong ng, ulong ngbits, const char *c01=0);


#endif  // !defined HAVE_PRINT_PATH_H__
