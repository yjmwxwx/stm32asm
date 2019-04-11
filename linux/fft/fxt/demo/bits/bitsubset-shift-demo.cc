
#include "bits/bitsubset.h"

#include "bits/print-bin.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "nextarg.h"

#include <cstdlib>  // strtoul()

//% Shifting through a bitset.

//#define TIMING  // uncomment to disable printing

const char *vv[] =
{
    "0000000000000000"
    "0000000000111111",
    "0000111111001010",
    "0010101110011001",
    "0010101110001011",
    "0010101110000011",
    "0001000000001010",
};
// -------------------------


void
show_subsets(ulong v)
{
    bit_subset S(v);
    S.last();
    print_bin("V ", S.full_set(), 16); cout << endl;
    // remove third-lowest bit:
    S.prev();  S.prev();  S.prev();  S.prev();
    print_bin("U ", S.current(), 16); cout << endl;

    do
    {
        print_bin("  ", S.shift_left(), 16);  cout << endl;
    }
    while ( S.current() );
    cout << endl;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong w = 0;

#ifdef TIMING

    NXARG(w, "With benchmark: shift until result zero, for all words w, w+1, ..., w+d");
    ulong d = 1;
    NXARG(d, "");

    bit_subset S(0);
    ulong ct = 0;
    for (ulong j=w; j <= d + w; ++j )
    {
        S.last( j );
        do { ++ct;
//            print_bin("  ", S.current(), 0);  cout << endl;
        }  while ( S.shift_left() );
    }
    cout << "ct=" << ct << endl;

#else

    NXARG(w, "word whose subsets are shown (0==> some default words)");
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
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.8.0:

 time ./bin 0xffffffff 0xfffffff
arg 1: 4294967295 == w  [With benchmark: shift until result zero, for all words w, w+1, ..., w+d]  default=0
arg 2: 268435455 == d  []  default=1
ct=4026531843
./bin 0xffffffff 0xfffffff  6.64s user 0.00s system 99% cpu 6.641 total
 ==> 4026531843/6.64 == 606,405,398 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitsubset-shift-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitsubset-shift-demo.cc DEMOFLAGS=-DTIMING"
/// End:

