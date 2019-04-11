#if !defined HAVE_SIGN_H__
#define      HAVE_SIGN_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.



template <typename Type>
static inline Type sign(const Type &x)
// Return sign(x)
{ return  x<0 ? -1 : (x==0?0:1); }

template <typename Type>
static inline Type sign1(const Type &x)
// Return 1 if x==0, else sign(x)
{ return  x<0 ? -1 : 1; }

template <typename Type>
static inline int sign_bit(const Type &x)
// Return 1 if x<0, else 0
{ return  x<0 ? 1 : 0; }

template <typename Type>
static inline Type Abs(const Type &x)
// Return abs(x)
{ return  x>=0 ? x : -x; }

//template <typename Type>
//static inline Type  sqr(Type x)
//{ return  x * x; }



#endif  // !defined HAVE_SIGN_H__
