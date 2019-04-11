#if !defined  HAVE_DIVISORS_H__
#define       HAVE_DIVISORS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxtalloca.h"
#include "comb/mixedradix-lex.h"
#include "mod/factor.h"
#include "fxttypes.h"


class divisors
// Generate all divisors of a number n.
// Method: generate subsets of the multiset of exponents
//  via mixed radix counting.
{
public:
    umod_t *p_;   // primes
    mixedradix_lex *mr_;  // exponents + 1  as radices
    umod_t *t_;   // aux (products)
    ulong n_;    // number of prime factors

private:  // have pointer data
    divisors(const divisors&);  // forbidden
    divisors & operator = (const divisors&);  // forbidden

private:
    void ctor_core(const factorization &F)
    {
        n_ =  F.nprimes();

        t_ = new umod_t[n_+1];
        t_[n_] = 1;

        p_ = new umod_t[n_];
        for (ulong j=0; j<n_; ++j)  p_[j] = F.prime(j);

        ALLOCA(ulong, r, n_);  // tiny table
        for (ulong j=0; j<n_; ++j)  r[j] = F.exponent(j) + 1;

        mr_ = new mixedradix_lex(n_, 0, r);

        first();
    }

public:
    explicit divisors(umod_t x, const umod_t *f=0)
    // f[] == factorization hint (list of primes)
    {
        factorization F(x, f);  // expensive!
        ctor_core(F);
    }

    explicit divisors(const factorization &F)
    { ctor_core(F); }

    ~divisors()
    {
        delete [] t_;
        delete [] p_;
        delete mr_;
    }

    umod_t first()
    {
        mr_ -> first();  // all exponents zero
        for (ulong j=0; j<n_; ++j)  t_[j] = 1;
        return 1;
    }

    umod_t next()  // current is last?
    {
        if ( false == (mr_ -> next()) )
        {
            first();
            return 0;
        }

        ulong j = mr_ -> pos();  // position of digit change
        bool q = ( (mr_ -> a_[j]) == 1 );  // update from right?
        umod_t t = t_[j+q];
        t *= p_[j];
        while ( (long)j>=0 )  { t_[j] = t; --j; }  // jjcast
        return t;
    }
};
// -------------------------


#endif  // !defined HAVE_DIVISORS_H__
