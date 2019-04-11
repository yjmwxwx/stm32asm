
#include "comb/wfl-hilbert.h"

#include "jjassert.h"
#include "fxttypes.h"
#include "fxtio.h"

//#include "jjassert.h"

//% Fred Lunnon's (second) iterative algorithm to convert linear coordinate
//% into coordinates of d-dimensional Hilbert curve (and back).


//#define TIMING // uncomment to disable printing

#include "nextarg.h"

int
main(int argc, char **argv)
{
    ulong d = 3;
    NXARG(d, "dimensions (1<=d<=5)");
    jjassert( d != 0 );
    jjassert( d <= WFL_MAXDIM );

    ulong mct = 32;
    NXARG(mct, "that many steps");

    wfl_hilbert W(d);

#ifndef TIMING
    const ulong *pt = W.get_coord();
    for (ulong ct=0; ct < mct; ++ct)
    {
        cout << setw(4) << ct << ":";
        cout << "    [";

        for (ulong j=0; j<d; ++j)
        {
            cout << " " << pt[j];
        }
        cout << " ]";
        ulong ml = W.next();
        cout << "   " << ml;
        cout << endl;
    }
#else
    for (ulong ct=0; ct < mct; ++ct)  W.next();
    if ( W.get_coord()[0]==239 )   cout << "dummy" << endl;
#endif

    cout << "ct=" << mct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 5 300000000
arg 1: 5 == d  [dimensions (2<=d<=5)]  default=3
arg 2: 300000000 == mct  [that many steps]  default=64
ct=300000000
./bin 5 300000000  7.88s user 0.00s system 99% cpu 7.887 total
==> 300000000/7.88 == 38,071,065 per second

 time ./bin 2 300000000
arg 1: 2 == d  [dimensions (2<=d<=5)]  default=3
arg 2: 300000000 == mct  [that many steps]  default=64
ct=300000000
./bin 2 300000000  8.70s user 0.00s system 99% cpu 8.700 total
==> 300000000/8.70 == 34,482,758 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/wfl-hilbert-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/wfl-hilbert-demo.cc DEMOFLAGS=-DTIMING"
/// End:
