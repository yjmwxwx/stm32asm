
#include "comb/dyck-gray.h"

#include "comb/comb-print.h"

#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"
#include "nextarg.h"


//% Gray code for k-ary Dyck words.
//% Loopless algorithm, all changes are homogeneous.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of ones in words.");
    ulong k = 3;
    NXARG(k, "k-ary Dyck words (k>=2).");
    jjassert( k >= 2 );

    dyck_gray D(n, k);
    D.first();

    ulong ct = 0;
    ulong ch = 0;
    do
    {
        ++ct;
#ifndef TIMING
//        const ulong *x = D.data();
        cout << setw(4) << ct << ":";
        print_sym_vec("  ", D.data(), n);
        print_sign_vec("    ", D.dr_+1, n);
//        print_vec("  np=", D.np_+1, n);
//        print_vec("  mx=", D.mx_+1, n);  // does not change

        print_set1_as_deltaset("    ", D.data(), n, k*n);

        cout << endl;
#endif
    }
    while ( (ch=D.next()) );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 18 2
  ct=477638700
./bin 18 2  4.92s user 0.02s system 99% cpu 4.942 total
 ==> 477638700/4.92 == 97,081,036 per second

 time ./bin 13 3
  ct=300830572
./bin 13 3  2.51s user 0.00s system 99% cpu 2.510 total
 ==> 300830572/2.51 == 119,852,817 per second

 time ./bin 12 4
  ct=1882933364
./bin 12 4  13.56s user 0.08s system 99% cpu 13.640 total
 ==> 1882933364/13.56 == 138,859,392 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)
 time ./bin 18 2
  ct=477638700
 ./bin 18 2  3.14s user 0.00s system 99% cpu 3.145 total
 ==> 477638700/3.14 == 152,114,235 per second

 time ./bin 13 3
  ct=300830572
./bin 13 3  1.93s user 0.00s system 99% cpu 1.931 total
 ==> 300830572/1.93 == 155,870,762 per second

 time ./bin 12 4
./bin 12 4  9.82s user 0.00s system 99% cpu 9.828 total
  ct=1882933364
 ==> 1882933364/9.82 == 191,744,741 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/dyck-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/dyck-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:
