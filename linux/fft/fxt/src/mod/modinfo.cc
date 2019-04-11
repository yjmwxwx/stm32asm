// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "mod/mod.h"
#include "mod/factor.h"
#include "bits/bit2pow.h"  // ld()

#include "fxtio.h"

//#include "jjassert.h"

#include <cmath>  // log()
//#include <cstdlib>  // abs(int)
#include "aux0/sign.h"  // Abs()


void
mod_info0()
{
    cout << "-------- start MOD_INIT():  m=" << mod::modulus <<  " --------" << endl;
}
// -------------------------

void
mod_info99()
{
    cout << "-------- end MOD_INIT(). --------" << endl;
}
// -------------------------


void
mod_info1()
{
    umod_t m = mod::modulus;

    cout << "modulus= " << m
         << " == 0x" << hex << m << dec << endl;

    cout << "modulus is ";
    if ( !is_cyclic(mod::modfact) )  cout << "NOT ";
    cout << "cyclic" << endl;

    cout << "modulus is ";
    if ( mod::modfact.is_prime() )
    {
        cout << "prime " << endl;
    }
    else
    {
        cout << "composite  ";
        cout << " == " << mod::modfact << endl;
    }
}
// -------------------------


static inline uint highest_one_idxp1(uint64 m)
{
    uint k = 0;
    while ( m )  { k++; m>>=1; }
    return k;
}
// -------------------------

void
mod_info1b()
{
    umod_t m = mod::modulus;
    umod_t mb = highest_one_idxp1(m);
    double mbd = log((double)m)/log(2.0);
    if ( (umod_t(1)<<(mb-1))==m )  mbd = (double)mb;

    cout << "bits(modulus)= ";
    cout.precision(8);
    cout << mbd;

//    cout.precision(16);
    double d = (double)mb - mbd;
    if ( d != 0.0 )
        cout << "  == " << mb << " - " << d;
    cout << endl;
}
// -------------------------


void
mod_info2()
{
    cout << "euler_phi(modulus)= " << (mod::phi)
         << " == 0x" << hex <<  (mod::phi) << dec
         << " == " << mod::phifact
         << endl;

    cout << "maxorder= " << (mod::maxorder)
         << " == 0x" << hex <<  (mod::maxorder) << dec
         << endl;
}
// -------------------------


void
mod_info3()
{
//    cout << " 1/2 = " << mod::half
//         << " == 0x" << hex << (mod::half) << dec
//         << endl;

    cout << "maxordelem= " << (mod::maxordelem)
         << " == 0x" << hex << (mod::maxordelem) << dec
         << endl;

    umod_t r = (mod(2)).order();
    cout << "order(2)= " << r;
    if ( 0!=r )
    {
        factorization F(r);
        cout << " == " << F;
    }
    cout << endl;

    for (umod_t x=4, xe=2, t=0;  x<mod::modulus;  x*=2, ++xe)
    {
        r = (mod(x)).order();
        umod_t ze = ld(r);
        if ( ((1ULL<<ze) == r) && !(r & t) )
        {
            t |= r;
            cout << "order(2^" << xe << ")=2^" << ze << endl;
        }
    }
}
// -------------------------


void
mod_info4()
{
    int m2 = (int)mod::max2pow;  // jjcast
    cout << "max2pow= " << m2
//         << "   (root of order 2**ldn exists for ldn<=max2pow)"
         << "   (max FFT length = 2**" << m2
         << " == " << ((umod_t)1<<m2) << ")"
         << endl;

    if ( mod::modfact.prime(0)==2 )
    {
        cout << "2\\modulus, cannot divide by 2 (or 2**n)" << endl;
        cout << " =--> no length 2**n inverse FFT !" << endl;
    }

    cout << "root2pow(max2pow)=" << mod::root2pow(m2)
         << "   root2pow(-max2pow)=" << mod::root2pow(-m2)
         << endl;

    if ( m2 >= 2 )
    {
        cout << "sqrt(-1) =: i = " << mod::root2pow(2) << endl;
    }

    if ( m2 > 0 )
    {
        if ( (mod::root2pow(1)).x_ != (mod::modulus - 1ULL) )
            cout << "root2pow(1)=" << mod::root2pow(1) << " != -1  (!)"
                 << endl;
    }

//    void mod_info_roots();
}
// -------------------------


//static void
//print_zcs(umod_t z, umod_t c, umod_t s)
//{
//}
// -------------------------

void
mod_info_roots()
{
    int m2 = (int)mod::max2pow;
    int w = 1;
    for (umod_t z=mod::modulus;  z;  z/=10)  ++w;

    mod ii = mod::one;
    if ( m2 >= 2 )  ii = mod::root2pow(-2);

    for (int k=m2; k>=-m2; --k)
    {
        mod z(mod::root2pow(k));
        mod c(mod::cos2pow(k));
        mod s(mod::isin2pow(k));
        cout << setw(2) << k << ":";  // << endl;
        cout << "    z=" << setw(w) << z;
        cout << "  = (" << setw(w) << c;
        cout << "   +" << setw(w) << s;
        cout << ")";
        cout << "  =  (" << setw(w) << c;
        cout << "   +" << setw(w) << s*ii;
        cout << "*i)";

//        cout << "      " << ( z-(c+s) );
//        cout << "   ord(z)=" << z.order();
        cout << endl;

//        jjassert( z.order()==(1ULL<<Abs(k)) );
//        jjassert( z==c+s );
    }
}
// -------------------------


