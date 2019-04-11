
#include "fxttypes.h"
//#include "jjassert.h"


ulong
ugcd(ulong a, ulong b)
{
    if ( a==0 )  return b;
    if ( b==0 )  return a;
    ulong r;
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

long
sgcd(long a, long b)
{
    if ( a==0 )  return b;
    if ( b==0 )  return a;
    long r;
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



long
binary_sgcd(long a, long b)
// Cf. Cohen p.14
{
    if ( a < b )  { long t = a; a = b; b = t; }
    if ( b==0 )  return a;

    long r = a % b;
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
        long t = (a-b) >> 1;
        if ( t==0 )  return  a << k;

        while ( !(t&1) )  t >>= 1;

        if ( t>0 )  a =  t;
        else        b = -t;
    }
}
// -------------------------

ulong
binary_ugcd(ulong a, ulong b)
{
    if ( a < b )  { ulong t = a; a = b; b = t; }
    if ( b==0 )  return a;

    ulong r = a % b;
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

        if ( a < b )  { ulong t = a; a = b; b = t; }
        ulong t = (a-b) >> 1;  // t>0
        while ( !(t&1) )  t >>= 1;
        a =  t;
    }
}
// -------------------------


ulong
ulcm(ulong a, ulong b)
{
    return  a / ugcd(a, b) * b;
}
// -------------------------


long
egcd(long u, long v, long &u1, long &u2)
// Return u3 and set u1,v1 so that
//   u3 == u*u1 + v*u2
//
// Cf. Knuth2, p.325
{
    long v1 = 0;
    long v3 = v;

    u1 = 1;
    u2 = 0;
    long u3 = u;
    long v2 = 1;
    while ( v3!=0 )
    {
        long q = u3/v3;

        long t1 = u1-v1*q;
        u1 = v1;
        v1 = t1;

        long t3 = u3-v3*q; // u3%v3
        u3 = v3;
        v3 = t3;

        long t2 = u2-v2*q;
        u2 = v2;
        v2 = t2;

//        jjassert( u*t1+v*t2==t3 );
//        jjassert( u*u1+v*u2==u3 );
//        jjassert( u*v1+v*v2==v3 );
    }

//    jjassert( (ulong)u3==gcd(u,v) );
//    jjassert( u*u1+v*u2==u3 );

    return u3;
}
// -------------------------

