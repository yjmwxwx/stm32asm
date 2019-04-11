
// demo-is-self-contained

#include "fxtio.h"
#include "bits/print-bin.h"

#include "fxttypes.h"

//% A pitfall with two's complement: one nonzero value equals its own negative.

#define TYPE short int

#define TYPE_BITS  (8*sizeof(TYPE))

void
Print(TYPE c)
{
    const char c01[]=".1";  // characters for printing zero and one
    print_bin("  c=", (ulong)c, TYPE_BITS, c01);
    print_bin("  -c=", (ulong)-c, TYPE_BITS, c01);
    cout << "   c=" << setw(6) << (TYPE)+c;
    cout << "  -c=" << setw(6) << (TYPE)-c;
    if ( (signed char)c==(signed char)-c )  cout << "  <--=";
    cout << endl;
}
// -------------------------

int
main()
{
    TYPE c;

    for (c=0; c<7; ++c)  Print(c);
    cout << " [--snip--]" << endl;

    c = (TYPE)1;
    c = (TYPE)(c << (TYPE_BITS-1));  // compiler's pedantry
    for (TYPE i=-3; i<7; ++i)  Print( (TYPE)(c + i) );
    cout << " [--snip--]" << endl;

    for (c=0-7; c!=0; ++c)  Print(c);


    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/gotcha-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/gotcha-demo.cc DEMOFLAGS=-DTIMING"
/// End:

