
#include "bits/bitsubset.h"

#include "bits/print-bin.h"
#include "bits/bit2pow.h"  // ld()

#include "bits/bitcount.h"  // for timing

#include "fxttypes.h"
#include "fxtio.h"

#include "nextarg.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Generating all subsets of a bitset.


//#define TIMING  // uncomment to disable printing

const char *vv[] =
{
    "00011010",
    "00010000",
    "00001111",
    "01001001",
    "00000000"
};
// -------------------------

#define CHECK() { ulong w = S.current();  S.prev();  S.next();  jjassert( w==S.current() ); }


void
show_subsets(ulong v)
{
    bit_subset S(v);
//    cout << endl;
//    cout << "v=" << v;
//    print_bin( " == ", v, ld(v)+1, "01");
    print_bin("V ", S.full_set(), 8);  cout << endl;

    print_bin("U ", S.current(), 8);  cout << endl;
    do
    {
        print_bin("  ", S.next(), 8);  cout << endl;
        CHECK();
    }
    while ( S.current() );

    CHECK();

    cout << "----" << endl;
    print_bin("U ", S.current(), 8);  cout << endl;
    do
    {
        print_bin("  ", S.prev(), 8);  cout << endl;
        CHECK();
    }
    while ( S.current() );

    cout << endl;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong w = 0;
    NXARG(w, "word whose subsets are shown (0==> some default words)");

#ifdef TIMING
    bool dir = 0;
    NXARG(dir, "With benchmark: whether to go backwards");
    bit_subset S(w);
    if ( !dir )
    {
        cout << "forward:" << endl;
        do { S.next(); }  while ( S.current() );
    }
    else
    {
        cout << "backward:" << endl;
        S.last();
        do { S.prev(); }  while ( S.current() );
    }

    cout << "ct=" << (1UL<<bit_count(w)) << endl;

#else

    if ( w )  show_subsets(w);
    else
    {
        for (ulong i=0; i<sizeof(vv)/sizeof(vv[0]); ++i)
        {
            ulong v = strtoul(vv[i], 0, 2);
            show_subsets(v);
        }
    }
#endif

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 0xffffffff 0
arg 1: 4294967295 == w  [word whose subsets are shown (0==> some default words)]  default=0
arg 2: 0 == dir  [With benchmark: whether to go backwards]  default=0
forward:
./bin 0xffffffff 0  3.91s user 0.00s system 99% cpu 3.911 total
 ==> 2^32/3.91 == 1,098,457,108 per second

 time ./bin 0xffffffff 1
arg 1: 4294967295 == w  [word whose subsets are shown (0==> some default words)]  default=0
arg 2: 1 == dir  [With benchmark: whether to go backwards]  default=0
backward:
./bin 0xffffffff 1  3.90s user 0.00s system 100% cpu 3.904 total
 ==> 2^32/3.90 == 1,101,273,665 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.8.0:

 time ./bin 0xffffffff 0
arg 1: 4294967295 == w  [word whose subsets are shown (0==> some default words)]  default=0
arg 2: 0 == dir  [With benchmark: whether to go backwards]  default=0
forward:
ct=4294967296
./bin 0xffffffff 0  2.85s user 0.00s system 99% cpu 2.858 total
 ==> 2^32/2.85 == 1,507,006,068 per second

 time ./bin 0xffffffff 1
arg 1: 4294967295 == w  [word whose subsets are shown (0==> some default words)]  default=0
arg 2: 1 == dir  [With benchmark: whether to go backwards]  default=0
backward:
ct=4294967296
./bin 0xffffffff 1  2.85s user 0.00s system 99% cpu 2.858 total
 ==> 2^32/2.85 == 1,507,006,068 per second

*/

/*
BENCHARGS=0xffffffff 0
BENCHARGS=0xffffffff 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitsubset-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitsubset-demo.cc DEMOFLAGS=-DTIMING"
/// End:

