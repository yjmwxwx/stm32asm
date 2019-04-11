#if !defined  HAVE_FACT2NUM_H__
#define       HAVE_FACT2NUM_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

// comb/fact2num.cc:
ulong ffact2num(const ulong *fc, ulong n);
bool num2ffact(ulong x, ulong *fc, ulong n);

ulong rfact2num(const ulong *fc, ulong n);
bool num2rfact(ulong x, ulong *fc, ulong n);


#endif  // !defined HAVE_FACT2NUM_H__
