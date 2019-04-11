
#include "bits/radix-2i.h"
#include "bits/radix-m4.h"
#include "bits/bitzip-pairs.h"

#include "complextype.h"

#include "fxttypes.h"  // ulong
#include "bits/bitsperlong.h"

#include "bits/print-bin.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Convert radix (2*i) numbers to complex numbers.
//% The radix(2*i) representation for complex integers needs
//% one digit (i.e., two bits) after the point.


typedef complex<long> Cplx;
Cplx eval_rad2i(ulong x)
{
    Cplx v = 0;
    Cplx rxpw = 1;
    long fd = (long)(x & 3);  // digit after point set (always 0 or 2).
    x >>= 2;  // remove digit after point
    while ( x )
    {
        long d = (long)(x & 3);  // two bits are one digit
        v += d * rxpw;
        rxpw *= Complex(0, +2);
        x >>= 2;
    }
    v.imag( v.imag() - fd/2 );
    return v;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong ldn = 7;
    NXARG(ldn, "Number of bits");
    ulong n = 1UL<<ldn;
    ulong pn = ldn + 4;
    pn -= pn&1;
    ulong pn2 = 2*pn;
    pn2 -= pn2/3;

    for (long s=0; s<(long)n; s+=2)
    {
        ulong z = (ulong)s;
        cout << setw(4) << s;
        print_bin(":  ", z, pn);

        ulong re, im;
        rad2i_to_bin(z, re, im);
//        print_bin("    ", re, pn);
//        print_bin("    ", im, pn);
        cout << "  = "
             << "(" << setw(3) << (long)re
             << "," << setw(3) << (long)im << ")";


        ulong tr = bin_real_to_rad2i(re);
        ulong ti = bin_imag_to_rad2i(im);
        print_bin("   re=", tr, pn);
        print_bin("   im=", ti, pn);

        cout << endl;

        // tests:
        Cplx zl = eval_rad2i(z);
        jjassert( zl.real() == (long)re );
        jjassert( zl.imag() == (long)im );

        if ( z!=0 )
        {
            if ( rad2i_is_real(z) )  jjassert( im == 0 );
            if ( rad2i_is_imag(z) )  jjassert( re == 0 );
        }
    }

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/radix-2i-to-z-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/radix-2i-to-z-demo.cc DEMOFLAGS=-DTIMING"
/// End:
