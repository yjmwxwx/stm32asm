#if !defined HAVE_GRAYREVPERMUTE_H__
#define      HAVE_GRAYREVPERMUTE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/graycode.h"  // gray_code()
#include "bits/bit2pow.h"  // is_pow_of_2()
#include "restrict.h"
#include "fxttypes.h"

//#include "bits/bitsubset.h"  // bitsubset
//#include "bits/bitsperlong.h"


template <typename Type>
inline void gray_rev_permute(const Type *f, Type * restrict g, ulong n)
// gray_rev_permute() =^=
//  { reverse(); gray_permute(); }
{
    for (ulong k=0, m=n-1;  k<n;  ++k, --m)  g[gray_code(m)] = f[k];
}
// -------------------------


template <typename Type>
inline void inverse_gray_rev_permute(const Type *f, Type * restrict g, ulong n)
// inverse of gray_rev_permute()
// inverse_gray_rev_permute() =^=
//  { inverse_gray_permute(); reverse(); }
{
    for (ulong k=0, m=n-1;  k<n;  ++k, --m)  g[k] = f[gray_code(m)];
}
// -------------------------


template <typename Type>
void gray_rev_permute(Type *f, ulong n)
// n must be a power of 2, n<=2**(BITS_PER_LONG-2)
{
    f -= n;  // note!

    ulong z = 1;  // mask for cycle maxima
    ulong v = 0;  // ~z
    ulong cl = 1;  // cycle length
    ulong ldm, m;
    for (ldm=1, m=2;  m<=n;  ++ldm, m<<=1)
    {
        z <<= 1;  v <<= 1;
        if ( is_pow_of_2(ldm) )  { ++z;  cl<<=1; }
        else  ++v;
    }

    ulong tv = v, tu = 0;  // cf. bitsubset.h
    do
    {
        tu = (tu-tv) & tv;
        ulong i = z | tu;  // start of cycle

        // --- do cycle: ---
        ulong g = gray_code(i);
        Type t = f[i];
        for (ulong k=cl-1; k!=0; --k)
        {
            Type tt = f[g];
            f[g] = t;
            t = tt;
            g = gray_code(g);
        }
        f[g] = t;
        // --- end (do cycle) ---
    }
    while ( tu );
}
// -------------------------


template <typename Type>
void inverse_gray_rev_permute(Type *f, ulong n)
// n must be a power of 2, n<=BITS_PER_LONG-2
{
    f -= n;  // note!

    ulong z = 1;  // mask for cycle maxima
    ulong v = 0;  // ~z
    ulong cl = 1;  // cycle length
    ulong ldm, m;
    for (ldm=1, m=2;  m<=n;  ++ldm, m<<=1)
    {
        z <<= 1;  v <<= 1;
        if ( is_pow_of_2(ldm) )  { ++z;  cl<<=1; }
        else  ++v;
    }

    ulong tv = v, tu = 0;  // cf. bitsubset.h
    do
    {
        tu = (tu-tv) & tv;
        ulong i = z | tu;  // start of cycle

        // --- do cycle: ---
        Type t = f[i];           // save start value
        ulong g = gray_code(i);  // next in cycle
        for (ulong k=cl-1; k!=0; --k)
        {
            f[i] = f[g];
            i = g;
            g = gray_code(i);
        }
        f[i] = t;
        // --- end (do cycle) ---
    }
    while ( tu );
}
// -------------------------



#endif  // !defined HAVE_GRAYREVPERMUTE_H__
