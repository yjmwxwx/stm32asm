#if !defined  HAVE_ALL_IRREDPOLY_H__
#define       HAVE_ALL_IRREDPOLY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/necklace2bitpol.h"
#include "bpol/poly-tab.h"

#include "bits/bit-necklace.h"
#include "bits/bitsperlong.h"

#include "aux0/gcd.h"  // gcd()
#include "fxttypes.h"  // ulong

class all_irredpoly
// Generate all irreducible binary polynomials of given degree
{
public:
    ulong p_;
    ulong mers_;
    bit_necklace    bn_;
    necklace2bitpol n2b_;

public:
    explicit all_irredpoly(ulong n, ulong c=0, ulong a=0)
        : p_(0), mers_(0), bn_(n), n2b_(n, c, a)
    {
        init(n);
    }

    ~all_irredpoly() {;}

    void init(ulong n=0, ulong c=0, ulong a=0)
    {
        if ( 0!=n )
        {
            mers_ = ~0UL;
            if ( n < BITS_PER_LONG )  mers_ = (1UL << n) - 1;
        }

        bn_.init( n );
        n2b_.init( n, c, a );
        next();  // goto first irreducible poly, for primitive c the poly is primitive
    }

    ulong data() const { return  p_; }

    ulong next()  // return poly, zero if there are no more
    {
        ulong b;
        do
        {
            b = bn_.next();
            if ( 0==b )  return 0;
        }
        while ( 0==bn_.is_lyndon_word() );

        p_ = n2b_.poly( bn_.data() );
        return  p_;
    }

    bool is_primitive()  const
    {
        ulong b = bn_.data();
        return  ( 1==gcd(b, mers_) );
    }

    ulong next_primitive()  // return poly, zero if there are no more
    {
        ulong b;
        do
        {
            do
            {
                b = bn_.next();
                if ( 0==b )  return 0;
            }
            while ( 0==bn_.is_lyndon_word() );
        }
        while ( 0==is_primitive() );

        p_ = n2b_.poly( bn_.data() );
        return  p_;
    }
};
// -------------------------

#endif  // !defined HAVE_ALL_IRREDPOLY_H__
