
#include "bits/bitsubset-gray.h"
// demo-include "bits/bitsubset.h"

#include "bits/print-bin.h"
#include "bits/bitcount.h"  // for timing

#include "fxttypes.h"
#include "fxtio.h"

#include "nextarg.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Generating all subsets of a bitset in Gray code order.

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
    bit_subset_gray S(v);
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
    bit_subset_gray S(w);
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
./bin 0xffffffff  11.67s user 0.03s system 100% cpu 11.704 total
 ==> 2^32/11.67 == 368,034,901 per second

 time ./bin 0xffffffff 1
arg 1: 4294967295 == w  [word whose subsets are shown (0==> some default words)]  default=0
arg 2: 1 == dir  [With benchmark: whether to go backwards]  default=0
backward:
./bin 0xffffffff 1  11.68s user 0.03s system 100% cpu 11.703 total
 ==> 2^32/11.68 == 367,719,802 per second
*/

/*
BENCHARGS=0xffffffff 0
BENCHARGS=0xffffffff 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitsubset-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitsubset-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:
