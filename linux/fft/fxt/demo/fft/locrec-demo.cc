
// demo-is-self-contained

#include "bits/print-bin.h"
#include "nextarg.h"
#include "fxttypes.h"
#include "jjassert.h"

//% Structure of iterative versions of localized radix-2 transforms.


ulong ldN=0;  // == ldn in main()


void Print(ulong f, ulong n)
{
    print_bin("   ", f, ldN+1);
    print_bin("   ", n, ldN+1);
    cout << endl;
}
// -------------------------


void loc_dif2(ulong f, ulong n)
{
    if ( n<2 ) return;

    Print(f, n);

    for (ulong m=2; m<n; m<<=1)  loc_dif2(f+m, m);
}
// -------------------------

void loc_dit2(ulong f, ulong n)
{
    if ( n<2 )  return;

    for (ulong m=2; m<n; m<<=1)  loc_dit2(f+m, m);

    Print(f, n);
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong ldn = 5;
    NXARG(ldn, "Using 2**ldn elements");
    ldN = ldn;
    const ulong n = (1UL<<ldn);

    cout << "    DIF      DIF" << endl;
    cout << "   start    length" << endl;
    loc_dif2(0, n);
    cout << endl;

    cout << "    DIT      DIT" << endl;
    cout << "   start    length" << endl;
    loc_dit2(0, n);
    cout << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/fft"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/fft/locrec-demo.cc"
/// make-target2: "1demo DSRC=demo/fft/locrec-demo.cc DEMOFLAGS=-DTIMING"
/// End:
