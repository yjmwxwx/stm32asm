
#include "bpol/fcsr.h"

#include "bits/print-bin.h"
//#include "bits/bitcount.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "nextarg.h"

#include "jjassert.h"


//% Feedback Carry Shift Register.


int
main(int argc, char **argv)
{
    ulong c = 37;
    NXARG(c, "Modulus: odd, e.g. a prime with primitive root 2");
    ulong ldn = 1 + highest_one_idx(c);
    ulong pn = ldn;  // ld(b+n)+1;
    print_bin("  c = ", c , pn);
    cout  << "  = " << c << endl;
    cout << "  ldn=" << ldn;
    cout << endl;

    fcsr sr(c);
//    print_bin("  m = ", sr.mask_ , pn);
    ulong a1 = sr.get_a();

    ulong k = 0;
    while ( k<c+ldn )
    {
        ulong a = sr.get_a();
        if ( a1==a )  cout << endl;
        cout << setw(4) << k << " : ";
        print_bin("  a= ", a , pn);
        cout << " = " << setw(4) << a << "  ";
        ulong w = sr.get_w();
        print_bin("  w= ", w , pn);
        cout  << " = " << setw(4) << w;
//        ulong m = sr.get_m();
//        print_bin("  m=", m , pn);

        sr.next();

//        print_bin("  k=", k , pn);
//        cout << " " << setw(2) << bit_count(k);

        cout << endl;
        ++k;
    }

    cout << endl;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/fcsr-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/fcsr-demo.cc DEMOFLAGS=-DTIMING"
/// End:

