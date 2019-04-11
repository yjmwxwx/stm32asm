
#include "comb/composition-ex-colex.h"

#include "comb/comb-print.h"
#include "nextarg.h"

#include "aux0/sign.h"  // Abs() (with OEIS counting)

#include "jjassert.h"

#include "fxttypes.h"
#include "fxtio.h"


//% Compositions of n into exactly k parts in co-lexicographic (colex) order.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Compositions of n (n>=1)");
    ulong k = 4;
    NXARG(k, "Into exactly k parts (must have: k<=n) ");
    jjassert( k<=n );

    composition_ex_colex P(n, k);

    ulong ct = 0;

#ifdef TIMING
    bool rq = 0;
    NXARG(rq, "With benchmark: whether to reverse order");
#ifdef COMPOSITION_EX_COLEX_FIXARRAYS
    cout << "COMPOSITION_EX_COLEX_FIXARRAYS defined" << endl;
#endif
    if ( rq )
    {
        P.last();
        cout << "backward:" << endl;
        do { ++ct; }  while  ( P.prev() != k );
    }
    else
    {
        P.first();
        cout << "forward:" << endl;
        do { ++ct; }  while  ( P.next() != k );
    }

#else
    const ulong *x = P.data();
    ulong q = k-1;
    do
    {
        // OEIS sequences:
//        {  bool qq = true;
//            for (ulong j=1; j<k; ++j)  if ( x[j]-x[j-1] != 1 )  { qq=false; break; }
//            if ( !qq )  continue;  // A129372
//        }
//        {  bool qq = true;  // A106351: no two adjacent parts are equal
//            for (ulong j=1; j<k; ++j)  if ( x[j]==x[j-1] )  { qq=false; break; }
//            if ( !qq )  continue;
//        }
//        {  if (k>1 ) { bool qq = false;  // A131044: at least two adjacent parts are equal.
//            for (ulong j=1; j<k; ++j)  if ( x[j]==x[j-1] )  { qq=true; break; }
//            if ( !qq )  continue; }
//        }
//        {  bool qq = true;
//            for (ulong j=0; j<k; ++j)
//                for (ulong i=j+1; i<k; ++i)
//                    if ( x[j]==x[i] )  { qq=false; goto dort; }
//        dort:
//            if ( !qq )  continue;  // A072574, cf. A032020
//        }

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
    while ( (q=P.next()) != k );
#endif

//    print_vec("    ", x, k+1, true);
//    cout << "  test:" << P.nk1_ << endl;

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing:

----------- next():

 time ./bin 40 10
  ct=211915132
./bin 40 10  1.05s user 0.01s system 99% cpu 1.064 total
 ==> 211915132/1.05 == 201,823,935 per second

----------- prev():  (set variable rq=1) identical

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

----------- next():
 time ./bin 40 10
arg 1: 40 == n  [Compositions of n (n>=1)]  default=8
arg 2: 10 == k  [Into exactly k parts (must have: k>=n) ]  default=4
  ct=211915132
./bin 40 10  0.61s user 0.00s system 99% cpu 0.610 total
 ==> 211915132/0.61 == 347,401,855 per second

----------- prev():
./bin 40 10  0.67s user 0.00s system 99% cpu 0.676 total
 ==> 211915132/0.67 == 316,291,241 per second


GCC 4.8.0:

 time ./bin 50 10 0
COMPOSITION_EX_COLEX_FIXARRAYS defined
forward:
 ct=2054455634
./bin 50 10 0  5.51s user 0.00s system 99% cpu 5.511 total
 ==> 2054455634/5.51 == 372,859,461 per second

 time ./bin 50 10 1
COMPOSITION_EX_COLEX_FIXARRAYS defined
backward:
 ct=2054455634
./bin 50 10 1  5.87s user 0.00s system 99% cpu 5.874 total
 ==> 2054455634/5.87 == 349,992,441 per second


 time ./bin 50 10 0
forward:
 ct=2054455634
./bin 50 10 0  7.24s user 0.00s system 99% cpu 7.242 total
 ==> 2054455634/7.24 == 283,764,590 per second

 time ./bin 50 10 1
backward:
 ct=2054455634
./bin 50 10 1  6.37s user 0.00s system 99% cpu 6.373 total
 ==> 2054455634/6.37 == 322,520,507 per second

*/

/*
BENCHRAGS=50 10 0
BENCHRAGS=50 10 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-ex-colex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-ex-colex-demo.cc DEMOFLAGS=-DTIMING"
/// End:
