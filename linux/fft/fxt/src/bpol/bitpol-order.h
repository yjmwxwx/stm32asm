#if !defined  HAVE_BITPOL_ORDER_H__
#define       HAVE_BITPOL_ORDER_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

// bpol/bitpol-order.cc:
class factorization;
ulong bitpol_el_order(ulong c, ulong h, const factorization &mfact, ulong a);
ulong bitpol_order(ulong c, ulong hc, const factorization &mfact);


#endif  // !defined HAVE_BITPOL_ORDER_H__
