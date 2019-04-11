
#include "comb/partition-asc-sorts2.h"

#include "sort/sort.h"  // is_sorted()

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Partitions into parts of s sorts, as weakly ascending lists.
//% Lexicographic order: major order by parts, minor by sorts, where
//% comparison proceeds as part1, sort1; part2, sort2; part3, sort3, etc.
//% Cf. OEIS sequences (partitions of n into parts of s kinds):
//% A000041 (s=1), A000712 (s=2), A000716 (s=3), A023003 (s=4),
//% A023004 (s=5), A023005 (s=6), A023006 (s=7), and A023007 (s=8).

// Cf. comb/partition-asc-sorts-demo.cc (partitions; lex: major by sorts, minor by parts)
// Cf. comb/composition-nz-sorts2-demo.cc (compositions; lex: major by parts, minor by sorts)
// Cf. comb/composition-nz-sorts-demo.cc (compositions; lex: major by sorts, minor by parts)
// Cf. comb/partition-asc-demo.cc for partitions (with one sort of parts)


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "partitions of n");

    ulong s = 2;
    NXARG(s, "number of sorts (s>=1)");

    partition_asc_sorts2 P(n, s);

    ulong ct = 0;

#ifdef TIMING
#ifdef PARTITION_ASC_SORTS2_FIXARRAYS
    cout << "PARTITION_ASC_SORTS2_FIXARRAYS defined." << endl;
#endif
    P.first();
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ulong m = P.num_parts();
    do
    {
#if 0  // at least one part of first sort in partition:  A000000
        bool q = false;
        const ulong *S = P.sdata();
        for (ulong j=0; j<m; ++j)
            if ( 0==S[j] )  { q=1; break; }
        if ( ! q )  continue;
#endif
#if 0  // at least one part of first sort for all part sizes:  A000000
        bool q = true;
        const ulong *A = P.data();
        const ulong *S = P.sdata();
        ulong v = 0;
        for (ulong j=0; j<m; ++j)
        {
            if ( A[j] != v )
            {
                if ( S[j]!=0 )  { q=0; break; }
                v = A[j];
            }
        }
        if ( ! q )  continue;
#endif
#if 0  // at most two parts of each sizes
        // ns=1 ==> A000726
        // ns=2 ==> A000000
        bool q = true;
        const ulong *A = P.data();
        const ulong *S = P.sdata();
//        if ( S[m-1] !=0 )  continue;
        for (ulong j=1; j<m; ++j)
        {
            if ( A[j] == A[j-1] )
            {
//                if ( S[j] == S[j-1] )  { q=0; break; }
                if ( j>=2 )
                    if ( A[j] == A[j-2] )  { q=0; break; }
            }
        }
        if ( ! q )  continue;
#endif

        ++ct;

        cout << setw(4) << ct << ":";
        P.print("  ");
//        P.print_rev("  ");  // print in weakly descending order
//        P.print_by_sorts("  ");
        cout << endl;

        jjassert( P.OK() );
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)


 time ./bin 110 1
arg 1: 110 == n  [partitions of n]  default=6
arg 2: 1 == s  [number of sorts (s>=1)]  default=2
 ct=607163746
./bin 110 1  4.36s user 0.00s system 99% cpu 4.360 total
 ==> 607163746/4.36 == 139,257,739 per second

 time ./bin 60 2
arg 1: 60 == n  [partitions of n]  default=6
arg 2: 2 == s  [number of sorts (s>=1)]  default=2
 ct=962759294
./bin 60 2  4.35s user 0.00s system 99% cpu 4.355 total
 ==> 976562500/4.35 == 224,497,126 per second

 time ./bin 35 4
arg 1: 35 == n  [partitions of n]  default=6
arg 2: 4 == s  [number of sorts (s>=1)]  default=2
 ct=1837560960
./bin 35 4  6.09s user 0.00s system 99% cpu 6.095 total
 ==> 1837560960/6.09 == 301,734,147 per second

 time ./bin 22 8
arg 1: 22 == n  [partitions of n]  default=6
arg 2: 8 == s  [number of sorts (s>=1)]  default=2
 ct=4053978040
./bin 22 8  10.98s user 0.00s system 99% cpu 10.984 total
 ==> 4053978040/10.98 == 369,214,757 per second



 time ./bin 110 1
arg 1: 110 == n  [partitions of n]  default=6
arg 2: 1 == s  [number of sorts (s>=1)]  default=2
PARTITION_ASC_SORTS2_FIXARRAYS defined.
 ct=607163746
./bin 110 1  4.23s user 0.00s system 99% cpu 4.236 total
 ==> 607163746/4.23 == 143,537,528 per second

 time ./bin 60 2
arg 1: 60 == n  [partitions of n]  default=6
arg 2: 2 == s  [number of sorts (s>=1)]  default=2
PARTITION_ASC_SORTS2_FIXARRAYS defined.
 ct=962759294
./bin 60 2  4.20s user 0.00s system 99% cpu 4.198 total
 ==> 976562500/4.20 == 232,514,880 per second

 time ./bin 35 4
arg 1: 35 == n  [partitions of n]  default=6
arg 2: 4 == s  [number of sorts (s>=1)]  default=2
PARTITION_ASC_SORTS2_FIXARRAYS defined.
 ct=1837560960
./bin 35 4  6.28s user 0.00s system 99% cpu 6.277 total
 ==> 1837560960/6.28 == 292,605,248 per second

 time ./bin 22 8
arg 1: 22 == n  [partitions of n]  default=6
arg 2: 8 == s  [number of sorts (s>=1)]  default=2
PARTITION_ASC_SORTS2_FIXARRAYS defined.
 ct=4053978040
./bin 22 8  11.64s user 0.00s system 99% cpu 11.640 total
 ==> 4053978040/11.64 == 348,279,900 per second

*/

/*
BENCHARGS=110 1
BENCHARGS=60 2
BENCHARGS=35 4
BENCHARGS=22 8
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-sorts2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-sorts2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

