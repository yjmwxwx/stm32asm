#if !defined  HAVE_TEST_GRAY_H__
#define       HAVE_TEST_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// comb/test-gray.cc:
ulong test_gray_path(const ulong *f, ulong n);
bool is_gray_path(const ulong *f, ulong n);
ulong test_canonical_gray(const ulong *f, ulong n);
bool is_canonical_gray(const ulong *f, ulong n);
bool is_monotonic_gray(const ulong *f, ulong n);
bool is_complementary_gray(const ulong *rv, ulong ng);


#endif  // !defined HAVE_TEST_GRAY_H__
