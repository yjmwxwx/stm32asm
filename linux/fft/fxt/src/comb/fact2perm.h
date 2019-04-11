#if !defined  HAVE_FACT2PERM_H__
#define       HAVE_FACT2PERM_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

// comb/fact2perm.cc:
void perm2ffact(const ulong *x, ulong n, ulong *fc);
void ffact2perm(const ulong *fc, ulong n, ulong *x, bool iq=true);
void ffact2invperm(const ulong *fc, ulong n, ulong *x, bool iq=true);

void perm2rfact(const ulong *x, ulong n, ulong *fc);
void rfact2perm(const ulong *fc, ulong n, ulong *x, bool iq=true);
void rfact2invperm(const ulong *fc, ulong n, ulong *x, bool iq=true);

void perm_rev_compl(ulong *x, ulong n, bool zb=true);


// comb/fact2perm-swp.cc:
void perm2ffact_swp(const ulong *x, ulong n, ulong *fc);
void ffact2perm_swp(const ulong *fc, ulong n, ulong *x, bool iq=true);
void ffact2invperm_swp(const ulong *fc, ulong n, ulong *x, bool iq=true);

void perm2rfact_swp(const ulong *fc, ulong n, ulong *x);
void rfact2perm_swp(const ulong *fc, ulong n, ulong *x, bool iq=true);
void rfact2invperm_swp(const ulong *fc, ulong n, ulong *x, bool iq=true);


// comb/fact2perm-rev.cc:
void perm2ffact_rev(const ulong *x, ulong n, ulong *fc);
void ffact2perm_rev(const ulong *fc, ulong n, ulong *x, bool iq=true);

void perm2rfact_rev(const ulong *fc, ulong n, ulong *x);
void rfact2perm_rev(const ulong *fc, ulong n, ulong *x, bool iq=true);


// comb/fact2perm-rot.cc:
void perm2ffact_rot(const ulong *x, ulong n, ulong *fc);
void ffact2perm_rot(const ulong *fc, ulong n, ulong *x, bool iq=true);

void perm2rfact_rot(const ulong *x, ulong n, ulong *fc);
void rfact2perm_rot(const ulong *fc, ulong n, ulong *x, bool iq=true);


// comb/fact2cyclic.cc:
void ffact2cyclic(const ulong *fc, ulong n, ulong *x, bool iq=true);

void rfact2cyclic(const ulong *fc, ulong n, ulong *x, bool iq=true);


#endif  // !defined HAVE_FACT2PERM_H__
