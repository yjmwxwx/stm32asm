
#include "comb/composition-colex.h"
#include "comb/comp2comb.h"

#include "comb/comb-print.h"
#include "nextarg.h"

#include "fxttypes.h"
#include "fxtio.h"


//% Generating all compositions of n into k parts in co-lexicographic (colex) order.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Compositions of n (n>=1)");
    ulong k = 5;
    NXARG(k, "Into k parts  (k-compositions of n) (k>=1) ");
    bool rq = 0;
    NXARG(rq, "Whether to reverse order");

    composition_colex P(n, k);

    if ( rq )  P.last();
    else       P.first();

    ulong ct = 0;

#ifdef TIMING
    if ( rq )  do { ++ct; }  while  ( P.prev() != k );
    else       do { ++ct; }  while  ( P.next() != k );

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

        if ( rq )  q = P.prev();
        else       q = P.next();
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

----------- next():

 time ./bin 30 10 0
arg 1: 30 == n  [Compositions of n (n>=1)]  default=3
arg 2: 10 == k  [Into k parts  (k-compositions of n) (k>=1) ]  default=5
arg 3: 0 == rq  [Whether to reverse order]  default=0
  ct=211915132
./bin 30 10 0  1.06s user 0.00s system 99% cpu 1.061 total
 ==> 211915132/1.06 == 199,919,935 per second

 time ./bin 10 30 0
arg 1: 10 == n  [Compositions of n (n>=1)]  default=3
arg 2: 30 == k  [Into k parts  (k-compositions of n) (k>=1) ]  default=5
arg 3: 0 == rq  [Whether to reverse order]  default=0
  ct=635745396
./bin 10 30 0  5.70s user 0.02s system 99% cpu 5.730 total
 ==> 635745396/5.70 == 111,534,280 per second

// very sparse case:
 time ./bin 5 100
arg 1: 5 == n  [Compositions of n (n>=1)]  default=3
arg 2: 100 == k  [Into k parts  (k-compositions of n) (k>=1) ]  default=5
arg 3: 0 == rq  [Whether to reverse order]  default=0
  ct=91962520
./bin 5 100  2.16s user 0.02s system 99% cpu 2.177 total
 ==> 91962520/2.16 == 42,575,240 per second

----------- prev():

 time ./bin 30 10 1
arg 1: 30 == n  [Compositions of n (n>=1)]  default=3
arg 2: 10 == k  [Into k parts  (k-compositions of n) (k>=1) ]  default=5
arg 3: 1 == rq  [Whether to reverse order]  default=0
  ct=211915132
./bin 30 10 1  1.15s user 0.00s system 99% cpu 1.160 total
 ==> 211915132/1.15 == 184,274,027 per second

 time ./bin 10 30 1
arg 1: 10 == n  [Compositions of n (n>=1)]  default=3
arg 2: 30 == k  [Into k parts  (k-compositions of n) (k>=1) ]  default=5
arg 3: 1 == rq  [Whether to reverse order]  default=0
  ct=635745396
./bin 10 30 1  5.97s user 0.04s system 99% cpu 6.014 total
 ==> 635745396/5.97 == 106,490,016 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-colex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-colex-demo.cc DEMOFLAGS=-DTIMING"
/// End:
