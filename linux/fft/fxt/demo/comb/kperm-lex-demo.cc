
#include "comb/kperm-lex.h"

#include "comb/check-kpermgen.h"
#include "comb/comb-print.h"

//#include "comb/fact2perm.h"


#include "jjassert.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Generate all k-permutations of n elements in lexicographic order.
//% Same as: k-prefixes of permutations of n elements.
//% Same as: arrangements of k out of n elements.

// Cf. comb/kperm-gray-demo.cc for minimal-change order
// Cf. comb/arrangement-rgs-demo.cc for all arrangements

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Total of n elements, n>=1");
    jjassert( n >= 1 );

    ulong k = 3;
    NXARG(k, "Permutations of k elements, (1<=k<=n)");
    jjassert( k <= n );

    kperm_lex P(n);
    P.first(k);

    ulong ct = 0;
#ifdef TIMING

    do { ++ct; }  while ( P.next() );

#else
    const bool dfz = true;  // whether to print dots for zeros
    const ulong *x = P.data();
    const ulong *d = P.d_;
    const ulong *ix = P.invdata();

//    ulong *F = new ulong[n];

    check_kpermgen C(n, k);
    C.first(P.data());

    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
        print_perm("    ", x, k, dfz);  // prefix
        print_perm("", x+k, n-k, dfz);  // rest
        print_mixedradix("    ", d, n-1, dfz);

//        perm2ffact(x, n, F);  // first k k positions same as in d[]
//        print_vec("  ", F, n-1, true);

        print_perm("    ", ix, n, dfz);

        cout << endl;

        jjassert( ! C.is_repeat() );
    }
    while ( P.next() );

    jjassert( C.have_all() );

#endif  // TIMING

    cout << " ct=" << ct << endl;

//    delete [] F;

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 12 12
arg 1: 12 == n  [Total of n elements, n>=1]  default=5
arg 2: 12 == k  [Permutations of k elements, (1<=k<=n)]  default=3
  ct=479001600
./bin 12 12  16.12s user 0.01s system 100% cpu 16.127 total
 ==> 479001600/16.12 == 29,714,739 per second


 time ./bin 12 11
arg 1: 12 == n  [Total of n elements, n>=1]  default=5
arg 2: 11 == k  [Permutations of k elements, (1<=k<=n)]  default=3
  ct=479001600
./bin 12 11  15.58s user 0.00s system 99% cpu 15.600 total
 ==> 479001600/15.58 == 30,744,646 per second

 time ./bin 12 10
arg 1: 12 == n  [Total of n elements, n>=1]  default=5
arg 2: 10 == k  [Permutations of k elements, (1<=k<=n)]  default=3
  ct=239500800
./bin 12 10  6.41s user 0.01s system 99% cpu 6.426 total
 ==> 239500800/6.41 == 37,363,619 per second

 time ./bin 24 6
arg 1: 24 == n  [Total of n elements, n>=1]  default=5
arg 2: 6 == k  [Permutations of k elements, (1<=k<=n)]  default=3
  ct=96909120
./bin 24 6  1.48s user 0.00s system 99% cpu 1.478 total
 ==> 96909120/1.48 == 65,479,135 per second

 time ./bin 52 5
arg 1: 52 == n  [Total of n elements, n>=1]  default=5
arg 2: 5 == k  [Permutations of k elements, (1<=k<=n)]  default=3
  ct=311875200
./bin 52 5  4.14s user 0.00s system 100% cpu 4.147 total
 ==> 311875200/4.14 == 75,332,173 per second

 time ./bin 100 4
arg 1: 100 == n  [Total of n elements, n>=1]  default=5
arg 2: 4 == k  [Permutations of k elements, (1<=k<=n)]  default=3
  ct=94109400
./bin 100 4  1.19s user 0.00s system 100% cpu 1.195 total
 ==> 94109400/1.19 == 79,083,529 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12 12
arg 1: 12 == n  [Total of n elements, n>=1]  default=5
arg 2: 12 == k  [Permutations of k elements, (1<=k<=n)]  default=3
 ct=479001600
./bin 12 12  12.31s user 0.00s system 99% cpu 12.316 total
 ==> 479001600/12.31 == 38,911,584 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12 12
arg 1: 12 == n  [Total of n elements, n>=1]  default=5
arg 2: 12 == k  [Permutations of k elements, (1<=k<=n)]  default=3
 ct=479001600
./bin 12 12  6.20s user 0.00s system 99% cpu 6.207 total
 ==> 479001600/6.20 == 77,258,322 per second

*/


/*
BENCHARGS=12 12
BENCHARGS=12 11
BENCHARGS=12 10
BENCHARGS=24 6
BENCHARGS=52 5
BENCHARGS=100 4
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/kperm-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/kperm-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

