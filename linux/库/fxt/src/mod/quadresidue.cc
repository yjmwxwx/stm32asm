// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/factor.h"
#include "mod/numtheory.h"

#include "mod/mtypes.h"
#include "fxttypes.h"  // ulong


bool
is_quadratic_residue_2ex(umod_t a, ulong x)
// Return whether a is quadratic residue mod 2**x
{
    if ( x==1 )  return true;
    if ( (x>=3 ) && (1==(a&7)) )  return true;
    if ( (x==2 ) && (1==(a&3)) )  return true;
    return false;
}
// -------------------------


bool
is_quadratic_residue(umod_t a, const factorization &mf)
// Return whether a is quadratic residue mod mf
{
    for (ulong i=0; i<mf.nprimes(); ++i)
    {
        umod_t p = mf.prime(i);
        if ( 2==p )
        {
            ulong x = mf.exponent(i);
            return  is_quadratic_residue_2ex(a, x);
        }

        if ( 1!=kronecker(a, p) )  return false;
    }

    return true;
}
// -------------------------


//bool
//is_quadratic_residue(const factorization &af, umod_t m)
//// Return whether af is quadratic residue mod m
////.
//// use (a*b/c) == (a/c) * (b/c)
//{
//    int k = 1;
//    for (ulong i=0; i<af.nprimes(); ++i)
//    {
//        int s = kronecker(af.prime(i), m);
//        if ( 1 & (af.exponent(i)) )  s = -s;
//        k *= s;
//    }
//
//    return  0==k;
//}
//// -------------------------
