
#include "comb/composition-nz-sorts2-pp.h"

#include "sort/sort.h"  // is_sorted()

#include "fxtio.h"

#include "aux1/copy.h"  // fill()
#include "fxtalloca.h"

#include "fxttypes.h"
#include "nextarg.h"

#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Compositions of n into positive parts of s[k] sorts for part (size) k.
//% Lexicographic order: major order by parts, minor by sorts, where
//% comparison proceeds as part1, sort1; part2, sort2; part3, sort3, etc.
//% Loopless algorithm.
//% Cf. OEIS sequence A088305
//%   compositions of n into one sort of 1's, two sorts of 2's, ..., k sorts of k's.
//% Cf. OEIS sequences (compositions of n into (all) parts of s kinds):
//% A011782 (s=1), A025192 (s=2), A002001 (s=3), A005054 (s=4),
//% A052934 (s=5), A055272 (s=6), A055274 (s=7), and A055275 (s=8).

// Cf. comb/composition-nz-sorts2-demo.cc (lex: major by parts, minor by sorts)
// Cf. comb/composition-nz-sorts-demo.cc (lex: major by sorts, minor by parts)


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "compositions of n");

    ulong ns = 0;
    NXARG(ns, "Number of sorts for parts by size (0==>1,2,3,4,...,n)");

    ulong ct = 0;

#ifdef TIMING
    composition_nz_sorts2_pp P(n, ns);
#ifdef COMPOSITION_NZ_SORTS2_PP_FIXARRAYS
    cout << "COMPOSITION_NZ_SORTS2_PP_FIXARRAYS defined." << endl;
#endif
    P.first();
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ALLOCA(ulong, vns, n);
    fill(vns, n, ns);
    RESTARGS("Optionally supply number of sorts for all part sizes (ns ignored)");
    if ( argc>3 )  jjassert( argc == (int)n+3 );
    for (ulong k=3;  k<(ulong)argc; ++k)  vns[k-3] = strtoul(argv[k], 0, 10);

    composition_nz_sorts2_pp P(n, ns, (argc>3? vns:0) );

    ulong m = P.num_parts();
    do
    {
#if 0  // limit max sort (with ns=0):
        const ulong mns = 5;
        // 1 ==> A011782 (1 - x) / (1 - 2*x) == 1/(1 - x/(1-x))
        // 2 ==> A001333 (1 - x) / (1 - 2*x - x^2) == 1 / (1 - (x+x^2)/(1 - x)) == 1/(1 - x*(1-x^2)/(1-x)^2)
        // 3 ==> A077997 (1-x)/(1-2*x-x^2-x^3) == 1 / (1 - (x+x^2+x^3)/(1 - x)) == 1/(1 - x*(1-x^3)/(1-x)^2)
        // 4 ==> A190139 (1-x)/(1-2*x-x^2-x^3-x^4) == 1 / (1 - (x+x^2+x^3+x^4)/(1 - x)) == 1/(1 - x*(1-x^4)/(1-x)^2)
        // 5 ==> A000000 (1-x)/(1-2*x-x^2-x^3-x^4-x^5) == ... == 1/(1 - x*(1-x^5)/(1-x)^2)
        // infinity ==> A088305 (cf. A001906) (1-x)^2/(1-3*x+x^2) == 1/(1 - x/(1-x)^2)
        const ulong *S = P.sdata();
        ulong j;
        for (j=0; j<m; ++j)
            if ( S[j] >= mns )  break;
        if ( j != m )  continue;
#endif
#if 0
        const ulong *A = P.data();
        const ulong *S = P.sdata();
//        if ( ! is_sorted(A, m) )   continue; // partitions, ascending
//        if ( ! is_sorted_desc(A, m) )   continue;  // partitions, descending
        if ( ! is_sorted(S, m) )   continue; // 2 sorts: A045623;  1,2,3,... sorts: A227682
//        if ( ! P.sorts_in_runs_sorted(1) )  continue; // 2 sorts: A052945; 1,2,3,... sorts: A000000
        // partitions: A000219 (with args n 0), compositions: A000000
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

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 31 1
arg 1: 31 == n  [compositions of n]  default=5
arg 2: 1 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
 ct=1073741824
./bin 31 1  3.62s user 0.00s system 99% cpu 3.625 total
 ==> 1073741824/3.62 == 296,613,763 per second

 time ./bin 20 2
arg 1: 20 == n  [compositions of n]  default=5
arg 2: 2 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
 ct=2324522934
./bin 20 2  6.93s user 0.00s system 99% cpu 6.937 total
 ==> 2324522934/6.93 == 335,428,994 per second

 time ./bin 13 4
arg 1: 13 == n  [compositions of n]  default=5
arg 2: 4 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
 ct=976562500
./bin 13 4  2.56s user 0.00s system 99% cpu 2.563 total
 ==> 976562500/2.56 == 381,469,726 per second



 time ./bin 31 1
arg 1: 31 == n  [compositions of n]  default=5
arg 2: 1 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
COMPOSITION_NZ_SORTS2_PP_FIXARRAYS defined.
 ct=1073741824
./bin 31 1  3.79s user 0.00s system 99% cpu 3.793 total
 ==> 1073741824/3.79 == 283,309,188 per second

 time ./bin 20 2
arg 1: 20 == n  [compositions of n]  default=5
arg 2: 2 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
COMPOSITION_NZ_SORTS2_PP_FIXARRAYS defined.
 ct=2324522934
./bin 20 2  6.56s user 0.00s system 99% cpu 6.563 total
 ==> 2324522934/6.56 == 354,348,008 per second

 time ./bin 13 4
arg 1: 13 == n  [compositions of n]  default=5
arg 2: 4 == ns  [Number of sorts for parts by size (0==>1,2,3,4,...,n)]  default=0
COMPOSITION_NZ_SORTS2_PP_FIXARRAYS defined.
 ct=976562500
./bin 13 4  2.33s user 0.00s system 99% cpu 2.331 total
 ==> 976562500/2.33 == 419,125,536 per second

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
/// make-target: "1demo DSRC=demo/comb/composition-nz-sorts2-pp-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-sorts2-pp-demo.cc DEMOFLAGS=-DTIMING"
/// End:

