
#include "bpol/gf2n.h"

#include "bits/print-bin.h"
#include "jjassert.h"
#include "fxttypes.h"  // ulong

#include "nextarg.h"


//% Solving the reduced quadratic equation z^2+z==C  over GF(2**n).

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "The n in GF(2^n)");

    GF2n::init(n);


    GF2n::print_info();
    cout  << endl;

//    ulong pn = n;
    GF2n f(1);
    GF2n g( GF2n::g_ );

#ifdef TIMING

    GF2n s;
    do
    {
        // solve  z*z+z = f:
        gf2n_solve_reduced_quadratic(f, s);
        f *= g;
    }
    while ( f!=1 );
    cout << "dummy=" << (s) << endl;
    cout << " ct=" << (1UL<<n) << endl;

#else

    cout << "   k:   f:=g**k  Tr(f)   RootOf(z^2+z=f)" << endl;
    ulong k = 0;
    do
    {
        ulong t = f.trace();

//        print_bin("    ",k,pn);
        cout << setw(4) << k;
        cout << ":";
        cout << "    " << f;
        cout << "    " << t;
        cout << "    ";

        // solve  z*z+z = f:
        GF2n s, s2s;
        bool qq = gf2n_solve_reduced_quadratic(f, s);
        if ( qq )
        {
            cout << "  " << s;
//            cout << "  t= " << s.trace();
            s2s = s.sqr() + s;
//            cout << "  s2s=" << s2s;
            ulong chk = (s2s - f).v_;
//            cout << "  chk=" << chk;
            jjassert( (1==t) || (0==chk) );

            s += GF2n::one;
            s2s = s.sqr() + s;
            chk = (s2s - f).v_;
//            cout << "  chk=" << chk;
            jjassert( (1==t) || (0==chk) );
        }


        cout << endl;

        f *= g;
        ++k;
    }
    while ( f!=1 );
#endif

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 22
arg 1: 22 == n  [The n in GF(2^n)]  default=5
  c = 1....................11 == x^22 + x + 1  (polynomial modulus)
dummy=.1..1.1..11..11111....
./bin 22  9.64s user 0.00s system 100% cpu 9.644 total
 ==> 2^22/9.64 == 435,093 per second
*/

/*
BENCHARGS=22
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/gf2n-solvequadratic-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/gf2n-solvequadratic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

