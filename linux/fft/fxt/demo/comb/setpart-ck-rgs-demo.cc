
#include "comb/setpart-ck-rgs.h"

#include "comb/is-setpart-rgs.h"
#include "comb/comb-print.h"

//#include "comb/is-catalan-rgs.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% Restricted growth strings (RGS) for set partitions:
//% each digit is either a fixed point or a digit from the prefix.
//% Equivalently: rooted trees of height <= 2.

// Cf. comb/setpart-rgs-lex-demo.cc for the "usual" RGS for set partitions
// Cf. comb/setpart-p-rgs-lex-demo.cc for the "usual" RGS for set partitions into p parts
// Cf. comb/setpart-zero-map-rgs-demo.cc for RGS using certain maps

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "RGS of length n");

    setpart_ck_rgs P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef SETPART_CK_RGS_NZ
    cout << "SETPART_CK_RGS_NZ is defined." << endl;
#endif
    do  { ++ct; }  while ( P.next() );
#else

    ulong *y = new ulong[n];
    do
    {
//        if ( ! is_setpart_rgs(P.data(), n) )  continue;  // A026898

        ++ct;
        cout << setw(3) << ct << ":";

        P.print("    ", true);  // RGS

#if 1
        P.make_setpart_rgs(y);  // "usual" RGS for set partitions
        print_vec("    ", y, n, true);
        jjassert( is_setpart_rgs(y, n) );
//        print_setpart("    ", y, n, 0);
//        cout << "  " << is_catalan_rgs(y, n);
#endif

        cout << endl;

        jjassert( P.OK() );
    }
    while ( (P.next()) );

    delete [] y;

#endif  // TIMING

    cout << " ct=" << ct << endl;  // A000110

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 15
arg 1: 15 == n  [RGS of length n]  default=5
  ct=1382958545
./bin 15  11.06s user 0.00s system 99% cpu 11.063 total
 ==> 1382958545/11.06 == 125,041,459 per second


With SETPART_CK_RGS_NZ defined:

 time ./bin 15
arg 1: 15 == n  [RGS of length n]  default=5
SETPART_CK_RGS_NZ is defined.
  ct=1382958545
./bin 15  8.05s user 0.00s system 99% cpu 8.050 total
 ==> 1382958545/8.05 == 171,796,092 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/setpart-ck-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/setpart-ck-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

