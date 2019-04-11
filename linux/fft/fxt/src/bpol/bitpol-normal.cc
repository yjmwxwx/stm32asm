// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bmat/bitmat-funcs.h"
#include "bmat/bitmat-inline.h"  // bitmat_get()
#include "bpol/bitpolmod-arith.h"
#include "bpol/bitpol-irred.h"

#include "bpol/normalpoly-dual.h"  // gf2n_xx2k_trace()

#include "fxtalloca.h"

#include "fxttypes.h"  // ulong

//#include "fxtio.h"

bool
bitpol_normal2_q(ulong c, ulong n)
// Return whether polynomial c (of degree n) is normal.
// Must have: c irreducible.
{
    const ulong t = gf2n_xx2k_trace(c, n);
    const ulong xn1 = (1UL<<n) | 1UL;  // x^n-1
    return  ( 1 == bitpol_gcd(t, xn1) );
}
// -------------------------


bool
bitpol_normal_q(ulong c, ulong n, ulong iq/*=0*/, ulong *M/*=0*/)
// Return whether polynomial c (of degree n) is normal.
// Set iq to 1 for polynomials known to be irreducible.
// If M is given then the multiplication matrix is computed.
{
    const ulong h = 1UL << (n-1);
    if ( 0==(c & h) )  return false;  // polynomial trace must be one

    if ( 0==iq )
    {
        iq = bitpol_irreducible_q(c, h);
        if ( 0==iq )  return false;  // polynomial reducible ==> not normal
    }

    if ( c==3 )  // special case with c=x+1
    {
        if ( M )  M[0] = 1;
        return true;
    }

    ALLOCA(ulong, A, n);
    ulong v = 2UL;  // 'x'
    for (ulong k=0; k<n; ++k)
    {
        A[k] = v;
        v = bitpolmod_square(v, c, h);
    }

    ALLOCA(ulong, Ai, n);
    bool q = bitmat_inverse(A, n, Ai);  // try to invert
    if ( 0==q )  return false;  // polynomial is not normal

    if ( 0!=M )  // compute multiplication matrix
    {
        // make valgrind happy (we have partial writes to words of M[]):
        for (ulong k=0; k<n; ++k)  M[k] = 0;

        ALLOCA(ulong, C, n);
        bitmat_companion(c, n, C);
        bitmat_transpose(C, n, C);

//        bitmat_print("A=", A, n);
//        bitmat_print("A^-1=", Ai, n);
//        bitmat_print("C^T=", C, n);

        bitmat_mult_MM(A, C, n, A);  // A*C^T
        bitmat_mult_MM(A, Ai, n, A);  // D=A*C^T*A^{-1}

//        bitmat_print("D=A*C^T*A^{-1}=", A, n);

        ulong im = 0;  // == -i mod n
        for (ulong i=0; i<n; ++i)
        {
//            cout << " i=" << i << "  im=" << im << endl;
            ulong jm = im;  // == j-i mod n
            for (ulong j=0; j<n; ++j)
            {
                bitmat_set(M, i, j, bitmat_get(A, jm, im));
                ++jm;  if ( n==jm )  { jm = 0; }  // ++jm (mod n)
            }
            if ( 0==im )  { im=n-1; }  else  { --im; }  // --im (mod n)
        }

//        bitmat_print("M=", M, n);
    }

    return 1;
}
// -------------------------
