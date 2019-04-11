#if !defined  HAVE_NORMAL_SOLVEQUADRATIC_H__
#define       HAVE_NORMAL_SOLVEQUADRATIC_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/revgraycode.h"
#include "bits/graycode.h"
#include "fxttypes.h"  // ulong


inline ulong normal_solve_reduced_quadratic(ulong c)
// Solve x^2 + x = c
// Must have:  trace(c)==0,  i.e. parity(c)==0
// Return one solution x, the other solution equals 1+x,
// that is, the complement of x.
{
    return  inverse_rev_gray_code(c);
    //    return  inverse_gray_code(c) >> 1;
    //    return  inverse_gray_code(c >> 1 );
}
// -------------------------

inline ulong normal_solve_reduced_quadratic_q(ulong c, ulong &x)
// Return t, the trace of c.
// If t==0 then x^2 + x = c is solvable
// and a solution is written to x.
{
    x = inverse_gray_code(c);
    ulong t = ( x & 1 );
    x >>= 1;  // immaterial if t==1, but avoid branch
    return t;
}
// -------------------------


#endif  // !defined HAVE_NORMAL_SOLVEQUADRATIC_H__
