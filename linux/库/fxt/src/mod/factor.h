#if !defined HAVE_FACTOR_H__
#define      HAVE_FACTOR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "mod/mtypes.h"
#include "bits/bitsperlong.h"
#include "fxtio.h"
#include "fxttypes.h"


class  factorization
// Factorization of a numbers into prime powers.
// Factors can be supplied for constructor,
//   otherwise trial division is used.
{
protected:
    ulong  npr_;

#if BITS_PER_LONG_LONG <= 64
    umod_t prime_[16];
    ulong  expon_[16];
    umod_t prpow_[16];
#else
    umod_t prime_[32];
    ulong  expon_[32];
    umod_t prpow_[32];
#endif

    umod_t  prod_;


public:
    static const ulong  maxprimes;

    friend class mod;

public:
    explicit factorization();
    explicit factorization(umod_t n, const umod_t* f=0);
    ~factorization();

    ulong nprimes()  const  { return npr_; }
    umod_t prime(ulong i) const  { return prime_[i]; }
    ulong  exponent(ulong i) const  { return expon_[i]; }
    ulong  exponent_of(umod_t p) const;  // exponent of prime p
    umod_t product() const  { return prod_; }
    umod_t primepow(ulong i) const  { return prpow_[i]; }

    bool make_factorization(umod_t n);
    bool make_factorization(umod_t n, const umod_t *f);

    bool is_factorization_of(umod_t n) const  { return  ( n == product() ); }

    bool  is_prime() const;

    ulong  numdiv() const;

    void print(const char *bla, std::ostream &os) const;

    bool  check()  const;

    void reset();
protected:
    void sort_by_primes();

private:
    factorization(const factorization &);  // forbidden
    const factorization & operator = (const factorization &);  // forbidden
};
// -------------------------


// mod/factor.cc:
umod_t get_factor_q(umod_t n, umod_t f);
ulong divide_out_factor(umod_t &n, umod_t v);

//istream&  operator >> (istream& is, factorization& h);
std::ostream&  operator << (std::ostream& os, const factorization& h);


#endif  // !defined HAVE_FACTOR_H__
