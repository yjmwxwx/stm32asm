#if !defined  HAVE_MODARITH_H__
#define       HAVE_MODARITH_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux0/ipow.h"  // ipow()
#include "aux0/gcd.h"  // egcd()
#include "mod/mtypes.h"
#include "mod/factor.h"

// whether to use left-to-right exponentiation:
//#define MODPOW_USE_L2R  // default: off
#ifdef MODPOW_USE_L2R
#include "bits/bitsperlong.h"
#endif

// arithmetic modulo some arbitrary modulus


//inline umod_t reduce_mod(umod_t x, umod_t m)
//{ if ( x>=m )  x %= m;  return x; }

inline umod_t incr_mod(umod_t a, umod_t m)
{ a++; if ( a==m )  a = 0;  return a; }

inline umod_t decr_mod(umod_t a, umod_t m)
{ if ( a==0 )  a = m - 1; else a--;  return a; }

inline umod_t neg_mod(umod_t b, umod_t m)
{ if ( 0==b )  return 0;  else  return m - b; }

inline umod_t sub_mod(umod_t a, umod_t b, umod_t m)
{
    if ( a>=b )  return  a - b;
    else         return  m - b + a;
}
// -------------------------

inline umod_t add_mod(umod_t a, umod_t b, umod_t m)
{
    if ( 0==b )  return  a;
    // return sub_mod(a, m-b, m);
    b = m - b;
    if ( a>=b )  return  a - b;
    else         return  m - b + a;
}
// -------------------------

inline umod_t mul_mod(umod_t a, umod_t b, umod_t m)
{
    umod_t x = a * b;
    umod_t y = m * (umod_t)( (ldouble)a * (ldouble)b/m + (ldouble)1/2 );
    umod_t r = x - y;
    if ( (smod_t)r < 0 )  r += m;
    return  r;
}
// -------------------------

inline umod_t sqr_mod(umod_t a, umod_t m)
{
    return  mul_mod(a, a, m);
}
// -------------------------

inline umod_t mul_mod_m1dd(umod_t a, umod_t b, umod_t m, ldouble m1dd)
// NOTE: fails for some moduli >62bit, e.g. 0x7ffedc0000000001
{
    umod_t x = a * b;
    umod_t y = m * (umod_t)( (ldouble)a * (ldouble)b * m1dd + (ldouble)1/2 );
    umod_t r = x - y;
    if ( (smod_t)r < 0 )  r += m;
    return  r;
}
// -------------------------


#ifdef MODPOW_USE_L2R
inline umod_t pow_mod(umod_t a, umod_t e, umod_t m)
// Left-to-right scan
{
    if ( 0==e )  return 1;
    umod_t s = a;

//    umod_t b = highest_one(e);  // fails if sizeof(ulong) != sizeof(umod_t)
    umod_t b = 1ULL << (BITS_PER_LONG_LONG-1);
    while ( b>e )  b >>= 1;

    while ( b>1 )
    {
        b >>= 1;
        s = sqr_mod(s, m);  // s *= s;
        if ( e & b )  s = mul_mod(s, a, m);  // s *= a;
    }
    return s;
}
// -------------------------

#else  // def MODPOW_USE_L2R

inline umod_t pow_mod(umod_t a, umod_t e, umod_t m)
// Right-to-left scan
{
    if ( 0==e )  return 1;
    else
    {
        umod_t z = a;
        umod_t y = 1;
        while ( 1 )
        {
            if ( e & 1 )  y = mul_mod(y, z, m);  // y *= z;
            e >>= 1;
            if ( 0==e )  break;
            z = sqr_mod(z, m);  // z *= z;
        }
        return  y;
    }
}
// -------------------------
#endif  // def MODPOW_USE_L2R


inline umod_t inv_modp(umod_t a, umod_t p)
// compute inverse of a modulo p where p is prime
{
    return  pow_mod(a, p-2, p);
}
// -------------------------


inline umod_t inv_modpp(umod_t a, umod_t p, ulong e)
// compute inverse of a modulo p^e where p is prime
{
    umod_t v = p-1;
    if ( e>1 )  v *= ipow(p, e-1);
    return  pow_mod(a, v-1, p);
}
// -------------------------


inline umod_t inv_mod_egcd(umod_t x, umod_t m)
// NOTE: computation of mod inverse by egcd()
// does not work for moduli >=2**63 because
// signed types are used.
{
    smod_t u, v;
    /*smod_t d =*/ egcd((smod_t)m, (smod_t)x, u, v);    // d==m*u+x*v
    if ( v<0 )  v += m;
    return  (umod_t)v;
}
// -------------------------

#undef MODPOW_USE_L2R


#endif  // !defined HAVE_MODARITH_H__
