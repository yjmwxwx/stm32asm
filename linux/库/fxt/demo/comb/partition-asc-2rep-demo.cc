
#include "comb/partition-asc-2rep.h"

#include "comb/partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions where parts have multiplicity at most 2.
//% Representation as weakly ascending list of parts.
//% Lexicographic order.
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

    partition_asc_2rep P(n);

    ulong ct = 0;


#ifdef TIMING
#ifdef PARTITION_ASC_2REP_FIXARRAYS
    cout << "PARTITION_ASC_2REP_FIXARRAYS is defined" << endl;
#endif
    do  { ++ct; }  while ( P.next() );
#else

//    ulong Z[64];
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

//        { ulong j=m; do { --j; cout << " " << x[j]; } while (j); }  // weakly descending list
        cout << " [" << setw(2) << m << "] ";
//        cout << " d=" << setw(2) << P.durfee_n() << " ";

        P.print("  ");

//        ulong pc = partition_asc_conj(P.data(), m, Z);
//        print_vec_rev("  ", Z, pc);

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
./bin 160  6.72s user 0.00s system 99% cpu 6.725 total
 ==> 1176931746/6.72 == 175,138,652 per second

## gcc 4.8.0:
 time ./bin 160
arg 1: 160 == n  [integer partitions of n]  default=14
arg 2: 0 == aa  [Whether to render as ASCII art]  default=0
 ct=1176931746
./bin 160  7.47s user 0.00s system 99% cpu 7.473 total
 ==> 1176931746/7.47 == 157,554,450 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-2rep-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-2rep-demo.cc DEMOFLAGS=-DTIMING"
/// End:

