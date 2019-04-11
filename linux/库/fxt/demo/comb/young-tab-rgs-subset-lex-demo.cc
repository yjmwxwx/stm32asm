
#include "comb/young-tab-rgs-subset-lex.h"
// demo-include "comb/print-young-tab-rgs-aa.cc"

//#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Restricted growth strings (RGS) for standard Young tableaux:
//% the k-th occurrence of a digit d in the RGS must precede
//% the k-th occurrence of the digit d+1.
//% Subset-lex order.
//% Cf. OEIS sequences A000085 (all tableaux),
//% A061343 (all shifted tableaux; using condition is_shifted(1)),
//% A210736 (shifted, height <= 2), A082395 (shifted, height <= 3).

// Cf. comb/young-tab-rgs-demo.cc for lexicographic order

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Length of strings");
//    ulong m = 0;
//    NXARG(m, "Number of allowed values for digits\n"
//          "         == max height of tableaux, 0 ==> all");
//    if ( m>n )  m = n;
//    if ( m==0 )  m = n;

    young_tab_rgs_subset_lex Y(n);

    ulong ct = 0;


#ifdef TIMING

    Y.first();
    do  { ++ct; }  while ( Y.next() );

#else // TIMING

    bool tq = 0;
    NXARG(tq, "Whether do draw tableaux (as ASCII art)");

    ulong j = 0;
    do
    {
#if 0  // impose certain conditions
//        if ( Y.height() != 4 )  continue;
//        if ( ! Y.is_falling(1) )  continue; // A218293
//        if ( ! Y.is_falling(2) )  continue; // A225121
//        if ( ! Y.is_falling(3) )  continue; // A000000
//        if ( ! Y.is_delayed(1) )  continue; // A000000

//        if ( ! Y.is_shifted(1) )  continue; // A061343
        if ( ! Y.is_shifted(2) )  continue; // A000000
        // 1, 1, 1, 1, 3, 4, 10, 15, 35, 98, 226, 606, 1760, 4523, ...

//        const ulong st[] = { 4, 2, 1 };
//        ulong hh = sizeof(st)/sizeof(st[0]);
////        cout << " :: hh=" << hh << endl;
//        if ( ! Y.has_shape(st, hh) )  continue;

#endif

        ++ct;

#if 1
        cout << setw(4) << ct << ":  ";

        Y.print("  ");  // RGS
        cout << setw(3) << j << " ";  // leftmost change

        Y.print_stats("    ");  // stats: partition of n
        cout << setw(3) << Y.height();  // height

#if 0  // list positions of first occurrence of digits:
        ulong h = Y.height();
        cout << "   [ ";
        for (ulong d=0; d<h; ++d)
        {
            ulong p = 0;
            while ( Y.a_[p] != d )  ++p;
            cout << p << " ";
        }
        cout << "]";
#endif

        if ( tq )
        {
            cout << endl;
            Y.print_aa( 1 );  // arg is offset (0 or 1)
            cout << endl;
        }


        cout << endl;

        jjassert( Y.OK() );
#endif
    }
    while ( (j=Y.next()) );


#endif  // TIMING

    cout << " ct=" << ct;
    cout << endl;

    return 0;
}
// -------------------------

/*
Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)

GCC 4.9.2:

 time ./bin 18
arg 1: 18 == n  [Length of strings]  default=6
 ct=997313824
./bin 18  8.45s user 0.00s system 99% cpu 8.464 total
 ==> 997313824/8.45 == 118,025,304 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.8.0:

 time ./bin 18
arg 1: 18 == n  [Length of strings]  default=6
 ct=997313824
./bin 18  17.15s user 0.00s system 99% cpu 17.150 total
 ==> 997313824/17.15 == 58,152,409 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/young-tab-rgs-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/young-tab-rgs-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

