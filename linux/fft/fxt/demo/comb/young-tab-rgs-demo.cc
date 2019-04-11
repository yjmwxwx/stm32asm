
#include "comb/young-tab-rgs.h"
// demo-include "comb/print-young-tab-rgs-aa.cc"
// demo-include "comb/is-shifted-young-tab-rgs.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Restricted growth strings (RGS) for standard Young tableaux:
//% the k-th occurrence of a digit d in the RGS must precede
//% the k-th occurrence of the digit d+1.
//% Lexicographic order.
//% The strings are also called ballot sequences.
//% Cf. OEIS sequences A000085 (all tableaux),
//%   A001405 (tableaux with height <= 2, central binomial coefficients)
//%   A001006 (tableaux with height <= 3, Motzkin numbers)
//%   A005817 (height <= 4),  A049401 (height <= 5),  A007579 (height <= 6)
//%   A007578 (height <= 7),  A007580 (height <= 8),  A212915 (height <= 9),
//%   A212916 (height <= 10).
//%   A001189 (height <= n-1),
//%   A014495 (height = 2),  A217323 (height = 3),  A217324 (height = 4),
//%   A217325 (height = 5),  A217326 (height = 6),  A217327 (height = 7),
//%   A217328 (height = 8).
//% Cf. A182172 (tableaux of n cells and height <= k).
//% Cf. OEIS sequences A061343 (all shifted tableaux; using condition is_shifted(1)),
//%   A210736 (shifted, height <= 2), A082395 (shifted, height <= 3).
//% Cf. OEIS sequences A161125 (descent numbers), A225617 (strict inversions),
//%   and A225618 (weak inversions).


// Cf. comb/young-tab-rgs-subset-lex-demo.cc for subset-lex order

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Length of strings");
    ulong m = 0;
    NXARG(m, "Number of allowed values for digits\n"
          "         == max height of tableaux, 0 ==> all");
    if ( m>n )  m = n;
    if ( m==0 )  m = n;

    young_tab_rgs Y(n, m);

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

        if ( ! Y.is_shifted(1) )  continue; // A061343
//        if ( ! Y.is_shifted(2) )  continue; // A000000
        // 1, 1, 1, 1, 3, 4, 10, 15, 35, 98, 226, 606, 1760, 4523, ...

//        const ulong st[] = { 4, 2, 1 };
//        ulong hh = sizeof(st)/sizeof(st[0]);
////        cout << " :: hh=" << hh << endl;
//        if ( ! Y.has_shape(st, hh) )  continue;

#endif
#if 0   // strict tableaux: A061343 (same as Y.is_shifted(1) )
        // cf. A003121:  ./bin 10 . 1 | g -F '    [ 4 3 2 1 '
        if ( ! Y.is_strict() )  continue;
#endif
#if 0   // no succession v, v+1 in a row:  A237770
        { const ulong *x = Y.data();
            bool q = true;
            for (ulong k=1; k<n; ++k)
                if ( x[k] == x[k-1] )  { q=0;  break; }
            if ( !q )  continue;
        }
#endif
#if 0   // chess tableaux:  A238014
        if ( ! Y.is_chess_tableau() )  continue;
#endif

        ++ct;

#if 1  // whether to print anything
        cout << setw(4) << ct << ":  ";

        Y.print("  ");  // RGS, starting with cell 0
//        Y.print1("  ");  // RGS, starting with cell 1
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
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 18
arg 1: 18 == n  [Length of strings]  default=5
arg 2: 0 == m  [Number of allowed values for digits
         == max height of tableaux, 0 ==> all]  default=0
 ct=997313824
./bin 18  10.14s user 0.00s system 99% cpu 10.147 total
 ==> 997313824/10.14 == 98,354,420 per second


 time ./bin 19 5
arg 1: 19 == n  [Length of strings]  default=5
arg 2: 5 == m  [Number of allowed values for digits
         == max height of tableaux, 0 ==> all]  default=0
 ct=1212962072
./bin 19 5  11.00s user 0.00s system 99% cpu 11.000 total
 ==> 1212962072/11.00 == 110,269,279 per second


 time ./bin 32 2
arg 1: 32 == n  [Length of strings]  default=5
arg 2: 2 == m  [Number of allowed values for digits
         == max height of tableaux, 0 ==> all]  default=0
 ct=601080390
./bin 32 2  6.16s user 0.00s system 99% cpu 6.159 total
 ==> 601080390/6.16 == 97,577,985 per second


GCC 4.8.0:

 time ./bin 18
arg 1: 18 == n  [Length of strings]  default=6
arg 2: 0 == m  [Number of allowed values for digits
         == max height of tableaux, 0 ==> all]  default=0
 ct=997313824
./bin 18  10.70s user 0.00s system 99% cpu 10.701 total
 ==> 997313824/10.70 == 93,206,899 per second

*/

/*
BENCHARGS=18
BENCHARGS=19 5
BENCHARGS=32 2
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/young-tab-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/young-tab-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

