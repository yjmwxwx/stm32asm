
#include "bits/bitfibgray.h"
// demo-include "bits/graycode.h"
// demo-include "bits/negbin.h"
#include "bits/fibrep.h"  // fibrep2bin()

#include "bits/print-bin.h"
#include "bits/bitlow.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

//% Fibonacci Gray code with binary words.

// Cf. bits/bit-rll2-demo.cc

//#define TIMING  // define to disable printing


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Number of bits in Gray code");

    bit_fibgray fg(n);
    ulong z, ct = 0;

#ifdef TIMING

    do
    {
        ++ct;
        z = fg.next();
    }
    while ( ~z );  // ~0 is returned with last

#else  // TIMING

    ulong kl = fg.k_;
    ulong xo = 0;
    do
    {
        ++ct;
        ulong k = fg.k_;
        ulong x = fg.data();
        cout << setw(6) << ct << ":";
        print_bin("    ", k, n+3);
        print_bin("    ", kl-k, n+3);
        print_bin("    ", bin2neg(k), n+3);
        print_bin("    ", x, n+3);
//        cout << " = " << setw(3) << fg.x_;
        cout << " = " << setw(3) << fibrep2bin(fg.x_);

        if ( ct>1 )  cout << "  : " << lowest_one_idx( x^xo );

        cout << endl;
        kl = k;
        xo = x;

        z = fg.next();
    }
    while ( ~z );  // ~0 is returned with last

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 40
arg 1: 40 == n  [Number of bits in Gray code]  default=7
  ct=267914296
./bin 40  2.05s user 0.00s system 99% cpu 2.053 total
 ==> 267914296/2.05 == 130,689,900 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 40
arg 1: 40 == n  [Number of bits in Gray code]  default=7
  ct=267914296
./bin 40  1.38s user 0.00s system 99% cpu 1.376 total
 ==> 267914296/1.38 == 194,140,794 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitfibgray-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitfibgray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

