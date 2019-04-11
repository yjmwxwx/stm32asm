
#include "bits/bitcombshifts.h"

#include "aux0/binomial.h"

#include "bits/print-bin.h"

#include "fxtio.h"
#include "fxttypes.h"  // ulong
#include "bits/bitsperlong.h"

#include "nextarg.h"
#include "jjassert.h"



//% bit-combinations in shifts order.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 7, k = 4;
    NXARG(n, "Shifts combinations (n over k):  n  (n>0)");
    NXARG(k, "  (0<=k<=n)");

    jjassert( n>0 );
    jjassert( n<=BITS_PER_LONG );
    jjassert( n>=k );

    class bit_comb_shifts C(n, k);

    ulong ct = 0;
    ulong g = C.first();
    do
    {
#if 0  // parenthesis strings: lex order
        { bool q = true;
            long s = 0;
            for (ulong b = 1UL<<(n-1); b!=0; b>>=1)
            {
                if ( b & g )  s += 1;
                else
                {
                    if ( 0==s )  { q=false;  break; }
                    s -= 1;
                }
            }
            if ( !q )  continue;
        }
#endif

        ++ct;
#ifndef TIMING
        cout << setw(4) << ct << ":";
        print_bin("  ", g, n);
//        print_bit_set(" = ", g);
        cout << endl;
#endif  // TIMING

    }
    while ( (g=C.next()) != 0 );

    cout << " ct=" << ct << endl;
    jjassert( ct == binomial(n, k) );

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 32 20
arg 1: 32 == n  [Shifts combinations (n over k):  n  (n>0)]  default=7
arg 2: 20 == k  [  (0<k<=n)]  default=4
./bin 32 20  1.53s user 0.00s system 100% cpu 1.533 total
 ==> binomial(32, 20)/1.53 == 147,577,019 per second
./bin 32 20  2.13s user 0.00s system 99% cpu 2.131 total  // with bit-scan


 time ./bin 32 12
arg 1: 32 == n  [Shifts combinations (n over k):  n  (n>0)]  default=7
arg 2: 12 == k  [  (0<k<=n)]  default=4
./bin 32 12  1.01s user 0.00s system 99% cpu 1.020 total
 ==> binomial(32, 12)/1.01 == 223,557,267  per second
./bin 32 12  1.16s user 0.00s system 99% cpu 1.164 total  // with bit-scan


 time ./bin 60 7  # very sparse:
./bin 60 7  0.93s user 0.00s system 99% cpu 0.936 total
 ==> binomial(60, 7)/0.93 == 415,276,258 per second
./bin 60 7  0.91s user 0.00s system 100% cpu 0.915 total  // with bit-scan


 time ./bin 60 53  # very dense:
./bin 60 53  3.48s user 0.02s system 99% cpu 3.503 total
 ==> binomial(60, 53)/3.48 == 110,979,000  per second
./bin 60 53  5.91s user 0.00s system 100% cpu 5.910 total  // with bit-scan

 time ./bin 33 16
arg 1: 33 == n  [Shifts combinations (n over k):  n  (n>0)]  default=7
arg 2: 16 == k  [  (0<=k<=n)]  default=4
./bin 33 16  6.22s user 0.00s system 100% cpu 6.218 total
 ==> binomial(33, 16)/6.22 == 187,588,924 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 33 16
arg 1: 33 == n  [Shifts combinations (n over k):  n  (n>0)]  default=7
arg 2: 16 == k  [  (0<=k<=n)]  default=4
 ct=1166803110
./bin 33 16  4.50s user 0.00s system 99% cpu 4.500 total
 ==> 1166803110/4.50 == 259,289,580 per second

*/

 /*
BENCHARGS=33 16
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitcombshifts-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitcombshifts-demo.cc DEMOFLAGS=-DTIMING"
/// End:
