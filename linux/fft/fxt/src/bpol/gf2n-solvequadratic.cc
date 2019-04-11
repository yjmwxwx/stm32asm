// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/gf2n.h"
#include "fxttypes.h"  // ulong


bool
gf2n_solve_reduced_quadratic(GF2n c, GF2n& r)
// Solve  z^2 + z == c
// Return  whether solutions exist.
// If so, one solutions is written to r.
// The other solution is r+1.
{
    if ( 1==c.trace() )  return  false;

#if 1
    if ( 1 & (GF2n::n_) )  // odd n:  use half_trace
    {
        r = c.half_trace();
    }
    else  // even n:  (also works for odd n)
#endif
    {
        GF2n t( GF2n::tr1e );
        GF2n z( GF2n::zero );
        GF2n u( t );
        for (ulong j=1; j<GF2n::n_; ++j)
        {
            GF2n u2 = u.sqr();
            z = z.sqr();  z += u2*c;   // z = z*z + c*u*u
            u = u2 + t;                // u = u*u + t
        }
        r = z;
    }

    return  true;
}
// -------------------------


bool
gf2n_solve_quadratic(GF2n a, GF2n b, GF2n c, GF2n& r0, GF2n& r1)
// Solve  a*z^2 + b*z + c == 0
// Return  whether solutions exist.
// If so, the solutions are written to r0 and r1.
{
    GF2n cc = a * c;
    cc /= (b.sqr());  // cc = (a*c)/(b*b)
    GF2n r;
    bool q = gf2n_solve_reduced_quadratic(cc, r);
    if ( !q )  return  false;

    GF2n s = b / a;
    r0 = r * s;
    r1 = (r + GF2n::one) * s;

    return  true;
}
// -------------------------

