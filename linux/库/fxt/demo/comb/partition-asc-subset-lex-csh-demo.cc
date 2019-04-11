
#include "comb/partition-asc-subset-lex-csh.h"

#include "comb/partition-conj.h"

#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Partitions of n into positive parts, cyclically shifted subset-lex order.
//% Loopless algorithm.

// Cf. comb/partition-asc-subset-lex-demo.cc for partitions in subset-lex order.
// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts.
// Cf. comb/composition-nz-subset-lex-demo.cc for compositions into positive parts in subset-lex order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 11;
    NXARG(n, "partitions of n");

    partition_asc_subset_lex_csh P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef PARTITION_ASC_SUBSET_LEX_CSH_FIXARRAYS
    cout << "PARTITION_ASC_SUBSET_LEX_CSH_FIXARRAYS defined." << endl;
#endif
    do  { ++ct; }  while ( P.next() );
#else // TIMING

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    ulong m = P.num_parts();
    do
    {
#if 0  // only into powers of 2, cf. A018819
        const ulong *x = P.data();
        bool q = true;
        for (ulong j = 0; j<m; ++j)
        { ulong v=x[j];  if ( !!(v & (v-1)) )  { q=false;  break; } }
        if ( !q )  continue;
#endif
#if 0  // only into self-conjugate partitions
        if ( !partition_asc_is_self_conj( P.data(), m ) )  continue;
#endif
#if 0  // multiplicity <= d:
        // d=1 == > A000726 (no parts multiples of 2)
        // d=2 == > A000726 (no parts multiples of 3)
        // d=3 == > A001935 (no parts multiples of 4)
        // d=4 == > A035959 (no parts multiples of 5)
        // d=5 == > A219601 (no parts multiples of 6)
        // d=6 == > A035985 (no parts multiples of 7)
        const ulong *x = P.data();
        bool q = true;
        const ulong d = 22;
        for (ulong j=d; j<m; ++j)
            if ( x[j]==x[j-d] )  { q=false;  break; }
        if ( !q )  continue;
#endif

        cout << setw(4) << ct << ":";

        cout << "  [" << setw(2) << m << "]";

        P.print("  ");


        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
//            P.print_conj_aa();
            cout << endl;
            cout << endl;
        }

        ++ct;

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

# gcc 4.5.0:
 time ./bin 110
arg 1: 110 == n  [partitions of n]  default=10
  ct=607163746
./bin 110  3.26s user 0.00s system 99% cpu 3.263 total
 ==> 607163746/3.26 == 186,246,547 per second

 time ./bin 110
arg 1: 110 == n  [partitions of n]  default=10
PARTITION_ASC_SUBSET_LEX_CSH_FIXARRAYS defined.
  ct=607163746
./bin 110  2.72s user 0.00s system 99% cpu 2.723 total
 ==> 607163746/2.72 == 223,221,965 per second


# gcc 4.8.0:
 time ./bin 110
arg 1: 110 == n  [partitions of n]  default=10
 ct=607163746
./bin 110  2.75s user 0.00s system 99% cpu 2.754 total
 ==> 607163746/2.75 == 220,786,816 per second

 time ./bin 110
arg 1: 110 == n  [partitions of n]  default=10
PARTITION_ASC_SUBSET_LEX_CSH_FIXARRAYS defined.
 ct=607163746
./bin 110  2.65s user 0.00s system 99% cpu 2.653 total
 ==> 607163746/2.65 == 229,118,394 per second
*/

/*
BENCHARGS=110
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-subset-lex-csh-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-subset-lex-csh-demo.cc DEMOFLAGS=-DTIMING"
/// End:

