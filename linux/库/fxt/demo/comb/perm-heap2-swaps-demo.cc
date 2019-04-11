
#include "comb/perm-heap2-swaps.h"

#include "comb/mixedradix.h"
#include "comb/comb-print.h"
#include "aux0/swap.h"

#include "aux0/factorial.h"  // for timing

#include "fxtio.h"
#include "nextarg.h"
#include "jjassert.h"
#include "fxttypes.h"


//% Swaps for Gray code for permutations, CAT algorithm, optimized version.
//% Algorithm following B.R.Heap (1963)

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements to permute n>0");
    jjassert( n>0 );


    perm_heap2_swaps P(n);
    P.first();


#ifdef TIMING
#ifdef PERM_HEAP2_SWAPS_FIXARRAYS
    cout << "PERM_HEAP2_SWAPS_FIXARRAYS is defined" << endl;
#endif

    ulong zz = 0;
    do  { zz^=(P.sw1_^P.sw2_); }  while ( P.next()!=n );

    cout << " ct=" << factorial(n) << endl;

    return (zz==999);  // will return 0 because zz <= n

#else  // TIMING

    ulong *x = new ulong[n];  // permutations
    ulong *xi = new ulong[n];  // inverse permutations

    for (ulong k=0; k<n; ++k)  x[k] = xi[k] = k;

    bool dfz= true;  // whether to print dots for zeros
    ulong ct = 0;
    do
    {
        cout << setw(4) << ct << ":";
        ulong sw1, sw2;
        P.get_swap(sw1, sw2);
        swap2( x[sw1], x[sw2]);  // update permutation
        print_perm("    ", x, n, dfz);

//        cout << " (" << P.ct_ << ") ";
//        cout << " (" << P.fc_ << ") ";

        cout << "     (" << sw1 << ", " << sw2 << ") ";

//        print_mixedradix("    ", P.d_+2, n-3, dfz);

        swap2( xi[x[sw1]], xi[x[sw2]] );  // update inverse permutation
        print_perm("    ", xi, n, dfz);

        cout << endl;
        ++ct;
    }
    while ( P.next()!=n );
    cout << endl;
    cout << " ct=" << ct << endl;

    delete [] xi;
    delete [] x;

    cout << endl;

#endif  // TIMING


    return 0;
}
// -------------------------

/*
Timing:

fix-arrays, and XOR-ing sw1 and sw2:
 time ./bin 13
./bin 13  17.39s user 0.04s system 100% cpu 17.429 total
 ==> 13!/17.39 == 358,080,552 per second

pointers, and XOR-ing sw1 and sw2:
 time ./bin 13
./bin 13  19.40s user 0.03s system 100% cpu 19.425 total
 ==> 13!/19.40 == 320,980,453 per second
*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

fix-arrays, and XOR-ing sw1 and sw2:
 time ./bin 13
arg 1: 13 == n  [Number of elements to permute n>0]  default=4
PERM_HEAP2_SWAPS_FIXARRAYS is defined
./bin 13  14.16s user 0.00s system 99% cpu 14.165 total
 ==> 13!/14.16 == 439,761,355 per second

pointers, and XOR-ing sw1 and sw2:
 time ./bin 13
arg 1: 13 == n  [Number of elements to permute n>0]  default=4
./bin 13  17.07s user 0.00s system 99% cpu 17.074 total
 ==> 13!/17.07 == 364,793,251 per second

*/

 /*
BENCHARGS=13
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-heap2-swaps-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-heap2-swaps-demo.cc DEMOFLAGS=-DTIMING"
/// End:

