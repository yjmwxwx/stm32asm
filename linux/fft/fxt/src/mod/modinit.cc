// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "mod/mod.h"
#include "mod/factor.h"
#include "mod/numtheory.h"
//#include "mod/modarith.h"


#include "fxtio.h"


//#define  INIT_DEBUG  // define for debug
#ifdef INIT_DEBUG
#include "jjassert.h"
#warning '******** INIT_DEBUG'
#define  MI_ASSERT(c, s)  { if ( !(c) ) { cout << s << endl; jjassert(0); } }
#else
#define  MI_ASSERT(c, s)  { ; }
#endif


//class mod_cleanup
//{
//public:
//    // no data
//    mod_cleanup()  { ; }  // nop
//    ~mod_cleanup()
//    {
//        mod_reset();
//    }
//};
//// -------------------------
//
//static mod_cleanup  do_mod_cleanup;

void
mod_reset()
{
#ifdef CLASS_MOD_USE_M1DD
    mod::m1dd = 0.0;
#endif
    mod::modfact.reset();

    mod::maxorder = 0;
    mod::max2pow = 0;

    mod::phi = 0;
    mod::phifact.reset();

    mod::zero.x_ = 0;
    mod::one.x_ = 0;
    mod::maxordelem.x_ = 0;

    if ( mod::mtab != 0 )  delete [] mod::mtab;
//    mod::root_2pow = 0;
//    mod::root_m2pow = 0;
}
// -------------------------


bool
mod_initialize(umod_t m, umod_t *primes/*=0*/)
{
    mod_reset();

    mod::modulus = m;
#ifdef CLASS_MOD_USE_M1DD
    mod::m1dd = (ldouble)1/(ldouble)m;
#endif

#ifdef INIT_DEBUG
    mod_info0();
#endif
    MI_ASSERT( !(m&((umod_t)3<<62)), " modulus must have less than 62 bits " );
//    MI_ASSERT( !(m&((umod_t)1<<63)), " modulus must have less than 64 bits " );


    // +++++ only after this point we can multiply mods !
#ifdef INIT_DEBUG
    cout << "MOD_INIT(): can multiply mods" << endl;
#endif

    mod::zero = (uint)0;
    mod::one =  (uint)1;

    mod::modfact.make_factorization(m, primes);
#ifdef INIT_DEBUG
    cout << mod::modfact << endl;
#endif
    MI_ASSERT( mod::modfact.check(), "factorization of the modulus failed" );
    MI_ASSERT( mod::modfact.is_factorization_of(m), "factorization of the modulus failed" );

    // +++++ have modulus, modfact
#ifdef INIT_DEBUG
    cout << "MOD_INIT(): have modulus, modfact" << endl;
    mod_info1();
    mod_info1b();
#endif


    if ( mod::modfact.is_prime() )  mod::phi = m-1;
    else  mod::phi = euler_phi(mod::modfact);

    (mod::phifact).make_factorization(mod::phi);
    MI_ASSERT( mod::modfact.check(), "factorization of the phi failed" );
    MI_ASSERT( mod::phifact.is_factorization_of(mod::phi), "factorization of phi failed" );

    // +++++ have phi, phifact
#ifdef INIT_DEBUG
    cout << "MOD_INIT(): have phi, phifact" << endl;
#endif

    mod::maxorder = maxorder_mod(mod::modfact);


    // +++++ have maxorder
#ifdef INIT_DEBUG
    cout << "MOD_INIT(): have maxorder" << endl;
    mod_info2();
#endif


#ifdef INIT_DEBUG
    cout << "MOD_INIT(): ping 1." << endl;
#endif
    mod::maxordelem = maxorder_element_mod(mod::modfact, mod::phifact);
#ifdef INIT_DEBUG
    cout << "MOD_INIT(): ping 2." << endl;
#endif

#ifdef INIT_DEBUG
    umod_t rr = (mod::maxordelem).order();
#endif

    MI_ASSERT( rr != 0, "oops, order of primitive root is ==0" );
    MI_ASSERT( rr == mod::maxorder,
               "oops, order of primitive root is != maxorder" );


    // +++++ have element of maximal order (primitive root if m cyclic)
#ifdef INIT_DEBUG
    cout << "MOD_INIT(): have element of maximal order" << endl;
    mod_info3();
#endif


    mod::max2pow = 0;
    {
        umod_t t = mod::maxorder;
        while ( 0==(t&1) )  { ++(mod::max2pow);  t>>=1; }
    }

    const int m2 = (int)mod::max2pow;  // jjcast
    const umod_t z = ((mod::maxorder) >> m2);
//    cout << "m2=" << m2 << endl;
//    cout << "z=" << z << endl;

    {
        const ulong nn = (ulong)(m2+1);  // jjcast

        mod::mtab = new mod[6*nn];
        mod *p = mod::mtab;

        mod::root_2pow = p;
        mod::root_m2pow = p + 1*nn;
        mod::cos = p + 2*nn;
        mod::isin = p + 3*nn;
        mod::cosm = p + 4*nn;
        mod::isinm = p + 5*nn;
    }


    // set up roots of order 2**(+-k):
    mod t2;
#ifdef INIT_DEBUG
    cout << "MOD_INIT(): searching maxorder-element ..." << endl;
#endif
    t2 = mod::maxordelem.pow(z);
#ifdef INIT_DEBUG
    cout << "MOD_INIT(): searching maxorder-element done." << endl;
#endif
//    cout << "t=" << t << endl;
    for (int k=m2; k>=0; --k)
    {
        mod::root_2pow[k] = t2;
        mod::root_m2pow[k] = t2.inv();
        t2 *= t2;
    }

    // set up sin/cos of order 2**(+-k):
    for (int k=0; k<=m2; ++k)
    {
        mod tr = mod::root2pow(k);
        mod tr2 = tr + tr;
        mod tc = (tr * tr + mod::one) / tr2;
        mod::cos[k] = tc;
        mod::isin[k] = tr - tc;
    }

    for (int k=1; k<=m2; ++k)
    {
        mod tr = mod::root2pow(-k);
        mod tr2 = tr + tr;
        mod tc = (tr * tr + mod::one) / tr2;
        mod::cosm[k] = tc;
        mod::isinm[k] = tr - tc;
    }




    // +++++ from now on we can do NTTs ...
#ifdef INIT_DEBUG
    cout << "MOD_INIT(): can do NTTs" << endl;
    mod_info4();
#endif

#ifdef INIT_DEBUG
    for (int k=0; k<=m2; ++k)
    {
        umod_t r;  // only used if MI_ASSERT is defined
        umod_t p2k = (1ULL << (uint)k);

        r = (mod::root2pow(k)).order();
        MI_ASSERT( r==p2k, "order(root_2pow(k)) is != 2**k" );

        r = (mod::root2pow(-k)).order();
        MI_ASSERT( r==p2k, "order(root2pow(-k)) is != 2**k" );

        mod t = (mod::root2pow(k))*(mod::root2pow(-k));
        MI_ASSERT( t==mod::one,  "root2pow(k) * root2pow(-k) is != 1" );
    }
#endif

#ifdef INIT_DEBUG
    mod_info99();
#endif

    return  true;
}
// -------------------------
