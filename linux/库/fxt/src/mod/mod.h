#if !defined HAVE_MOD_H__
#define      HAVE_MOD_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "mod/mtypes.h"
#include "mod/numtheory.h"
#include "mod/modarith.h"
class factorization;

#include "fxtio.h"

// mod/modinit.cc:
void mod_reset();
bool mod_initialize(umod_t m, umod_t *primes=0);

//#define CLASS_MOD_USE_M1DD  // default off

class mod
// Modular type and arithmetic operations on it
{
public:
    umod_t x_;

public:
    static umod_t modulus;        // 0 <= x < modulus
#ifdef CLASS_MOD_USE_M1DD
    static ldouble m1dd;          // 1.0/modulus (for multiplication)
#endif
    static factorization modfact;  // factorization of modulus
    static umod_t maxorder;       // maximal order of elements

    static umod_t phi;            // euler_phi(modulus)
    static factorization phifact;  // factorization of phi
//    static umod_t default_modulus;  // a default useful for NTTs (unused)

    static mod zero;             // = 0
    static mod one;              // = 1
    static mod maxordelem;       // element of maximal order


    static uint max2pow;       // root of order 2**ldn exists for ldn<=max2pow
    // NTT length <= 2^(max2pow)  (for NTTs restricted to powers of 2)

    static mod *mtab;  // data for root_2pow[] ... isinm[] (all below)
    static mod *root_2pow;  // [max2pow+1];    // element[k] is of order 2^k
    static mod *root_m2pow;  // [max2pow+1];   // element[k] is of order 2^-k
    static mod *cos, *isin;  // [max2pow+1];   // cos/i*sin corresponding to root_2pow
    static mod *cosm, *isinm;  // [max2pow+1];  // cos/sin corresponding to root_m2pow


public:
    explicit mod()
        : x_(0)
    { ; }

    explicit mod(const umod_t i)
        : x_( ( i<modulus ? i :  i%modulus ) )
    { ; }

    mod(const mod &m) : x_(m.x_)  { ; }
    ~mod()  { ; }

    static bool init(umod_t m, factorization *mf=0);
    friend bool mod_initialize(umod_t m, umod_t *primes/*=0*/);
    friend void mod_reset();

    mod pow(umod_t e)  const
    {
        mod s;
        s.x_ = pow_mod(x_, e, mod::modulus);
        return  s;
    }

    mod inv() const
    {
        mod s;
//        s.x_ = inv_mod_egcd(x_, mod::modulus);
//        s.x_ = pow_mod(x_, mod::phi-1ULL, mod::modulus);
        s.x_ = pow_mod(x_, mod::maxorder-1ULL, mod::modulus);
        return  s;
    }

    umod_t order()  const
    {
        return  order_mod(x_, mod::modulus, mod::phifact);
    }

    mod sqr() const
    {
        mod s;
        s.x_ = mul_mod(x_, x_, mod::modulus);
        return  s;
    }

    inline mod & operator = (const mod &h)  { x_ = h.x_;  return *this; }
    inline mod & operator = (umod_t i)  { (*this) = mod(i);  return *this; }
    inline mod & operator = (uint i)  { (*this) = mod(i);  return *this; }
    inline mod & operator = (ulong i)  { (*this) = mod(i);  return *this; }

    friend inline mod & operator ++ (mod &z)
    { ++z.x_; if ( z.x_==mod::modulus ) z.x_=0;  return z; }

    friend inline mod & operator -- (mod &z)
    { if ( z.x_==0 ) z.x_=mod::modulus;  z.x_--;  return z; }

    friend inline mod & operator += (mod &z, const mod &h)
    { z.x_ = add_mod(z.x_, h.x_, mod::modulus);  return z; }

    friend inline mod & operator -= (mod &z, const mod &h)
    { z.x_ = sub_mod(z.x_, h.x_, mod::modulus);  return z; }

    friend inline mod & operator *= (mod &z, const mod &h)
    { z.x_ = mul_mod(z.x_, h.x_, mod::modulus);  return z; }
//    { z.x_ = mul_mod_m1dd(z.x_, h.x_, mod::modulus, mod::m1dd);  return z; }

    friend inline mod & operator /= (mod &z, const mod &h)
    { z *= h.inv();  return z; }


    friend inline mod operator + (const mod &h1, const mod &h2)
    { mod z(h1); z += h2; return z; }

    friend inline mod operator - (const mod &h1, const mod &h2)
    { mod z(h1); z -= h2; return z; }

    friend inline mod operator * (const mod &h1, const mod &h2)
    { mod z(h1); z *= h2; return z; }

    friend inline mod operator / (const mod &h1, const mod &h2)
    { mod z(h2.inv()); z *= h1; return z; }


    mod & negate()  { x_ = neg_mod(x_, mod::modulus);  return *this; }

    friend inline mod operator - (const mod &h)
    { mod n(h);  n.negate();  return n; }

    friend inline mod operator + (const mod &h)  { return h; }



    friend inline bool operator == (const mod &h1, const mod &h2)
    { return  h1.x_ == h2.x_; }

    friend inline bool operator != (const mod &h1, const mod &h2)
    { return  h1.x_ != h2.x_; }


    friend inline bool operator < (const mod &h1, const mod &h2)
    { return  h1.x_ < h2.x_; }

    friend inline bool operator <= (const mod &h1, const mod &h2)
    { return  h1.x_ <= h2.x_; }

    friend inline bool operator > (const mod &h1, const mod &h2)
    { return  h1.x_ > h2.x_; }

    friend inline bool operator >= (const mod &h1, const mod &h2)
    { return  h1.x_ >= h2.x_; }


    static mod root2pow(int ldorder);  // root of order 2^ldorder
    static mod cos2pow(int ldorder);  // cos of order 2^ldorder
    static mod isin2pow(int ldorder);  // i*sin of order 2^ldorder

    static void print_info();
};
// -------------------------

std::istream&  operator >> (std::istream& is, mod& h);
std::ostream&  operator << (std::ostream& os, const mod& h);



// jj_end_autodoc

// mod/modinfo.cc:
void mod_info0();
void mod_info1();
void mod_info1b();
void mod_info2();
void mod_info3();
void mod_info4();
void mod_info_roots();
void mod_info99();



#endif  // !defined HAVE_MOD_H__
