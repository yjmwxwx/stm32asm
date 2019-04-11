#if !defined  HAVE_FACTORIAL_H__
#define       HAVE_FACTORIAL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "fxttypes.h"

template <typename Type>
inline Type factorial(Type n)
// Return n!
//.
// For n<=12 n! fits into 32 bits.
// For n<=20 n! fits into 64 bits.
// For n<=34 n! fits into 128 bits.
// For n<=57 n! fits into 256 bits.
{
    Type f = 1;
    while ( n>1 )  { f *= n;  --n; }
    return f;
}
// -------------------------

template <typename Type>
inline Type ffactpow(Type x, Type n)
// Falling factorial power.
{
    Type p = 1;
    for (Type k=0; k<n; ++k)  p *= (x-k);
    return p;
}
// -------------------------

template <typename Type>
inline Type rfactpow(Type x, Type n)
// Rising factorial power.
{
    Type p = 1;
    for (Type k=0; k<n; ++k)  p *= (x+k);
    return p;
}
// -------------------------



#endif  // !defined HAVE_FACTORIAL_H__
