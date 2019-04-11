
#include "bpol/bitpol-irred.h"
// demo-include "bpol/bitpol-irred-rabin.cc"
// demo-include "bpol/bitpol-irred-ben-or.cc"
// demo-include "bpol/bitpol-spi.cc"

#include "bpol/bitpol-arith.h"
#include "bpol/bitpol-print.h"

#include "bits/print-bin.h"
#include "bits/bitsperlong.h"

#include "nextarg.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "fxtio.h"


//% Find binary irreducible polynomials via exhaustive search.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Degree of polynomials");
    jjassert( n <= BITS_PER_LONG );

    ulong st = 0;
    NXARG(st, "Stop after st polynomials where found,  zero==>list all polynomials");

    const ulong h = 1UL << (n-1);
    const ulong N = (n==BITS_PER_LONG) ? ~0UL : (h<<1);

    ulong ct = 0;
//    for (ulong k=1; k<N; k+=2)  // skip polynomials with zero constant term
    for (ulong k=0; k<N; ++k)  // for testing
    {
        ulong z = k | (h<<1);
//        ulong z = (k^(k<<1)) | (h<<1);  // avoid factor x+1 (with skip 2)

        const bool iq = bitpol_irreducible_q(z, h);
//        const bool iq2 = bitpol_irreducible_rabin_q(z, h, n);  // slower
        if ( iq )
        {
            ++ct;
#ifndef TIMING
            const ulong pn = (n==BITS_PER_LONG) ? 0 : n+1;  // precision for printing
            cout << setw(4) << ct << ":";
            print_bin("  ", z, pn);  // missing leading coeff. when n==BITS_PER_LONG
            bitpol_print_coeff(" = ", z);
            cout << endl;
#endif  // TIMING
            if ( ct==st )  break;
        }
//        if ( iq != iq2 )  cout << " *** @ z=" << z << endl;
//        jjassert( iq == iq2 );
    }
    cout << "n = " << n << "  ct=" << ct << endl;

    cout << endl;
    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 24
arg 1: 24 == ldn  [Degree of polynomials]  default=7
n = 24  ct = 698870
./bin 24  4.75s user 0.02s system 99% cpu 4.775 total
 ==> 698870/4.75 == 147,130 per second

 time ./bin 35 300000
arg 1: 35 == n  [Degree of polynomials]  default=7
arg 2: 300000 == st  [Stop after st polynomials where found,  zero==>list all polynomials]  default=0
n = 35  ct = 300000
./bin 35 300000  4.70s user 0.03s system 99% cpu 4.732 total
 ==> 300000/4.70 == 63,829 per second

 time ./bin 45 100000
arg 1: 45 == n  [Degree of polynomials]  default=7
arg 2: 100000 == st  [Stop after st polynomials where found,  zero==>list all polynomials]  default=0
n = 45  ct = 100000
./bin 45 100000  2.74s user 0.01s system 99% cpu 2.754 total
 ==> 100000/2.74 == 36,496 per second

 time ./bin 59 100000
arg 1: 59 == n  [Degree of polynomials]  default=7
arg 2: 100000 == st  [Stop after st polynomials where found,  zero==>list all polynomials]  default=0
n = 59  ct = 100000
./bin 59 100000  4.92s user 0.03s system 99% cpu 4.959 total
 ==> 100000/4.92 == 20,325 per second

 time ./bin 63 100000
arg 1: 63 == n  [Degree of polynomials]  default=7
arg 2: 100000 == st  [Stop after st polynomials where found,  zero==>list all polynomials]  default=0
n = 63  ct = 100000
./bin 63 100000  5.60s user 0.04s system 99% cpu 5.647 total
 ==> 100000/5.60 == 17,857 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/bitpol-search-irred-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/bitpol-search-irred-demo.cc DEMOFLAGS=-DTIMING"
/// End:

