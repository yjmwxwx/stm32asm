#if !defined  HAVE_CLHCA_H__
#define       HAVE_CLHCA_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bmat/bitmat-funcs.h"  // bitmat_charpoly()
#include "bits/bitrotate.h"
#include "fxtalloca.h"
#include "fxttypes.h"


//: Cyclic (additive) Linear Hybrid Cellular Automata (CLHCA).

inline ulong clhca_next(ulong x, ulong r, ulong n)
// Compute next state of a linear hybrid cellular automaton
//  with cyclic boundary condition (CLHCA).
{
    r &= x;
    ulong t = x ^ bit_rotate_right(x, 1, n);
    t ^= r;
    return  t;
}
// -------------------------

inline ulong clhca2poly(ulong r, ulong n)
// Compute the binary polynomial corresponding
//   to the length-n CLHCA with rule r.
{
    ulong c = 1UL << n;
    for (ulong k=0; k<n; ++k)  if ( 0==(r & (1UL<<k)) )  c ^= (c>>1);
    c ^= 1;
    return c;
}
// -------------------------


inline ulong clhca2poly_too(ulong r, ulong n)
// Compute the binary polynomial corresponding
//   to the length-n CLHCA with rule r.
// This is the more general (and expensive) version.
{
    ALLOCA(ulong, M, n);  // tiny table
    for (ulong k=0; k<n; ++k)
    {
        // Function will compute polynomial for any
        // additive automaton when its next() function
        // is used in the following line:
        M[k] = clhca_next( 1UL<<k, r, n );
    }
    ulong c = bitmat_charpoly(M, n);
//    ulong c = bitmat_hessenberg2charpoly(M, n);  // shortcut for CLHCA

    return c;
}
// -------------------------


#endif  // !defined HAVE_CLHCA_H__
