#if !defined HAVE_GRAYPERMUTE_H__
#define      HAVE_GRAYPERMUTE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/graycode.h"  // gray_code()
#include "bits/bit2pow.h"  // is_pow_of_2()
#include "bits/bitsubset.h"  // bitsubset
#include "restrict.h"


template <typename Type>
inline void gray_permute(const Type *f, Type * restrict g, ulong n)
// Put Gray permutation of f[] to g[], i.e. g[gray_code(k)] == f[k]
{
    for (ulong k=0; k<n; ++k)  g[gray_code(k)] = f[k];
}
// -------------------------


template <typename Type>
inline void inverse_gray_permute(const Type *f, Type * restrict g, ulong n)
// Put inverse Gray permutation of f[] to g[], i.e. g[k] == f[gray_code(k)]
// (same as: g[inverse_gray_code(k)] == f[k])
{
    for (ulong k=0; k<n; ++k)  g[k] = f[gray_code(k)];
}
// -------------------------


template <typename Type>
void gray_permute(Type *f, ulong n)
// Gray permutation, in-place version
// the only difference to inverse_gray_permute()
//  is the 'do cycle' block
{
    ulong z = 1;  // mask for cycle maxima
    ulong v = 0;  // ~z
    ulong cl = 1;  // cycle length
    for (ulong ldm=1, m=2;  m<n;  ++ldm, m<<=1)
    {
        z <<= 1;
        v <<= 1;
        if ( is_pow_of_2(ldm) )
        {
            ++z;
            cl <<= 1;
        }
        else  ++v;

        bit_subset b(v);
        do
        {
            // --- do cycle: ---
            ulong i = z | b.next();  // start of cycle
            Type t = f[i];           // save start value
            ulong g = gray_code(i);  // next in cycle
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
        while ( b.current() );
    }
}
// -------------------------


template <typename Type>
void inverse_gray_permute(Type *f, ulong n)
// Inverse Gray permutation, in-place version
// the only difference to gray_permute()
//  is the 'do cycle' block
{
    ulong z = 1;
    ulong v = 0;
    ulong cl = 1;
    for (ulong ldm=1, m=2;  m<n;  ++ldm, m<<=1)
    {
        z <<= 1;
        v <<= 1;
        if ( is_pow_of_2(ldm) )
        {
            ++z;
            cl <<= 1;
        }
        else  ++v;

        bit_subset b(v);
        do
        {
            // --- do cycle: ---
            ulong i = z | b.next();  // start of cycle
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
        while ( b.current() );
    }
}
// -------------------------



#endif  // !defined HAVE_GRAYPERMUTE_H__
