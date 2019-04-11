
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


//% Convert radix (-1+i) numbers to complex numbers
//% and give radix (-1+i) expansion of real and imaginary part.


typedef complex<long> Cplx;
Cplx eval_radm1pi(ulong x)
{
    Cplx v = 0.0;
    Cplx rxpw = 1.0;
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
    ulong ldn = 6;
    NXARG(ldn, "Number of bits");
    ulong n = 1UL<<ldn;
    ulong pn = ldn + 4;
    pn -= pn&1;
    ulong pn2 = 2*pn;
    pn2 -= pn2/3;

    for (long s=0; s<(long)n; ++s)
    {
        ulong z = (ulong)s;
        cout << setw(4) << s;
        print_bin(":  ", z, pn);

        ulong re, im;
        radm1pi_to_bin(z, re, im);
//        print_bin("    ", re, pn);
//        print_bin("    ", im, pn);
        cout << "  = "
             << "(" << setw(3) << (long)re
             << "," << setw(3) << (long)im << ")";


        ulong tr = bin_real_to_radm1pi(re);
        ulong ti = bin_imag_to_radm1pi(im);
        print_bin("   re=", tr, pn2);
        print_bin("   im=", ti, pn2);

        cout << endl;

        Cplx zl = eval_radm1pi(z);
        jjassert( zl.real() == (long)re );
        jjassert( zl.imag() == (long)im );

        jjassert( add_radm1pi(tr, ti) == z );

        if ( z!=0 )
        {
            if ( radm1pi_is_real(z) )  jjassert( im == 0 );
            if ( radm1pi_is_imag(z) )  jjassert( re == 0 );
        }
    }

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/radix-m1pi-to-z-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/radix-m1pi-to-z-demo.cc DEMOFLAGS=-DTIMING"
/// End:
