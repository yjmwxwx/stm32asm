#if !defined  HAVE_SWAP_H__
#define       HAVE_SWAP_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


template <typename Type>
static inline void  swap2(Type &x, Type &y)
// swap values
{ Type t(x);  x = y;  y = t; }

template <typename Type>
static inline void  swap0(Type &x, Type &y)
// swap() for y known to be zero
{ y = x;  x = 0; }


#endif  // !defined HAVE_SWAP_H__
