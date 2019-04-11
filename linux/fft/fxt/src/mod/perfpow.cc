// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitsperlong.h"
//#include "mod/mtypes.h"
#include "mod/isqrt.h"
#include "bits/tinyfactors.h"
#include "ds/bitarray.h"

#include "fxttypes.h"


static bitarray * perfpow_bitarray = 0;
static ulong small_perfpow_limit = 512;  // <=BITS_PER_LONG**2


static bitarray *
make_perfpow_bitarray(ulong n)
{
    bitarray *B = new bitarray( n );
    B->clear_all();

    const ulong sn = isqrt(n)+1;
    for (ulong p=2; p<sn; ++p)
    {
//        if ( ! is_tiny_prime(p) )   continue;
        for (ulong pp=p*p; pp<n; pp*=p)  B->set(pp);
    }

    return B;
}
// -------------------------

class init_perfpow
{
    // (no data)
public:
    init_perfpow(ulong n)
    {
//        if ( 0!=perfpow_bitarray )  delete perfpow_bitarray;
        perfpow_bitarray = make_perfpow_bitarray(n);
    }

    ~init_perfpow()
    {
        delete perfpow_bitarray;
    }
};
// -------------------------

// automatic initialization:
static init_perfpow do_init_perfpow(small_perfpow_limit);
// warning: declaration requires a global constructor
// this is avoided by
//init_perfpow & do_init_perfpow()
//// automatic initialization (lazy initialization)
//{ // fixme: lazy initialization does not work
//    static init_perfpow x(small_perfpow_limit);
//    return x;
//}
//// -------------------------


bool
is_small_perfpow(ulong n)
// Return whether n is a small perfect power in perfpow_bitarray
{
    if ( n >= perfpow_bitarray->n_ )  return false;
    return  perfpow_bitarray->test( n );
}
// -------------------------
