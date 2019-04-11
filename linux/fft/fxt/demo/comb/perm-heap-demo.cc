
#include "comb/perm-heap.h"
#include "comb/fact2perm.h"

#include "comb/mixedradix.h"
#include "comb/comb-print.h"
#include "aux0/swap.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"


//% Gray code for permutations, CAT algorithm.
//% Algorithm following B.R.Heap (1963)

//#define TIMING  // uncomment to disable printing

#define INVERSE  // define to show inverse permutations

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements to permute");


    perm_heap P(n);
    P.first();

    ulong ct = 0;

#ifdef TIMING

    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    const bool dfz= true;  // whether to print dots for zeros
    const ulong *x = P.data();
    ulong *rfc = new ulong[n];  // rising factorial

#ifdef INVERSE
    ulong *xi = new ulong[n];  // inverse permutations
    for (ulong k=0; k<n; ++k)  xi[k] = k;
#endif  // INVERSE

    do
    {
        cout << setw(4) << ct << ":";
        P.print("    ", dfz);

        ulong sw1, sw2;
        P.get_swap(sw1, sw2);
        cout << "     (" << sw1 << ", " << sw2 << ") ";

        print_mixedradix("    ", P.d_, n-1, dfz);


        perm2rfact(x, n, rfc);
        print_mixedradix("    ", rfc, n-1, dfz);


#ifdef INVERSE
        cout << "    ";
        swap2( xi[x[sw1]], xi[x[sw2]]);  // update inverse permutation
        print_perm("    ", xi, n, dfz);
        perm2rfact(xi, n, rfc);
        print_mixedradix("    ", rfc, n-1, dfz);
#endif  // INVERSE

        cout << endl;
        ++ct;
    }
    while ( P.next() );

    delete [] rfc;
#ifdef INVERSE
    delete [] xi;
#endif

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:
 time ./bin 12
 ct=479001600
./bin 12  3.59s user 0.01s system 99% cpu 3.605 total
 ==> 479001600/3.59 == 133,426,629 per second

no swaps:
 time ./bin 12
 ct=479001600
./bin 12  2.22s user 0.00s system 99% cpu 2.229 total
 ==> 479001600/2.22 == 215,766,486 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12
arg 1: 12 == n  [Number of elements to permute]  default=4
 ct=479001600
./bin 12  3.13s user 0.00s system 99% cpu 3.136 total
 ==> 479001600/3.13 == 153,035,654 per second

 time ./bin 12
arg 1: 12 == n  [Number of elements to permute]  default=4
 ct=479001600
./bin 12  1.33s user 0.00s system 99% cpu 1.332 total
 ==> 479001600/1.33 == 360,151,578 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-heap-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-heap-demo.cc DEMOFLAGS=-DTIMING"
/// End:

