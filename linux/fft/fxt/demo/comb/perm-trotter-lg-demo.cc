
#include "comb/perm-trotter-lg.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Generate all permutations in strong minimal-change order using Trotter's algorithm.
//% Largest element moves most often.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements.");
    bool bq = 0;
    NXARG(bq, "Whether to go backwards.");


    perm_trotter_lg P(n);
    if ( bq )  P.last();

    ulong ct = 0;

#ifdef TIMING
    if ( !bq )
    {
        cout << "forward:" << endl;
        do { ++ct; } while ( P.next() );
    }
    else
    {
        cout << "backward:" << endl;
        do { ++ct; } while ( P.prev() );
    }

#else  // TIMING

    const bool dfz = true;  // whether to print dots for zeros
    do
    {
        cout << setw(4) << ct << ":";
        ++ct;

        P.print("    ", dfz);

        ulong sw1, sw2;
        P.get_swap(sw1, sw2);
        cout << "    (" << sw1 << ", " << sw2 << ") ";

        P.print_inv("    ", dfz);

        // print directions:
        cout << "    ";
        for (ulong j=0; j<n; ++j)  cout << " " << (P.d_[j]==1?'+':'-');

        cout << endl;
    }
    while ( (!bq ? P.next() : P.prev()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

%  time ./bin 12
arg 1: 12 == n  [Permutations of n elements.]  default=4
arg 2: 0 == bq  [Whether to go backwards.]  default=0
  ct=479001600
./bin 12  3.27s user 0.00s system 99% cpu 3.275 total
 ==> 12!/3.27 == 146,483,669 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12 0
arg 1: 12 == n  [Permutations of n elements.]  default=4
arg 2: 0 == bq  [Whether to go backwards.]  default=0
forward:
 ct=479001600
./bin 12 0  2.34s user 0.00s system 99% cpu 2.339 total
 ==> 12!/2.34 == 204,701,538 per second

 time ./bin 12 1
arg 1: 12 == n  [Permutations of n elements.]  default=4
arg 2: 1 == bq  [Whether to go backwards.]  default=0
backward:
 ct=479001600
./bin 12 1  2.17s user 0.00s system 99% cpu 2.172 total
 ==> 12!/2.17 == 220,738,064 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-trotter-lg-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-trotter-lg-demo.cc DEMOFLAGS=-DTIMING"
/// End:

