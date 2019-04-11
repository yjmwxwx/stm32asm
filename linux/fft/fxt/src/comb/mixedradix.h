#if !defined HAVE_MIXEDRADIX_H__
#define      HAVE_MIXEDRADIX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


// comb/mixedradix-init.cc:
void mixedradix_init(ulong n, ulong mm, const ulong *m, ulong *m1);  // aux

// comb/mixedradix2num.cc:
ulong mixedradix2num(const ulong *x, const ulong *m1, ulong n);
void num2mixedradix(ulong N, ulong *x, const ulong *m1, ulong n);
ulong product(const ulong *x, ulong n);
ulong product_p1(const ulong *x, ulong n);


#endif  // !defined HAVE_MIXEDRADIX_H__
