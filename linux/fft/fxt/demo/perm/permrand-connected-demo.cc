
#include "perm/permrand-connected.h"

#include "perm/printcycles.h"
#include "aux0/randf.h"  // rseed()

//#include "aux0/rand-idx.h"
//#include "perm/permrand.h"

#include "perm/permq.h"
#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"
#include "nextarg.h"


//% Random connected (indecomposable) permutations

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "Number of elements.");
    ulong rep = 15;
    NXARG(rep, "This many derangements.");
    rseed(4);

//    cout << " RAND_MAX=" << RAND_MAX << endl;

    ulong *f = new ulong[n];

    for (ulong k=0; k<rep; ++k)
    {
        random_connected_permutation(f, n);

#ifndef TIMING
        print_perm("   f=", f, n, false);
        print_cycles("    ", f, n);
        cout << endl;
#endif  // TIMING
//        jjassert( is_valid_permutation(f, n) );
        jjassert( is_connected(f, n) );
    }

    delete [] f;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/permrand-connected-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/permrand-connected-demo.cc DEMOFLAGS=-DTIMING"
/// End:
