
#include "comb/partition-dist-asc.h"

//#include "comb/partition-odd-to-dist.h"
//#include "comb/comb-print.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions into distinct parts as ascending list of parts,
//% lexicographic order.
//% Cf. OEIS sequence A000009.

// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts
// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending compositions
// Cf. comb/partition-demo.cc for partitions given as multiplicities of parts
// Cf. seq/A179080-demo.cc for partitions into distinct parts and adjacent parts have different parity.
// Cf. comb/composition-nz-demo.cc for all compositions as lists of parts

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 19;
    NXARG(n, "integer partitions of n into distinct parts");

    partition_dist_asc P(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
//    ulong *T = new ulong[n];
//    ulong *X = new ulong[n];
    do
    {
#if 0
        const ulong *x = P.data();
        bool q = true;
        for (ulong j=1; j<m; ++j)
            if ( x[j] - x[j-1] < 2 )  // min diff == 2: A003114
//            if ( x[j] - x[j-1] < 3 )  // min diff == 3: A025157
            // sum(n>=0, x^(n*(3*n-1)/2)/prod(k=1..n,1-x^k))
//            if ( x[j] - x[j-1] < 4 )  // min diff == 4: A025158
            // A025158, sum(k>=1, x^(2*k^2-k)/prod(i=1..k, 1-x^i )),
                // cf. A179046: sum(n>=0, x^(D*n*(n+1)/2) / prod(k=1,n,1-x^k) )
//            if ( x[j] - x[j-1] != 1 )  // diff == 1: A001227: Number of odd divisors
            { q=0;  break; }
        if ( ! q )  continue;
#endif
#if 0  // k-th part not k, same as first part>=2: A025147
        if ( P.data()[0]==1 ) continue;
#endif
#if 0
//        if ( m % 2 == 1 )  continue;  // even m: A067661
        if ( m % 2 != 1 )  continue;  // odd m: A067659
        const ulong *x = P.data();
        ulong e = 1;  for (ulong j=0; j<m; ++j)  e &= x[j];
        e &= 1;  if ( e==0 )  continue;  // all odd parts
        // all: A000700, following are bisections:
        // even m: A069910 partitions of 2*n into distinct odd parts
        // odd m: A069911 partitions of 2*n+1 into distinct odd parts
#endif
        ++ct;

#if 1 // whether to print anything
        cout << setw(4) << ct << ":";
//        cout << " [" << setw(2) << m << "] ";
        P.print("  ");

//        ulong mt = partition_asc_dist_to_odd(P.data(), m, T);
//        print_vec("\n  T: ", T, mt);
//        ulong mx = partition_asc_odd_to_dist(T, mt, X);
//        print_vec("\n  X: ", X, mx);
//        for (ulong i=0; i<m; ++i)  jjassert( X[i] == P.data()[i] );
//        cout << endl;

        cout << endl;

        jjassert( P.OK() );
#endif
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 220
arg 1: 220 == n  [integer partitions of n into distinct parts]  default=16
  ct=1586861606
./bin 220  6.41s user 0.00s system 99% cpu 6.415 total
 ==> 1586861606/6.41 == 247,560,312 per second

*/

/*
BENCHARGS= 220
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-dist-asc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-dist-asc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

