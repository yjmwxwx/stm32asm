
#include "bits/bitlex.h"

#include "bits/print-bin.h"

#include "fxttypes.h"
#include "fxtio.h"
//#include "bits/bitsperlong.h"

//#include "bits/graycode.h"
//#include "bits/revgraycode.h"
//#include "bits/bitcount.h"
//#include "bits/bitlow.h"

#include "nextarg.h"


//% Generating binary words in subset-lexrev order.

// Cf. bits/bit-sl-gray-demo.cc for the corresponding Gray code.
// Cf. comb/mixedradix-subset-lex-demo.cc for subset-lex order for mixed radix numbers
// Cf. bits/fibrep-subset-lexrev-demo.cc for Fibonacci words in subset-lex order

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "n-bit binary words (n>=1)");
    const ulong mm = 1UL << (n-1);  // last
    bool bq = 0;
    NXARG(bq, "Whether to generate in backward order");


#ifndef TIMING

    ulong x = ( bq ? 0 : mm );  // first word
    ulong xe = x ^ mm;  // last word
    ulong ct = 0;
    while ( true )
    {
        ++ct;
        cout  << setw(4) << ct << ":";
        print_bin("  ", x, n);
        cout << "  = " << setw(4) << x;  // A108918
//        cout << "   b=" << setw(2) << bit_count(x);  // A100661
        print_bit_set("    ", x, n);
        // index of the lowest set bit of x is sequence A082850 - 1

        cout << endl;

        if  ( x == xe )  break;

        if ( bq )  x = prev_lexrev(x);
        else       x = next_lexrev(x);
    }

#else  // TIMING

    if ( !bq )
    {
        cout << "forward:" << endl;
        ulong x = mm;
        do  { x = next_lexrev(x); }  while ( x!=0 );
    }
    else
    {
        cout << "backward:" << endl;
        ulong x = 0;
        do  { x = prev_lexrev(x); }  while ( x!=mm );
    }

    cout << " ct=" << (1UL<<n) << endl;

#endif  // TIMING

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 32 0
arg 1: 32 == n  [n-bit binary words]  default=5
arg 2: 0 == bq  [Whether to also print backwards list]  default=0
forward:
./bin 32 0  15.66s user 0.03s system 100% cpu 15.689 total
 ==> 2^32/15.66 == 274,263,556 per second

 time ./bin 32 1
arg 1: 32 == n  [n-bit binary words]  default=5
arg 2: 1 == bq  [Whether to also print backwards list]  default=0
backward:
./bin 32 1  16.93s user 0.00s system 99% cpu 16.937 total
 ==> 2^32/16.93 == 253,689,739 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32 0
forward:
./bin 32 0  10.71s user 0.00s system 99% cpu 10.717 total
 ==> 2^32/10.71 == 401,024,023 per second

 time ./bin 32 1
backward:
./bin 32 1  9.56s user 0.00s system 99% cpu 9.566 total
 ==> 2^32/9.56 == 449,264,361 per second
*/

/*
Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)

GCC 4.9.2

./bin 32 0  6.61s user 0.00s system 99% cpu 6.622 total
 ==> 2^32/6.61 == 649,768,123 per second

./bin 32 1  5.40s user 0.00s system 99% cpu 5.407 total
 ==> 2^32/5.40 == 795,364,314 per second

*/

/*
BENCHARGS=32 0
BENCHARGS=32 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitlex-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitlex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

