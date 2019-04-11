
#include "bits/radix-m1pi.h"
#include "bits/radix-m4.h"
#include "bits/bitzip.h"

#include "complextype.h"

#include "fxttypes.h"  // ulong
#include "bits/bitsperlong.h"

#include "bits/print-bin.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"

//% Representation of purely real and imaginary numbers in radix(-1+i).


typedef complex<long> Cplx;
Cplx eval_radm1pi(ulong x)
{
    Cplx v = 0;
    Cplx rxpw = 1;
    while ( x )
    {
        if ( x & 1 )  v += rxpw;
        rxpw *= Complex(-1, +1);
        x >>= 1;
    }
    return v;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong ldn = 5;
    NXARG(ldn, "Number of bits");
    ulong n = 1UL<<ldn;
    ulong pn = ldn + 4;
    pn -= pn&1;
    ulong pn2 = 2*pn;

    for (long s=(long)-n; s<(long)n; ++s)
    {
        ulong k = (ulong)s;

        ulong re = bin_real_to_radm1pi(k);
        ulong im = add_radm1pi(re, re<<1);  // re + (-1+i)*re == i * re

        cout << setw(4) << s;
        print_bin(":  ", k, pn);

        print_bin("    ", re, pn2);
        cout << "  = " << setw(7) << eval_radm1pi(re);

//        cout << "  " << setw(4) << re;  // A066321  and A256441

        cout << "  ";
        print_bin("    ", im, pn2);
        cout << "  = "  << setw(7) << eval_radm1pi(im);

//        cout << "  " << setw(4) << im;  // A000000

        cout << endl;


        // tests:
        ulong tr = radm1pi_to_bin_real(re);
        jjassert( tr == k );
        ulong ti = radm1pi_to_bin_imag(im);
//        print_bin("    ", ti, pn2);
        jjassert( ti == k );

        jjassert( radm1pi_is_real(re) );
        jjassert( radm1pi_is_imag(im) );
        if ( k != 0 )
        {
            jjassert( ! radm1pi_is_real(im) );
            jjassert( ! radm1pi_is_imag(re) );
        }
    }
    cout << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/radix-m1pi-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/radix-m1pi-demo.cc DEMOFLAGS=-DTIMING"
/// End:
