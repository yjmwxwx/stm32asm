#if !defined  HAVE_FIB_WALSH_H__
#define       HAVE_FIB_WALSH_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/constants.h"  // SQRT1_2
#include "fxttypes.h"  // ulong


inline void fibonacci_walsh(double *a, ulong f0, ulong f1)
// In-place Fibonacci-Walsh transform of a[0,...,f0-1].
// f0 must be a Fibonacci number, f1 the next smaller Fibonacci number.
{
    if ( f0 < 2 )  return;

    ulong f2 = f0 - f1;
    for (ulong j=0, k=f1;  j<f2;  ++j, ++k)
    {
        double u = a[j],  v = a[k];
        a[j] = (u+v) * SQRT1_2;
        a[k] = (u-v) * SQRT1_2;
    }
    fibonacci_walsh(a, f1, f2);
    fibonacci_walsh(a+f1, f2, f1-f2);
}
// -------------------------


inline void fibonacci_walsh_nn(double *a, ulong f0, ulong f1)
// In-place Fibonacci-Walsh transform of a[0,...,f0-1].
// Non-normalized version.
// f0 must be a Fibonacci number, f1 the next smaller Fibonacci number.
{
    if ( f0 < 2 )  return;

    ulong f2 = f0 - f1;
    for (ulong j=0, k=f1;  j<f2;  ++j, ++k)
    {
        double u = a[j],  v = a[k];
        a[j] = (u+v);
        a[k] = (u-v);
    }
    fibonacci_walsh_nn(a, f1, f2);
    fibonacci_walsh_nn(a+f1, f2, f1-f2);
}
// -------------------------


#endif  // !defined HAVE_FIB_WALSH_H__
