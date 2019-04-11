
#include "comb/paren-lex.h"
#include "comb/is-paren-string.h"

#include "comb/paren-string-to-rgs.h"
#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "nextarg.h"
#include "jjassert.h"


//% Parentheses strings, lexicographic order.
//% Representation as list of positions of opening parenthesis.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong k = 5;
    NXARG(k, "Number of parenthesis pairs");

    paren_lex C(k);
    ulong *rgs = new ulong[k];

    ulong ct = 0;

#ifdef TIMING
    bool bwq = 0;
    NXARG(bwq, "Whether to generate in backward direction");
#ifdef PAREN_LEX_FIXARRAY
    cout << "PAREN_LEX_FIXARRAY is defined." << endl;
#endif
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
    ulong j = 0;
//    C.last();
    do
    {
        ++ct;

        cout << setw(4) << ct << ":  ";

        const char * str = C.string();
        cout << str;

        print_set_as_deltaset("  ", C.data(), k, n );
        bool q = paren_string_to_rgs(str, rgs);
        print_vec("    ", rgs, k, true);

        print_vec("    ", C.data(), k, true);  // where parens open

        cout << setw(4) << j;

        cout << endl;

        jjassert( C.OK() );
        jjassert( is_paren_string(str, n) );
        jjassert( q );
    }
    while ( 0 != (j=C.next()) );
//    while ( 0 != (j=C.prev()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    delete [] rgs;

    return 0;
}
// -------------------------


/*

Timing: (AMD Phenom II X4 945 3000MHz)

 ---- with gcc 4.5.0:
 time ./bin 18 0
arg 1: 18 == k  [Number of parenthesis pairs]  default=5
arg 2: 0 == bwq  [Whether to generate in backward direction]  default=0
forward:
 ct = 477638700
./bin 18 0  1.67s user 0.00s system 99% cpu 1.676 total
 ==> 477638700/1.67 == 286,011,197 per second

 time ./bin 18 0
arg 1: 18 == k  [Number of parenthesis pairs]  default=5
arg 2: 0 == bwq  [Whether to generate in backward direction]  default=0
PAREN_LEX_FIXARRAY is defined.
forward:
 ct = 477638700
./bin 18 0  1.52s user 0.00s system 99% cpu 1.527 total
 ==> 477638700/1.52 == 314,235,986 per second


 ---- with gcc 4.8.0:
 time ./bin 18 0
arg 1: 18 == k  [Number of parenthesis pairs]  default=5
arg 2: 0 == bwq  [Whether to generate in backward direction]  default=0
forward:
 ct = 477638700
./bin 18 0  1.81s user 0.00s system 99% cpu 1.817 total
 ==> 477638700/1.81 == 263,888,784 per second

 time ./bin 18 0
arg 1: 18 == k  [Number of parenthesis pairs]  default=5
arg 2: 0 == bwq  [Whether to generate in backward direction]  default=0
PAREN_LEX_FIXARRAY is defined.
forward:
 ct = 477638700
./bin 18 0  1.95s user 0.00s system 99% cpu 1.954 total
 ==> 477638700/1.95 == 244,942,923 per second
*/

/*
BENCHARGS=18 0
BENCHARGS=18 1
*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/paren-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/paren-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

