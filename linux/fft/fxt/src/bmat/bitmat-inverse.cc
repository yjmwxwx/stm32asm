// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bmat/bitmat-inline.h"
#include "bmat/bitmat-funcs.h"
#include "bits/bitlow.h"
#include "bits/bitsperlong.h"
#include "aux0/swap.h"

#include "fxtalloca.h"
#include "fxttypes.h"
#include "restrict.h"
//#include "fxtio.h"

#define BMI_OPT  // define to use optimized code
//#define BMI_CHECK  // define for asserts
#ifdef BMI_CHECK
#include "jjassert.h"
#endif


bool
bitmat_inverse_q(const ulong *M, ulong n, const ulong *Mi)
{
    ALLOCA(ulong, T, n);
    bitmat_mult_MM(M, Mi, n, T);
    return bitmat_is_unit(T, n);
}
// -------------------------


// Get vector entry j:
#define vGET(v, j)  (((v)>>(j)) & 1UL)
// Set vector entry j to s:
#define vSET(v, j, s) { ulong bj=1UL<<(j);  if ( s ) {v|=bj;}  else {v&=~(bj);} }



bool
bitmat_inverse(const ulong *M, ulong n,
               ulong * restrict Mi,
               const ulong * restrict B/*=0*/)
//
// Compute Mi=M^(-1)*B or Mi=M^(-1) if B not given.
// Return false if M is not invertible.
//.
// Algorithm as in Cohen p.48
{
    ALLOCA(ulong, T, n);
    // 1 [Initialize]:
    if ( B )  bitmat_copy(B, n, T);  // supplied value
    else      bitmat_unit(T, n);


    for (ulong k=0; k<n; ++k)  Mi[k] = M[k];  // Don't modify M

    for (ulong j=0; j<n; ++j)
    {
        // 3 [Find non-zero entry]:
        ulong i = j;
        do
        {
            if ( 0!=bitmat_get(Mi, i, j) )  break;
        }
        while ( ++i < n );

        if ( i==n )  return false;  // M is not invertible


        // 4 [Swap?]:
        if ( i>j )
        {
#ifndef BMI_OPT
            for (ulong l=j; l<n; ++l)
            {
                ulong si = bitmat_get(Mi, i, l);
                ulong sj = bitmat_get(Mi, j, l);
                bitmat_set(Mi, j, l, si);
                bitmat_set(Mi, i, l, sj);
            }
#else  // BMI_OPT
#ifdef BMI_CHECK
            for (ulong l=0; l<j; ++l)
            {
                const ulong xi = bitmat_get(Mi, i, l);
                const ulong xj = bitmat_get(Mi, j, l);
                jjassert( 0==xi );  // OK
                jjassert( 0==xj );  // OK
                jjassert( xi==xj );  // OK
            }
#endif  // BMI_CHECK
            swap2(Mi[i], Mi[j]);
#endif  // BMI_OPT

            swap2(T[i], T[j]);
        }
//        bitmat_print(" [4] Mi == ", Mi, n);
//        bitmat_print(" [4] T  == ", T, n);

        // 5 [Eliminate]:  // we have d==1
//        jjassert ( 1UL==bitmat_get(Mi,j,j) );
        ulong c = 0;  // auxiliary vector
        for (ulong k=j+1; k<n; ++k)
        {
            ulong v = bitmat_get(Mi, k, j);
            vSET(c, k, v);
        }

        for (ulong k=j+1; k<n; ++k)
        {
            ulong ck = vGET(c, k);
            if ( ck )
            {
#ifndef BMI_OPT
                for (ulong l=j+1; l<n; ++l)
                {
                    ulong s = bitmat_get(Mi, k, l);
//                    ulong sp = bitmat_get(Mi, j, l) & ck;
                    ulong sp = bitmat_get(Mi, j, l);  // with if ( ck ) ...
                    s ^= sp;
                    bitmat_set(Mi, k, l, s);
                }
#else  // BMI_OPT
#ifdef BMI_CHECK
                for (ulong l=0; l<=j; ++l)
                {
                    const ulong xk = bitmat_get(Mi, k, l);
                    const ulong xj = bitmat_get(Mi, j, l);
//                    jjassert( 0==xk );  // not true
//                    jjassert( 0==xj );  // not true
                    jjassert( xk==xj );  // OK
                }
#endif  // BMI_CHECK
                Mi[k] ^= Mi[j];
#endif  // BMI_OPT
            }
        }
//        bitmat_print(" [5] Mi == ", Mi, n);
        for (ulong k=j+1; k<n; ++k)  if ( vGET(c, k) )  T[k] ^= T[j];
    }

    // 6 [Solve triangular system]:
    ulong *X = T;
    ulong i = n;
    do
    {
        --i;
        // X[i] = T[i];
        ulong v = 0;
        for (ulong j=i+1; j<n; ++j)  if ( bitmat_get(Mi, i, j) )  v ^= X[j];
        X[i] ^= v;
    }
    while ( i );

    for (ulong k=0; k<n; ++k)  Mi[k] = X[k];
    return  true;
}
// -------------------------



bool
bitmat_invert(ulong *M, ulong n)
{
    ALLOCA(ulong, T, n);
    bool q = bitmat_inverse(M, n, T);
    for (ulong k=0; k<n; ++k)  M[k] = T[k];
    return q;
}
// -------------------------

