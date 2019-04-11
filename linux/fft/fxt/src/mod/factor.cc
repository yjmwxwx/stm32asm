// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/mtypes.h"
#include "mod/factor.h"
#include "mod/primes.h"
#include "mod/modarith.h"

#include "bits/bitsperlong.h"
#include "fxttypes.h"

#include "fxtalloca.h"  // ALLOCA

#include "jjassert.h"

//#include "fxtio.h"

//#include <cmath>


//#define  FACT_DEBUG
#ifdef FACT_DEBUG
#warning '***** FACT_DEBUG'
#endif


#if BITS_PER_LONG_LONG <= 64
const ulong factorization::maxprimes = 16;
#else
const ulong factorization::maxprimes = 32;
#endif
// extreme case is  2*3*5*7*11*...
// 16 primes are enough for 64 bit
// 27 primes are enough for 128 bit

factorization::factorization()
{
    reset();
}
// -------------------------


factorization::factorization(umod_t n, const umod_t *f/*=0*/)
//
// Initialize from zero-terminated (complete!)
// list of prime factors of n.
// Setup exponents and factors.
//
{
    reset();
    make_factorization(n, f);
    sort_by_primes();
}
// -------------------------

bool factorization::is_prime() const
{
    return ((1==npr_) && (1==expon_[0]));
}
// -------------------------

ulong factorization::numdiv() const
{
    ulong nd = 1;
    for (ulong j=0; j<npr_; ++j)  nd *= (1 + exponent(j));
    return nd;
}
// -------------------------

factorization::~factorization()
{
}
// -------------------------


void
factorization::reset()
{
    for (ulong k=0; k<maxprimes; k++)  prime_[k] = expon_[k] = prpow_[k] = 0;
    npr_ = 0;
    prod_ = 0;
}
// -------------------------


void
factorization::sort_by_primes()
// sort wrt. primes
{
    ALLOCA(umod_t, pr, maxprimes);
    ALLOCA(ulong,  ex, maxprimes);
    ALLOCA(umod_t, fc, maxprimes);

    for (ulong i=0; i<npr_; ++i)
    {
        pr[i] = prime_[i];
        ex[i] = expon_[i];
        fc[i] = prpow_[i];
        prime_[i] = 0;
        expon_[i] = 0;
        prpow_[i] = 0;
    }

    for (ulong i=0; i<npr_; ++i)
    {
        umod_t mi = (umod_t)(~0);
        ulong f = 0;
        for (ulong j=0; j<npr_; ++j)
        {
            if ( pr[j]<mi )
            {
                mi = pr[j];
                f = j;
            }
        }

        prime_[i] = pr[f];
        expon_[i] = ex[f];
        prpow_[i] = fc[f];
        pr[f] = (umod_t)(~0);
    }

#ifdef FACT_DEBUG
    jjassert( check() );
#endif
}
// -------------------------


ulong
factorization::exponent_of(umod_t p) const
// return exponent of prime p in factorization
{
    for (ulong i=0; i<npr_; ++i)  if ( p==prime_[i] )  return expon_[i];
    return 0;
}
// -------------------------


void
factorization::print(const char *bla, std::ostream &os) const
{
    if ( bla )  os << bla;

    ulong k;
    for (k=0; k<npr_-1; ++k)
    {
        os << prime_[k];
        if ( expon_[k]>1 )  os << "^" << expon_[k];
        os << " * ";
    }

    if ( npr_>0 )
    {
        os << prime_[k];
        if ( expon_[k]>1 )  os << "^" << expon_[k];
    }
}
// -------------------------



std::ostream&  operator << (std::ostream& os, const factorization& h)
{
    h.print(0, os);
    return os;
}
// -------------------------


bool
factorization::check()  const
{
    umod_t m = 1;
    for (ulong i=0; i<npr_; ++i)
    {
        umod_t p = prime_[i];
        bool rm = ::rabin_miller(p, 100);
#ifdef FACT_DEBUG
        cout << " check()ing: primality of " << p << endl;
        if ( rm==false )
        {
            cout << " **** check(): prime # " << i;
            cout << " == " << p;
            cout << endl;
        }
#endif
        if ( rm==false )  return false;
        m *= primepow(i);
    }

#ifdef FACT_DEBUG
    cout << " m = " << m << endl;
    cout << " prod = " << product() << endl;
#endif
    return ( m == product() );
}
// -------------------------


// auxiliary functions:

umod_t
get_factor_q(umod_t n, umod_t f)
//
// if f divides n  return n/f
// else            return 0
//
{
    umod_t q = n/f;
    if ( q*f==n )  return q;
    else           return 0;
}
// -------------------------

ulong
divide_out_factor(umod_t &n, umod_t v)
//
// while v divides  n
//   divide n by v
// return how often divided
//
{
//    cout << " :: divide_out_factor(): n=" << n << "  v=" << v << endl;
    umod_t q = get_factor_q(n, v);

    if ( q==0 )  return 0;
    else
    {
        ulong ex = 0;
        do
        {
            n = q;
            ++ex;
//            cout << " :: divide_out_factor(): n=" << n << "  ex=" << ex << endl;
            q = get_factor_q(n, v);
        }
        while ( q!=0 );
        return ex;
    }
}
// -------------------------

