
#include "bits/bitcombcolex.h"
#include "bits/revbin.h"

#include "bits/print-bin.h"

#include "fxttypes.h"
#include "nextarg.h"
#include "fxtio.h"
#include "jjassert.h"


//% Generating combinations of bits (as binary words) in lexicographic order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Combinations (n choose k) in lexicographic order");
    ulong k = 4;
    NXARG(k, "  (0<k<=n)");
    jjassert( n>0 );
    jjassert( k>0 );
    jjassert( n>=k );


    ulong x = first_comb(n-k);        // first colex (n-k choose n)
    const ulong m = first_comb(n);    // aux mask
    const ulong l = last_comb(k, n);  // last colex
    ulong y;

#ifdef TIMING

    do
    {
        y = revbin(~x, n) & m;  // lex order
        x = next_colex_comb(x);
    }
    while ( y != l );

#else  // TIMING

    ulong ct = 0;
    do
    {
        y = revbin(~x, n) & m;  // lex order

        ++ct;
        cout << setw(3) << ct << ":";
        print_bin("    ", y, n);
        print_bit_set(" = ", y);
        cout << "    ";
        print_bin("    ", x, n);
        print_bit_set(" = ", x);
        cout << endl;

        x = next_colex_comb(x);
    }
    while ( y != l );

#endif  // TIMING

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 32 20
arg 1: 32 == n  [Combinations (n choose k) in lexicographic order]  default=7
arg 2: 20 == k  [  (0<k<=n)]  default=4
./bin 32 20  2.62s user 0.02s system 99% cpu 2.654 total
==> binomial(32,20)/2.62 == 86,180,473 per second

 time ./bin 32 12
arg 1: 32 == n  [Combinations (n choose k) in lexicographic order]  default=7
arg 2: 12 == k  [  (0<k<=n)]  default=4
./bin 32 12  2.29s user 0.03s system 99% cpu 2.323 total
==> binomial(32,12)/2.29 == 98,599,493 per second

*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32 20
arg 1: 32 == n  [Combinations (n choose k) in lexicographic order]  default=7
arg 2: 20 == k  [  (0<k<=n)]  default=4
./bin 32 20  1.81s user 0.00s system 99% cpu 1.814 total
==> binomial(32,20)/1.81 == 124,747,425 per second

 time ./bin 32 12
arg 1: 32 == n  [Combinations (n choose k) in lexicographic order]  default=7
arg 2: 12 == k  [  (0<k<=n)]  default=4
./bin 32 12  1.65s user 0.00s system 99% cpu 1.650 total
==> binomial(32,12)/1.65 == 136,844,145 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitcomblex-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitcomblex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

