
#include "comb/score-sequence.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Score sequences: weakly increasing sequences a[0,1,...,n-1] where
//% sum(j=0..k, a[j]) >= k*(k+1)/2 and sum(j=0..n-1, a[j]) = (n-1)*n/2.
//% Lexicographic order.
//% See OEIS sequence A000571.


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Length of sequences");

    score_sequence S(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef SCORE_SEQUENCE_FIXARRAYS
    cout << "SCORE_SEQUENCE_FIXARRAYS is defined" << endl;
#endif
    S.first();
    do  { ++ct; }  while ( S.next() );
#else  // TIMING

    ulong j = 0;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

        print_vec("  ", S.data(), n, true );
//        print_vec("    ", S.s_+1, n, true );
//        print_vec("    ", S.t_+1, n, true );

        cout << setw(4) << j;

        cout << endl;

        jjassert( S.OK() );
    }
    while ( (j=S.next()) );

#endif  // TIMING

    cout << " ct=" << ct;  // A000571
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.8.0:

 time ./bin 20
arg 1: 20 == n  [Length of sequences]  default=5
 ct=259451116
./bin 20  5.12s user 0.00s system 99% cpu 5.121 total
 ==> 259451116/5.12 == 50,674,046 per second

 time ./bin 20
arg 1: 20 == n  [Length of sequences]  default=5
SCORE_SEQUENCE_FIXARRAYS is defined
 ct=259451116
./bin 20  5.08s user 0.00s system 99% cpu 5.089 total
 ==> 259451116/5.08 == 51,073,054 per second
*/


/*
Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)

GCC 4.9.2:

 time ./bin 20
arg 1: 20 == n  [Length of sequences]  default=7
SCORE_SEQUENCE_FIXARRAYS is defined
 ct=259451116
./bin 20  2.84s user 0.00s system 99% cpu 2.847 total
  ==> 259451116/2.84 == 91,356,026 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/score-sequence-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/score-sequence-demo.cc DEMOFLAGS=-DTIMING"
/// End:

