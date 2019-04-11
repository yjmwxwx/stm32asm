#if !defined  HAVE_FIBONACCI_H__
#define       HAVE_FIBONACCI_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

inline ulong fibonacci(ulong n)
// Return the n-th Fibonacci number
// Limitation:  F(n) must fit into ulong
// 32 bit:  n<=47, F(47)=2971215073 [F(48)=4807526976 > 2^32]
// 64 bit:  n<=93  F(93)=12200160415121876738 [F(94) > 2^64]
{
    if ( n<=1 )  return n;
    ulong f0=0, f1=1;
    for (ulong k=1; k<n; ++k)  { ulong t=f0+f1;  f0=f1;  f1=t; }
    return f1;
}
// -------------------------

inline void fibonacci_pair(ulong n, ulong &f0, ulong &f1)
// Set f0 to F(n), the n-th Fibonacci number, and
// f1 to the F(n-1).
// Limitation:  F(n) must fit into ulong
// 32 bit:  n<=47, F(47)=2971215073 [F(48)=4807526976 > 2^32]
// 64 bit:  n<=93  F(93)=12200160415121876738 [F(94) > 2^64]
{
    ulong a=0, b=1;
    for (ulong k=1; k<n; ++k)  { ulong t=a+b;  a=b;  b=t; }
    f0 = b;
    f1 = a;
}
// -------------------------



#endif  // !defined HAVE_FIBONACCI_H__
