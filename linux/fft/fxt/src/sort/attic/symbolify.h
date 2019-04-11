#if !defined HAVE_SYMBOLIFY_H__
#define      HAVE_SYMBOLIFY_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "sort/quantize.h"
#include "sort/sortidx.h"

#include "perm/permq.h"
#include "perm/permapply.h"

#include "aux1/copy.h"  // set_seq()


#include "fxtalloca.h"
#include "restrict.h"
#include "fxttypes.h"



template <typename Type>
ulong symbolify_by_size(const Type *f, Type * restrict g, ulong n,
                        Type eps=1e-6, ulong *ix=0)
//
// From f[] compute an array of 'symbols' g[] (i.e. numbers)
//   that represent the different values.
// Values are considered identical if their absolute difference
//   is less than eps.
// Symbols are given with respect to sort-order.
// Return number of different values found (after quantize).
// Optionally supply x[] (scratch space for permutations).
//
// This routine is useful to find structure in numerical data.
// Example:
//
//   1.3133     -1.0101     0.79412     -0.71544
//   0.29064     0.99173   -1.4382       0.79412
//  -1.1086      1.2521     0.99173     -1.0101
//  -0.18003    -1.1086     0.29064      1.3133
//
// is (using eps==1e-4) transformed to
//
//   9           2           6           3
//   5           7           0           6
//   1           8           7           2
//   4           1           5           9
//
{
    ulong *x = ix;
    if ( 0==ix )  x = new ulong[n];

    set_seq(x, n);
    idx_quick_sort(f, n, x);

    apply_inverse_permutation(x, f, g, n);
    quantize(g, n, eps);

    eps *= 0.5;  // some val <1.0
    ulong nsym = 1;

    ulong z = 0;
    Type s = 0.0;
    Type el = g[z], lel;
    g[z] = s;
    for(ulong k=z+1; k<n; ++k)
    {
        lel = el;
        el = g[k];
        if ( fabs(el-lel) > eps )
        {
            ++nsym;
            s += 1.0;
        }
        g[k] = s;
    }

    apply_permutation(x, g, n);

    if ( 0==ix )  delete [] x;

    return  nsym;
}
// -------------------------



template <typename Type>
ulong symbolify_by_order(const Type *f, Type * restrict g, ulong n,
                         Type eps=1e-6,
                         ulong *ix=0)
//
// From f[] compute an array of 'symbols' (i.e. numbers)
// that represent the different values.
//
// Symbols are given with respect to order of appearence.  The first
// appearence of each value gets its index as value.  The later
// appearences of the same value 'point' to the first appearance.
//
// Return number of different values found (after quantize)
//
// e.g.:
//
//   1.3133     -1.0101     0.79412     -0.71544
//   0.29064     0.99173   -1.4382       0.79412
//  -1.1086      1.2521     0.99173     -1.0101
//  -0.18003    -1.1086     0.29064      1.3133
//
// is (using eps==1e-4) transformed to:
//
//     0           1           2           3
//     4           5           6           2
//     8           9           5           1
//    12           8           4           0
//
// This routine is useful to find structure
// in purely numerical data.
//
// Primitive algorithm, proportional to n*n, could be improved.
//
{
    ulong *x = ix;
    if ( 0==ix )  x = new ulong[n];

    ulong nsym = symbolify_by_size(f, g, n, eps, x);

    ALLOCA(Type, t, n);
    for (ulong k=0; k<n; ++k)
    {
        Type s = (Type)k;
        Type so = g[k];
        if ( so<0 )  continue;

        for (ulong j=0; j<n; ++j)
        {
            if ( g[j]==so )
            {
                t[j] = s;
                g[j] = -1;
            }
        }
    }
    acopy(t, g, n);

    if ( 0==ix )  delete [] x;

    return  nsym;
}
// -------------------------


#endif // !defined HAVE_SYMBOLIFY_H__
