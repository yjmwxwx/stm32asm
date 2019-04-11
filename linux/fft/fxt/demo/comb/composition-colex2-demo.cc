
// If defined, an array is used instead of a pointer:
//#define COMP_COLEX2_MAX_ARRAY_LEN  128  // default off because limits max k
#include "comb/composition-colex2.h"
#include "comb/comp2comb.h"

#include "comb/comb-print.h"
#include "nextarg.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "jjassert.h"


//% Generating all compositions of n into k parts in co-lexicographic (colex) order.
//% Algorithm efficient also with sparse case, i.e. k much greater than n.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Compositions of n (n>=1)");
    ulong k = 5;
    NXARG(k, "Into k parts  (k-compositions of n) (k>=1) ");

#ifdef COMP_COLEX2_MAX_ARRAY_LEN
    jjassert( k<=COMP_COLEX2_MAX_ARRAY_LEN );
#endif

    composition_colex2 P(n, k);
    P.first();

    ulong ct = 0;

#ifdef TIMING
#ifdef COMP_COLEX2_MAX_ARRAY_LEN
    cout << "COMP_COLEX2_MAX_ARRAY_LEN is defined." << endl;
#endif
    do { ++ct; }  while  ( P.next() != k );

#else
    ulong K = n;
    ulong N = n + k -1;
    ulong *c = new ulong[K];
    const ulong *p = P.data();
    ulong q = k-1;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
        P.print("    ", true);
        cout << "  " << q << "  ";

        comp2comb(p, k, c);
        print_set_as_deltaset("    ", c, K, N);
        print_vec("    ", c, K, false);

        cout << endl;

        q = P.next();
    }
    while ( q != k );

    delete [] c;
#endif

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing:

-------- using a pointer x_ (default):

 time ./bin 30 10 0
arg 1: 30 == n  [Compositions of n (n>=1)]  default=3
arg 2: 10 == k  [Into k parts  (k-compositions of n) (k>=1) ]  default=5
  ct=211915132
./bin 30 10 0  0.77s user 0.00s system 99% cpu 0.773 total
 ==> 211915132/0.77 == 275,214,457 per second

 time ./bin 10 30 0
arg 1: 10 == n  [Compositions of n (n>=1)]  default=3
arg 2: 30 == k  [Into k parts  (k-compositions of n) (k>=1) ]  default=5
  ct=635745396
./bin 10 30 0  2.31s user 0.00s system 100% cpu 2.311 total
 ==> 635745396/2.31 == 275,214,457 per second

// very sparse case:
 time ./bin 5 100
arg 1: 5 == n  [Compositions of n (n>=1)]  default=3
arg 2: 100 == k  [Into k parts  (k-compositions of n) (k>=1) ]  default=5
  ct=91962520
./bin 5 100  0.34s user 0.00s system 94% cpu 0.358 total
 ==> 91962520/0.34 == 270,478,000 per second


-------- using an array x_[] (define  COMP_COLEX2_MAX_ARRAY_LEN):
 time ./bin 30 10 0
COMP_COLEX2_MAX_ARRAY_LEN is defined.
  ct=211915132
./bin 30 10 0  0.58s user 0.00s system 99% cpu 0.583 total
 ==> 211915132/0.58 == 365,370,917  per second

 time ./bin 10 30 0
COMP_COLEX2_MAX_ARRAY_LEN is defined.
  ct=635745396
./bin 10 30 0  1.74s user 0.00s system 99% cpu 1.749 total
 ==> 635745396/1.74 == 365,370,917 per second

// very sparse case:
 time ./bin 5 100
COMP_COLEX2_MAX_ARRAY_LEN is defined.
  ct=91962520
./bin 5 100  0.25s user 0.00s system 99% cpu 0.257 total
 ==> 91962520/0.25 == 367,850,080 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

-------- using a pointer x_ (default):

 time ./bin 30 10 0
  ct=211915132
./bin 30 10 0  0.56s user 0.00s system 99% cpu 0.565 total
 ==> 211915132/0.56 == 378,419,878  per second

 time ./bin 10 30 0
  ct=635745396
./bin 10 30 0  1.69s user 0.00s system 99% cpu 1.692 total
 ==> 635745396/1.69 == 376,180,707 per second

// very sparse case:
 time ./bin 5 100
  ct=91962520
./bin 5 100  0.24s user 0.00s system 99% cpu 0.246 total
 ==> 91962520/0.24 == 383,177,166 per second

-------- using an array x_[] (define  COMP_COLEX2_MAX_ARRAY_LEN):

Identical timigs(!)

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-colex2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-colex2-demo.cc DEMOFLAGS=-DTIMING"
/// End:
