
#include "comb/dyck-pref.h"

#include "comb/comb-print.h"

//#include "comb/composition-nz-rank.h"

#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"
#include "nextarg.h"


//% k-ary Dyck words via prefix shifts.

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

    dyck_pref D(n, k);
    D.first();
    ulong *rgs = new ulong[n];

    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(4) << ct << ":";

        const ulong *x = D.data();
        print_deltaset("    ", x, k*n);
        print_deltaset_as_set("    ", x, k*n);

        // show RGS:
        for (ulong j=0, z=0;  j<k*n;  ++j)  if ( x[j] )  rgs[z++] = j;  // set
        for (ulong j=0; j<n; ++j)  rgs[j] = j*k - rgs[j];  // RGS
        print_vec("    ", rgs, n, true);


//        ulong C[64];
//        ulong r = 0;
////        for (ulong j=0;  j<k*n;  ++j)  if ( x[j] )  r |= (1UL << (k*n-1-j));
//        for (ulong j=0;  j<k*n;  ++j)  if ( x[j] )  r |= (1UL << (j));
//        ulong nc = composition_nz_unrank(r, C, k*n);
//        print_vec("    ", C, nc);
//        r = ~r;
//        nc = composition_nz_unrank(r, C, k*n);
//        print_vec("    ", C, nc);

        cout << endl;
#endif
    }
    while ( D.next() );

    cout << " ct=" << ct << endl;

    delete [] rgs;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 18 2
  ct=477638700
./bin 18 2  1.31s user 0.00s system 99% cpu 1.310 total
 ==> 477638700/1.31 == 364,609,694 per second

 time ./bin 13 3
  ct=300830572
./bin 13 3  0.92s user 0.00s system 99% cpu 0.917 total
 ==> 300830572/0.92 == 326,989,752 per second

 time ./bin 12 4
  ct=1882933364
./bin 12 4  5.66s user 0.00s system 99% cpu 5.667 total
 ==> 1882933364/5.66 == 332,673,739 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/dyck-pref-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/dyck-pref-demo.cc DEMOFLAGS=-DTIMING"
/// End:
