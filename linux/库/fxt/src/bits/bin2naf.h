#if !defined  HAVE_BIN2NAF_H__
#define       HAVE_BIN2NAF_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

static inline void bin2naf(ulong x, ulong &np, ulong &nm)
// Compute (nonadjacent form, NAF) signed binary representation of x:
// the unique representation of x as
//   x=\sum_{k}{d_k*2^k} where d_j \in {-1,0,+1}
//   and no two adjacent digits d_j, d_{j+1} are both nonzero.
// np has bits j set where d_j==+1
// nm has bits j set where d_j==-1
// We have:  x = np - nm
{
    ulong xh = x >> 1;  // x/2
    ulong x3 = x + xh;  // 3*x/2
    ulong c = xh ^ x3;
    np = x3 & c;
    nm = xh & c;
}
// -------------------------


static inline ulong naf2bin(ulong np, ulong nm)
// Inverse of bin2naf()
// Works also for signed-binary pairs np, nm
// that are not nonadjacent forms.
{
    return  np - nm;
}
// -------------------------


static inline void bin2sbin(ulong x, ulong &np, ulong &nm)
// Compute a signed binary representation of x:
// a representation of x as
//   x=\sum_{k}{d_k*2^k} where d_j \in {-1,0,+1}
// Inverse function is naf2bin().
{
    ulong xh = x << 1;
    ulong xr = x ^ xh;
    np = xr & xh;
    nm = xr & x;
}
// -------------------------


#endif  // !defined HAVE_BIN2NAF_H__
