
#include "comb/perm-st-gray.h"
#include "comb/perm-gray-rot1.h"
#include "comb/mixedradix-gray.h"

#include "comb/comb-print.h"
//#include "comb/fact2perm.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

//% Gray code for single track permutations:
//% one transposition per update with odd n,
//% one extra transposition once in (n-1)! updates with even n (optimal).

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Permutations of n elements (n>=2).");

    perm_st_gray P(n);

#ifdef TIMING
    while ( P.next() ) {;}

#else // TIMING

    const bool dfz = true;  // whether to print dots for zeros

//    ulong *tt = new ulong[n-1];  // aux
    const ulong *x = P.data();
    const ulong *ix = P.invdata();
    ulong ct = 0;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

//        if ( n>1 )  print_mixedradix("    ", P.G->M_->data(), n-2, dfz);
//        print_perm("    ", P.G->data(), n-1, dfz);

        print_perm("    ", x, n, dfz);
        print_perm("    ", ix, n, dfz);

//        perm2rfact(x, n, tt);
//        print_mixedradix("    ", tt, n-1, dfz);

        cout << endl;
    }
    while ( P.next() );
#endif  // TIMING


    return 0;
}
// -------------------------

/*
Timing:
time ./bin 12
arg 1: 12 == n  [Permutations of n elements (n>=2).]  default=5
./bin 12  17.99s user 0.09s system 99% cpu 18.081 total
 ==> 12!/17.99 == 26,625,992 per second
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-st-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-st-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:
