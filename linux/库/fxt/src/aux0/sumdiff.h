#if !defined HAVE_SUMDIFF_H__
#define      HAVE_SUMDIFF_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "aux0/sumdiff.h"  // this file

template <typename Type>
static inline void sumdiff(Type &a, Type &b)
// {a, b}  <--| {a+b, a-b}
{ Type t=a-b; a+=b; b=t; }

template <typename Type>
static inline void sumdiff_r(Type &a, Type &b)
// {a, b}  <--| {b+a, b-a}
// Up to scaling (by a factor 2) the inverse of diffsum(a,b).
{ Type t=b-a; a+=b; b=t; }


template <typename Type>
static inline void sumdiff05(Type &a, Type &b)
// {a, b}  <--| {0.5*(a+b),  0.5*(a-b)}
{ Type t=(a-b)*0.5; a+=b; a*=0.5; b=t; }

template <typename Type>
static inline void sumdiff05_r(Type &a, Type &b)
// {a, b}  <--| {0.5*(a+b), 0.5*(b-a)}
{ Type t=(b-a)*0.5; a+=b; a*=0.5; b=t; }

template <typename Type>
static inline void diffsum(Type &a, Type &b)
// {a, b}  <--| {a-b, a+b}
// Up to scaling (by a factor 2) the inverse of sumdiff_r(a,b).
{ Type t=a-b; b+=a; a=t; }

//template <typename Type>
//static inline void diffsum_r(Type &d, Type &a)
//// {a, b}  <--| {b-a, a+b}
//{ Type t=b-a; b+=a; a=t; }


// ------ 4 arg versions:

template <typename Type>
static inline void sumdiff(Type a, Type b, Type &s, Type &d)
// {s, d}  <--| {a+b, a-b}
{ s=a+b; d=a-b; }

template <typename Type>
static inline void sumdiff05(Type a, Type b, Type &s, Type &d)
// {s, d}  <--| {0.5*(a+b), 0.5*(a-b)}
{ s=(a+b)*0.5; d=(a-b)*0.5; }


// ------ 3 arg versions used in split-radix FFTs:

template <typename Type>
static inline void sumdiff3(Type &a, Type b, Type &d)
// {a, b, d} <--| {a+b, b, a-b}  (used in split-radix FFTs)
// NEVER call like func(a,b,a) or func(a,b,b)
{ d=a-b; a+=b; }

template <typename Type>
static inline void sumdiff3_r(Type &a, Type b, Type &d)
// {a,b,d} <--| {a+b, b, b-a}  (used in split-radix FFTs)
// NEVER call like func(a,b,a) or func(a,b,b)
{ d=b-a; a+=b; }

template <typename Type>
static inline void diffsum3(Type a, Type &b, Type &s)
// {a, b, s} <--| {a, a-b, a+b}  (used in split-radix FFTs)
// NEVER call like func(a,b,a) or func(a,b,b)
{ s=a+b; b=a-b; }

template <typename Type>
static inline void diffsum3_r(Type a, Type &b, Type &s)
// {a, b, s} <--| {a, b-a, a+b}  (used in split-radix FFTs)
// NEVER call like func(a,b,a) or func(a,b,b)
{ s=a+b; b-=a; }


#endif  // !defined HAVE_SUMDIFF_H__
