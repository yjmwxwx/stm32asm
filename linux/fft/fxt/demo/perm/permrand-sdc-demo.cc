
#include "perm/permrand-sdc.h"
#include "perm/perm2ccf.h"
// demo-include "perm/perm2ccf.cc"

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

#include <cstdlib>  // strtoul()


//% Random permutations with prescribed Sets into Distinct Cycles

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of elements.");
    ulong rep = 15;
    NXARG(rep, "This many permutations.");
    rseed(4);


//    cout << " RAND_MAX=" << RAND_MAX << endl;

    ulong *f = new ulong[n];
    ulong *c = new ulong[n];

    ulong *tmp = new ulong[n];
    bitarray B(n);


    RESTARGS("Supply at least on number >=1");
    ulong cn;
    { ulong k;
        for (k=3;  k<(ulong)argc; ++k)  c[k-3] = strtoul(argv[k], 0, 10);
        cn = k - 3;
    }

    if ( cn==0 )
    {
        cn = 1;
        c[0] = 2;
    }

    cout << " cn=" << cn << endl;

    for (ulong k=0; k<rep; ++k)
    {
        random_sdc_permutation(f, n, c, cn, tmp);

#ifndef TIMING
        print_perm("   f=", f, n, false);
//        print_cycles("    ", f, n);

        print_ccf("   ", f, n, &B);

        cout << endl;
#endif  // TIMING
//        jjassert( is_valid_permutation(f, n) );
    }

    delete [] f;
    delete [] c;
    delete [] tmp;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/permrand-sdc-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/permrand-sdc-demo.cc DEMOFLAGS=-DTIMING"
/// End:
