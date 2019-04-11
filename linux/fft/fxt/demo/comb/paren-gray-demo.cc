
#include "comb/paren-gray.h"

#include "comb/paren-string-to-rgs.h"
#include "comb/comb-print.h"

#include "fxttypes.h"
#include "nextarg.h"
#include "fxtio.h"

//% Parentheses strings in a homogeneous minimal-change order.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of parentheses pairs");

    paren_gray P(n);
    ulong *rgs = new ulong[n];

    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        const char * str = P.paren_string();
        cout << setw(4) << ct << ":    ";
        cout << str;

        // print as bit array:
        cout << "    ";
        for (ulong k=0; k<2*n; ++k)
            cout << (str[k]=='(' ? '1' : '.' );

        paren_string_to_rgs(str, rgs);
        print_vec("    ", rgs, n, true);

        cout << endl;
#endif  // TIMING
    }
    while ( P.next() );
    cout << " ct = " << ct << endl;

    delete [] rgs;

    return 0;
}
// -------------------------

/*
Timing:

  time ./bin 18
arg 1: 18 == n  [Number of parentheses pairs]  default=5
 ct = 477638700
./bin 18  5.84s user 0.01s system 99% cpu 5.862 total
 ==> 477638700/5.84 == 81,787,448 per second


Timing: (AMD Phenom II X4 945 3000MHz)
 time ./bin 18
arg 1: 18 == n  [Number of parentheses pairs]  default=5
 ct = 477638700
./bin 18  3.47s user 0.00s system 99% cpu 3.478 total
 ==> 477638700/3.47 == 137,648,040 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/paren-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/paren-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:
