
#include "comb/composition-nz-sorts.h"

#include "sort/sort.h"  // is_sorted()

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts of s sorts.
//% Lexicographic order: major order by sorts, minor by parts, where
//% comparison proceeds as sort1, part1; sort2, part2; sort3, part3, etc.
//% Loopless algorithm.
//% Cf. OEIS sequences (compositions of n into parts of s kinds):
//% A011782 (s=1), A025192 (s=2), A002001 (s=3), A005054 (s=4),
//% A052934 (s=5), A055272 (s=6), A055274 (s=7), and A055275 (s=8).

// Cf. comb/composition-nz-sorts2-demo.cc (lex: major by parts, minor by sorts)
// Cf. comb/composition-nz-demo.cc for compositions (with one sort of parts)
// Cf. comb/ruler-func-s-demo.cc for radix-s ruler function


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "compositions of n");

    ulong s = 2;
    NXARG(s, "number of sorts (s>=1)");

    composition_nz_sorts P(n, s);

    ulong ct = 0;

#ifdef TIMING
#ifdef COMPOSITION_NZ_SORTS_FIXARRAYS
    cout << "COMPOSITION_NZ_SORTS_FIXARRAYS defined." << endl;
#endif
    P.first();
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ulong m = P.num_parts();
    do
    {
#if 0
        const ulong *A = P.data();
        const ulong *S = P.sdata();
        // the following sequence numbers are for s=2:
        if ( ! is_sorted(A, m) )   continue; // A070933 (partitions, ascending)
//        if ( ! is_sorted_desc(A, m) )   continue;  // A070933 (partitions, descending)

//        if ( ! is_sorted(S, m) )   continue; // (partitions: A093694; compositions: A045623)
        if ( ! P.sorts_in_runs_sorted(1) )  continue;
        // s=2 ==> partitions: A000712, compositions: A052945
        // s=3 ==> partitions: A000716, compositions: A000000
#endif

        ++ct;

        cout << setw(4) << ct << ":";
        P.print("  ");
//        P.print_by_sorts("  ");
        cout << endl;

        jjassert( P.OK() );
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;  // == s*(s+1)^(n-1)

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 31 1
arg 1: 31 == n  [compositions of n]  default=4
arg 2: 1 == s  [number of sorts (s>=1)]  default=2
 ct=1073741824
./bin 31 1  3.21s user 0.00s system 99% cpu 3.212 total
 ==> 1073741824/3.21 == 334,499,010 per second

 time ./bin 20 2
arg 1: 20 == n  [compositions of n]  default=4
arg 2: 2 == s  [number of sorts (s>=1)]  default=2
 ct=2324522934
./bin 20 2  7.31s user 0.00s system 99% cpu 7.312 total
 ==> 2324522934/7.31 == 317,992,193 per second

 time ./bin 13 4
arg 1: 13 == n  [compositions of n]  default=4
arg 2: 4 == s  [number of sorts (s>=1)]  default=2
 ct=976562500
./bin 13 4  3.14s user 0.00s system 99% cpu 3.141 total
 ==> 976562500/3.14 == 311,007,165 per second


 time ./bin 31 1
arg 1: 31 == n  [compositions of n]  default=4
arg 2: 1 == s  [number of sorts (s>=1)]  default=2
COMPOSITION_NZ_SORTS_FIXARRAYS defined.
 ct=1073741824
./bin 31 1  2.65s user 0.00s system 99% cpu 2.651 total
 ==> 1073741824/2.65 == 405,185,593 per second

 time ./bin 20 2
arg 1: 20 == n  [compositions of n]  default=4
arg 2: 2 == s  [number of sorts (s>=1)]  default=2
COMPOSITION_NZ_SORTS_FIXARRAYS defined.
 ct=2324522934
./bin 20 2  5.23s user 0.00s system 99% cpu 5.234 total
 ==> 2324522934/5.23 == 444,459,452 per second

 time ./bin 13 4
arg 1: 13 == n  [compositions of n]  default=4
arg 2: 4 == s  [number of sorts (s>=1)]  default=2
COMPOSITION_NZ_SORTS_FIXARRAYS defined.
 ct=976562500
./bin 13 4  2.19s user 0.00s system 99% cpu 2.191 total
 ==> 976562500/2.19 == 445,918,949 per second


*/

/*
BENCHARGS=31 1
BENCHARGS=20 2
BENCHARGS=13 4
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-sorts-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-sorts-demo.cc DEMOFLAGS=-DTIMING"
/// End:

