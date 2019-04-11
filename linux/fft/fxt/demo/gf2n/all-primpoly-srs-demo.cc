
#include "bpol/all-irredpoly.h"
#include "bpol/lfsr.h"

#include "fxttypes.h"
#include "bits/print-bin.h"
#include "jjassert.h"
#include "fxtio.h"

#include "nextarg.h"  // NXARG()

//% Shift register sequences (SRS) for all primitive binary polynomials of given degree.
//% The sequences are maximum period sequences (m-sequences).

int
main(int argc, char **argv)
{
    ulong n = 6;  // default
    NXARG(n, "Degree of polynomials 2<=n<BITS_PER_LONG");
    if ( (n<2) || (n>32) )  n = 6;
    ulong ct = 0;

    cout << "degree = " << n << endl;
    all_irredpoly ip(n);

    ulong c = ip.data();
    do
    {
        ++ct;
        print_bin("c=", c, n+1);  cout << " :  ";
        lfsr srs(n, c);
        srs.set_w(1);  // to get cyclic min
        ulong end = srs.max_period();
        ulong a = srs.get_a(), a1 = a;
        for (ulong k=1; k<=end; ++k)
        {
//            ulong w = srs.get_w();
//            cout << setw(4) << k << "  ";
//            print_bin("  a= ", a, n);
//            cout << "    ";
//            print_bin("w= ", w, n);
//            cout << " = " << w;
//            cout << endl;

            char ch = ((srs.w_ >> (n-1)) ? '1' : '.');
            cout << ch;
//            if ( 0==(k%n) )  cout << ' ';
            srs.next();
            a = srs.get_a();

            if ( a==a1 )  jjassert( k==end );
        }
        cout << endl;

        c = ip.next_primitive();
    }
    while ( c );

    cout << " # = " << ct;
    cout << endl;
    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/all-primpoly-srs-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/all-primpoly-srs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

