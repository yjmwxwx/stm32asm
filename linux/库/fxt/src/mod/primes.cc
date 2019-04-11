// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/mtypes.h"
#include "mod/isqrt.h"
#include "mod/primes.h"
#include "ds/bitarray.h"

//#include "fxtio.h"
#include "fxttypes.h"


static bitarray * oddprime_bitarray = 0;
ulong small_prime_limit = 64*1024;


class init_small_primes
{
    // (no data)
public:
    init_small_primes(ulong n)
    {
//        cout << "ctor: init_small_primes" << endl;
//        if ( oddprime_bitarray )  delete oddprime_bitarray;
        oddprime_bitarray = make_oddprime_bitarray(n, oddprime_bitarray);
    }

    ~init_small_primes()
    {
        delete oddprime_bitarray;
    }
};
// -------------------------

// automatic initialization:
static init_small_primes do_init_small_primes(small_prime_limit);
// warning: declaration requires a global constructor
// this is avoided by
//init_small_primes & do_init_small_primes()
//// automatic initialization (lazy initialization)
//{ // fixme: lazy initialization does not work
//    static init_small_primes x(small_prime_limit);
//    return x;
//}
//// -------------------------

bool
is_small_prime(ulong n, const bitarray *B/*=0*/)
// Return true if n is a small prime.
// Return false if table of primes is not big enough.
{
    if ( 0==(n&1) )  return  (2==n);  // n even: 2 is prime, else composite
    if ( n<=1 )  return  0;  // zero or one

    if ( 0==B )  B = oddprime_bitarray;
    ulong nh = n/2;
    if ( nh >= B->n_ )  return false;
    return  B->test( nh );
}
// -------------------------


ulong
next_small_prime(ulong n, const bitarray *B/*=0*/)
// Return next prime >= n.
// Return zero if table of primes is not big enough.
{
    if ( n<=2 )  return 2;

    if ( 0==B )  B = oddprime_bitarray;
    ulong nh = n/2;

    n = B->next_set( nh );
    if ( n==(B->n_) )  return 0;
    return  2 * n + 1;
}
// -------------------------
