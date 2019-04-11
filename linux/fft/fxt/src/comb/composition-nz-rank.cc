// This file is part of the FXT library.
// Copyright (C) 2012, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/graycode.h"  // inverse_gray_code()

#include "bits/bitlex.h"  // lexrev2negidx(), negidx2lexrev

#include "bits/bithigh.h"  // highest_one_idx()

#include "fxttypes.h"

#include "comb/composition-nz-rank.h"

//#include "jjassert.h"


ulong
composition_nz_rank(const ulong *x, ulong m)
// Return rank r of composition x[], 0 <= r < 2**(n-1)
// where n is the sum of all parts.
// For lexicographic order (cf. class composition_nz).
{
    if ( m==0 )  return 0;
    // make things work with the empty composition
    // represented as one part which is zero:
    if ( x[0]==0 )  return 0;

    ulong r = 0;
    ulong b = 1;
    ulong j = m;
    do // read from x[m-1], x[m-2], ..., x[0]
    {
        --j;
        ulong p = x[j];
        while ( --p != 0 )
        {
            r |= b;
            b <<= 1;
        }
        b <<= 1;
    }
    while ( j );

    return  r;
}
// -------------------------


ulong
composition_nz_unrank(ulong r, ulong *x, ulong n)
// Generate composition x[] of n with rank r.
// Return number of parts m of generated composition, 1 <= m <= n.
// For lexicographic order (cf. class composition_nz).
// The rank r is taken modulo  2 ** (n-1).
{
    if ( n == 0 )  return 0;

    // take rank modulo 2 ** (n-1):
    ulong b = 1UL << (n-1);
    r &= (b - 1);

    ulong s = 0;
    ulong m = 0;
    while ( s < n )  // write to x[0], x[1], ...
    {
        b >>= 1;
        ulong p = 1;
        while ( r & b )
        {
            ++p;
            b >>= 1;
        }
        x[m] = p;
        s += p;
        ++m;
    }
//    jjassert( s == n );

    return m;
}
// -------------------------


ulong
composition_nz_rl_rank(const ulong *x, ulong m)
// Return (run-length) rank r of composition x[], 0 <= r < 2**(n-1)
// where n is the sum of all parts.
// For RL-order (cf. class composition_nz_rl).
{
    if ( m==0 )  return 0;

    ulong r = composition_nz_rank(x, m);
    r = ~r;
    r = inverse_gray_code(r);

    ulong s = 0;
    for (ulong j=0; j<m; ++j)  s += x[j];

    if ( (s&1)==0 )  r = ~r;

    r &= (1UL << (s-1)) - 1;

    return  r;
}
// -------------------------


ulong
composition_nz_rl_unrank(ulong r, ulong *x, ulong n)
// Generate composition x[] of n with rank r.
// Return number of parts m of generated composition, 1 <= m <= n.
// For RL-order (cf. class composition_nz_rl).
// The rank r is taken modulo  2 ** (n-1).
{
    // take rank modulo 2 ** (n-1):
    ulong b = 1UL << (n-1);
    r &= (b - 1);

    bool v = 0;
    ulong s = 0;
    ulong m = 0;
    while ( s < n )  // write to x[0], x[1], ...
    {
        b >>= 1;
        ulong p = 1;
        while ( ((r & b) ==0) != v )
        {
            if ( b==0 )  break;
            ++p;
            b >>= 1;
        }
        v = ! v;
        x[m] = p;
        s += p;
        ++m;
    }
//    jjassert( s == n );
//    jjassert( r == composition_nz_rl_rank(x, m) );

    return m;
}
// -------------------------



ulong
composition_nz_subset_lex_rank(const ulong *x, ulong m, ulong n)
// Return rank r of composition x[], 0 <= r < 2**(n-1)
// where n is the sum of all parts.
// For subset-lex order (cf. class composition_nz_subset_lex).
{
#if 1
    ulong r = 0;  // rank
    ulong e = 0;  // position of first part
    while ( e < m )
    {
        ulong f = x[e];
        if ( f==n )  return r;
        r += 1;
        ulong t = 1UL << (n-1);
        n -= f;
        while ( f > 1 )
        {
            t >>= 1;
            r += t;
            f -= 1;
        }
        e += 1;
    }
    return r;  // return r==0 for the empty composition

#else

    ulong r = composition_nz_rank(x, m);
    const ulong w = (1UL<<n) - 1;
    r ^= w;
    r = lexrev2negidx(r);
    r ^= w;
    return r;
#endif
}
// -------------------------


ulong
composition_nz_subset_lex_unrank(ulong r, ulong *x, ulong n)
// Generate composition x[] of n with rank r.
// Return number of parts m of generated composition, 1 <= m <= n.
// For subset-lex order (cf. class composition_nz_subset_lex).
// The rank r is taken modulo  2 ** (n-1).
{
    if ( n == 0 )  return 0;

    { // take rank modulo 2 ** (n-1):
        ulong b = 1UL << (n-1);
        r &= (b - 1);
    }

#if 1
    ulong m = 0;
    while ( true )
    {
        if ( r==0 )  // composition into one part
        {
            x[m++] = n;
            return m;
        }
        r -= 1;
        ulong t = 1UL << (n-1);
        for (ulong f=1; f<n; ++f)  // find first part f >= 1
        {
            t >>= 1;  // == 2**(n-f-1)
            // == number of compositions of n with first part f

            if ( r < t )  // first part is f
            {
                x[m++] = f;
                n -= f;
                break;
            }
            r -= t;
        }
    }
//    return m;  // unreached

#else

    const ulong w = (1UL<<n) - 1;
    ulong r2 = +r;
    r2 ^= w;
    r2 = negidx2lexrev(r2);
    r2 ^= w;
    ulong m = composition_nz_unrank(r2, x, n);
    return m;
#endif
}
// -------------------------


ulong
composition_nz_gray_rank(const ulong *x, ulong m, ulong n)
// Return rank r of composition x[], 0 <= r < 2**(n-1)
// where n is the sum of all parts.
// For Gray code (cf. class composition_nz_gray).
{
    if ( m <= 1 )  return 0;

    ulong f = x[0];   // first part
    ulong s = n - f;  // remaining sum

    ulong y = composition_nz_gray_rank(x+1, m-1, s);  // recursion
    if ( 0 == ( f & 1 ) )  // first part even
        return  ( 1UL << (s-1) ) + y;
    else
        return  ( 1UL << s ) - 1 - y;
}
// -------------------------


ulong
composition_nz_gray_unrank(ulong r, ulong *x, ulong n)
// Generate composition x[] of n with rank r.
// Return number of parts m of generated composition, 0 <= m <= n.
// For Gray code (cf. class composition_nz_gray).
// The rank r is taken modulo  2 ** (n-1).
{
    { // take rank modulo 2 ** (n-1):
        ulong b = 1UL << (n-1);
        r &= (b - 1);
    }

    if ( r == 0 )
    {
        if ( n==0 )  return 0;
        x[0] = n;
        return 1;
    }

    ulong h = highest_one_idx(r);
    ulong f = n - 1 - h;  // first part
    x[0] = f;

    ulong b = 1UL << h;  // highest one
    r ^= b;  // delete highest one

    bool p = f & 1;  // first part f odd ?
    if ( p )  r = b - 1 - r;  // change direction with odd f

    return  1 + composition_nz_gray_unrank( r , x+1, n-f );  // recursion
}
// -------------------------
