#if !defined  HAVE_SORT23FUNC_H__
#define       HAVE_SORT23FUNC_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "fxttypes.h"


//: Sorting 2 or 3 elements, with comparison function


template <typename Type>
inline void sort2(Type &x1, Type &x2,
                  int (*cmp)(const Type &, const Type &))
// sort x1, x2 wrt. cmp()
{
    if ( cmp(x1, x2) > 0 )  swap2(x1, x2);
}
// -------------------------


template <typename Type>
inline void sort3(Type &x0, Type &x1, Type &x2,
                  int (*cmp)(const Type &, const Type &))
// sort x0, x1, x2
// =^= { sort2(x0,x1); sort2(x1,x2); sort2(x0,x1); }
{
    sort2(x0, x1, cmp);
    if ( cmp(x1, x2) > 0 )
    {
        swap2(x1, x2);
        sort2(x0, x1, cmp);
    }
}
// -------------------------



#endif  // !defined HAVE_SORT23FUNC_H__
