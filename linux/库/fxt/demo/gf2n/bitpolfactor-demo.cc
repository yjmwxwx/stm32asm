
#include "bpol/bitpol-factor.h"
#include "bpol/bitpol-squarefree.h"
#include "bpol/bitpol-degree.h"
#include "bpol/bitpol-print.h"

#include "bits/bittransforms.h"

#include "bits/print-bin.h"
#include "bits/bitsperlong.h"
#include "fxttypes.h"
#include "fxtio.h"
#include "fxtalloca.h"
#include "jjassert.h"

#include "nextarg.h"

//% Factorization of binary polynomials.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Degree of polynomials");
    jjassert( n < BITS_PER_LONG );  // cannot factor
    ulong cn = 1UL<<n;  // leading coeff.
    ulong np = 0;
    NXARG(np, "Number of polynomials to factor (0==>up to next degree)");
    if ( 0==np )  { np = cn;  cout << "np=" << np << endl; }
    uint frm = 0;
    NXARG(frm, "Output form: 0==>ascii, 1==>coeff-list, 2==>TeX, 3==>bin");
//    if ( frm>3 )  frm = 0;

    ALLOCA(ulong, f, n);  // factors
    ALLOCA(ulong, e, n);  // exponents
    for (ulong k=0; k<np; ++k)
    {
        ulong c = cn + k;

//        c ^= (c>>1);  // Gray code order
//        c = blue_code(c);  // blue code order

        ulong fct = bitpol_factor(c, f, e);
        bitpol_sort_factorization(f, e, fct);

#ifndef TIMING
        cout << setw(5) << k << ":    ";
        switch ( frm )
        {
        case 0: bitpol_print("", c); break;
        case 1: bitpol_print_coeff("", c); break;
        case 2: bitpol_print_tex("", c); break;
        case 3: bitpol_print_bin("", c); break;
        }
        cout << "  ==  ";
        switch ( frm )
        {
        case 0: bitpol_print_factorization("", f, e, fct); break;
        case 1: bitpol_print_coeff_factorization("", f, e, fct); break;
        case 2: bitpol_print_tex_factorization("", f, e, fct); break;
        case 3: bitpol_print_bin_factorization("", f, e, fct); break;
        case 4: bitpol_print_short_factorization("", f, e, fct); break;
        }

        cout << endl;

        ulong fi;
        ulong q = bitpol_test_factorization(c, f, e, fct, fi);
        if ( q )
        {
            cout << "Error " << q << " at factor # " << fi << endl;
            jjassert( 0 );
        }
#endif  // TIMING
    }
#ifdef TIMING
    cout << " ct=" << np << endl;
#endif
    return 0;
}
// -------------------------

/*
Timing:

time ./bin 21
arg 1: 21 == n  [Degree of polynomials]  default=5
arg 2: 0 == np  [Number of polynomials to factor (0==>up to next degree)]  default=0
np=2097152
arg 3: 0 == frm  [Output form: 0==>ascii, 1==>coeff-list, 2==>TeX, 3==>bin]  default=0
./bin 21  11.95s user 0.00s system 99% cpu 11.967 total
 ==> 2097152/11.95 == 175,493 per second

BENCHARGS=21 0 0


 2.2GHz AMD64:
./bin 18  1.09s user 0.02s system 99% cpu 1.108 total
./bin 20  5.14s user 0.02s system 99% cpu 5.170 total
./bin 21  11.05s user 0.05s system 100% cpu 11.093 total
./bin 21 1048576  5.52s user 0.02s system 99% cpu 5.538 total
./bin 24 1048576  6.73s user 0.04s system 99% cpu 6.773 total
./bin 25 1048576  7.14s user 0.04s system 99% cpu 7.194 total
./bin 30 1048576  9.49s user 0.06s system 99% cpu 9.545 total
./bin 31 1048576  9.98s user 0.04s system 99% cpu 10.021 total
./bin 40 1048576  15.12s user 0.07s system 100% cpu 15.188 total
./bin 60 1048576  30.19s user 0.15s system 99% cpu 30.342 total

 2GHz AMD Athlon (32 bit):
./bin 18  2.17s user 0.01s system 99% cpu 2.182 total
./bin 20  7.71s user 0.00s system 99% cpu 7.725 total
./bin 24 1048577  10.62s user 0.00s system 99% cpu 10.629 total
./bin 25 1048576  11.35s user 0.00s system 99% cpu 11.365 total
./bin 30 1048576  15.82s user 0.00s system 99% cpu 15.847 total
./bin 31 1048577  16.75s user 0.01s system 99% cpu 16.782 total

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/bitpolfactor-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/bitpolfactor-demo.cc DEMOFLAGS=-DTIMING"
/// End:

