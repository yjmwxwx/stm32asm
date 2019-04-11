
#include "bits/parenwords.h"  // next_parenword()
#include "bits/print-bin.h"  // print_bin()

#include "jjassert.h"
#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"  // ulong

//% Binary 'parentheses words' in colex order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of paren pairs");
    char *str = new char[2*n+1];  str[2*n] = 0;

    ulong x = first_parenword(n);
    ulong ct = 0;

#ifdef TIMING
    while ( x )
    {
        ++ct;
        x = next_parenword(x);
    }
#else  // TIMING
    while ( x )
    {
        ++ct;

        const ulong pn = 2*n;
        print_bin("  ", x, pn);
        parenword2str(x, str);
        cout << "    " << str;

        cout << endl;
        jjassert( is_parenword(x) );
        x = next_parenword(x);
    }
#endif  // TIMING
    cout << " ct=" << ct << endl;

//    cout << endl;
//    ulong lp = last_parenword(n);
//    print_bin("  ", lp, pn);
//    cout << endl;

    delete [] str;

    return 0;
}
// -------------------------


/*
Timing:
 time ./bin 19
arg 1: 19 == n  [Number of paren pairs]  default=5
  pct=1767263190
./bin 19  10.43s user 0.02s system 100% cpu 10.442 total
 ==> 1767263190/10.43 == 169,440,382 per second

Knuth's version:
 time ./bin 19
./bin 19  21.75s user 0.11s system 100% cpu 21.862 total
 ==> 1767263190/21.75 == 81,253,480 per second

Knuth's version, with easy case treated separately:
 time ./bin 19
./bin 19  12.83s user 0.07s system 100% cpu 12.899 total
 ==> 1767263190/12.83 == 137,744,597 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 19
arg 1: 19 == n  [Number of paren pairs]  default=5
 ct=1767263190
./bin 19  6.99s user 0.00s system 99% cpu 6.991 total
 ==> 1767263190/6.99 == 252,827,351 per second

Knuth's version, with easy case treated separately:
 time ./bin 19
arg 1: 19 == n  [Number of paren pairs]  default=5
 ct=1767263190
./bin 19  6.21s user 0.00s system 99% cpu 6.214 total
 ==> 1767263190/6.21 == 284,583,444  per second
Note: HAVE_AMD64_POPCNT activated

*/

/*
BENCHARGS=19
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/parenword-colex-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/parenword-colex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

