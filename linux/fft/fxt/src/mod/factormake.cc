// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/factor.h"
#include "mod/primes.h"
#include "mod/isqrt.h"

#include "aux0/ipow.h"
#include "fxttypes.h"

//#include "jjassert.h"

#include "fxtio.h"


//#define  FACT_DEBUG
#ifdef FACT_DEBUG
#warning '***** FACT_DEBUG (make_factorization)'
#endif


bool
factorization::make_factorization(umod_t n,  const umod_t *f)
// Setup factorization
// from a zero-terminated list of possible prime factors.
// All but the greatest prime factor have to be in the list.
// If the greatest prime factor is omitted, it must have exponent one.
{
    if ( 0==f )  { return  make_factorization(n); }


#ifdef FACT_DEBUG
    cout << endl << " :: make_factorization(n,f): (start) n = " << n << endl;
    jjassert( n!=0 );
#endif

    reset();
    prod_ = n;
    ulong k = 0, kf = 0;
    do
    {
        umod_t v = f[k];
#ifdef FACT_DEBUG
        cout << " :: make_factorization(): n = " << n << endl;
        cout << " :: make_factorization(): v = " << v << endl;
//        jjassert( check() );
#endif

        ulong ex = divide_out_factor(n, v);
#ifdef FACT_DEBUG
        cout << " :: make_factorization(): ex = " << ex << endl;
#endif
        if ( 0==ex )
        {
            bool q = rabin_miller(n, 30);
#ifdef FACT_DEBUG
            cout << " :: make_factorization(): RM = " << q << endl;
#endif
            if ( q )
            {
                prime_[kf] = n;
                expon_[kf] = 1;
                prpow_[kf] = n;
                n = 1;
                ++kf;
                goto done;
            }
        }
        else
        {
            prime_[kf] = v;
            expon_[kf] = ex;
            prpow_[kf] = ipow(v, ex);
            ++kf;
        }

        ++k;
    }
    while ( 1!=n );
 done:

    npr_ = kf;
//    if ( 0==prime_[kf] )  { prime_[kf]=1; expon_[kf]=1; }


#ifdef FACT_DEBUG
    jjassert( 1==n );
    jjassert( check() );
#endif

    return  true;
}
// -------------------------


bool
factorization::make_factorization(umod_t n)
// Setup factorization
{
    reset();
    prod_ = n;

#ifdef FACT_DEBUG
    cout << endl << " :: make_factorization(n): (start) n = " << n << endl;
    jjassert( n!=0 );
#endif

    if ( ::rabin_miller(n, 30) )
    {
        prime_[0] = n;
        expon_[0] = 1;
        prpow_[0] = n;
        npr_ = 1;
#ifdef FACT_DEBUG
        cout << " :: make_factorization(): PRIME " << n << endl;
        jjassert( check() );
#endif
        return  true;
    }

    umod_t maxv = isqrt(n) + 1;
#ifdef FACT_DEBUG
    cout << " ::  n = " << n << endl;
    cout << " ::  maxv = " << maxv << endl;
#endif
    umod_t v = 1, vn;
    ulong ex;
    ulong k = 0;
    while ( (vn=next_small_prime(v+1)) )
    {
        v = vn;

#ifdef FACT_DEBUG
        cout << " ::  1 trying " << v << endl;
#endif
        if ( 0==v )  break;
        if ( maxv<v )  break;

        ex = divide_out_factor(n, v);
#ifdef FACT_DEBUG
        cout << " :: make_factorization(): (SP) v=" << v << " ex = " << ex << endl;
#endif
        if ( ex )
        {
            prime_[k] = v;
            expon_[k] = ex;
            prpow_[k] = ipow(v, ex);
            k++;

            maxv = isqrt(n) + 1;
        }
    }

    ulong pw = 1;
    umod_t w = isqrt(n);
    if ( w*w == n )  // check whether n is a perfect square
    {
        n = w;
        pw = 2;
        maxv = isqrt(n) + 1;
    }

    v += 2;
    for ( ; v<=maxv; v+=2)
    {
#ifdef FACT_DEBUG
        cout << " ::  2 trying " << v << endl;
#endif
        ex = divide_out_factor(n, v);
#ifdef FACT_DEBUG
        cout << " :: make_factorization():  v=" << v << " ex = " << ex << endl;
#endif
        if ( ex )
        {
            ex *= pw;
            prime_[k] = v;
            expon_[k] = ex;
            prpow_[k] = ipow(v, ex);
            k++;

            maxv = isqrt(n) + 1;
        }
    }

    if ( n!=1 )
    {
        prime_[k] = n;
        expon_[k] = pw;
        prpow_[k] = ipow(n, pw);
        k++;
    }

    npr_ = k;

#ifdef FACT_DEBUG
    cout << " :: make_factorization(): COMPOSITE " << endl;
    print(" :: factorization = ", cout);  cout << endl;
    jjassert( check() );
#endif

    return  true;
}
// -------------------------

