
#include "bits/fibrep.h"

#include "bits/print-bin.h"  // print_bin()
#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "bits/bitsperlong.h"

#include "jjassert.h"


//% Fibonacci representations: successive generation in lexicographic order.
//% Cf. OEIS sequence A003714.

// Cf. bits/fibrep-subset-lexrev-demo.cc for subset-lex order.
// Cf. bits/bitfibgray-demo.cc for a gray code.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Number of bits");
    jjassert( n<BITS_PER_LONG );
    bool fq = 1;
    NXARG(fq, "Whether to use increasing order");

    ulong ct = 0;


    if ( fq )  // forward
    {
        const ulong f = 1UL << n;
        ulong t = 0;
        do
        {
#ifndef TIMING
            cout << setw(4) << ct;
            print_bin(":  ", t, n);
            cout << "  " << setw(4) << t; // OEIS sequence A003714
            cout << endl;
            jjassert( is_fibrep(t) );
            jjassert( fibrep2bin(t) == ct );
#endif
            ++ct;
            t = next_fibrep(t);
        }
        while ( t!=f );
    }
    else  // backward
    {
        ulong f = 1UL << n;
        do
        {
            f = prev_fibrep(f);
#ifndef TIMING
            jjassert( is_fibrep(f) );
            cout << setw(4) << ct;
            print_bin(": ", f, n);
            cout << endl;
#endif
            ++ct;
        }
        while ( f );
    }

    cout << "ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 44 1
ct=1836311903
./bin 44 1  10.02s user 0.00s system 100% cpu 10.022 total
 ==> 1836311903/10.02 == 183,264,660 per second

 time ./bin 44 0
ct=1836311903
./bin 44 0  10.82s user 0.03s system 100% cpu 10.841 total
 ==> 1836311903/10.82 == 169,714,593 per second

*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 44 1
ct=1836311903
./bin 44 1  6.71s user 0.00s system 99% cpu 6.713 total
 ==> 1836311903/6.71 == 273,667,943 per second


 time ./bin 44 0
ct=1836311903
./bin 44 0  7.32s user 0.00s system 99% cpu 7.324 total
 ==> 1836311903/7.32 == 250,862,281 per second

*/


/*

BENCHARGS=44 1
BENCHARGS=44 0

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/fibrep2-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/fibrep2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

