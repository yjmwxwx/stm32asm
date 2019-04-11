#if !defined  HAVE_DELTA2GRAY_H__
#define       HAVE_DELTA2GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// comb/delta2gray.cc:
void delta2gray(const unsigned char *d, ulong ldn, ulong *g, ulong g0=0);
void gray2delta(ulong ldn, const ulong *g, unsigned char *d);


#endif  // !defined HAVE_DELTA2GRAY_H__
