#if !defined  HAVE_GCD_H__
#define       HAVE_GCD_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "fxttypes.h"


template <typename Type>
Type gcd(Type a, Type b)
// Return greatest common divisor of a and b.
{
    if ( a < b )  swap2(a, b);
    if ( b==0 )  return a;
    Type r;
    do
    {
        r = a % b;
        a = b;
        b = r;
    }
    while ( r!=0 );
    return a;
}
// -------------------------


template <typename Type>
Type egcd(Type u, Type v, Type &tu1, Type &tu2)
// Return u3 and set u1,v1 so that
//   gcd(u,v) == u3 == u*u1 + v*u2
// Type must be a signed type.
//.
// Cf. Knuth2, p.325
{
    Type u1 = 1,  u2 = 0;
    Type v1 = 0,  v3 = v;
    Type u3 = u,  v2 = 1;
    while ( v3!=0 )
    {
        Type q = u3 / v3;

        Type t1 = u1 - v1 * q;
        u1 = v1;  v1 = t1;

        Type t3 = u3 - v3 * q;
        u3 = v3;  v3 = t3;

        Type t2 = u2 - v2 * q;
        u2 = v2;  v2 = t2;
    }
    tu1 = u1;  tu2 = u2;
    return u3;
}
// -------------------------




template <typename Type>
Type binary_ugcd(Type a, Type b)
// Return greatest common divisor of a and b.
// Version for unsigned types.
{
    if ( a < b )  swap2(a, b);
    if ( b==0 )  return a;

    Type r = a % b;
    a = b;
    b = r;
    if ( b==0 )  return a;

    ulong k = 0;
    while ( !((a|b)&1) )  // both even
    {
        k++;
        a >>= 1;
        b >>= 1;
    }

    while ( !(a&1) )  a >>= 1;
    while ( !(b&1) )  b >>= 1;

    while ( 1 )
    {
        if ( a==b )  return  a << k;

        if ( a < b )  swap2(a, b);
        Type t = (a-b) >> 1;  // t>0

        while ( !(t&1) )  t >>= 1;
        a = t;
    }
}
// -------------------------


template <typename Type>
Type binary_sgcd(Type a, Type b)
// Return greatest common divisor of a and b.
// Version for signed types.
{
    if ( a < b )  swap2(a, b);
    if ( b==0 )  return a;

    Type r = a % b;
    a = b;
    b = r;
    if ( b==0 )  return a;

    ulong k = 0;
    while ( !((a|b)&1) )  // both even
    {
        k++;
        a >>= 1;
        b >>= 1;
    }

    while ( !(a&1) )  a >>= 1;
    while ( !(b&1) )  b >>= 1;

    while ( 1 )
    {
        Type t = (a-b) >> 1;
        if ( t==0 )  return  a << k;

        while ( !(t&1) )  t >>= 1;

        if ( t>0 )  a =  t;  // <--= signed
        else        b = -t;
    }
}
// -------------------------


template <typename Type>
Type lcm(Type a, Type b)
// Return least common multiple of a and b.
{
    return  a / gcd(a, b) * b;
}
// -------------------------



#endif  // !defined HAVE_GCD_H__
