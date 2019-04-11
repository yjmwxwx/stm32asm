
#include "comb/composition-nz.h"
#include "comb/composition-nz-rank.h"

#include "comb/composition-nz-conj.h"
#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "comb/is-unimodal.h"
#include "comb/is-smooth.h"
#include "comb/arith-3-progression.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts.

// Cf. comb/composition-nz-rl-demo.cc for compositions in run-length order
// Cf. comb/composition-nz-subset-lex-demo.cc for compositions in subset-lex order

// Cf. comb/composition-nz-max-demo.cc for compositions into parts <= mx
// Cf. comb/composition-nz-min-demo.cc for compositions into parts >= mi

// Cf. comb/composition-nz-left-smooth-demo.cc for left-smooth compositions
// Cf. comb/composition-nz-smooth-demo.cc for smooth compositions
// Cf. comb/composition-nz-max-demo.cc for compositions into parts <= mx

// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/partition-desc-demo.cc for partitions as weakly descending list of parts

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "compositions of n");

#ifndef TIMING
    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");
#endif

    composition_nz P(n);

    ulong ct = 0;
//    ulong ctx = 0;

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "With benchmark: whether to generate in backward order");
#ifdef COMPOSITION_NZ_FIXARRAYS
    cout << "COMPOSITION_NZ_FIXARRAYS defined." << endl;
#endif
    if ( !bq )
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

    ulong m = P.num_parts();
//    ulong C[64];
    do
    {
#if 0  // avoiding part P:
        //  P=1 ==> A000045,  P=2 ==> A005251,  P=3 ==> A049856,
        //  P=4 ==> A108758,  P=5 ==> A000000,  P=6 ==> A000000
        const ulong *x = P.data();
        bool q = true;
        for (ulong j=0; j<m; ++j)
            if ( x[j] == 1 )  { q=false; break; }
        if ( !q )  continue;
#endif
#if 0
//        if ( P.last_part() != 1 )  continue;
//        if ( P.data()[0] != 1 )  continue;
        if ( ! is_smooth(P.data(), m, 1) )  continue;  // i-smooth A034297
//        if ( ! is_left_smooth(P.data(), m) )  continue;  // left-smooth: A005169
        if ( ! is_weakly_unimodal(P.data(), m) )  continue;  // A001523
        // with i-smoothness: A238871
        // with smoothness: A001522
//        if ( 0==(1UL & P.last_part()) )  continue;  // A001045
//        if ( ! is_sorted_desc(P.data(), m) )  continue;  // same as partition_desc
//        if ( ! is_sorted(P.data(), m) )  continue;  // same as partition_asc_subset_lex
#endif
#if 0
        const ulong *x = P.data();
        bool q = true;
//        for (ulong j=1; j<m; ++j)  // A063978
//            if ( x[j] < j+1 )  { q=false; break; }
//        for (ulong j=0; j<m; ++j)  // A219282
//            if ( x[j] < j+1 )  { q=false; break; }
//        for (ulong j=0; j<m; ++j)  // A000000
//            if ( x[j] == j+1 )  { q=false; break; }
        for (ulong j=0; j<m; ++j)  // A238874
            if ( x[j] <= j+1 )  { q=false; break; }
        if ( !q )  continue;
#endif

#if 0  // Avoiding 3-term arithmetic progressions:
//        if ( 0 != test_arith_3_progression(P.data(), m) )  continue;  // A238569
//        if ( 0 != test_arith_3_progression_eqd(P.data(), m) )  continue;  // A238432
        if ( 0 != test_arith_3_progression_consec(P.data(), m) )  continue;  // A238423

#endif
#if 0  // Avoiding x, x+1, x+2, or avoiding 123:
        const ulong *x = P.data();
        bool q = true;
        for (ulong j=2; j<m; ++j)
            if ( (x[j] == x[j-1]+1) && (x[j-1] == x[j-2]+1) ) // A000000; A000000
//            if ( (x[j-2]==1) && (x[j-1]==2)  && (x[j]==3) ) // A239941; A006980
            { q=false; break; }
//        if ( !q )  continue;
        if ( q )  continue;
#endif

#if 1  // allow/suppress printing

//        cout << P.data()[m-2] << ", ";  continue;  // A089309

        cout << setw(4) << ct << ":";
//        cout << "[" << setw(2) << ct << "]";

        const ulong r = P.rank();
        print_bin("  ", r, (n>1 ? n-1 : 1) );

//        cout << "  [" << setw(2) << m << "]";


//        cout << "[" << n-m << "]  ";  // OEIS sequence A000120
//        cout << " [" << setw(2) << P.last_part() << "] ";  // A001511
        P.print("  ");

//        ulong nc = composition_nz_conj(P.data(), m, C);
//        print_vec("        ", C, nc);

        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
            cout << endl;
            cout << endl;
        }

#if 1  // increment ct below these tests
        jjassert( r == ct );
        P.unrank(r);  jjassert( r == P.rank() );
        jjassert( r == composition_nz_rank(P.data(), m) );
#endif

        jjassert( P.OK() );

#endif  // allow/suppress printing

        ++ct;
//        for (ulong j=0; j<m; ++j)  ctx += (P.a_[1+j]%2);
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;  // A011782
//    cout << " ctx=" << ctx << endl;  // A059570

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 33 0
arg 1: 33 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
  ct=4294967296
./bin 33 0  9.99s user 0.00s system 99% cpu 9.995 total
 ==> 4294967296/9.99 == 429,926,656 per second

 time ./bin 33 1
arg 1: 33 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
  ct=4294967296
./bin 33 1  15.26s user 0.00s system 99% cpu 15.261 total
 ==> 4294967296/15.26 == 281,452,640 per second


With COMPOSITION_NZ_FIXARRAYS defined:

 time ./bin 33 0
arg 1: 33 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_FIXARRAYS defined.
forward:
  ct=4294967296
./bin 33 0  7.24s user 0.00s system 99% cpu 7.246 total
 ==> 4294967296/7.24 == 593,227,527 per second

 time ./bin 33 1
arg 1: 33 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_FIXARRAYS defined.
backward:
  ct=4294967296
./bin 33 1  15.50s user 0.00s system 99% cpu 15.505 total
 ==> 4294967296/15.50 == 277,094,664 per second

*/

/*
BENCHARGS=33 0
BENCHARGS=33 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-demo.cc DEMOFLAGS=-DTIMING"
/// End:

