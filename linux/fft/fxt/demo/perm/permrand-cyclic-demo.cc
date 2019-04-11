
#include "perm/permrand-cyclic.h"
#include "perm/printcycles.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "aux0/swap.h"
#include "fxttypes.h"

#include "perm/permq.h"  // is_cyclic(), ...
#include "jjassert.h"

#include "nextarg.h"  // NXARG()

//% Random cyclic permutations.

//#define TIMING  // uncomment to disable printing

#ifdef TIMING
void visit(const ulong *f, ulong n, ulong)
{
    jjassert( is_cyclic(f, n) );
}
#else  // TIMING
void visit(const ulong *f, ulong n, ulong ct)
{
    cout << setw(4) << ct << ":";
//    for (ulong i=0; i<n; ++i)  cout << " " << f[i];
    print_perm("    ", f, n);

    cout << "    ";
    print_cycle(f, 0);

//    if ( is_connected(f, n) )  cout << "  Ind";  // always true
//    if ( is_updown_permutation(f, n) )  cout << "  UpD";
//    if ( is_derangement(f, n) )  cout << "  Der";  // always true
//    if ( is_cyclic(f, n) )  cout << "  Cyc";
    cout << endl;
}
// -------------------------
#endif  // TIMING



int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Permutations of n>0 elements");

    ulong c = 20;
    NXARG(c, "Number of permutations");

    ulong *f = new ulong[n];
//    ulong *fc = new ulong[n-1];
    for (ulong k=0; k<c; ++k)
    {
        random_cyclic_permutation(f, n);
        visit(f, n, k);

//        fact2perm(f, n, fc);
//        cout << " [ ";
//        for (ulong i=0; i<n-1; ++i)  cout << " " << fc[i];
//        cout << " ]" << endl;
    }

    delete [] f;
//    delete [] fc;

    return 0;
}
// -------------------------

/*
check whether unbiased:
 for n in $(seq 2 5); do ./bin $n 100000 | cut -d: -f2| sort | uniq -c | sort ; done;
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/permrand-cyclic-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/permrand-cyclic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

