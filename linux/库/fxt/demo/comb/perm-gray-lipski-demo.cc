
#include "comb/perm-gray-lipski.h"

#include "comb/comb-print.h"

#include "comb/check-permgen.h"

#include "nextarg.h"
#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"


//#include "comb/fact2perm.h"
//#include "perm/perminvert.h"


//% Four Gray codes for permutations, CAT algorithm.

//#define TIMING  // uncomment to disable printing

#define INVERSE  // define to show inverse permutations

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of elements to permute");
    ulong r = 1;
    NXARG(r, "Ordering:"
          "\n    0 ==> Lipski(9) == Heap,"
          "\n    1 ==> Lipski(16),"
          "\n    2 ==> Lipski(10),"
          "\n    3 ==> order not in Lipski's paper");
    cout << endl;

    perm_gray_lipski P(n, r);
    P.first();

    ulong ct = 0;

#ifdef TIMING
    do { ++ct; } while ( P.next() );

#else  // TIMING

    const bool dfz= true;  // whether to print dots for zeros


#ifdef INVERSE
    const ulong *x = P.data();
    ulong *xi = new ulong[n];  // inverse permutations
    for (ulong k=0; k<n; ++k)  xi[k] = k;
#endif  // INVERSE

    check_permgen C(n);
    C.first( P.data() );

    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
        P.print("    ", dfz);

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
        jjassert( ! C.is_repeat() );
    }
    while ( P.next() );

#ifdef INVERSE
    delete [] xi;
#endif

#endif // TIMING

    cout << " ct=" << ct << endl;


    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 12
 ct=479001600
./bin 12  4.37s user 0.02s system 99% cpu 4.400 total
 ==> 479001600/4.37 == 109,611,350 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12
arg 1: 12 == n  [Number of elements to permute]  default=5
arg 2: 1 == r  [Ordering:
    0 ==> Lipski(9) == Heap,
    1 ==> Lipski(16),
    2 ==> Lipski(10),
    3 ==> order not in Lipski's paper]  default=1
 ct=479001600
./bin 12  2.74s user 0.00s system 99% cpu 2.738 total
 ==> 479001600/2.74 == 174,818,102 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-gray-lipski-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-gray-lipski-demo.cc DEMOFLAGS=-DTIMING"
/// End:
