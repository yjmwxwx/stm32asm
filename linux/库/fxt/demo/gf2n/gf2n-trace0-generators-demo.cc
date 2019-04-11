
#include "bpol/gf2n.h"
//demo-include "bpol/gf2n.cc"
#include "bpol/bitpolmod-arith.h"  // bitpolmod_times_x()

#include "aux0/gcd.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "jjassert.h"


//% Count primitive elements with trace==0 in GF(2**n)  (OEIS sequences A192211 and A152049).

//#define TIMING  // uncomment to disable printing

#define USE_GCD  // define to optimize using gcd()  // big speedup
#define GENX  // define to optimize using generator 'x'  // small speedup

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "degree of field (n>=2)");
    jjassert( n>=2 );

    GF2n::init(n);

//    GF2n::print_info();
//    cout << "" << endl;

    GF2n f(1);
#ifdef GENX
    { GF2n g(2); jjassert( g.is_generator() ); }  // want generator 'x'
    const ulong c = GF2n::c_;
    const ulong h = GF2n::h_;
#else
    GF2n g( GF2n::g_ );
    jjassert( g.is_generator() );
#endif

#ifdef USE_GCD
    const ulong mm = GF2n::mm_;  // max order (used for gcd())
#endif

    ulong k = 0;
    ulong ct = 0;
    do
    {
        ++k;

#ifdef GENX
        f.v_ = bitpolmod_times_x(f.v_, c, h);
#else
        f *= g;
#endif

        if ( 0!=f.trace() )  continue;
#ifdef USE_GCD
        if ( 1 != gcd(k, mm) )  continue;  // much faster!
#else
        if ( ! f.is_generator() )  continue;
#endif
        ++ct;


#ifndef TIMING


        cout << "     " << f;
//        cout << "  [" << f.is_generator() << "]";
//        cout << "  [" << gcd(k, mm) << "]";
        cout << endl;
#ifdef GENX
#ifdef USE_GCD
        jjassert( (1==gcd(k, mm)) == f.is_generator() );
#endif
#endif
#endif
    }
    while ( f!=1 );

    cout << "  ct=" << ct;
    cout << endl;


    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

Using f.is_generator():
% time ./bin 22
arg 1: 22 == n  [degree of field (n>=2)]  default=5
  ct =1319758
./bin 22  10.79s user 0.00s system 99% cpu 10.792 total
 ==> 2^22/10.79 == 388,721 per second

Using gcd(k, mm):
% time ./bin 26
arg 1: 26 == n  [degree of field (n>=2)]  default=5
  ct =22355866
./bin 26  6.39s user 0.00s system 99% cpu 6.394 total
 ==> 2^26/6.39 == 10,502,169 per second

Using gcd and GENX:
% time ./bin 26
arg 1: 26 == n  [degree of field (n>=2)]  default=5
  ct =22355866
./bin 26  6.02s user 0.00s system 99% cpu 6.022 total
 ==> 2^26/6.02 == 11,147,651 per second

No condition (but trace==zero):
% time ./bin 26
arg 1: 26 == n  [degree of field (n>=2)]  default=5
  ct =33554431
./bin 26  0.26s user 0.00s system 99% cpu 0.258 total
 ==> 2^26/0.26 == 258,111,015 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/gf2n-trace0-generators-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/gf2n-trace0-generators-demo.cc DEMOFLAGS=-DTIMING"
/// End:
