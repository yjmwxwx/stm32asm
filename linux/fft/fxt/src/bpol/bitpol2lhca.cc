// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/bitpolmod-solvequadratic.h"
#include "bpol/bitpol-degree.h"
#include "bpol/bitpol-deriv.h"
#include "bpol/bitpolmod-arith.h"
#include "bits/revbin.h"
#include "fxttypes.h"

ulong
poly2lhca(ulong p)
// Return LHCA rule corresponding to the binary polynomial P.
// Must have: P irreducible.
{
    ulong dp = bitpol_deriv(p);
    const ulong h = bitpol_h(p);

    ulong b = dp;
    b ^= bitpolmod_times_x(b, p, h);  // p' * (x+1)
    b = bitpolmod_times_x(b, p, h);  // p' * (x^2+x)

    ulong r0, r1;  // solutions of  1 + (p'*(x*x+x))*z + z*z == 0 modulo p
    bool q = bitpolmod_solve_quadratic(1, b, 1, r0, r1, p);
    if ( 0==q )  return 0;

    // GCD steps:
    ulong r = 0;  // rule vector
    ulong x = p,  y = r0;  // same result with r1
    while ( y )
    {
        ulong tq, tr;
        bitpol_divrem(x, y, tq, tr);
        r <<= 1;
        r |= (tq & 1);
        x = y;
        y = tr;
    }

//    r = revbin(r, bitpol_deg(p));

    return r;
}
// -------------------------
