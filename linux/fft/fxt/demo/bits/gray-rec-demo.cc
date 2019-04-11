
// demo-is-self-contained

#include "bits/print-bin.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Recursive algorithm for the binary Gray code.

ulong ldn;

void gray_b(ulong f, ulong n);
void gray_f(ulong f, ulong n)
{
    if ( n<1 )  return;
    // loop 1:
    print_bin("F  ", f, ldn);
    cout << endl;
    for (ulong m=1; m<n; m<<=1)  gray_b(f+m, m);  // f: count  b: bitlexb
}
// -------------------------
//
void gray_b(ulong f, ulong n)
{
    if ( n<1 )  return;
    // loop 2:
    for (ulong m=n>>1; m>0; m>>=1)  gray_f(f+m, m);
    print_bin("B  ", f, ldn);
    cout << endl;
}
// -------------------------


int
main(int argc, char **argv)
{
    ldn = 5;
    NXARG(ldn, "Number of bits");

    gray_f(0, 1UL<<ldn);  // forward
//    gray_b(0, 1UL<<ldn);  // backward

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/gray-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/gray-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

