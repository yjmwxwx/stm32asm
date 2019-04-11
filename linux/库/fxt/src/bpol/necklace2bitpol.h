#if !defined  HAVE_NECKLACE2BITPOL_H__
#define       HAVE_NECKLACE2BITPOL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bithigh.h"
#include "bpol/bitpolmod-arith.h"
#include "bpol/bitpolmod-minpoly.h"
#include "bpol/poly-tab.h"
#include "bits/bitsperlong.h"

#include "fxttypes.h"


class necklace2bitpol
// Generate irreducible polynomials from necklaces.
{
public:
    ulong n_;  // degree of c_
    ulong c_;  // modulus (irreducible polynomial)
    ulong h_;  // mask used for computation
    ulong a_;  // generator modulo c
    ulong e_;  // a^b
    ulong bp_;  // result as bit-vector

private:  // have pointer data
    necklace2bitpol(const necklace2bitpol&);  // forbidden
    necklace2bitpol & operator = (const necklace2bitpol&);  // forbidden

public:
    explicit necklace2bitpol(ulong n, ulong c=0, ulong a=0)
        : n_(n), c_(c), a_(a)
    {
        init(n, c, a);
    }

    ~necklace2bitpol()  { ; }

    void init(ulong n, ulong c=0, ulong a=0)
    {
        if ( 0==c )  c_ = lowbit_primpoly[n_];
        if ( 0==a )  a_ = 2UL;  // 'x'
        h_ = (1UL << (n-1));
    }

    ulong poly(ulong b)
    {
#if 1  // much faster version(s):
        const ulong e = bitpolmod_power(a_, b, c_, h_);
        e_ = e;  // for reference

#if 0  // canned routine from bpol/bitpolmod-minpoly.h:
        bitpolmod_minpoly(e, c_, n_, bp_);
        return  bp_;
#else  // inlined code
        const ulong x = 2;  // a root of C
        ulong s = e;
        ulong m = 1;  // minpoly
        for (ulong j=0; j<n_; ++j)
        {
            ulong t = x ^ s;
            m = bitpolmod_mult(m, t, c_, h_);
            s = bitpolmod_square(s, c_, h_);
        }
        bp_ = m ^ c_;
        return  bp_;
#endif

#else  // slow version
        ulong p_[BITS_PER_LONG+1];  // polynomial over GF(2**n_)
        for (ulong k=0; k<=n_; ++k)  p_[k] = 0;
        p_[0] = 1;
        ulong e = bitpolmod_power(a_, b, c_, h_);
        e_ = e;  // for reference

        for (ulong d=1; d<=n_; ++d)
        {
            for (ulong k=d; k; --k)  p_[k] = p_[k-1];
            p_[0] = 0;
            for (ulong k=0; k<d; ++k)
            {
                p_[k] ^= bitpolmod_mult( p_[k+1], e, c_, h_);
            }

            e = bitpolmod_square(e, c_, h_);
        }

        ulong bp = 0;
        for (ulong j=0; j<=n_; ++j)  bp |= (p_[j] << j);
        bp_ = bp;
        return  bp_;
#endif
    }
};
// -------------------------

#endif  // !defined HAVE_NECKLACE2BITPOL_H__
