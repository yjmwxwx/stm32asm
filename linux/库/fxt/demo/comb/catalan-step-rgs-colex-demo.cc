
#include "comb/catalan-step-rgs-colex.h"
#include "comb/is-catalan-step-rgs.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Catalan (step-)RGS for lattice paths from (0,0) to (n,n)
//% that do not go below the diagonal (k, k) for 0 <= k <= n.
//% Co-lexicographic order.
//% Cf. OEIS sequence A000108.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Catalan (step-)RGS for paths from (0,0) to (n,n)");

    catalan_step_rgs_colex C(n);

    ulong ct = 0;

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "With benchmark: whether do generate in backward order");
    if ( !bq )
    {
        cout << "forward:" << endl;
        C.first();
        do  { ++ct; }  while ( C.next() );
    }
    else
    {
        cout << "backward:" << endl;
        C.last();
        do  { ++ct; }  while ( C.prev() );
    }
#else

    bool pq = 0;
    NXARG(pq, "Whether do draw path (as ASCII art)");

//    C.last();
    ulong j = ( n ? n-1 : 0);  // position of first nonzero digit
    do
    {
        ++ct;

        cout << setw(4) << ct << ":";
        C.print("  ", true);
        cout << "  " << j;
        cout << endl;

        if ( pq )
        {
            C.print_aa();
            cout << endl;
        }

        jjassert( C.OK() );
    }
    while ( (j=C.next()) );
//    while ( (j=C.prev()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 19 0
arg 1: 19 == n  [Catalan (step-)RGS for paths from (0,0) to (n,n)]  default=5
arg 2: 0 == bq  [With benchmark: whether do generate in backward order]  default=0
forward:
 ct=1767263190
./bin 19 0  5.42s user 0.00s system 99% cpu 5.426 total
 ==> 1767263190/5.42 == 326,063,319 per second

 time ./bin 19 1
arg 1: 19 == n  [Catalan (step-)RGS for paths from (0,0) to (n,n)]  default=5
arg 2: 1 == bq  [With benchmark: whether do generate in backward order]  default=0
backward:
 ct=1767263190
./bin 19 1  4.95s user 0.00s system 99% cpu 4.952 total
 ==> 1767263190/4.95 == 357,022,866 per second

*/

/*
BENCHARGS=19
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-step-rgs-colex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-step-rgs-colex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

