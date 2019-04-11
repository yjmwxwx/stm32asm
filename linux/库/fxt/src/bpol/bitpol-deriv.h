#if !defined  HAVE_BITPOL_DERIV_H__
#define       HAVE_BITPOL_DERIV_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"  // ulong
#include "bits/bitsperlong.h"


inline ulong bitpol_deriv(ulong c)
// Return derivative of polynomial c
{
#if  BITS_PER_LONG >= 64
    c &= 0xaaaaaaaaaaaaaaaaUL;
#else
    c &= 0xaaaaaaaaUL;
#endif
    return  (c>>1);
}
// -------------------------


#endif  // !defined HAVE_BITPOL_DERIV_H__
