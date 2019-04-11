
#include "comb/composition-nz-rl.h"
#include "comb/composition-nz-rank.h"

#include "comb/composition-nz-conj.h"
#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts, run-length order.
//% Loopless algorithm.


// Cf. comb/composition-nz-demo.cc for compositions in lexicographic order
// Cf. comb/composition-nz-subset-lex-demo.cc for compositions in subset-lex order

// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/partition-desc-demo.cc for partitions as weakly descending list of parts

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "compositions of n");

    composition_nz_rl P(n);

    ulong ct = 0;

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "With benchmark: whether to generate in backward order");
    if ( !bq )
    {
        cout << "forward:" << endl;
        P.first();
        do  { ++ct; }  while ( P.next() );
    }
    else
    {
        cout << "backward:" << endl;
        P.last();
        do  { ++ct; }  while ( P.prev() );
    }

#else  // TIMING

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

//    P.last();
    ulong m = P.num_parts();
//    ulong C[64];
    do
    {
#if 0
        const ulong *x = P.data();
        bool q = true;
        for (ulong j=0; j<m; ++j)    // max part<=2 (==> A000045)
            if ( x[j] > 2 )  { q=false;  break; }

//        for (ulong j=1; j<m-1; ++j)  // "inner" parts !=1 (==> A000045)
//            if ( x[j] == 1 )  { q=false;  break; }

        if ( !q )  continue;
#endif
//        if ( 0==(1UL & P.last_part()) )  continue;  // A001045

//        cout << m << ", ";  continue;  // A088748 = A005811 + 1
//        cout << m-1 << ", ";  continue;  // A005811: number of 1's in Gray code for n
//        cout << P.last_part() << ", ";  continue;  // A136480

        cout << setw(4) << ct << ":";

//        cout << "  [" << setw(2) << m << "]";

        ulong r1 = composition_nz_rank(P.data(), m);  // *not* RL rank
        const ulong pn = ( n>=2 ? n-1 : 1 );
        print_bin("    ", r1, pn);  // RL Gray code if limit on max part
        print_bin("    ", P.rank(), pn);   // RLL word if limit on max part

        P.print("    ");

//        ulong nc = composition_nz_conj(P.data(), m, C);
//        print_vec("        ", C, nc); // endo order: pointer to ones in RL word


#if 1 // with forward generation only
        const ulong r = P.rank();
        jjassert( r == ct );
        jjassert( m == P.unrank(r) );
        jjassert( r == P.rank() );
        jjassert( r == composition_nz_rl_rank(P.data(), m) );
#endif

        cout << endl;
        if ( aa )  // ASCII art
        {
            P.print_aa();
            cout << endl;
            cout << endl;
        }

        ++ct;
        jjassert( P.OK() );
    }
    while ( (m=P.next()) );
//    while ( (m=P.prev()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32
arg 1: 32 == n  [compositions of n]  default=7
  ct=2147483648
./bin 32  6.79s user 0.00s system 99% cpu 6.793 total
 ==> 2147483648/6.79 == 316,271,524 per second


GCC 4.8.0:

 time ./bin 32 0
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
 ct=2147483648
./bin 32 0  6.65s user 0.00s system 99% cpu 6.651 total
 ==> 2147483648/6.65 == 322,929,871 per second

 time ./bin 32 1
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
 ct=2147483648
./bin 32 1  6.53s user 0.00s system 99% cpu 6.529 total
 ==> 2147483648/6.53 == 328,864,264 per second

*/

/*
BENCHARGS=32 0
BENCHARGS=32 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-rl-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-rl-demo.cc DEMOFLAGS=-DTIMING"
/// End:

