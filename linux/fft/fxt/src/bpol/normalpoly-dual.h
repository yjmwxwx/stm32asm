#if !defined  HAVE_NORMALPOLY_DUAL_H__
#define       HAVE_NORMALPOLY_DUAL_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

// bpol/normalpoly-dual.cc:
ulong gf2n_xx2k_trace(ulong c, ulong deg);
ulong gf2n_dual_normal(ulong c, ulong deg, ulong t=0, ulong *dt=0);


#endif  // !defined HAVE_NORMALPOLY_DUAL_H__
