#if !defined  HAVE_PARTITION_CONJ_H__
#define       HAVE_PARTITION_CONJ_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// comb/partition-conj.cc:
ulong partition_asc_conj(const ulong *a, ulong m, ulong *b);
bool partition_asc_is_conj(const ulong *a, ulong ma, const ulong *b, ulong mb);
bool partition_asc_is_self_conj(const ulong *a, ulong m);

ulong partition_desc_conj(const ulong *a, ulong m, ulong *b);
bool partition_desc_is_conj(const ulong *a, ulong ma, const ulong *b, ulong mb);
bool partition_desc_is_self_conj(const ulong *a, ulong m);


#endif  // !defined HAVE_PARTITION_CONJ_H__
