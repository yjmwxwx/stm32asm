#if !defined  HAVE_MONOTONIC_GRAY_H__
#define       HAVE_MONOTONIC_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// comb/monotonic-gray.cc:
void monotonic_gray_delta(unsigned char *d, ulong ldn);
void monotonic_gray(ulong *g, ulong ldn);


#endif  // !defined HAVE_MONOTONIC_GRAY_H__
