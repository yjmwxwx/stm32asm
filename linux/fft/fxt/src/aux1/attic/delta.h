#if !defined HAVE_DELTA_H__
#define      HAVE_DELTA_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template <typename Type>
inline void make_delta(Type *f, ulong n, ulong d, Type v=1)
// Set to v at index d, other indices to zero.
{
    for (ulong k=0; k<n; ++k)  f[k] = 0;
    if ( d<n )  f[d] = v;
}
// -------------------------

//template <typename Type>
//inline ulong test_delta(const Type *f, ulong n, Type *vp, double eps=1e-7)
//// If f[] is a delta sequence then
////   return index 0<=i<n where f[i]!=0
////   and set vp to the value of the delta pulse
//// otherwise  return n
//{
//    ulong k = 0;
//    ulong i = n;
//    // search first element != 0:
//    while ( k<n )  { if ( 0!=f[k] ) break;  ++k; }
//    // check whether there is another one:
//    if ( k<n )
//    {
//        i = k;
//        ++k;
//        while ( k<n )
//        {
//            if ( 0!=f[k] ) { i = ~0UL; break; }
//            ++k;
//        }
//    }
//    if ( (i!=n) && (0!=vp) )  *vp = f[i];
//    // zero if sequence is not a delta seq.
//
//    return  i;
//}
//// -------------------------


#endif // !defined HAVE_DELTA_H__
