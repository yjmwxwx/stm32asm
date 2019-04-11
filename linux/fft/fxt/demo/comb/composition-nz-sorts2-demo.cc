
#include "comb/composition-nz-sorts2.h"

#include "sort/sort.h"  // is_sorted()

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts of s sorts.
//% Lexicographic order: major order by parts, minor by sorts, where
//% comparison proceeds as part1, sort1; part2, sort2; part3, sort3, etc.
//% Loopless algorithm.
//% Cf. OEIS sequences (compositions of n into parts of s kinds):
//% A011782 (s=1), A025192 (s=2), A002001 (s=3), A005054 (s=4),
//% A052934 (s=5), A055272 (s=6), A055274 (s=7), and A055275 (s=8).

// Cf. comb/composition-nz-sorts-demo.cc (lex: major by sorts, minor by parts)
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

    composition_nz_sorts2 P(n, s);

    ulong ct = 0;

#ifdef TIMING
#ifdef COMPOSITION_NZ_SORTS2_FIXARRAYS
    cout << "COMPOSITION_NZ_SORTS2_FIXARRAYS defined." << endl;
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

//        if ( ! is_sorted(A, m) )   continue; // A070933 (partitions, ascending)
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
./bin 31 1  3.21s user 0.00s system 99% cpu 3.213 total
==> 1073741824/3.21 == 334,499,010 per second

 time ./bin 20 2
arg 1: 20 == n  [compositions of n]  default=4
arg 2: 2 == s  [number of sorts (s>=1)]  default=2
 ct=2324522934
./bin 20 2  5.76s user 0.00s system 99% cpu 5.763 total
 ==> 2324522934/5.76 == 403,563,009 per second

 time ./bin 13 4
arg 1: 13 == n  [compositions of n]  default=4
arg 2: 4 == s  [number of sorts (s>=1)]  default=2
 ct=976562500
./bin 13 4  2.29s user 0.00s system 99% cpu 2.290 total
 ==> 976562500/2.29 == 426,446,506 per second



 time ./bin 31 1
arg 1: 31 == n  [compositions of n]  default=4
arg 2: 1 == s  [number of sorts (s>=1)]  default=2
COMPOSITION_NZ_SORTS2_FIXARRAYS defined.
 ct=1073741824
./bin 31 1  3.51s user 0.00s system 99% cpu 3.510 total
 ==> 1073741824/3.51 == 305,909,351 per second

 time ./bin 20 2
arg 1: 20 == n  [compositions of n]  default=4
arg 2: 2 == s  [number of sorts (s>=1)]  default=2
COMPOSITION_NZ_SORTS2_FIXARRAYS defined.
 ct=2324522934
./bin 20 2  5.48s user 0.00s system 99% cpu 5.479 total
 ==> 2324522934/5.48 == 424,183,017 per second

 time ./bin 13 4
arg 1: 13 == n  [compositions of n]  default=4
arg 2: 4 == s  [number of sorts (s>=1)]  default=2
COMPOSITION_NZ_SORTS2_FIXARRAYS defined.
 ct=976562500
./bin 13 4  2.11s user 0.00s system 99% cpu 2.111 total
 ==> 976562500/2.11 == 462,825,829 per second


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
/// make-target: "1demo DSRC=demo/comb/composition-nz-sorts2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-sorts2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

