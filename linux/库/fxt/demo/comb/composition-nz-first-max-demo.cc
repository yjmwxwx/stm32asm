
#include "comb/composition-nz-first-max.h"

//#include "comb/comb-print.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts where no part is greater than the first.
//% Lexicographic order.
//% See OEIS sequencs A079500 and A007059.

// Cf. comb/balanced-ordered-tree-lev-seq-demo.cc for balanced trees
// Cf. comb/composition-nz-demo.cc for all compositions

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "compositions of n");

#ifndef TIMING

    bool tq = 0;
    NXARG(tq, "Whether to print level sequences for corresponding (balanced) trees");


    bool aa = 0;
//    NXARG(aa, "Whether to render as ASCII art");
#endif

    composition_nz_first_max P(n);

    ulong ct = 0;

#ifdef TIMING
//    bool bq = 0;
//    NXARG(bq, "With benchmark: whether to generate in backward order");
#ifdef COMPOSITION_NZ_FIRST_MAX_FIXARRAYS
    cout << "COMPOSITION_NZ_FIRST_MAX_FIXARRAYS defined." << endl;
#endif
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

#if 1  // allow/suppress printing


        cout << setw(4) << ct << ":";

        if ( tq )  P.print_tree_lev_seq("  ");

        P.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
            cout << endl;
            cout << endl;
        }

        jjassert( P.OK() );

#endif  // allow/suppress printing

        ++ct;
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;  // A079500

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.1:

% time ./bin 35 0
arg 1: 35 == n  [compositions of n]  default=8
 ct=1394632365
./bin 35 0  5.98s user 0.00s system 99% cpu 5.985 total
 ==> 1394632365/5.98 == 233,216,114 per second


With COMPOSITION_NZ_FIRST_MAX_FIXARRAYS defined:

% time ./bin 35 0
arg 1: 35 == n  [compositions of n]  default=8
COMPOSITION_NZ_FIRST_MAX_FIXARRAYS defined.
 ct=1394632365
./bin 35 0  5.97s user 0.00s system 99% cpu 5.980 total


*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-first-max-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-first-max-demo.cc DEMOFLAGS=-DTIMING"
/// End:

