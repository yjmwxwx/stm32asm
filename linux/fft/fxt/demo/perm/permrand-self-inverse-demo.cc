
#include "perm/permrand-self-inverse.h"
#include "perm/printcycles.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "aux0/swap.h"
#include "fxttypes.h"

#include "perm/permq.h"  // is_cyclic(), ...
#include "jjassert.h"

#include "nextarg.h"  // NXARG()

//% Random involutions (self-inverse permutations).


//#define TIMING  // uncomment to disable printing

void visit(const ulong *f, ulong n, ulong ct)
// What to do with valid permutations.
// Here: simply print them
{
    cout << setw(4) << ct << ":";
//    for (ulong i=0; i<n; ++i)  cout << " " << f[i];
    print_perm("    ", f, n);

//    cout << "    ";
//    print_cycle(f, 0);

    if ( is_connected(f, n) )  cout << "  Ind";
    if ( is_updown_permutation(f, n) )  cout << "  UpD";
    if ( is_derangement(f, n) )  cout << "  Der";  // only for n even
//    if ( is_cyclic(f, n) )  cout << "  Cyc";
    cout << endl;
    jjassert( is_involution(f, n) );
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Involutions of n elements");

    ulong c = 20;
    NXARG(c, "Number of permutations");

    ulong *f = new ulong[n];
    for (ulong k=0; k<c; ++k)
    {
        random_self_inverse_permutation(f, n);
#ifndef TIMING
        visit(f, n, k);
#endif
    }

    delete [] f;

    return 0;
}
// -------------------------

/*
Timing:
 time ./bin 200 500000
arg 1: 200 == n  [Permutations of n elements (Note: must have n<=290)]  default=8
arg 2: 500000 == c  [Number of permutations]  default=20
./bin 200 500000  4.51s user 0.02s system 100% cpu 4.528 total
 ==> 200*500000/4.51 == 22,172,949 elements per second
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/permrand-self-inverse-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/permrand-self-inverse-demo.cc DEMOFLAGS=-DTIMING"
/// End:

