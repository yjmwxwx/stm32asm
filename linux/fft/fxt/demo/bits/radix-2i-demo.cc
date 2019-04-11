
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


//% Representation of purely real and imaginary numbers in radix(2*i).
//% The radix(2*i) representation for complex integers needs
//% one digit (i.e., two bits) after the point.

// Cf. seq/A212494-demo.cc
// Cf. seq/A177505-demo.cc


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
    ulong ldn = 5;
    NXARG(ldn, "Number of bits");
    ulong n = 1UL<<ldn;
    ulong pn = ldn + 4;
    pn -= pn & 1;
    ulong pn2 = 2*pn;

    for (long s=(long)-n; s < (long)n; ++s)
    {
        ulong k = (ulong)s;

        ulong re = bin_real_to_rad2i(k);
        ulong im = bin_imag_to_rad2i(k);

        cout << setw(4) << s;
        print_bin(":  ", k, pn);
        print_bin("    ", re, pn2);
        cout << "  = " << setw(7) << eval_rad2i(re);
        cout << "  ";
        print_bin("    ", im, pn2);
        cout << "  = "  << setw(7) << eval_rad2i(im);

        cout << endl;


        // tests:
        jjassert( eval_rad2i(re).real() == s );
        jjassert( eval_rad2i(im).imag() == s );

        ulong rtr, rti;
        rad2i_to_bin(re, rtr, rti);
        jjassert( rtr == k );
        jjassert( rti == 0 );
        ulong itr, iti;
        rad2i_to_bin(im, itr, iti);
        jjassert( iti == k );
        jjassert( itr == 0 );

        ulong tr = rad2i_to_bin_real(re);
        jjassert( tr == k );
        ulong ti = rad2i_to_bin_imag(im);
        jjassert( ti == k );

        jjassert( rad2i_is_real(re) );
        jjassert( rad2i_is_imag(im) );
        if ( k != 0 )
        {
            jjassert( ! rad2i_is_real(im) );
            jjassert( ! rad2i_is_imag(re) );
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
/// make-target: "1demo DSRC=demo/bits/radix-2i-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/radix-2i-demo.cc DEMOFLAGS=-DTIMING"
/// End:
