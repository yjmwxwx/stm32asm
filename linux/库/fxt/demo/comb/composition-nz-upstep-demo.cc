
#include "comb/composition-nz-upstep.h"

//#include "comb/composition-nz-rank.h"
//#include "comb/composition-nz-conj.h"
#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "comb/is-unimodal.h"
#include "comb/is-smooth.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts, with limit on up-step.
//% Lexicographic order.
//% Cf. OEIS sequences A003116 (max up-step 1)
//% and A224959 (max up-step 2).
//% Max up-step 0 gives partitions as weakly descending lists.


// Cf. comb/composition-nz-demo.cc for all compositions
// Cf. comb/partition-desc-demo.cc for (all) partitions

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "compositions of n");

    ulong u = 1;
    NXARG(u, "maximal up-step");

    bool aa = 0;
    NXARG(aa, "whether to render as ASCII art");

    composition_nz_upstep P(n, u);

    ulong ct = 0;

#ifdef TIMING
//    bool bq = 0;
//    NXARG(bq, "With benchmark: whether to generate in backward order");
//#ifdef COMPOSITION_NZ_FIXARRAYS
//    cout << "COMPOSITION_NZ_FIXARRAYS defined." << endl;
//#endif
//    if ( !bq )
//    {
//        cout << "forward:" << endl;
        P.first();
        do  { ++ct; }  while ( P.next() );
//    }
//    else
//    {
//        cout << "backward:" << endl;
//        P.last();
//        do  { ++ct; }  while ( P.prev() );
//    }

#else  // TIMING

    ulong m = P.num_parts();
    do
    {
        cout << setw(4) << ct << ":";
//        cout << "[" << setw(2) << ct << "]";

        cout << "  [" << setw(2) << m << "]";


//        cout << "[" << n-m << "]  ";  // OEIS sequence A000120
//        cout << " [" << setw(2) << P.last_part() << "] ";  // A001511
        P.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
            cout << endl;
            cout << endl;
        }

        ++ct;

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

 time ./bin 110 0  ## worst case: partitions
arg 1: 110 == n  [compositions of n]  default=7
arg 2: 0 == u  [maximal up-step]  default=1
arg 3: 0 == aa  [Whether to render as ASCII art]  default=0
 ct=607163746
./bin 110 0  9.18s user 0.00s system 99% cpu 9.186 total
 ==> 607163746/9.18 == 66,139,841 per second

 time ./bin 40 1
arg 1: 40 == n  [compositions of n]  default=7
arg 2: 1 == u  [maximal up-step]  default=1
arg 3: 0 == aa  [Whether to render as ASCII art]  default=0
 ct=3479231178
./bin 40 1  12.52s user 0.00s system 99% cpu 12.526 total
 ==> 3479231178/12.52 == 277,893,864 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-upstep-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-upstep-demo.cc DEMOFLAGS=-DTIMING"
/// End:

