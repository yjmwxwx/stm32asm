// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bpol/poly-tab.h"
#include "bmat/bitmat-inline.h"
#include "bmat/bitmat-funcs.h"
#include "bits/bitlow.h"
#include "bits/print-bin.h"
#include "bpol/bitpol-irred.h"
#include "bpol/bitpol-order.h"
#include "bpol/normalbasis.h"
#include "bpol/gf2n.h"
#include "mod/factor.h"
#include "mod/mersenne.h"

#include "fxtio.h"

#include "jjassert.h"  //  jjnote: asserts used in code: GF2n::check() GF2n::init()


ulong GF2n::n_ = 0;  // the 'n' in GF(2**n)
ulong GF2n::c_ = 0;  // polynomial modulus
ulong GF2n::h_ = 0;  // auxiliary bit-mask for computations
ulong GF2n::mm_ = 0;  // 2**n - 1 == max order
ulong GF2n::g_ = 0;  // a generator
ulong GF2n::tv_ = 0;  // trace vector
ulong GF2n::sqr_tab[BITS_PER_LONG];  // table for fast squaring

ulong GF2n::is_normal_ = 0;  // whether field polynomial is normal
// tables for basis conversion:
ulong GF2n::p2n_tab[BITS_PER_LONG];  // polynomial to normal
ulong GF2n::n2p_tab[BITS_PER_LONG];  // normal to polynomial

// fixme: the following requires a global constructor (and destructor):
factorization GF2n::mfact_;  // factorization of max order

const char* GF2n::pc_ = 0;  // chars to print for zero and one: e.g.  "01" or ".1"

// fixme: the following three require global constructors (and global destructors):
GF2n GF2n::zero;  // zero (neutral element wrt. addition) in GF(2**n)
GF2n GF2n::one;  // one (neutral element wrt. multiplication) in GF(2**n)
//GF2n GF2n::tr0e;  // an element with trace == 0
GF2n GF2n::tr1e;  // an element with trace == 1


// if INIT_ASSERT is defined, asserts are C asserts,
// else init() returns false if one of the tests fail:
#define INIT_ASSERT

bool  // static
GF2n::init(ulong n, ulong c/*=0*/, bool normalq/*=0*/, bool trustme/*=0*/)
// Initialize class GF(2**n) for 0<n<=BITS_PER_LONG.
// If an irreducible polynomial c is supplied it is used as modulus,
// else a primitive polynomial of degree n is used.
// Irreducibility of c is asserted.
// If normalq is set, then a primitive normal polynomial is used,
// if in addition c is supplied, then normality of c is asserted.
// If trustme is set, then the asserts are omitted.
{
    n_ = n;

#ifdef INIT_ASSERT
    jjassert ( (0!=n_) && (n_<=BITS_PER_LONG) );
#else
    if ( (0==n_) || (n_>BITS_PER_LONG) )  return false;
#endif

    c_ = c;
    g_ = 0;

    h_ = (1UL << (n_-1));

    if ( 0==c_ )
    {
        if ( normalq )  c_ = highbit_normal_primpoly[n_];
        else            c_ = minweight_primpoly[n_];

//        g_ = 2UL;  // =='x' (comment out to always search for max order element)
    }
    else  // polynomial supplied
    {
        // do not accept reducible polynomials:
//        if ( n_ < BITS_PER_LONG )  // test only works for polynomials that fit into words
        {
            if ( ! trustme )
            {
#ifdef INIT_ASSERT
                jjassert( bitpol_irreducible_q(c_, h_) );
#else
                if ( ! bitpol_irreducible_q(c_, h_) )  return false;
#endif
            }
        }
    }


    h_ = (1UL << (n_-1));
    mm_ = (h_<<1) - 1;

#if 0
    tv_ = gf2n_trace_vector(2UL, c_, h_);
#else
    tv_ = gf2n_trace_vector_x(c_, n_);
#endif

    tr1e = lowest_one(tv_);
//    tr0e = 0;


    for (ulong k=0, m=1, s=1;  k<n_;  ++k, m<<=1)
    {
#if 0
        sqr_tab[k] = bitpolmod_square(m, c_, h_);
#else
        sqr_tab[k] = s;
//        s = bitpolmod_times_x(s, c_, h_);
//        s = bitpolmod_times_x(s, c_, h_);
        s = bitpolmod_times_x2(s, c_, h_);
#endif
    }


    // conversion to and from normal representation:
    for (ulong k=0, s=2;  k<n_;  ++k)
    {
        n2p_tab[k] = s;
        s = bitpolmod_square(s, c_, h_);
    }
    bitmat_transpose(n2p_tab, n_, n2p_tab);
    is_normal_ = bitmat_inverse(n2p_tab, n_, p2n_tab);

    // detect is supplied polynomial was declared normal but is not:
    if ( normalq )
    {
        if ( ! trustme )
        {
#ifdef INIT_ASSERT
            jjassert( is_normal_ );
#else
            if ( !is_normal_ )  return false;
#endif
        }
    }

    pc_ = ".1";

    mfact_.make_factorization(mm_, mersenne_prime_factor_tab);
//    mfact_.check();


    if ( 0==g_ )  // find maxorder element
    {
        ulong z;
        for (z=2; z<mm_; ++z)
        {
            ulong r = gf2n_order(z, c_, h_, mfact_);
            if ( r==mm_ )  { g_=z;  break; }
        }
        // jjassert( z < mm_ );
    }

    if ( 1==n_ )  g_ = 1;  // special case

    GF2n::zero.v_ = 0;
    GF2n::one.v_ = 1;

    return true;
}
// -------------------------


void  // static
GF2n::print_info(int level/*=0*/)
{
    ulong pn = n_ + 1;
    if ( n_ == BITS_PER_LONG )  pn = BITS_PER_LONG;
    cout << "  n = " << n_ << "  GF(2^n)" << endl;

    print_bin("  c = ", c_, pn, pc_);
    if ( is_normal_ ) cout << " [normal]";
    if ( 2!=g_ ) cout << " [NON-primitive]";
    cout << " == ";

    cout << "x^" << n_ << " + ";
    ulong j = n_ - 1;
    do
    {
        if ( c_ & (1UL<<j) )
        {
            if ( j )
            {
                cout << "x";
                if ( j>1 ) cout << "^" << j;
                cout << " + ";
            }
            else      cout << 1;
        }
    }
    while ( j-- );
    cout << "  (polynomial modulus)";
    cout<< endl;

    print_bin("  mm= ", mm_, pn, pc_);
    cout << "   == " << mm_;
    if ( 1 == mfact_.nprimes() )  cout << " (prime) ";
    else   cout << "  =  " << mfact_;
    cout << "  (maximal order)" << endl;
//    cout << endl;

    print_bin("  h = ", h_, pn, pc_);  cout << " (aux. bit-mask)" << endl;
    print_bin("  g = ", g_, pn, pc_);  cout << " (element of maximal order)" << endl;
    print_bin("  tv= ", tv_, pn, pc_);  cout << " (traces of x^i)" << endl;
//    {  // TEST:
//        ulong qq = gf2n_trace_vector_x(c_, n_);
//        print_bin(" ?tv= ", qq, pn, pc_);  cout << " (traces of x^i)" << endl;
//        jjassert( qq == tv_ );
//    }


//    print_bin("tr0e= ", tr0e.v_, pn, pc_);  cout << " (element with trace=0)" << endl;
    print_bin("tr1e= ", tr1e.v_, pn, pc_);  cout << " (element with trace=1)" << endl;

    if ( level>=1 )
    {
        cout << "sqr_tab[]=" << endl;
        for (ulong k=0; k<n_; ++k)
        {
            print_bin("  ", sqr_tab[k], pn, pc_);
            cout << endl;
        }

        cout << "  pc= \"" << pc_ << "\""
             << "  (symbols for zero and one when printing)" << endl;
    }

    check();
}
// -------------------------

void  // static
GF2n::check()  // uses asserts
{
//    jjassert( (n_<2) || (0!=tr0e) );
//    jjassert( 0==tr0e.trace() );
    jjassert( 0!=tr1e );
    jjassert( 1==tr1e.trace() );
    if ( n_<BITS_PER_LONG )  jjassert( bitpol_irreducible_q(c_, h_) );
    jjassert( mfact_.is_factorization_of(mm_) );
}
// -------------------------

ulong  // static
GF2n::p2n(ulong f)
{
    return  bitmat_mult_Mv(p2n_tab, n_, f);
}
// -------------------------

ulong  // static
GF2n::n2p(ulong f)
{
    return  bitmat_mult_Mv(n2p_tab, n_, f);
}
// -------------------------



std::ostream & operator << (std::ostream & os, const GF2n & f)
{
    char p[BITS_PER_LONG+1];
    ulong n = GF2n::n_;
    p[n] = 0;  // terminate string
    ulong v = f.v_;
    for (ulong k=0; k<n; ++k)  // lowest term appears left
    {
        p[n-1-k] = GF2n::pc_[ v & 1 ];
        v >>= 1;
    }
    os << p;
    return os;
}
// -------------------------
