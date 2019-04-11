#if !defined  HAVE_MERSENNE_COPRIME_H__
#define       HAVE_MERSENNE_COPRIME_H__
// This file is part of the FXT library.
// Copyright (C) 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/priorityqueue.h"

#include "mod/mersenne.h"  // mersenne_prime_factor_tab[]
#include "mod/mtypes.h"  // umod_t

#include "fxttypes.h"  // ulong


class mersenne_coprime
// For k=1 .. m, determine whether gcd(k,m) != 0 where m=2^e-1.
// Must have e <= 64 (=sizeof(umod_t)).
{
public:
    umod_t j_;   // current index 1 <= j <= 2**e - 1
    umod_t p_[15];  // prime factors (OK for e<=128)
    ulong e_;    // exponent
    ulong np_;   // number of prime factors
    priority_queue<umod_t, umod_t> PQ_;

private:  // have pointer data
    mersenne_coprime(const mersenne_coprime&);  // forbidden
    mersenne_coprime & operator = (const mersenne_coprime&);  // forbidden

private:
    umod_t pq_top()  const  { return PQ_.t1_[1]; }

public:
    explicit mersenne_coprime(ulong e)
        : e_(0), np_(0), PQ_(15, 0)
    {
        first(e);
    }

    ~mersenne_coprime()  {;}

    void first(ulong e)
    {
        if ( e != e_ )  init(e);
        for (ulong n=0; n<np_; ++n)  PQ_.insert(p_[n], p_[n]);
        j_ = 1;
    }

    void init(ulong e)
    {
        if ( e > (8*sizeof(umod_t)) )  return;  // user error
        umod_t m = (umod_t(1) << e) - 1;
        if ( e == 0 )  m = ~0ULL;

        ulong j = 0;
        np_ = 0;
        while ( m != 1 )
        {
            umod_t p = mersenne_prime_factor_tab[j];  // Works for e<=64 only
            ++j;
            if ( m % p == 0 )
            {
                p_[np_] = p;
                ++np_;
                do  { m /= p; }  while ( m % p == 0 );
            }
        }
    }

    umod_t pos()  const  { return j_; }

    bool current()  const { return j_ != pq_top(); }

    bool next()
    {
        ++j_;
        const umod_t t = pq_top();
        if ( j_ != t )  return  true;

        do
        {
            const umod_t p = PQ_.e1_[1];  // get_next_e()
            PQ_.reschedule_next( t + p );
        }
        while ( t == pq_top() );
        return false;
    }
};
// -------------------------


#endif  // !defined HAVE_MERSENNE_COPRIME_H__
