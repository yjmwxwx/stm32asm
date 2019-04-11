
#include "comb/partition-asc-sorts.h"

#include "comb/print-partition-conj.h"

#include "sort/sort.h"  // is_sorted()

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Partitions into parts of s sorts, as weakly ascending lists.
//% Lexicographic order: major order by parts, minor by sorts, where
//% comparison proceeds as sort1, part1; sort2, part2; sort3, part3, etc.
//% Cf. OEIS sequences (partitions of n into parts of s kinds):
//% A000041 (s=1), A000712 (s=2), A000716 (s=3), A023003 (s=4),
//% A023004 (s=5), A023005 (s=6), A023006 (s=7), and A023007 (s=8).

// Cf. comb/partition-asc-sorts2-demo.cc (partitions; lex: major by parts, minor by sorts)
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

    partition_asc_sorts P(n, s);

    ulong ct = 0;

#ifdef TIMING
#ifdef PARTITION_ASC_SORTS_FIXARRAYS
    cout << "PARTITION_ASC_SORTS_FIXARRAYS defined." << endl;
#endif
    P.first();
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ulong m = P.num_parts();
    do
    {
#if 0  // S-distinct: no two successive parts are of same sort
        // ns=1 ==> just 1 partition for all n
        // ns=2 ==> A182372 (!)
        // ns=3 ==> A000000
        bool q = true;
        const ulong *S = P.sdata();
        for (ulong j=1; j<m; ++j)
            if ( S[j]==S[j-1] )  { q=0; break; }
        if ( ! q )  continue;
#endif
#if 0 // with args n n: planar partitions (A000219)
        bool q = true;
        const ulong *S = P.sdata();
        const ulong *A = P.data();
        for (ulong j=0; j<m; ++j)  // max p sorts of part p
            if ( S[j] >= A[j] )  { q=0; break; }
        if ( ! q )  continue;
#endif
#if 0  // at most one sort > 0 with each type of part
        // ns == 1 ==> A000041 (partitions)
        // ns == 2 ==> A015128 (overpartitions)
        // ns == 3 ==> A000000
        // ns == n ==> A000000
        bool q = true;
        const ulong *S = P.sdata();
        const ulong *A = P.data();
        for (ulong j=1; j<m; ++j)
            if ( S[j] > 0 )
                if ( (S[j-1]==S[j]) && (A[j-1]==A[j]) )
                { q=0; break; }
        if ( ! q )  continue;
#endif

        ++ct;

        cout << setw(4) << ct << ":";
        P.print("  ");
//        P.print_rev("  ");  // print in weakly descending order
//        P.print_by_sorts("  ");
//        print_partition_asc_conj("  ", P.data(), m);
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
 echo $(for n in $(seq 0 15); do ./bin $n 2; done | g ct=) | sed 's/ ct=/, /g; s/ct=//'
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

gcc 4.8.0:

 time ./bin 110 1
arg 1: 110 == n  [partitions of n]  default=6
arg 2: 1 == s  [number of sorts (s>=1)]  default=2
 ct=607163746
./bin 110 1  4.92s user 0.00s system 99% cpu 4.918 total
 ==> 607163746/4.92 == 123,407,265 per second

 time ./bin 60 2
arg 1: 60 == n  [partitions of n]  default=6
arg 2: 2 == s  [number of sorts (s>=1)]  default=2
 ct=962759294
./bin 60 2  6.69s user 0.00s system 99% cpu 6.695 total
 ==> 962759294/6.69 == 143,910,208 per second

 time ./bin 35 4
arg 1: 35 == n  [partitions of n]  default=6
arg 2: 4 == s  [number of sorts (s>=1)]  default=2
 ct=1837560960
./bin 35 4  10.38s user 0.00s system 99% cpu 10.382 total
 ==> 1837560960/10.38 == 177,028,994 per second

 time ./bin 22 8
arg 1: 22 == n  [partitions of n]  default=6
arg 2: 8 == s  [number of sorts (s>=1)]  default=2
 ct=4053978040
./bin 22 8  20.51s user 0.00s system 99% cpu 20.514 total
 ==> 4053978040/20.51 == 197,658,607 per second



 time ./bin 110 1
arg 1: 110 == n  [partitions of n]  default=6
arg 2: 1 == s  [number of sorts (s>=1)]  default=2
PARTITION_ASC_SORTS_FIXARRAYS defined.
 ct=607163746
./bin 110 1  3.67s user 0.00s system 99% cpu 3.676 total
 ==> 607163746/3.67 == 165,439,712 per second

 time ./bin 60 2
arg 1: 60 == n  [partitions of n]  default=6
arg 2: 2 == s  [number of sorts (s>=1)]  default=2
PARTITION_ASC_SORTS_FIXARRAYS defined.
 ct=962759294
./bin 60 2  4.85s user 0.00s system 99% cpu 4.855 total
 ==> 962759294/4.85 == 198,507,070 per second


 time ./bin 35 4
arg 1: 35 == n  [partitions of n]  default=6
arg 2: 4 == s  [number of sorts (s>=1)]  default=2
PARTITION_ASC_SORTS_FIXARRAYS defined.
 ct=1837560960
./bin 35 4  7.59s user 0.00s system 99% cpu 7.594 total
 ==> 1837560960/7.59 == 242,102,893 per second

 time ./bin 22 8
arg 1: 22 == n  [partitions of n]  default=6
arg 2: 8 == s  [number of sorts (s>=1)]  default=2
PARTITION_ASC_SORTS_FIXARRAYS defined.
 ct=4053978040
./bin 22 8  15.99s user 0.00s system 99% cpu 15.990 total
 ==> 4053978040/15.99 == 253,532,085 per second

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
/// make-target: "1demo DSRC=demo/comb/partition-asc-sorts-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-sorts-demo.cc DEMOFLAGS=-DTIMING"
/// End:

