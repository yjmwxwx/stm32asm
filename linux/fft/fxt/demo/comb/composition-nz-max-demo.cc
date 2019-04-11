
#include "comb/composition-nz-max.h"
#include "comb/composition-nz-rank.h"

#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts <= mx.
//% Lexicographic order.

// Cf. comb/composition-nz-min-demo.cc for compositions into parts >= mi
// Cf. comb/composition-nz-demo.cc for all compositions
// Cf. comb/composition-nz-left-smooth-demo.cc for left-smooth compositions
// Cf. comb/composition-nz-smooth-demo.cc for smooth compositions
// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 9;
    NXARG(n, "compositions of n into parts <= mx");
    ulong mx = 2;
    NXARG(mx, "parts <= mx (mx>=1)");
    // mx==2:  ==> A000045 (Fibonacci numbers)
    // mx==3:  ==> A000073 (Tribonacci numbers)
    // mx==4:  ==> A000078 (Tetranacci numbers)
    // mx==5:  ==> A001591 (Pentanacci numbers)
    // mx==6:  ==> A001592 (Hexanacci numbers)

    composition_nz_max P(n, mx);

    ulong ct = 0;

#ifdef TIMING
#ifdef COMPOSITION_NZ_MAX_FIXARRAYS
    cout << "COMPOSITION_NZ_MAX_FIXARRAYS is defined." << endl;
#endif
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
    do
    {
#if 0
        if ( mx != P.max_part() )  continue;
        // mx = 2 ==> AA000071,  3 ==> A000100, 4 ==> A000102
        // 5 ==> A006979,  6 ==> A006980, 7 ==> A000000
        // oo ==> A045623
#endif
#if 0
        { const ulong *x = P.data();  bool q = true;
            for (ulong j=1; j<m; ++j)
//                if ( x[j]==2 && x[j-1]==1 )  { q=false; break; } // mx = 3 ==> A000045
                if ( x[j]==3 && x[j-1]==1 )  { q=false; break; } // mx = 3 ==> A116732
            if ( ! q )  continue;
        }
#endif

        ++ct;

        cout << setw(4) << ct << ":";
        cout << "  [" << setw(2) << m << "]";
//        cout << "  [" << n-m << "]";

        ulong r = composition_nz_rank( P.data(), m);
//        ulong r = composition_nz_rl_rank( P.data(), m);
        print_bin("  ", r, n);

        P.print("  ");

        cout << endl;

        jjassert( P.OK() );
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

// Worst case  mx==2:

 time ./bin 45 2
arg 1: 45 == n  [compositions of n into parts <= mx]  default=6
arg 2: 2 == mx  [parts <= mx (mx>=1)]  default=2
  ct=1836311903
./bin 45  6.31s user 0.00s system 99% cpu 6.315 total
 ==> 1836311903/6.31 == 291,016,149 per second

With COMPOSITION_NZ_MAX_FIXARRAYS defined:
 time ./bin 45 2
arg 1: 45 == n  [compositions of n into parts <= mx]  default=6
arg 2: 2 == mx  [parts <= mx (mx>=1)]  default=2
COMPOSITION_NZ_MAX_FIXARRAYS is defined.
  ct=1836311903
./bin 45  5.17s user 0.00s system 99% cpu 5.173 total
 ==> 1836311903/5.17 == 355,186,054 per second


// Best case mx==n:

 time ./bin 32 32
arg 1: 32 == n  [compositions of n into parts <= mx]  default=6
arg 2: 32 == mx  [parts <= mx (mx>=1)]  default=2
  ct=2147483648
./bin 32 32  5.35s user 0.00s system 99% cpu 5.354 total
 ==> 2147483648/5.35 == 401,398,812 per second

 time ./bin 32 32
arg 1: 32 == n  [compositions of n into parts <= mx]  default=6
arg 2: 32 == mx  [parts <= mx (mx>=1)]  default=2
COMPOSITION_NZ_MAX_FIXARRAYS is defined.
  ct=2147483648
./bin 32 32  5.00s user 0.00s system 99% cpu 4.998 total
 ==> 2147483648/5.00 == 429,496,729 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-max-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-max-demo.cc DEMOFLAGS=-DTIMING"
/// End:

