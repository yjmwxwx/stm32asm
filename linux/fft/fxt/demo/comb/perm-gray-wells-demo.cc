
#include "comb/perm-gray-wells.h"

#include "comb/comb-print.h"

#include "nextarg.h"
#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"


//#include "comb/fact2perm.h"
//#include "perm/perminvert.h"


//% Two Gray codes for permutations (Wells' order and a variant of it), CAT algorithm.

//#define TIMING  // uncomment to disable printing

#define INVERSE  // define to show inverse permutations

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of elements to permute");
    ulong r = 0;
    NXARG(r, "Ordering:"
          "\n    0 ==> Wells' order == Lipski(8),"
          "\n    1 ==> Lipski(14),"
          "\n    2 ==> Lipski(15)");

    perm_gray_wells P(n, r);
    P.first();

    ulong ct = 0;
#ifdef TIMING
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    cout << endl;

    const bool dfz= true;  // whether to print dots for zeros
    const ulong *x = P.data();
#ifdef INVERSE
    ulong *xi = new ulong[n];  // inverse permutations
    for (ulong k=0; k<n; ++k)  xi[k] = k;
#endif  // INVERSE

    do
    {
        ++ct;

        cout << setw(4) << ct << ":";
        print_perm("    ", x, n, dfz);

        ulong sw1, sw2;
        P.get_swap(sw1, sw2);
        cout << "     (" << sw1 << ", " << sw2 << ") ";


        print_mixedradix("    ", P.d_, n-1, dfz);

#ifdef INVERSE
        cout << "    ";
        swap2( xi[x[sw1]], xi[x[sw2]]);  // update inverse permutation
        print_perm("    ", xi, n, dfz);
//        perm2rfact(xi, n, rfc);
//        print_mixedradix("    ", rfc, n-1, dfz);
#endif  // INVERSE

        cout << endl;
    }
    while ( P.next() );

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

 time ./bin 12 1
arg 1: 12 == n  [Number of elements to permute]  default=5
arg 2: 1 == r  [Ordering:
    0 ==> Wells' order == Lipski(8),
    1 ==> Lipski(14),
    2 ==> Lipski(15)]  default=0
 ct=479001600
./bin 12 1  4.47s user 0.00s system 99% cpu 4.474 total
 ==> 479001600/4.47 == 107,159,194 per second

 time ./bin 12 0
arg 1: 12 == n  [Number of elements to permute]  default=5
arg 2: 0 == r  [Ordering:
    0 ==> Wells' order == Lipski(8),
    1 ==> Lipski(14),
    2 ==> Lipski(15)]  default=0
 ct=479001600
./bin 12 0  4.50s user 0.01s system 99% cpu 4.511 total
 ==> 479001600/4.50 == 106,444,800 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12 1
arg 1: 12 == n  [Number of elements to permute]  default=5
arg 2: 1 == r  [Ordering:
    0 ==> Wells' order == Lipski(8),
    1 ==> Lipski(14),
    2 ==> Lipski(15)]  default=0
 ct=479001600
./bin 12 1  2.56s user 0.00s system 99% cpu 2.562 total
 ==> 479001600/2.56 == 187,110,000 per second

 time ./bin 12 0
arg 1: 12 == n  [Number of elements to permute]  default=5
arg 2: 0 == r  [Ordering:
    0 ==> Wells' order == Lipski(8),
    1 ==> Lipski(14),
    2 ==> Lipski(15)]  default=0
 ct=479001600
./bin 12 0  2.88s user 0.00s system 99% cpu 2.883 total
 ==> 479001600/2.88 == 166,320,000 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-gray-wells-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-gray-wells-demo.cc DEMOFLAGS=-DTIMING"
/// End:
