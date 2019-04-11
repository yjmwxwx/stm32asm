#if !defined  HAVE_NUM2PERM_H__
#define       HAVE_NUM2PERM_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


// comb/num2perm.cc:
void num2perm_rfact(ulong x, ulong *f, ulong n);
ulong perm2num_rfact(const ulong *f, ulong n);
void num2perm_ffact(ulong x, ulong *f, ulong n);
ulong perm2num_ffact(const ulong *f, ulong n);
//void num2perm(ulong x, ulong *f, ulong n);
//ulong perm2num(const ulong *f, ulong n);

void num2perm_swp(ulong x, ulong *f, ulong n);
ulong perm2num_swp(const ulong *f, ulong n);

ulong permlex2num(const ulong *f, ulong n);



#endif  // !defined HAVE_NUM2PERM_H__
