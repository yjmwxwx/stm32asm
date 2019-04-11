#if !defined  HAVE_ACGRAY_H__
#define       HAVE_ACGRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// comb/acgray.cc:
void ac_gray_delta(uchar *d, ulong ldn);
ulong test_ac_gray(ulong *g, ulong n);
void ac_gray(ulong *g, ulong ldn);


#endif  // !defined HAVE_ACGRAY_H__
