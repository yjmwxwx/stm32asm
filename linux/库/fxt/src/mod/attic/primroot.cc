
#include "mod.h"
#include "modm.h"
#include "factor.h"

//#include "jjassert.h"


int
is_primitive_root_mod(umod_t r, umod_t m, const factorization &pf)
//
// tests whether r is a primitive root
//
// r is a primitive root of m  <==>
// r^((m-1)/a)!=1 for all prime factors a of m-1
//
{
    cout << "\n\n  is_primitive_root():  testing r=" << r << endl;
    umod_t h = m-1;  // cardinality
    cout << "\n  is_primitive_root():  cardinality h=" << h << endl;

    for (int i=0; i<pf.npr; i++)
    {
        umod_t v = pf.prime[i];

        umod_t x = pow_mod(r,h/v,m);

//        cout << "\n(mod::phi-1)=" << (mod::phi-1) << endl;
//      cout << " test for prime[" << i << "]= " << v
//           << " (ex=" << h/v << ")"
//           << " gave:" << x
//           << endl;

        if ( x==1 )  return 0;  // r is not a primitive root
    }

    return 1;  // all factors tested, r is a primitive root
}
// -------------------------




umod_t
primitive_root_mod(umod_t m, const factorization &pf)
//
// finds a primitive root mod m
//
{
    if ( m==2 )  return 1;
    if ( m==4 )  return 3;

    umod_t x;

    // first search small primes:
    int i = 0;
    while ( 0!=(x=prime(i)) )
    {
        if ( x>=m )  break;
        i++;
//        if ( mod::modfact.exponent(x) )  continue;
        if ( is_primitive_root_mod(x,m,pf) )  return x;
    }

    // (rarely ever reached)
    while (  ++x<m )
    {
//        if ( gcd(mod::modulus,x)!=1 )  continue;
        if ( is_primitive_root_mod(x,m,pf) )  return x;
    }

    jjassert2( 0, "primitive_root_mod() failed." );
    return 0;
}
// -------------------------

