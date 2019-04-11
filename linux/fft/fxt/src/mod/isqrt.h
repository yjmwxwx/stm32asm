#if !defined  HAVE_ISQRT_H__
#define       HAVE_ISQRT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>  // ceil()


template <typename Type>
Type isqrt(Type d)
// Return x (the integer quare root of d) so that
//  x*x <= d  and  (x+1)*(x+1) > d
//.
// see Cohen p.38
{
    Type x = (Type)ceil(sqrt((double)d));
//    Type x = 1;
//    for (Type dd=d;  0!=dd;  dd>>=2)  x <<= 1;

    Type y = (x + d/x)/2;
    while ( y<x )
    {
        x = y;
        y = (x + d/x)/2;
    }

    return  x;
}
// -------------------------

#endif  // !defined HAVE_ISQRT_H__
