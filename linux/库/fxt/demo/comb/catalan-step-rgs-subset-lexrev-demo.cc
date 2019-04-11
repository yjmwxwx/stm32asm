
#include "comb/catalan-step-rgs-subset-lexrev.h"
#include "comb/is-catalan-step-rgs.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Catalan (step-)RGS for lattice paths from (0,0) to (n,n)
//% that do not go below the diagonal (k, k) for 0 <= k <= n.
//% Subset-lexrev order.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Catalan (step-)RGS for paths from (0,0) to (n,n)");

    catalan_step_rgs_subset_lexrev C(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef CATALAN_STEP_RGS_SUBSET_LEXREV_FIXARRAYS
    cout << "CATALAN_STEP_RGS_SUBSET_LEXREV_FIXARRAYS is defined." << endl;
#endif

    do  { ++ct; }  while ( C.next() );
#else

    bool pq = 0;
    NXARG(pq, "Whether do draw path (as ASCII art)");

    ulong j = (n ? n-1 : 0);  // position of *rightmost* change
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

        C.print("  ", true);
        cout << "  " << j;
//        cout << "  " << C.tr_;
        cout << endl;

        if ( pq )
        {
            C.print_aa();
            cout << endl;
        }

        jjassert( C.OK() );
    }
    while ( (j=C.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 19
arg 1: 19 == n  [Catalan (step-)RGS for paths from (0,0) to (n,n)]  default=5
 ct=1767263190
./bin 19  7.07s user 0.00s system 99% cpu 7.072 total
 ==> 1767263190/7.07 == 249,966,504 per second


GCC 4.8.0:

 time ./bin 19
arg 1: 19 == n  [Catalan (step-)RGS for paths from (0,0) to (n,n)]  default=5
 ct=1767263190
./bin 19  6.80s user 0.00s system 99% cpu 6.809 total
 ==> 1767263190/6.80 == 259,891,645 per second

 time ./bin 19
arg 1: 19 == n  [Catalan (step-)RGS for paths from (0,0) to (n,n)]  default=5
CATALAN_STEP_RGS_SUBSET_LEXREV_FIXARRAYS is defined.
 ct=1767263190
./bin 19  5.66s user 0.00s system 99% cpu 5.657 total
 ==> 1767263190/5.66 == 312,237,312 per second

*/

/*
BENCHARGS=19
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-step-rgs-subset-lexrev-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-step-rgs-subset-lexrev-demo.cc DEMOFLAGS=-DTIMING"
/// End:

