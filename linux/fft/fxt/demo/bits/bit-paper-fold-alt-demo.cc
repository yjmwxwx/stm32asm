
#include "bits/bit-paper-fold.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "jjassert.h"


//% Generate the alternate paper-folding sequence.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 65;
    NXARG(n, "Number of bits generated");

#ifdef TIMING
    ulong x = 0;
    for (ulong k=1; k<=n; ++k)  x += bit_paper_fold_alt(k);

    if ( x > (1UL<<31) )  cout << "great!" << endl;  // dummy

    cout << " ct=" << n << endl;

#else
    ulong dir = 0;
    for (ulong k=1; k<=n; ++k)  // note start with k==1
    {
        bool p = bit_paper_fold_alt(k);
        cout << (p==0 ? '.' : '1' );  // OEIS sequence A106665, dots for zeros
//        cout << (p==0 ? '0' : '1' ) << ", ";  // A106665

        dir += (p ? +1UL : -1UL );   dir &= 3;    // modulo 4
        ulong t = bit_paper_fold_alt_rot(k);
//        cout << "[" << dir << "," << t << "]";
//        cout << "[" << dir << "]";
//        cout << dir << ",";
        jjassert( t == dir );
    }
    cout << endl;
#endif

    return 0;
}
// -------------------------

/*
Timing:

% time ./bin $(( 2**30 ))
arg 1: 1073741824 == n  [Number of bits generated]  default=65
./bin $(( 2**30 ))  2.60s user 0.00s system 100% cpu 2.605 total
 ==> 1073741824/2.60 == 412,977,624 per second

BENCHARGS=1073741824
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bit-paper-fold-alt-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bit-paper-fold-alt-demo.cc DEMOFLAGS=-DTIMING"
/// End:

