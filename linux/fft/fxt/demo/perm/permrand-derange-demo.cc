
#include "perm/permrand-derange.h"

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


//% Random derangements (permutations with no fixed points)

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
    ulong *tr = new ulong[n];
    double *td = new double[32];  // must be == 32
    init_derange_branch_ratios(td);

//    for (ulong k=2; k<=10; ++k)  cout << k << ": " << td[k-1] << endl;

    for (ulong k=0; k<rep; ++k)
    {
        random_derangement(f, n, tr, td, true);

#ifndef TIMING
        print_perm("   f=", f, n, false);
        print_cycles("    ", f, n);
        cout << endl;
#endif  // TIMING
//        jjassert( is_valid_permutation(f, n) );
        jjassert( is_derangement(f, n) );
    }

    delete [] f;
    delete [] tr;
    delete [] td;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/permrand-derange-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/permrand-derange-demo.cc DEMOFLAGS=-DTIMING"
/// End:
