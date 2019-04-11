
#include "bits/bit-paper-fold.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong


//% Generate the paper-folding sequence.
//% Cf. OEIS sequences A014577, A014707, A091072, and A091067.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 65;
    NXARG(n, "Number of bits generated");

#ifdef TIMING
    ulong x = 0;
    for (ulong k=1; k<=n; ++k)  x += bit_paper_fold(k);

    if ( x > (1UL<<31) )  cout << "great!" << endl;  // dummy

    cout << " ct=" << n << endl;

#else
    for (ulong k=1; k<=n; ++k)  // note: start with k==1
    {
        bool p = bit_paper_fold(k);

        cout << (p==0 ? '.' : '1' );  // dots for zeros (A014577)

//        cout << (p==0 ? '0' : '1' ) << ", ";  // OEIS sequence A014577
//        cout << (p!=0 ? '0' : '1' ) << ", ";  // A014707
//        if ( (p&1)==(k&1) )  cout << k << ", ";  // not in OEIS
//        if ( (p&1)!=(k&1) )  cout << k << ", ";  // not in OEIS
//        if ( (p&1)==(k&1) )  cout << p << ", ";  // not in OEIS
//        if ( (p&1)!=(k&1) )  cout << p << ", ";  // not in OEIS
//        if ( p!=0 )  cout << k << ", ";  // A091072
//        if ( p==0 )  cout << k << ", ";  // A091067

//        const ulong p2 = bit_paper_fold(k+1);
//        if ( p==p2 )  cout << k << ", ";  // not in OEIS
//        if ( p!=p2 )  cout << k << ", ";  // not in OEIS
//        if ( p < p2 )  cout << k << ", ";  // not in OEIS
//        if ( p > p2 )  cout << k << ", ";  // A047617, =={2, 5} mod 8.
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
./bin $(( 2**30 ))  2.44s user 0.00s system 100% cpu 2.439 total
 ==> 1073741824/2.44 == 440,058,124 per second

BENCHARGS=1073741824

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bit-paper-fold-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bit-paper-fold-demo.cc DEMOFLAGS=-DTIMING"
/// End:

