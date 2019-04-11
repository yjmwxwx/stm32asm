
#include "comb/composition-ex-lex.h"

#include "comb/comb-print.h"
#include "nextarg.h"

#include "aux0/sign.h"  // Abs() (with OEIS counting)

#include "jjassert.h"

#include "fxttypes.h"
#include "fxtio.h"


//% Compositions of n into exactly k parts in lexicographic order.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Compositions of n (n>=1)");
    ulong k = 4;
    NXARG(k, "Into exactly k parts (must have: k<=n) ");
    jjassert( k<=n );

    composition_ex_lex P(n, k);

    ulong ct = 0;

#ifdef TIMING
    bool rq = 0;
    NXARG(rq, "With benchmark: whether to reverse order");
#ifdef COMPOSITION_EX_LEX_FIXARRAYS
    cout << "COMPOSITION_EX_LEX_FIXARRAYS defined" << endl;
#endif
    if ( rq )
    {
        P.last();
        cout << "backward:" << endl;
        do { ++ct; }  while  ( P.prev() != 0 );
    }
    else
    {
        P.first();
        cout << "forward:" << endl;
        do { ++ct; }  while  ( P.next() != 0 );
    }

#else
//    P.last();
    const ulong *x = P.data();
    ulong q = 0;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
        P.print("    ");
        cout << "  " << q << "  ";

#if 1  // show corresponding compositions of n-k into at most k parts:
        cout << "    [";
        for (ulong j=0; j<k; ++j)
        {
            cout << " ";
            ulong v = x[j] - 1;
            if ( 0==v )  cout << '.';
            else         cout << v;
        }
        cout << " ]";
#endif

        cout << endl;

        jjassert( P.OK() );
    }
    while ( (q=P.next()) != 0 );
//    while ( (q=P.prev()) != 0 );
#endif

//    print_vec("    ", x, k+1, true);
//    cout << "  test:" << P.nk1_ << endl;

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing:

GCC 4.8.0:

 time ./bin 50 10 0
COMPOSITION_EX_LEX_FIXARRAYS defined
forward:
 ct=2054455634
./bin 50 10 0  5.14s user 0.00s system 99% cpu 5.145 total
 ==> 2054455634/5.14 == 399,699,539 per second

 time ./bin 50 10 1
COMPOSITION_EX_LEX_FIXARRAYS defined
backward:
 ct=2054455634
./bin 50 10 1  5.65s user 0.00s system 99% cpu 5.647 total
 ==> 2054455634/5.65 == 363,620,466 per second


 time ./bin 50 10 0
forward:
 ct=2054455634
./bin 50 10 0  5.55s user 0.00s system 99% cpu 5.557 total
 ==> 2054455634/5.55 == 370,172,186 per second

 time ./bin 50 10 1
backward:
 ct=2054455634
./bin 50 10 1  5.95s user 0.00s system 99% cpu 5.956 total
 ==> 2054455634/5.95 == 345,286,661 per second

*/

/*
BENCHRAGS=50 10 0
BENCHRAGS=50 10 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-ex-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-ex-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:
