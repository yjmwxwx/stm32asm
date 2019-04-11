
#include "comb/paren.h"

#include "comb/paren-string-to-rgs.h"
#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "nextarg.h"
#include "jjassert.h"


//% Parentheses strings, co-lexicographic order.
//% Representation as list of positions of opening parenthesis.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong k = 5;
    NXARG(k, "Number of parenthesis pairs >=2");
    jjassert( k>= 2 );

    paren C(k);
    ulong *rgs = new ulong[k];

    ulong ct = 0;

#ifdef TIMING
    bool bwq = 0;
    NXARG(bwq, "Whether to generate in backward direction");
    if ( bwq )
    {
        cout << "backward:" << endl;
        C.last();
        do { ++ct; } while ( C.prev() );
    }
    else
    {
        cout << "forward:" << endl;
        C.first();
        do { ++ct; } while ( C.next() );
    }

#else
    ulong n = 2*k;
    do
    {
        ++ct;
        cout << setw(3) << ct << ":  ";

        const char * str = C.string();
        cout << str;

        print_set_as_deltaset("  ", C.data(), k, n );

        bool q = paren_string_to_rgs(str, rgs);
        print_vec("    ", rgs, k, true);

        print_vec("    ", C.data(), k, true);  // where parens open

        cout << endl;

        jjassert( C.OK() );
        jjassert( q );
    }
    while ( C.next() );
#endif  // TIMING

    cout << " ct = " << ct << endl;

    delete [] rgs;

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 18
arg 1: 18 == k  [Number of paren pairs >=2]  default=5
arg 2: 0 == bwq  [Whether to also generate in backward direction]  default=0
 ct = 477638700
./bin 18  7.08s user 0.02s system 100% cpu 7.095 total
 ==> 477638700/7.08 == 67,463,093 per second


Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 18
arg 1: 18 == k  [Number of paren pairs >=2]  default=5
arg 2: 0 == bwq  [Whether to generate in backward direction]  default=0
 ct = 477638700
./bin 18  4.26s user 0.00s system 99% cpu 4.261 total
 ==> 477638700/4.26 == 112,121,760 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/paren-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/paren-demo.cc DEMOFLAGS=-DTIMING"
/// End:

