#if !defined  HAVE_BITPOL_PRIMITIVE_H__
#define       HAVE_BITPOL_PRIMITIVE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "mod/factor.h"
#include "bpol/bitpol-order.h"


inline ulong test_bitpol_primitive(ulong c, ulong h, const factorization &mfact)
// For an irreducible polynomial c, test whether it is primitive,
//  that is, whether 'x' is of maximal order.
// mfact must be the factorization of the maximal order (2**n-1).
// Return zero of c is primitive.
{
    ulong r = bitpol_order(c, h, mfact);
    ulong mers = ((h<<1)-1);  // == r==2**n-1
    r ^= mers;  // ==0 if r==mers
    return  r;
}
// -------------------------


#endif  // !defined HAVE_BITPOL_PRIMITIVE_H__
