
#include "comb/composition-nz-gray2.h"

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
//% Same as class composition_nz_gray for odd n, reversed list for even.
//% First composition has one part for n odd, and two parts for n even.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

// Cf. comb/composition-nz-gray-demo.cc version always starting with one part.
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

    composition_nz_gray2 P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef COMPOSITION_NZ_GRAY2_FIXARRAYS
    cout << "COMPOSITION_NZ_GRAY2_FIXARRAYS defined." << endl;
#endif
    P.first();
    do  { ++ct; }  while ( P.next() );
#else  // TIMING

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    ulong m = P.num_parts();
    do
    {
//        if ( m!=6 ) continue;  // with n=9, see fxtbook p.189 (enup)

        cout << setw(4) << ct << ":";

        const ulong w = composition_nz_rank( P.data(), m );
        print_bin("  ", w, (n>1 ? n-1 : 1) );  // two-close homogeneous moves

        P.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
            cout << endl;
            cout << endl;
        }


        jjassert( P.OK() );

#if 0 // check rank and unrank
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
#endif  // TIMING

    cout << " ct=" << ct << endl;  // A011782

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.0:

 time ./bin 31
arg 1: 31 == n  [compositions of n]  default=7
 ct=1073741824
./bin 31  6.81s user 0.00s system 99% cpu 6.820 total
 ==> 1073741824/6.81 == 157,671,339 per second

 time ./bin 31
arg 1: 31 == n  [compositions of n]  default=7
COMPOSITION_NZ_GRAY2_FIXARRAYS defined.
 ct=1073741824
./bin 31  3.83s user 0.00s system 99% cpu 3.829 total
 ==> 1073741824/3.83 == 280,350,345 per second

*/

/*
BENCHARGS=31
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-gray2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-gray2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

