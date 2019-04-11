#if !defined HAVE_DIFF_H__
#define      HAVE_DIFF_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

//<<
//  in  =  (sqr func in [0...6])
//    0-        +4
//    1-     +7.84
//    2-    +12.96
//    3-    +19.36
//    4-    +27.04
//    5-       +36
//
//  apply diff:
//    0-        +4 <-- unchanged
//    1-     +3.84
//    2-     +5.12
//    3-      +6.4
//    4-     +7.68
//    5-     +8.96
//
//  apply diff:
//    0-        +4 <-- unchanged
//    1-     +3.84 <-- unchanged
//    2-     +1.28
//    3-     +1.28
//    4-     +1.28
//    5-     +1.28
//
//  apply anti_diff:
//    0-        +4 <-- unchanged
//    1-     +3.84 <-- unchanged
//    2-     +5.12
//    3-      +6.4
//    4-     +7.68
//    5-     +8.96
//
//  apply anti_diff: (got back original)
//    0-        +4 <-- unchanged
//    1-     +7.84
//    2-    +12.96
//    3-    +19.36
//    4-    +27.04
//    5-       +36
//>>


template <typename Type>
inline void diff(Type *f, ulong n, ulong j=1)
// first difference (applied j times) of f[]
// element zero ('integration constant' is preserved) in each pass
{
    for (ulong k=1; k<=j; ++k)
    {
        ulong i = n - k;
        while ( 0!=i )  { f[i] -= f[i-1];  --i; }
    }
}
// -------------------------

template <typename Type>
inline void anti_diff(Type *f, ulong n, ulong j=1)
// inverse of diff()
{
    for (ulong k=j; k!=0; --k)
    {
        ulong i = 1;
        while ( i<=n-k )  { f[i] += f[i-1];  ++i; }
    }
}
// -------------------------


template <typename Type>
inline void diff(Type *f, ulong n, Type (*func)(Type, Type), ulong j=1)
// func on pairs (applied j times) applied to  f[] (result into right 'operand')
// element zero ('integration constant' is preserved) in each pass.
//
// With  Type func(Type a, Type b)  { return a-b; }  this is identical to
// the 'simple' diff()
{
    for (ulong k=1; k<=j; ++k)
    {
        ulong i = n - k;
        while ( 0!=i )  { f[i] = func(f[i], f[i-1]);  --i; }
    }
}
// -------------------------

template <typename Type>
inline void anti_diff(Type *f, ulong n, Type (*func)(Type, Type), ulong j=1)
// inverse of diff()
// ... whith appropriate 'inverse' func of course:
// if  func used in diff() is df with  df(a, b) =: x
// then func in anti_diff() af must be so that:  af(x, b) == a
// that is:
//  af(df(a, b), b) == a  for all a, b  (e.g. (a-b) + b == a)
// equivalently:
//  df(af(a, b), b) == a  for all a, b  (e.g. (a+b) - b == a)
//
// With  Type func(Type a, Type b)  { return a+b; }  this is identical to
// the 'simple' anti_diff()
{
    for (ulong k=j; k!=0; --k)
    {
        ulong i = 1;
        while ( i<=n-k )  { f[i] = func(f[i], f[i-1]);  ++i; }
    }
}
// -------------------------




#endif // !defined HAVE_DIFF_H__
