#if !defined  HAVE_MERS_HAAR_H__
#define       HAVE_MERS_HAAR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/constants.h"  // SQRT1_2
#include "fxttypes.h"  // ulong


inline void mersenne_haar(double *a, ulong f0)
// In-place Mersenne-Haar transform of a[0,...,f0-1].
// f0 must be a Mersenne number.
{
    if ( f0 < 2 )  return;
    ulong f1 = f0 >> 1;  // next smaller Mersenne number

//    for (ulong j=0, k=f0-1;  j<k;  ++j, --k)
    for (ulong j=0, k=f1+1;  j<f1;  ++j, ++k)
    {
        double u = a[j],  v = a[k];
        a[j] = (u+v) * SQRT1_2;
        a[k] = (u-v) * SQRT1_2;
    }
    mersenne_haar(a, f1);
}
// -------------------------


inline void mersenne_haar_nn(double *a, ulong f0)
// In-place Mersenne-Haar transform of a[0,...,f0-1].
// Non-normalized version.
// f0 must be a Mersenne number.
{
    if ( f0 < 2 )  return;
    ulong f1 = f0 >> 1;  // next smaller Mersenne number

//    for (ulong j=0, k=f0-1;  j<k;  ++j, --k)
    for (ulong j=0, k=f1+1;  j<f1;  ++j, ++k)
    {
        double u = a[j],  v = a[k];
        a[j] = (u+v);
        a[k] = (u-v);
    }
    mersenne_haar_nn(a, f1);
}
// -------------------------


#endif  // !defined HAVE_MERS_HAAR_H__
