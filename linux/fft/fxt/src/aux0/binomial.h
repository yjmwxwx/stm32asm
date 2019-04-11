#if !defined  HAVE_BINOMIAL_H__
#define       HAVE_BINOMIAL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// Code for the binomial coefficients more carefully
// guarded against overflow is available at
//   https://gist.github.com/jlaire/be48c44c59770051e467
// Reported by Johannes Laire, 21 Oct 2015

inline ulong binomial(ulong n, ulong k)
{
    if ( k>n )  return  0;
    if ( (k==0) || (k==n) )  return  1;
//    if ( 2*k > n )  // use symmetry
    if ( k > n / 2 )  k = n-k;  // use symmetry

    ulong b = n - k + 1;
    ulong f = b;
    for (ulong j=2; j<=k; ++j)
    {
        ++f;
        b *= f;
        b /= j;
    }
    return  b;
}
// -------------------------


#endif  // !defined HAVE_BINOMIAL_H__
