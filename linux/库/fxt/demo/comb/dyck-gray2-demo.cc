
#include "comb/dyck-gray2.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "nextarg.h"

#include "jjassert.h"


//% Gray code for k-ary Dyck words.
//% Loopless algorithm, homogeneous two-close changes.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong m = 4;
    NXARG(m, "Number of ones in words.");
    ulong k = 3;
    NXARG(k, "k-ary Dyck words (k>=2).");
    jjassert( k>=2 );

    dyck_gray2 D(k, m);
    D.first();

    ulong ct = 0;

#ifdef TIMING

    do  { ++ct; }  while ( D.next() );

#else  // TIMING

    const ulong *c = D.data();
    const ulong N = m*k;  // for printing as delta-sequence
    ulong ch = 0;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":  ";
        print_sym_vec("  ", c, m);  // print 10 as A, 11 as B, etc.
        print_set1_as_deltaset("    ", c, m, N);  cout << "";

        cout << "    [ ";
        for (ulong j=1; j<=m; ++j)
        {
            const int s = (int)D.s_[j];
            if ( s==0 )  { cout << " . "; continue; }
            if ( s>=0 )  cout << '+';
            cout << s << " ";
        }
        cout << "]";

//        print_vec("   e=", D.e_, m+1, 0);
//        print_vec("   p=", D.p_+1, m, 1);
//        print_vec("   s=", D.s_+1, m);

        cout << endl;
    }
    while ( (ch=D.next()) );

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 18 2
  ct=477638700
./bin 18 2  9.46s user 0.01s system 99% cpu 9.476 total
 ==> 477638700/9.46 == 50,490,348 per second

 time ./bin 13 3
  ct=300830572
./bin 13 3  5.08s user 0.01s system 99% cpu 5.087 total
 ==> 300830572/5.08 == 59,218,616 per second

 time ./bin 12 4
  ct=1882933364
./bin 12 4  28.85s user 0.03s system 99% cpu 28.905 total
 ==> 1882933364/28.85 == 65,266,321 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 18 2
  ct=477638700
./bin 18 2  5.63s user 0.00s system 99% cpu 5.630 total
 ==> 477638700/5.63 == 84,838,134 per second

 time ./bin 13 3
  ct=300830572
./bin 13 3  3.29s user 0.00s system 99% cpu 3.295 total
 ==> 300830572/3.29 == 91,437,863 per second

 time ./bin 12 4
  ct=1882933364
./bin 12 4  19.33s user 0.00s system 99% cpu 19.335 total
 ==> 1882933364/19.33 == 97,409,899 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/dyck-gray2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/dyck-gray2-demo.cc DEMOFLAGS=-DTIMING"
/// End:
