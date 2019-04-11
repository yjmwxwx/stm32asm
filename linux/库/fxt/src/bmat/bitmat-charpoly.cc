// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bmat/bitmat-inline.h"  // bitmat_get()
#include "bmat/bitmat-funcs.h"  // bitmat_hessenberg()

#include "fxtalloca.h"
#include "fxttypes.h"  // ulong


ulong
bitmat_hessenberg2charpoly(const ulong *H, ulong n)
// Return the characteristic polynomial of the Hessenberg matrix H
//.
// cf. Cohen p.55
{
    // 5 [Initialize characteristic polynomial]:
    ALLOCA(ulong, vp, n+1);
    vp[0] = 1;
    for (ulong m=1; m<=n; ++m)
    {
        const ulong m1 = m - 1;  // 0,...,n-1

        // 6 [Initialize computation]:
        const ulong Hmm = bitmat_get(H, m1, m1);
        const ulong p = vp[m1];
        vp[m] = (p<<1) ^ ( Hmm ? p : 0 );
//        ulong t = 1;

        // 7 [Compute p_m]:
        for (ulong i=1; i<m; ++i)
        {
            const ulong x = m1 - i;  // m-2, ..., 0
//            ulong q1 = bitmat_get(H, x+1, x);  t &= q1;
//            if ( 0==t )  break;
            if ( 0==bitmat_get(H, x+1, x) )  break;

//            const ulong q2 = bitmat_get(H, x, m1);
////            q2 &= t;
//            if ( q2 )  vp[m] ^= vp[x];
            if ( bitmat_get(H, x, m1) )  vp[m] ^= vp[x];
        }
    }
    return vp[n];
}
// -------------------------


ulong
bitmat_charpoly(const ulong *M, ulong n)
// Return the characteristic polynomial of M.
//.
// cf. Cohen p.55
{
    ALLOCA(ulong, H, n);
    bitmat_hessenberg(M, n, H);
    ulong cp = bitmat_hessenberg2charpoly(H, n);
    return  cp;
}
// -------------------------



//#if 0  // only for reals:
//ulong
//bitmat_charpoly(const ulong *M, ulong n, ulong *T=0)
//// Cohen p.53
//{
//    ulong a = 1UL;  // a_0 = 0
//    ALLOCA(ulong, C, n);
//    bitmat_unit(C, n);
////    bitmat_copy(M, n, C);
//    for (ulong i=1; i<n; ++i)
//    {
//        bitmat_mult_MM(M, C, n, C);  // C = M*C
//        ulong ai = bitmat_trace(C, n);  // a_i = -tr(C)/i  // !
//        a |= (ai<<i);
//        if ( ai )  bitmat_add_unit(C, n);  //  C += a_i * Id_n
//    }
//
//    if ( T )  bitmat_copy(C, n, T);  // C = (-1)^{n-1} * C
//
//    bitmat_mult_MM(M, C, n, C);
//    ulong an = bitmat_trace(C, n);  // a_n = -tr(M*C)/n  // !
//    a |= (an << n);
//    return  a;
//}
//// -------------------------
//#endif  // 0

