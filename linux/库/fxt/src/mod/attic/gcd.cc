
#include "fxttypes.h"
#include "mod/numtheory.h"
#include "aux0/swap.h"

umod_t
ugcd(umod_t a, umod_t b)
{
    if ( a < b )  swap2(a, b);
    if ( b==0 )  return a;
    umod_t r;
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


smod_t
binary_sgcd(smod_t a, smod_t b)
{
    if ( a < b )  swap2(a, b);
    if ( b==0 )  return a;

    smod_t r = a % b;
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
        smod_t t = (a-b) >> 1;
        if ( t==0 )  return  a << k;

        while ( !(t&1) )  t >>= 1;

        if ( t>0 )  a =  t;
        else        b = -t;
    }
}
// -------------------------


umod_t
binary_ugcd(umod_t a, umod_t b)
{
    if ( a < b )  swap2(a, b);
    if ( b==0 )  return a;

    umod_t r = a % b;
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
        umod_t t = (a-b) >> 1;  // t>0

        while ( !(t&1) )  t >>= 1;
        a = t;
    }
}
// -------------------------


umod_t
ulcm(umod_t a, umod_t b)
{
    return  a / ugcd(a, b) * b;
}
// -------------------------


smod_t
egcd(smod_t u, smod_t v, smod_t &u1, smod_t &u2)
//
// Return u3 and set u1,v1 so that
//   u3 == u*u1 + v*u2
//
// Cf. Knuth2, p.325
{
    smod_t v1 = 0;
    smod_t v3 = v;

    u1 = 1;
    u2 = 0;
    smod_t u3 = u;
    smod_t v2 = 1;
    while ( v3!=0 )
    {
        smod_t q = u3 / v3;

        smod_t t1 = u1 - v1 * q;
        u1 = v1;
        v1 = t1;

        smod_t t3 = u3 - v3 * q;
        u3 = v3;
        v3 = t3;

        smod_t t2 = u2 - v2 * q;
        u2 = v2;
        v2 = t2;
    }

    return u3;
}
// -------------------------

