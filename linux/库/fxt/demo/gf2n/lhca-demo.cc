
#include "bpol/lhca.h"

#include "bits/bitcombcolex.h"  // first_comb() for mask

#include "fxttypes.h"
#include "bits/print-bin.h"
#include "jjassert.h"
#include "fxtio.h"
#include "nextarg.h"


//% Linear Hybrid Cellular Automata (LHCA).


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of bits");


    ulong r = minweight_lhca_rule[n];
    NXARG(r, "Rule (default is minweight rule)");
    ulong pn  = n;

    print_bin("rule = ", r, pn);
    cout << "  == 0x" << hex << r << dec;// << endl;
    cout << "  length=" << (n) << endl;
    cout << endl;

    const ulong end = (1UL<<n)-1;

    const ulong m = first_comb(n);
    ulong x = 1;
    for (ulong k=1; k<=end+1; ++k)
    {
        cout << setw(4) << k;
        print_bin("   ", x, pn);

        cout << endl;

        x = lhca_next(x, r, m);
        if ( x==1 )  jjassert( k==end );
    }
    jjassert( x==lhca_next(1, r, m) );

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/lhca-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/lhca-demo.cc DEMOFLAGS=-DTIMING"
/// End:

