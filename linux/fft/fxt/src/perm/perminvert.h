#if !defined  HAVE_PERMINVERT_H__
#define       HAVE_PERMINVERT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "ds/bitarray.h"
class bitarray;

#include "fxttypes.h"


// perm/perminvert.cc:
void make_inverse(const ulong *f, ulong *g, ulong n);
void make_inverse(ulong *f, ulong n, bitarray *bp=0);
void make_inverse_notag(ulong *f, ulong n);
void boothroyd_invert(ulong *f, ulong n, bitarray *bp=0);


#endif  // !defined HAVE_PERMINVERT_H__
