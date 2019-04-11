
#include "comb/binary-sl-gray.h"

#include "bits/print-bin.h"
#include "ds/bitarray.h"

//#include "comb/composition-nz-rank.h"
//#include "comb/composition-nz-conj.h"


#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"


//% Binary numbers in a minimal-change order
//% related so subset-lex order ("SL-Gray" order).
//% Cf. OEIS sequence A217262.

// Cf. comb/mixedradix-sl-gray-demo.cc for the general case.
// Cf. bits/bit-sl-gray-demo.cc for generation in a binary word.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Number of digits");
//    jjassert( n>=1 );

    binary_sl_gray M(n);
#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "Benchmark: whether to generate in backward order");
#else
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

//    M.last();
    do
    {
        cout << setw(4) << ct << ":";
        M.print("  ", true );
        cout << "  ";

        print_bin("    ", 1UL << (n-1 - M.pos()), (n ? n : 1) );

        // position and direction of change:
        cout << "  " << M.pos();
        cout << "  " << (M.dir() > 0 ? '+' : '-');

        // internal data (track and direction):
        cout << "    " << M.tr_ << "  " << (M.dt_ == 1 ?  '+' : '-');

//        print_bin("    ", ct, n);


        // Print set:
        print_deltaset_as_set("    ", M.data(), n, false );
//        print_multi_deltaset_as_set("    ", M.data(), n, false );

        cout << endl;

#if 1
        jjassert( ct == M.rank() );  // test rank()
        M.unrank(ct);  jjassert( ct == M.rank() );  // test unrank()
#endif
        ++ct;
    }
    while ( M.next() );
//    while ( M.prev() );


#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 0
forward:
 ct=1073741824
./bin 30 0  2.50s user 0.00s system 99% cpu 2.499 total
 ==> 1073741824/2.50 == 429,496,729 per second


 time ./bin 30 1
backward:
 ct=1073741824
./bin 30 1  2.80s user 0.00s system 99% cpu 2.806 total
 ==> 1073741824/2.80 == 383,479,222 per second


GCC 4.9.0:

 time ./bin 30 0
arg 1: 30 == n  [Number of digits]  default=6
arg 2: 0 == bq  [Benchmark: whether to generate in backward order]  default=0
forward:
 ct=1073741824
./bin 30 0  2.64s user 0.00s system 99% cpu 2.638 total
 ==> 1073741824/2.64 == 406,720,387 per second

 time ./bin 30 1
arg 1: 30 == n  [Number of digits]  default=6
arg 2: 1 == bq  [Benchmark: whether to generate in backward order]  default=0
backward:
 ct=1073741824
./bin 30 1  2.66s user 0.00s system 99% cpu 2.664 total
 ==> 1073741824/2.66 == 403,662,339 per second

*/


/*

BENCHARGS=30 0
BENCHARGS=30 1

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/binary-sl-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/binary-sl-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

