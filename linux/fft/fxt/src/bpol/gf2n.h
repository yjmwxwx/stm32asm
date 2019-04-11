#if !defined  HAVE_GF2N_H__
#define       HAVE_GF2N_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bpol/bitpolmod-arith.h"
//#include "bpol/bitpol-order.h"
#include "bpol/gf2n-trace.h"

#include "fxtio.h"


class factorization;
class GF2n;

// bpol/gf2n.cc:
//std::istream&  operator >> (std::istream& is, GF2n& f);
std::ostream&  operator << (std::ostream& os, const GF2n& f);

// bpol/gf2n-minpoly.cc:
ulong gf2n_minpoly(GF2n a, ulong &bp);
ulong gf2n_minpoly2(GF2n a, ulong &bp);
GF2n gf2n_eval_poly(GF2n a, ulong bp);


// bpol/gf2n-solvequadratic.cc:
bool gf2n_solve_reduced_quadratic(GF2n c, GF2n& r);
bool gf2n_solve_quadratic(GF2n a, GF2n b, GF2n c, GF2n& r0, GF2n& r1);

// bpol/gf2n-order.cc:
ulong gf2n_order(ulong g, ulong c, ulong h, const factorization &mfact);


class GF2n
// Implementation of binary finite fields GF(2**n)
// with the arithmetic operations.
// GF2n::init(n)  _MUST_ be called before usage.
// n must be <= BITS_PER_LONG.
{
public:
    ulong v_;

public:
    static ulong n_;  // the 'n' in GF(2**n)
    static ulong c_;  // polynomial modulus
    static ulong h_;  // auxiliary bit-mask for computations
    static ulong mm_;  // 2**n - 1 == max order (a Mersenne number)
    static ulong g_;  // a generator (element of maximal order)
    static ulong tv_;  // trace vector
    static ulong sqr_tab[BITS_PER_LONG];  // table for fast squaring
    static factorization mfact_;  // factorization of max order
    static const char* pc_;  // chars to print zero and one: e.g.  "01" or ".1"

    static ulong is_normal_;  // whether field polynomial is normal
    // tables for basis conversion:
    static ulong p2n_tab[BITS_PER_LONG];  // polynomial to normal
    static ulong n2p_tab[BITS_PER_LONG];  // normal to polynomial

    static GF2n zero;  // zero (neutral element wrt. addition) in GF(2**n)
    static GF2n one;  // one (neutral element wrt. multiplication) in GF(2**n)
//    static GF2n tr0e;  // an element with trace == 0
    static GF2n tr1e;  // an element with trace == 1

public:
    explicit GF2n() : v_(0)  { ; }
    explicit GF2n(const ulong i) : v_(i & mm_)  { ; }
    /*explicit*/ GF2n(const GF2n &g) : v_(g.v_)  { ; }
//    virtual
    ~GF2n()  { ; }

    // bpol/gf2n.cc:
    static bool init(ulong n, ulong c=0, bool normalq=0, bool trustme=0);
    static void print_info(int level=0);
    static void check();  // uses asserts
    static bool is_normal()  { return (bool)is_normal_; }
    static ulong p2n(ulong f);
    static ulong n2p(ulong f);
    // (end gf2n.cc)

    ulong get_normal()  const  { return p2n(v_); }
    ulong set_normal(ulong r)  { v_ = n2p(r);  return v_; }

    ulong order() const
    {
        return  gf2n_order(v_, c_, h_, mfact_);
    }

    bool is_generator()  const { return order() == mm_; }

    GF2n inv()  const
    {
        GF2n z;
#if 1  // work also if n == BITS_PER_LONG
        z.v_= bitpolmod_inverse_irred(v_, GF2n::c_, GF2n::h_);  // by powering
#else
        z.v_= bitpolmod_inverse(v_, GF2n::c_);  // by extended GCD
#endif
        return z;
    }

    GF2n pow(ulong e)  const
    {
        GF2n z( bitpolmod_power(v_, e, GF2n::c_, GF2n::h_) );
        return z;
    }

    GF2n sqr()  const
    {
#if 0
        GF2n z( bitpolmod_square(v_, GF2n::c_, GF2n::h_) );
#else
        // This version is about 30% faster with
        // squaring all words in GF(2^{24}):
        ulong v = 0;
        ulong m1 = 1,  m2 = 1;
        ulong k = 0;
        while ( 2*k < n_ )
        {
            if ( m1 & v_ )  v ^= m2;
            m1 <<= 1;
            m2 <<= 2;
            ++k;
        }

        while ( k < n_ )
        {
            if ( m1 & v_ )  v ^= sqr_tab[k];
            m1 <<= 1;
            ++k;
        }

        GF2n z;  z.v_ = v;
#endif
        return z;
    }

    GF2n sqrt()  const
    {
        GF2n z( bitpolmod_sqrt(v_, GF2n::c_, GF2n::h_) );
        return z;
    }

    ulong trace()  const
    {
        return  gf2n_fast_trace(v_, tv_);
    }

    GF2n half_trace()  const
    {
        GF2n t( gf2n_half_trace(v_, c_, h_) );
        return t;
    }

    ulong minpoly()  const
    {
        ulong m;
//        gf2n_minpoly2(*this, m);  // returned degree is discarded
        gf2n_minpoly(*this, m);  // returned degree is discarded
        return m;
    }

    inline GF2n & operator = (const GF2n &f)  { v_ = f.v_;  return *this; }
    inline GF2n & operator = (ulong i)  { (*this) = GF2n(i);  return *this; }


    friend inline GF2n & operator += (GF2n &z, const GF2n &f)
    { z.v_ ^= f.v_;  return z; }

    friend inline GF2n & operator -= (GF2n &z, const GF2n &f)
    { z.v_ ^= f.v_;  return z; }

    friend inline GF2n & operator *= (GF2n &z, const GF2n &f)
    { z.v_ = bitpolmod_mult(z.v_, f.v_, GF2n::c_, GF2n::h_);  return z; }

    friend inline GF2n & operator /= (GF2n &z, const GF2n &f)
    { z *= f.inv();  return z; }


    friend inline const GF2n operator + (const GF2n &f1, const GF2n &f2)
    { GF2n z(f1); z.v_ ^= f2.v_; return z; }

    friend inline const GF2n operator - (const GF2n &f1, const GF2n &f2)
    { GF2n z(f1); z.v_ ^= f2.v_; return z; }

    friend inline const GF2n operator * (const GF2n &f1, const GF2n &f2)
    { GF2n z(f1); z *= f2; return z; }

    friend inline const GF2n operator / (const GF2n &f1, const GF2n &f2)
    { GF2n z(f1); z /= f2; return z; }


    friend inline bool operator == (const GF2n &f1, const GF2n &f2)
    { return  f1.v_ == f2.v_; }

    friend inline bool operator != (const GF2n &f1, const GF2n &f2)
    { return  f1.v_ != f2.v_; }

    friend inline bool operator == (const GF2n &f, ulong v)    { return  f.v_ == v; }
    friend inline bool operator == (ulong v, const GF2n &f)    { return  f.v_ == v; }

    friend inline bool operator != (const GF2n &f, ulong v)    { return  f.v_ != v; }
    friend inline bool operator != (ulong v, const GF2n &f)    { return  f.v_ != v; }
};
// -------------------------




#endif  // !defined HAVE_GF2N_H__
