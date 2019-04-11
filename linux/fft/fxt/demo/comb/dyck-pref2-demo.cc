
#include "comb/dyck-pref2.h"

#include "comb/comb-print.h"

#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"
#include "nextarg.h"


//% k-ary Dyck words via prefix shifts (loopless generation).

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of ones in words (n>=1).");
    jjassert( n>=1 );
    ulong k = 3;
    NXARG(k, "k-ary Dyck words (k>=1, k==2 gives Catalan strings).");
    jjassert( k>=1 );

    dyck_pref2 D(n, k);
    D.first();

    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(4) << ct << ":";

        const ulong *x = D.data();
        print_deltaset("    ", x, k*n);
        print_deltaset_as_set("    ", x, k*n);  // RGS
        cout << endl;
#endif
    }
    while ( D.next() );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 18 2
  ct=477638700
./bin 18 2  1.17s user 0.00s system 99% cpu 1.172 total
 ==> 477638700/1.17 == 408,238,205 per second

 time ./bin 13 3
  ct=300830572
./bin 13 3  0.95s user 0.00s system 99% cpu 0.949 total
 ==> 300830572/0.95 == 316,663,760 per second

 time ./bin 12 4
  ct=1882933364
./bin 12 4  5.65s user 0.00s system 99% cpu 5.654 total
 ==> 1882933364/5.65 == 333,262,542 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/dyck-pref2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/dyck-pref2-demo.cc DEMOFLAGS=-DTIMING"
/// End:
