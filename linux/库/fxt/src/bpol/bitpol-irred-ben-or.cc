// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitsperlong.h"
//#include "bpol/bitpol-arith.h"
#include "bpol/bitpol-gcd.h"
#include "bpol/bitpolmod-arith.h"
//#include "bpol/bitpol-squarefree.h"

#include "bits/bitsperlong.h"
#include "fxttypes.h"

//#include <cmath>  // floor()



bool
bitpol_irreducible_ben_or_q(ulong c, ulong h)
// Return whether C is irreducible (via the Ben-Or irreducibility test_;
// h needs to be a mask with one bit set:
//  h == highest_one(C) >> 1  == 1UL << (degree(C)-1)
// Note: routine will fail for deg(c)==BITS_PER_LONG (GCD fails)
{
    if ( c<4 )
    {
        if ( c>=2 )  return true;   // x, and 1+x are irreducible
        else         return false;  // constant polynomials are reducible
    }

    if ( 0==(1&c) )  return false;  // x is a factor

//#if BITS_PER_LONG == 64
//    if ( 0==(c & 0xaaaaaaaaaaaaaaaaUL ) )  return 0;  // at least one odd degree term
//#else
//    if ( 0==(c & 0xaaaaaaaaUL ) )  return 0;  // at least one odd degree term
//#endif

    // if ( 0==parity(c) )  return 0;  // need odd number of nonzero coeff.
    // if ( 0!=bitpol_test_squarefree(c) )  return 0;  // must be square-free

    ulong d = h >> 1;
    ulong u = 2;  // =^= x
    while ( 0 != d )  // floor( degree/2 ) times
    {
        // Square r-times for coefficients of c in GF(2^r).
        // We have r==1:
        u = bitpolmod_square(u, c, h);

        ulong upx = u ^ 2;  // =^= u+x

        // Note: GCD does not work for work for deg(C)==BITS_PER_LONG
//        ulong g = bitpol_gcd(upx, c);
        ulong g = bitpol_binary_gcd(upx, c);
//        if ( 1!=g )
//        {
//            cout << " :: bitpol_irreducible_q() " << endl;
//            cout << " upx= " << upx << endl;
//            cout << " c= " << c << endl;
//            cout << " g= " << g << endl;
//        }

        if ( 1!=g )  return  false;   // reducible

        d >>= 2;
    }
    return  true;  // irreducible
}
// -------------------------

