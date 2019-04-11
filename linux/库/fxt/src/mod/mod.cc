// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/sign.h"  //  Abs()
#include "mod/mod.h"
#include "mod/factor.h"

#include "fxtio.h"
#include "fxttypes.h"

//#include "jjassert.h"

umod_t          mod::modulus = 0;
#ifdef CLASS_MOD_USE_M1DD
ldouble         mod::m1dd = 0.0;
#endif

// fixme: several global constructors and destructors required for the following
factorization   mod::modfact;

umod_t          mod::maxorder = 0;
uint            mod::max2pow = 0;

umod_t          mod::phi = 0;
factorization   mod::phifact;

mod    mod::zero;
mod    mod::one;
mod    mod::maxordelem;

//umod_t mod::default_modulus = 0x3fffc00000000001ULL;

mod  * mod::mtab = 0;
mod  * mod::root_2pow = 0;
mod  * mod::root_m2pow = 0;
mod  * mod::cos = 0;
mod  * mod::isin = 0;
mod  * mod::cosm = 0;
mod  * mod::isinm = 0;



bool
mod::init(umod_t m, factorization *mf/*=0*/)
{
    bool q;
    if ( mf )  q = mod_initialize(m, (*mf).prime_);
    else       q = mod_initialize(m, 0);
    return  q;
}
// -------------------------

//mod
//root(umod_t r)
//// find root of unity of order r
//{
//    umod_t mx = mod::maxorder;
//
//    if ( r==mx )  return mod::maxordelem;
//
//    umod_t mxr = mx/r;
//    if ( (mxr*r)!=mx )  // r must be a divider of maxorder
//    {
//        cerr << " request for root of impossible order " << r << endl;
//        jjassert( 0 );
//    }
//
//    mod  h( (mod::maxordelem).pow(mxr) );
////    jjassert( r==order(h) );
//    return h;
//}
//// -------------------------


mod
mod::root2pow(int ldorder)
// Return root of order 2**ldorder
{
    if ( Abs(ldorder) >  (long)max2pow )  return  mod::zero;
    if ( ldorder>=0 )  return root_2pow[ldorder];
    else               return root_m2pow[-ldorder];
}
// -------------------------

mod
mod::cos2pow(int ldorder)
// Return cos corresponding to root of order 2**ldorder
{
    if ( Abs(ldorder) >  (long)max2pow )  return  mod::zero;
    if ( ldorder>=0 )  return cos[ldorder];
    else               return cosm[-ldorder];
}
// -------------------------

mod
mod::isin2pow(int ldorder)
// Return i*sin corresponding to root of order 2**ldorder
{
    if ( Abs(ldorder) >  (long)max2pow )  return  mod::zero;
    if ( ldorder>=0 )  return isin[ldorder];
    else               return isinm[-ldorder];
}
// -------------------------


void
mod::print_info()
{
    mod_info0();
    mod_info1();
    mod_info1b();
    mod_info2();
    mod_info3();
    mod_info4();
    mod_info99();
}
// -------------------------


std::istream & operator >> (std::istream & is, mod & h)
{
    is >> h.x_;
    return is;
}
// -------------------------


std::ostream & operator << (std::ostream & os, const mod & h)
{
    os << h.x_;
    return os;
}
// -------------------------
