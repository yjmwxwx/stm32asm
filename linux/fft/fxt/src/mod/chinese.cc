// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "mod/modarith.h"
#include "fxttypes.h"


umod_t
chinese(const umod_t *x, const factorization &f)
// Return R modulo M where:
//   f[] is the factorization of M,
//   x[] := R modulo the prime powers of f[].
{
    const ulong n = f.nprimes();
    // (omitted test that gcd(m_0,...,m_{n-1})=1 )

    const umod_t M = f.product();
    umod_t R = 0;
    for (ulong i=0; i<n; ++i)
    {
        // Ti = prod(mk)  (where k!=i);  Ti==M/mi:
        const umod_t Ti = M / f.primepow(i);  // exact division

        // ci = 1 / Ti:
        umod_t ci = inv_modpp(Ti, f.prime(i), f.exponent(i));
        // here:  0 <= ci < mi

        // Xi = x[i] * ci * Ti:
        umod_t Xi = ci * Ti;  // 0 <= Xi < M
        Xi = mul_mod(Xi, x[i], M);

        // add Xi to result:
        R = add_mod(R, Xi, M);
    }

    return R;
}
// -------------------------

