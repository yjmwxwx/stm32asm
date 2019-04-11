
#include "comb/partition-asc-subset-lex.h"

#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//#include "comb/partition-conj.h"
//#include "comb/is-nonsquashing.h"

//% Partitions of n into positive parts as ascending list of parts.
//% Subset-lex order.
//% Loopless algorithm.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503


// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/composition-nz-subset-lex-demo.cc for compositions into positive parts in subset-lex order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 11;
    NXARG(n, "partitions of n");

    partition_asc_subset_lex P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef PARTITION_ASC_SUBSET_LEX_FIXARRAYS
    cout << "PARTITION_ASC_SUBSET_LEX_FIXARRAYS defined." << endl;
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
//        if ( !partition_asc_is_self_conj( P.data(), m ) )  continue; // lex order
//        if ( !is_nonsquashing_asc( P.data(), m ) )  continue;
        if ( !is_strongly_increasing( P.data(), m ) )  continue;
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

# GCC 4.9.0:

 time ./bin 110
arg 1: 110 == n  [partitions of n]  default=11
 ct=607163746
./bin 110  2.59s user 0.00s system 99% cpu 2.592 total
 ==> 607163746/2.59 == 234,426,156 per second

 time ./bin 110
arg 1: 110 == n  [partitions of n]  default=11
PARTITION_ASC_SUBSET_LEX_FIXARRAYS defined.
 ct=607163746
./bin 110  2.57s user 0.00s system 99% cpu 2.576 total
 ==> 607163746/2.57 == 236,250,484 per second
*/

/*
BENCHARGS=110
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:
