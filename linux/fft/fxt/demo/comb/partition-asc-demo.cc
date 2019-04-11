
#include "comb/partition-asc.h"

#include "comb/partition-conj.h"
#include "comb/print-partition-conj.h"

#include "comb/comb-print.h"

#include "comb/arith-3-progression.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions as weakly ascending list of parts.
//% Lexicographic order.
//% Cf. OEIS sequence A000041.

// Cf. comb/partition-desc-demo.cc for partitions as weakly descending lists
// Cf. comb/partition-asc-subset-lex-demo.cc for partitions in subset-lex order
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts
// Cf. comb/mpartition-demo.cc for partitions into m parts
// Cf. comb/partition-demo.cc for partitions given as multiplicities of parts
// Cf. comb/composition-nz-demo.cc for all compositions as list of parts

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 11;
    NXARG(n, "integer partitions of n");

    partition_asc P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef PARTITION_ASC_FIXARRAYS
    cout << "PARTITION_ASC_FIXARRAYS is defined" << endl;
#endif
    bool bq = false;
    NXARG(bq, "With benchmark: whether to generate in backward order");
    if ( ! bq )
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


    ulong m = P.num_parts();
    do
    {
#if 0  // only self-conjugate partitions
        if ( !partition_asc_is_self_conj( P.data(), m ) )  continue;
#endif
#if 0  // bounding box
        if ( m > 7 )  continue;
        if ( P.last_part() > 7 )  continue;
#endif
#if 0  // A002865, A229816, A229863
        { bool q = 1;
            if ( P.first_part() == 1 )  goto OK;
            for (ulong j=0; j<m; ++j)
                if ( P.data()[j]==m )  { q=0; break; }
            if ( q==0 )  continue;
        } OK:
#endif

#if 0
        { ulong c = 0;
            for (ulong j=0; j<m; ++j)  c += ( (P.data()[j] & 1) == 0 );
//            if ( (c & 1) == 0 )  continue;  // odd num of even parts: A000701
            if ( (c & 1) == 1 )  continue;  // even num of even parts: A046682
        }
#endif
#if 0
        { bool q = 1;
            const ulong d = 3; // max diff <= d: d-smooth
            // A000005 (d=0), A034296 (d=1), A224956 (d=2), A238863
            // (d=3), A238864 (d=4), A238865 (d=5), A238866 (d=6),
            // A238867 (d=7), A238868 (d=8), A238868 (d=9)
            for (ulong j=1; j<m; ++j)
                if ( P.data()[j] - P.data()[j-1] > d )
                { q=0; break; }
            if ( ! q )  continue;
        }
#endif

#if 0
        { const ulong d = 2; // max diff == d
            // A000005 (d=0), A237665 (d=1), A000000 (d=2)
            ulong md = 0;
            for (ulong j=1; j<m; ++j)
            {
                ulong t =  P.data()[j] - P.data()[j-1];
                if ( t > md )  md = t;
            }
            if ( md != d )  continue;
        }
#endif

#if 0  // Avoiding 3-term arithmetic progressions:
//        if ( 0 != test_arith_3_progression(P.data(), m) )  continue;  // A238571
//        if ( 0 != test_arith_3_progression_eqd(P.data(), m) )  continue;  // A238433
        if ( 0 != test_arith_3_progression_consec(P.data(), m) )  continue;  // A238424
#endif
#if 0
        { // gap-free: A000009
            ulong w = 0;
            for (ulong j=0; j<m; ++j)  w |= (1UL << P.data()[j]);
            w >>= 1;  w += 1;
            if ( w != ( w & -w ) )  continue;
        }
#endif
#if 0
        // largest part p at most once, p-1 at most twice, p-2 at most thrice, ...
        // A244393, cf. A244395
        { const ulong *x = P.data();
            ulong st[64];
            for (ulong k=0; k<64; ++k)  st[k] = 0;
            for (ulong k=0; k<m; ++k)  st[x[k]] += 1;
            ulong p = x[m - 1]; // p is the largest part
            bool q = true;
            for (ulong i=1; p!=0; --p,++i)  if ( st[p] > i )  { q=false; break; }
            if ( ! q )  continue;
        }
#endif
#if 0  // A274174
        {
            ulong f = 1, k = 1, p = P.data()[0];
            for (ulong j=1; j<m; ++j)
                if ( P.data()[j] != p )  { ++k; f *= k; p = P.data()[j]; }
            ct += f;
        }
        --ct;
#endif
        ++ct;

#if 1  // allow/suppress printing

        cout << setw(4) << ct << ": ";

//        { ulong j=m; do { --j; cout << " " << x[j]; } while (j); }  // weakly descending list
        cout << " [" << setw(2) << m << "] ";
//        cout << " d=" << setw(2) << P.durfee_n() << " ";

//        cout << " [" << setw(2) << n-m << "] ";  // A218829 (recycled)
//        cout << " [" << setw(2) << P.data()[m-1] << "] ";  // A218735 (recycled)


        P.print("  ");

//        print_partition_asc_conj("    ", P.data(), m);

        if ( aa )  // ASCII art
        {
            P.print_aa();
//            P.print_conj_aa();
            cout << endl;
            cout << endl;
        }

        cout << endl;

        jjassert( P.OK() );
#endif  // allow/suppress printing
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

gcc 4.5.0:
 time ./bin 110
arg 1: 110 == n  [integer partitions of n]  default=10
  ct=607163746
./bin 110  3.39s user 0.00s system 99% cpu 3.389 total
 ==> 607163746/3.39 == 179,104,349 per second


With PARTITION_ASC_FIXARRAYS:
 time ./bin 110
arg 1: 110 == n  [integer partitions of n]  default=10
PARTITION_ASC_FIXARRAYS is defined
  ct=607163746
./bin 110  2.88s user 0.00s system 99% cpu 2.877 total
 ==> 607163746/2.88 == 210,820,745 per second



gcc 4.8.0:

 time ./bin 110 0
arg 1: 110 == n  [integer partitions of n]  default=10
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
 ct=607163746
./bin 110  2.80s user 0.00s system 99% cpu 2.805 total
 ==> 607163746/2.80 == 216,844,195 per second

 time ./bin 110 1
arg 1: 110 == n  [integer partitions of n]  default=10
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
 ct=607163746
./bin 110 1  2.90s user 0.00s system 99% cpu 2.903 total
 ==> 607163746/2.90 == 209,366,808 per second


 time ./bin 110 0
arg 1: 110 == n  [integer partitions of n]  default=10
PARTITION_ASC_FIXARRAYS is defined
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
 ct=607163746
./bin 110 0  3.01s user 0.00s system 99% cpu 3.011 total
 ==> 607163746/3.01 == 201,715,530 per second

 time ./bin 110 1
arg 1: 110 == n  [integer partitions of n]  default=10
PARTITION_ASC_FIXARRAYS is defined
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
 ct=607163746
./bin 110 1  3.16s user 0.00s system 99% cpu 3.167 total
 ==> 607163746/3.16 == 192,140,425 per second
*/

/*
BENCHARGS=110
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

