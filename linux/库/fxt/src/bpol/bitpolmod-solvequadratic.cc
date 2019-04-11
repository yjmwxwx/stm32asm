// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/bitpol-degree.h"  // bitpol_h()
#include "bpol/bitpolmod-arith.h"
#include "bpol/gf2n-trace.h"  // gf2n_trace()
#include "fxttypes.h"  // ulong


bool
bitpolmod_solve_reduced_quadratic(ulong c, ulong& r, ulong m)
// Solve  z^2 + z == c modulo m
// Return whether solutions exist.
// If so, one solutions is written to r.
// The other solution is r+1.
{
    const ulong h = bitpol_h(m);
    if ( 1==gf2n_trace(c, m, h) )  return  false;

    const ulong tv = gf2n_trace_vector(2, m, h);
    ulong t = lowest_one(tv);  // an element with trace one
    ulong u = t;
    ulong z = 0;
    ulong j = h;
    while ( j>>=1 )
    {
        ulong u2 = bitpolmod_square(u, m, h);
        z = bitpolmod_square(z, m, h);
        z ^= bitpolmod_mult(u2, c, m, h);  // z = z*z + c*u*u
        u = u2 ^ t;  // u = u*u + t
    }
    r = z;

    return  true;
}
// -------------------------


bool
bitpolmod_solve_quadratic(ulong a, ulong b, ulong c, ulong& r0, ulong& r1, ulong m)
// Solve  a*z^2 + b*z + c == 0  modulo m
// Return whether solutions exist.
// If so, the solutions are written to r0 and r1.
// Must have: m irreducible.
{
    const ulong h = bitpol_h(m);
    ulong cc = bitpolmod_mult(a, c, m, h);
    ulong b2 = bitpolmod_square(b, m, h);
    cc = bitpolmod_divide(cc, b2, m, h);  // cc = (a*c)/(b*b)
    ulong r;
    bool q = bitpolmod_solve_reduced_quadratic(cc, r, m);
    if ( !q )  return  false;

    ulong s = bitpolmod_divide(b, a, m, h);
    r0 = bitpolmod_mult(r, s, m, h);
    r1 = bitpolmod_mult(r^1, s, m, h);

    return  true;
}
// -------------------------
