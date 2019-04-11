
#include "comb/composition-nz-gray.h"

#include "comb/composition-nz-rank.h"

#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts.
//% Gray code with moves of only one unit, all moves are one-close or
//% two-close, two-close moves always cross a part =1 and all moves are
//% at the end, involving the last element.
//% Loopless algorithm.
//% First composition has one part for all n.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

// Cf. comb/composition-nz-gray-rec-demo.cc recursive version.
// Cf. comb/composition-nz-demo.cc for compositions in lexicographic order.
// Cf. comb/composition-nz-rl-demo.cc for compositions in run-length order
// Cf. comb/composition-nz-subset-lex-demo.cc for compositions in subset-lex order


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "compositions of n");

    composition_nz_gray P(n);

    ulong ct = 0;

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "With benchmark: whether to generate in backward order");
#ifdef COMPOSITION_NZ_GRAY_FIXARRAYS
    cout << "COMPOSITION_NZ_GRAY_FIXARRAYS defined." << endl;
#endif
    if ( !bq )
    {
        cout << "forward:" << endl;
        P.first();
        do  { ++ct; }  while ( P.next() );
    }
    else
    {
        cout << "backward:" << endl;
        P.last();
        do  { ++ct; }  while ( P.prev() );
    }

#else  // TIMING

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

//    P.last();
    ulong m = P.num_parts();
    do
    {
#if 0
        { bool q = true;
            for (ulong j=0; j<m; ++j)
                if ( P.data()[j] > 2 )  { q=false;  break; }
            if ( ! q )  continue;
        }
#endif

//        if ( m!=6 ) continue;  // with n=9, see fxtbook p.189 (enup)

        cout << setw(4) << ct << ":";

        const ulong w = composition_nz_rank( P.data(), m );
        print_bin("  ", w, (n>1 ? n-1 : 1) );  // two-close homogeneous moves
//        cout << "  " << w;  // A000000

        P.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
            cout << endl;
            cout << endl;
        }


        jjassert( P.OK() );

#if 1 // check rank and unrank
        const ulong r = P.rank();
//        print_bin("  ", r, (n>1 ? n-1 : 1) );
        jjassert( r == ct );

        ulong t = P.unrank(r);
        ulong r2 = P.rank();
//        print_bin("  r2= ", r2, (n>1 ? n-1 : 1) );
//        P.print("  ");
//        cout << endl;

        jjassert( P.OK() );
        jjassert( r2 == r );
        jjassert( m == t );
#endif

        ++ct;
    }
    while ( (m=P.next()) );
//    while ( (m=P.prev()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;  // A011782

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.0:

 time ./bin 30 0
arg 1: 30 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_GRAY_FIXARRAYS defined.
forward:
 ct=536870912
./bin 30 0  2.97s user 0.00s system 99% cpu 2.970 total
 ==> 536870912/2.97 ==180,764,616  per second

 time ./bin 30 1
arg 1: 30 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_GRAY_FIXARRAYS defined.
backward:
 ct=536870912
./bin 30 1  2.24s user 0.00s system 99% cpu 2.241 total
 ==> 536870912/2.24 == 239,674,514 per second

  time ./bin 31 0
arg 1: 31 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_GRAY_FIXARRAYS defined.
forward:
 ct=1073741824
./bin 31 0  4.64s user 0.00s system 99% cpu 4.639 total
 ==> 1073741824/4.64 == 231,409,875 per second

 time ./bin 31 1
arg 1: 31 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_GRAY_FIXARRAYS defined.
backward:
 ct=1073741824
./bin 31 1  5.92s user 0.00s system 99% cpu 5.922 total
 ==> 1073741824/5.92 == 181,375,308 per second

*/

/*
BENCHARGS=30 0
BENCHARGS=31 0
BENCHARGS=30 1
BENCHARGS=31 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

