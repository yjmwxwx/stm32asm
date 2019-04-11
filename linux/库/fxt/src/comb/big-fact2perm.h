#if !defined  HAVE_BIG_FACT2PERM_H__
#define       HAVE_BIG_FACT2PERM_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

// ds/left-right-array.h
class left_right_array;

// comb/big-fact2perm.cc:
void perm2ffact(const ulong *x, ulong n, ulong *fc, left_right_array &LR);
void ffact2perm(const ulong *fc, ulong n, ulong *x, left_right_array &LR);
void ffact2invperm(const ulong *fc, ulong n, ulong *x, left_right_array &LR);

void perm2rfact(const ulong *x, ulong n, ulong *fc, left_right_array &LR);
void rfact2perm(const ulong *fc, ulong n, ulong *x, left_right_array &LR);
void rfact2invperm(const ulong *fc, ulong n, ulong *x, left_right_array &LR);


#endif  // !defined HAVE_BIG_FACT2PERM_H__
