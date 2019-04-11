#if !defined  HAVE_PERMCOMPOSE_H__
#define       HAVE_PERMCOMPOSE_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "ds/bitarray.h"
class bitarray;

#include "fxttypes.h"


// perm/permcompose.cc:
void make_square(ulong *f, ulong n, bitarray *bp=0);
void make_square(const ulong *f, ulong *g, ulong n);
void compose(const ulong *f, const ulong *g, ulong *h, ulong n);
void compose(const ulong *f, ulong *g, ulong n);
void power(const ulong *f, ulong *g, ulong n, long e, ulong *t=0);


#endif  // !defined HAVE_PERMCOMPOSE_H__
