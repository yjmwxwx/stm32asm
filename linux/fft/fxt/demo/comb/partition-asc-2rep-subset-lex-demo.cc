
#include "comb/partition-asc-2rep-subset-lex.h"

#include "comb/partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions where parts have multiplicity at most 2.
//% Representation as weakly ascending list of parts.
//% Subset-lex order.
//% Loopless algorithm.
//% Cf. OEIS sequence A000726.

// Cf. comb/partition-asc-demo.cc for all partitions
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 14;
    NXARG(n, "integer partitions of n");

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    partition_asc_2rep_subset_lex P(n);

    ulong ct = 0;


#ifdef TIMING
#ifdef PARTITION_ASC_2REP_SUBSET_LEX_FIXARRAYS
    cout << "PARTITION_ASC_2REP_SUBSET_LEX_FIXARRAYS is defined" << endl;
#endif
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
    do
    {
#if 0  // only into odd parts
        const ulong *x = P.data();
        bool q = true;
        for (ulong j = 0; j<m; ++j)
            if ( 0==(x[j] & 1) )  { q=false; break; }
        if ( !q )  continue;
#endif
#if 0  // only into self-conjugate partitions
        if ( !partition_asc_is_self_conj( P.data(), m ) )  continue;
#endif

        ++ct;
        cout << setw(4) << ct << ": ";

        P.print("  ");

        if ( aa )  // ASCII art
        {
            P.print_aa();
//            P.print_conj_aa();
            cout << endl;
            cout << endl;
        }

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

## gcc 4.5.0:
 time ./bin 160
arg 1: 160 == n  [integer partitions of n]  default=14
arg 2: 0 == aa  [Whether to render as ASCII art]  default=0
 ct=1176931746
./bin 160  5.22s user 0.00s system 99% cpu 5.224 total
 ==> 1176931746/5.22 == 225,465,851 per second

 time ./bin 160
arg 1: 160 == n  [integer partitions of n]  default=14
arg 2: 0 == aa  [Whether to render as ASCII art]  default=0
PARTITION_ASC_2REP_SUBSET_LEX_FIXARRAYS is defined
 ct=1176931746
./bin 160  4.33s user 0.00s system 99% cpu 4.326 total
 ==> 1176931746/4.33 == 271,808,717 per second


## gcc 4.8.0:
 time ./bin 160
arg 1: 160 == n  [integer partitions of n]  default=14
arg 2: 0 == aa  [Whether to render as ASCII art]  default=0
 ct=1176931746
./bin 160  4.90s user 0.00s system 99% cpu 4.903 total
 ==> 1176931746/4.90 == 240,190,152 per second

 time ./bin 160
arg 1: 160 == n  [integer partitions of n]  default=14
arg 2: 0 == aa  [Whether to render as ASCII art]  default=0
PARTITION_ASC_2REP_SUBSET_LEX_FIXARRAYS is defined
 ct=1176931746
./bin 160  4.63s user 0.00s system 99% cpu 4.637 total
 ==> 1176931746/4.63 == 254,196,921 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-2rep-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-2rep-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

