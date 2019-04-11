#if !defined  HAVE_PERMRAND_INV_MOD_M_H__
#define       HAVE_PERMRAND_INV_MOD_M_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "comb/fact2perm.h"
//#include "jjassert.h"


inline void perm_fix_inv_mod(ulong *x, ulong n,
                             ulong r, ulong m,
                             ulong *tfc=0)
// Adjust permutation x[] such that (i%m)==r
// where i is the number of inversions.
// Must have: 2 <= m <= n  and  0 <= r < m.
{
    ulong *fc = tfc;
    if ( tfc==0 )  fc = new ulong[n-1];

    perm2ffact(x, n, fc);  // may replace by O(n*log(n)) routine
    ulong i = 0;  // number of inversions
    for (ulong k=0; k<n-1; ++k)  i += fc[k];

    ulong mi = i % m;  // i mod m of given permutation
    if ( mi != r )  // need to adjust digit
    {
        const ulong p = n - m;  // position of digit to adjust
        ulong d = fc[p];  // value of digit
        d += (r-mi);
        if ( (long)d < 0 )  d += m;
        if ( d >= m )  d -= m;
//        if ( d >= m )  d -= m;
//        else           d += m;
//        jjassert( d<m );
        fc[p] = d;
        ffact2perm(fc, n, x);  // may replace by O(n*log(n)) routine
    }

    // Could use cyclic shift with m==n
    // Could use swap of last two elements with m=2

    if ( tfc==0 )  delete [] fc;
}
// -------------------------


inline void random_inv_mod_m_permutation(ulong *p, ulong n,
                                         ulong r, ulong m,
                                         ulong *tfc=0)
// Create random permutation p[] such that (i%m)==r
// where i is the number of inversions.
// Must have: 2 <= m <= n  and  0 <= r < m.
{
#if 1
    ulong *fc = tfc;
    if ( tfc==0 )  fc = new ulong[n-1];

    // Create random factorial number:
    for (ulong rx=n, j=0;  rx>1;  --rx, ++j)  fc[j] = rand_idx(rx);

    ulong i = 0;  // number of inversions (sum of digits):
    for (ulong j=0; j<n; ++j)  i += fc[j];

    ulong mi = i % m;  // i mod m of given permutation
    if ( mi != r )  // need to adjust digit
    {
        const ulong ps = n - m;  // position of digit to adjust
        ulong d = fc[ps];  // value of digit
        d += (r-mi);
        if ( (long)d < 0 )  d += m;
        if ( d >= m )  d -= m;
//        if ( d >= m )  d -= m;
//        else           d += m;
//        jjassert( d<m );
        fc[ps] =  d;
    }

    ffact2perm(fc, n, p);  // may replace by O(n*log(n)) routine


    if ( tfc==0 )  delete [] fc;

#else
    random_permutation(p, n);
    perm_fix_inv_mod(p, n, r, m, fc);
#endif
}
// -------------------------


#endif  // !defined HAVE_PERMRAND_INV_MOD_M_H__
