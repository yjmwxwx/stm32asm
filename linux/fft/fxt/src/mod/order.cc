// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "mod/modarith.h"



//#define  ORDER_DEBUG  // define for debug
#ifdef ORDER_DEBUG
#warning '******** ORDER_DEBUG'
#include "jjassert.h"
#endif


umod_t
order_mod(umod_t x, umod_t m,
          const factorization &phifact)
//
// Return the order of x (mod m).
//
// See Cohen, p.25
//
{
    // pari says:  ***   not an element of (Z/nZ)* in order
    if ( 1!=gcd(m, x) )  return 0;

#ifdef ORDER_DEBUG
    jjassert( phifact.check() );
    ulong dct = 0;
#endif

    umod_t h = phifact.product();
    umod_t e = h;
    for (ulong i=0; i<phifact.nprimes() ; ++i)
    {
        umod_t p = phifact.prime(i);
        umod_t f = phifact.primepow(i);

#ifdef ORDER_DEBUG
        cout << " -------- " << i << ": " << endl;
        cout << " m = " << m << endl;
        cout << " e = " << e << endl;
        cout << " p = " << p << endl;
        cout << " f = " << f << endl;
#endif

        e /= f;
        umod_t g1 = pow_mod(x, e, m);  // Cohen
//        umod_t g1 = pow_mod(x, (h/f), m);  // different value, same order

#ifdef ORDER_DEBUG
        cout << " e_0 = " << e << endl;
        cout << " g1_0 = " << g1 << endl;
        umod_t zz = pow_mod(x, (h/f), m);
        cout << " zz = " << zz << endl;
        cout << " g1-zz=" << sub_mod(g1, zz, m) << endl;
//        jjassert( zz == g1 );
#endif

        while ( g1!=1 )
        {
#ifdef ORDER_DEBUG
            cout << "  ---- " << endl;
            cout << "   e = " << e << endl;
            cout << "   g1 = " << g1 << endl;
            jjassert( ++dct < 128 );  // can't be OK even for 128 bits
#endif
            g1 = pow_mod(g1, p, m);
            e *= p;
        }
    }

    return e;
}
// -------------------------
