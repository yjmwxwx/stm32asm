
#include "comb/mixedradix-subset-lex.h"

#include "comb/comb-print.h"

#include "aux1/copy.h"  // fill()

//#include "comb/subset-lex-compare.h"
//#include "comb/is-young-tab-rgs.h"
//#include "comb/is-schroeder-rgs.h"
//#include "comb/is-catalan-step-rgs.h"
//#include "comb/is-dyck-rgs.h"


#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix numbers in subset-lex order.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Number of digits");

    ulong rr = 4;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "Benchmark: whether to generate in backward order");
    mixedradix_subset_lex M(n, rr);

#else
    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply radix for all digits (rr ignored)");
    if ( argc>3 )  jjassert( argc == (int)n+3 );

    for (ulong i=3;  i<(ulong)argc; ++i)  r[i-3] = strtoul(argv[i], 0, 10);

    mixedradix_subset_lex M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");
    cout << endl;
#endif


    ulong ct = 0;
#ifdef TIMING
    if ( ! bq )
    {
        cout << "forward:" << endl;
        M.first();
        do  { ++ct; }  while ( M.next() );
    }
    else
    {
        cout << "backward:" << endl;
        M.last();
        do  { ++ct; }  while ( M.prev() );
    }

#else

    const ulong *x = M.data();
//    ulong Z[64];
    do
    {
//        if ( M.card() > 5 )  continue;
//        if ( ! is_young_tab_rgs(x, n, Z, 0) )  continue;
//        if ( ! is_schroeder_rgs(x, n, 0) )  continue;  // strange order
//        if ( ! is_catalan_step_rgs(x, n) )  continue;  // strange order
//        if ( ! is_dyck_rgs(x, n) )  continue;

        cout << setw(4) << ct << ":";
        M.print("  ", true );

        print_multi_deltaset_as_set("    ", x, n, true);

#if 0
        int q1, q2;
        if ( ct > 0 )
        {
            q1 = subset_lex_compare(x, n, Z, n);
            jjassert( q1 );
            cout << "  " << (q1==+1 ? '+' : '-');

            q2 = subset_lex_compare(Z, n, x, n);
//            cout << "  " << (q2==+1 ? '+' : '-');

            jjassert( q2 = -q1 );
        }
        for (ulong j=0; j<n; ++j)  Z[j] = x[j];
        if ( ct )  jjassert( q1 == +1 );
#endif

        cout << endl;

        ++ct;
    }
    while ( M.next() );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)


 time ./bin 30 2 0 ## binary is worst case
forward:
 ct=1073741824
./bin 30 2 0  3.99s user 0.00s system 99% cpu 3.989 total
 ==> 1073741824/3.99 == 269,108,226 per second

 time ./bin 30 2 1 ## binary is worst case
backward:
 ct=1073741824
./bin 30 2 1  3.08s user 0.00s system 99% cpu 3.085 total
 ==> 1073741824/3.08 == 348,617,475 per second


 time ./bin 19 3 0
forward:
 ct=1162261467
./bin 19 3 0  2.51s user 0.00s system 99% cpu 2.509 total
 ==> 1162261467/2.51 == 463,052,377 per second

 time ./bin 19 3 1
backward:
 ct=1162261467
./bin 19 3 1  1.85s user 0.00s system 99% cpu 1.849 total
 ==> 1162261467/1.85 == 628,249,441 per second


 time ./bin 16 4 0
forward:
 ct=4294967296
./bin 16 4 0  7.62s user 0.00s system 99% cpu 7.620 total
 ==> 4294967296/7.62 == 563,644,002 per second

 time ./bin 16 4 1
backward:
 ct=4294967296
./bin 16 4 1  6.29s user 0.00s system 99% cpu 6.291 total
 ==> 4294967296/6.29 == 682,824,689 per second


 time ./bin 10 8 0
forward:
 ct=1073741824
./bin 10 8 0  1.95s user 0.00s system 99% cpu 1.953 total
 ==> 1073741824/1.95 == 550,636,832 per second

 time ./bin 10 8 1
backward:
 ct=1073741824
./bin 10 8 1  1.19s user 0.00s system 99% cpu 1.188 total
 ==> 1073741824/1.19 == 902,304,053 per second


 time ./bin 8 16 0
forward:
 ct=4294967296
./bin 8 16 0  8.76s user 0.00s system 99% cpu 8.764 total
 ==> 4294967296/8.76 == 490,293,070 per second

 time ./bin 8 16 1
backward:
 ct=4294967296
./bin 8 16 1  5.72s user 0.00s system 99% cpu 5.718 total
 ==> 4294967296/5.72 == 750,868,408  per second



 time ./bin 12 0 0
forward:
 ct=6227020800
./bin 12 0 0  15.72s user 0.00s system 99% cpu 15.723 total
 ==> 13!/15.72 == 396,120,916 per second

 time ./bin 12 0 1
backward:
 ct=6227020800
./bin 12 0 1  13.28s user 0.00s system 99% cpu 13.286 total
 ==> 13!/13.28 == 468,902,168 per second


 time ./bin 12 1 0
forward:
 ct=6227020800
./bin 12 1 0  10.56s user 0.00s system 99% cpu 10.563 total
 ==> 13!/10.56 == 589,680,000 per second

 time ./bin 12 1 1
backward:
 ct=6227020800
./bin 12 1 1  6.51s user 0.00s system 99% cpu 6.515 total
 ==> 13!/6.51 == 956,531,612 per second

*/


/*

BENCHARGS=30 2 0
BENCHARGS=30 2 1
BENCHARGS=19 3 0
BENCHARGS=19 3 1
BENCHARGS=16 4 0
BENCHARGS=16 4 1
BENCHARGS=10 8 0
BENCHARGS=10 8 1
BENCHARGS=8 16 0
BENCHARGS=8 16 1

BENCHARGS=12 0 0
BENCHARGS=12 0 1
BENCHARGS=12 1 0
BENCHARGS=12 1 1

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

