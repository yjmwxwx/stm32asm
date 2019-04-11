
#include "comb/setpart-zero-map-rgs.h"
#include "comb/is-zero-map-rgs.h"
#include "comb/print-zero-map-rgs.h"

#include "comb/comb-print.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% Restricted growth strings (RGS) for set partitions:
//%   each digit a[k] is either zero or a[k] < k and a[a[k]] == 0.
//% Same as: maps from {1, 2, 3, ..., n} to {0, 1, 2, 3, ..., n}
//%   such that f(x) < x and f(f(x)) == 0.
//% Cf. OEIS sequence A000110.

// Cf. comb/setpart-s-zero-map-rgs-demo.cc for set partitions into parts <= s+1
// Cf. comb/setpart-rgs-lex-demo.cc for the "usual" RGS for set partitions
// Cf. comb/setpart-p-rgs-lex-demo.cc for the "usual" RGS for set partitions into p parts
// Cf. comb/setpart-ck-rgs-demo.cc for the Cooper-Kennedy RGS

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "RGS of length n");

    setpart_zero_map_rgs P(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else

    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

        P.print("    ", true);
        P.print_fp_rgs("    ", true, true);
        P.print_setpart("    ", false);

        cout << endl;

        jjassert( P.OK() );
//        jjassert( is_zero_map_rgs(P.data(), n) );
    }
    while ( (P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;  // A000110

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 15
arg 1: 15 == n  [RGS of length n]  default=4
  ct=1382958545
./bin 15  6.33s user 0.00s system 99% cpu 6.338 total
 ==> 1382958545/6.33 == 218,476,863 per second


// using the "slight optimization" in next():
 time ./bin 15
arg 1: 15 == n  [RGS of length n]  default=5
  ct=1382958545
./bin 15  5.99s user 0.00s system 99% cpu 5.988 total
 ==> 1382958545/5.99 == 230,877,887 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/setpart-zero-map-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/setpart-zero-map-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

