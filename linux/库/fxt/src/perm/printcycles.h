#if !defined  HAVE_PRINTCYCLES_H__
#define       HAVE_PRINTCYCLES_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


//#include "ds/bitarray.h"
class bitarray;

#include "fxttypes.h"

// perm/printcycles.cc:
void print_cycles(const char *bla, const ulong *f, ulong n, bitarray *tb=0);
void print_cycles_len(const ulong *f, ulong n, bitarray *tb=0);
ulong print_cycle(const ulong *f, ulong e0=0);
void print_inv_perm_code(const char *bla, const ulong *f, ulong n, bitarray *tb=0);



#endif  // !defined HAVE_PRINTCYCLES_H__
