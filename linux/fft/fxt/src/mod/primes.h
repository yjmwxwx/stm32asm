#if !defined HAVE_PRIMES_H__
#define      HAVE_PRIMES_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "mod/mtypes.h"

//#include "ds/bitarray.h"
class bitarray;

// mod/primes.cc:
extern ulong small_prime_limit;
bool  is_small_prime(ulong n, const bitarray *B=0);
ulong  next_small_prime(ulong n, const bitarray *B=0);


// mod/eratosthenes.cc:
bitarray *make_prime_bitarray(ulong n, bitarray *B=0);
bitarray *make_oddprime_bitarray(ulong n, bitarray *B=0);


// mod/rabinmiller.cc:
void n2qt(const umod_t n, umod_t &q, uint &t);
bool is_strong_pseudo_prime(const umod_t n, const umod_t a, const umod_t q, const uint t);
bool rabin_miller(umod_t n, uint cm=0);


// mod/perfpow.cc:
bool  is_small_perfpow(ulong n);


#endif  // !defined HAVE_PRIMES_H__
