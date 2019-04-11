// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitrotate.h"
#include "bits/parity.h"

#include "bmat/bitmat-inline.h"

#include "fxttypes.h"  // ulong
//#include "bits/print-bin.h"
//#include "fxtio.h"


ulong
normal_mult(ulong a, ulong b, const ulong *M, ulong n)
// Multiply two elements (a and b in GF(2^n)) in normal basis representation.
// The multiplication matrix has to be supplied in M.
{
    ulong p = 0;
    for (ulong k=0; k<n; ++k)
    {
#if 0
        ulong v = bitmat_mult_Mv(M, n, b);  // M*b
        v = parity( v & a );  // a*M*b (dot product)
        p ^= ( v << k );
        a = bit_rotate_right(a, 1, n);
        b = bit_rotate_right(b, 1, n);

#else  // more efficient:

        ulong v = bitmat_mult_vM(M, n, a);  // a*M
        v = parity( v & b );  // a*M*b (dot product)
        p ^= ( v << k );
        a = bit_rotate_right(a, 1, n);
        b = bit_rotate_right(b, 1, n);
#endif
    }
    return  p;
}
// -------------------------
