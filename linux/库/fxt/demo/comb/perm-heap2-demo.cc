
#include "comb/perm-heap2.h"

#include "comb/mixedradix.h"
#include "comb/comb-print.h"
#include "aux0/swap.h"

#include "fxtio.h"
#include "nextarg.h"
#include "jjassert.h"
#include "fxttypes.h"


//% Gray code for permutations, CAT algorithm, optimized version.
//% Algorithm following B.R.Heap (1963)

//#define TIMING  // uncomment to disable printing

#ifdef TIMING
#include "aux0/factorial.h"
#endif


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements to permute n>0");
    jjassert( n>0 );

    perm_heap2 P(n);
    P.first();

#ifdef TIMING

#ifdef PERM_HEAP2_FIXARRAYS
    cout << "PERM_HEAP2_FIXARRAYS is defined." << endl;
#endif
    ulong ct = 0;
//    do { ++ct; }  while ( P.next() );
    do { ++ct; }  while ( P.next()!=n );

//    do
//    {
//        ulong s1, s2;
//        P.get_swap(s1, s2);
//        ct += s1 + s2;
//    }
//    while ( P.next() );
//    { ulong f = factorial(n);  if (ct!=f) ct=f; }

#else  // TIMING

    ulong *x = new ulong[n];  // permutations
    ulong *xi = new ulong[n];  // inverse permutations
    for (ulong k=0; k<n; ++k)  x[k] = xi[k] = k;

    const bool dfz= true;  // whether to print dots for zeros

    ulong ct = 0;
    do
    {
        ulong sw1, sw2;
        P.get_swap(sw1, sw2);
        swap2( x[sw1], x[sw2] );  // update permutation
        cout << setw(4) << ct << ":";
        print_perm("    ", x, n, dfz);

//        cout << " (" << P.ct_ << ") ";
//        cout << " (" << P.fc_ << ") ";

        cout << "     (" << sw1 << ", " << sw2 << ") ";

//        print_mixedradix("    ", P.d_+2, n-3, dfz);

        swap2( xi[x[sw1]], xi[x[sw2]]);  // update inverse permutation
        print_perm("    ", xi, n, dfz);

        cout << endl;
        ++ct;
    }
//    while ( P.next() );
    while ( P.next()!=n );

    delete [] x;
    delete [] xi;

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 13
PERM_HEAP2_FIXARRAYS is defined.
./bin 13  13.53s user 0.03s system 99% cpu 13.561 total
 ==> 13!/13.53 == 460,238,048 per second
 ==> 4.78 cycles per update

 time ./bin 13
./bin 13  22.21s user 0.04s system 100% cpu 22.245 total
 ==> 13!/22.21 == 280,370,139 per second
 ==> 7.85 cycles per update

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 13
arg 1: 13 == n  [Number of elements to permute n>0]  default=4
PERM_HEAP2_FIXARRAYS is defined.
 ct=6227020800
./bin 13  14.63s user 0.00s system 99% cpu 14.639 total
 ==> 13!/14.63 == 425,633,684 per second

 time ./bin 13
arg 1: 13 == n  [Number of elements to permute n>0]  default=4
 ct=6227020800
./bin 13  19.08s user 0.00s system 99% cpu 19.087 total
 ==> 13!/19.08 == 326,363,773 per second

*/


/*
BENCHARGS=13
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-heap2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-heap2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

