
#include "comb/partition.h"

#include "fxttypes.h"

#include "jjassert.h"
#include "nextarg.h"

#include "fxtio.h"

//% Generate all integer partitions, iterative algorithm.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Partitions of n");
    bool sq = 0;
#ifdef TIMING
    NXARG(sq, "Whether to generate in backward order");
#else
    NXARG(sq, "Whether to print in partitions in falling order");
#endif
    partition P(n);

    ulong ct = 0;

#ifdef TIMING
    if ( !sq )  // here: whether forward or backward
    {
        cout << "forward:" << endl;
        P.first();
        do  { ++ct; }  while ( P.next() );
    }
    else
    {
        cout << "backward:" << endl;
        P.last();
        do  { ++ct; }  while ( P.prev() );
    }

#else  // TIMING

    do
    {
        ++ct;

        cout << setw(4) << ct << ": ";

//        cout << " [" << P.num_parts() << "]  ";
//        cout << " [" << P.num_sorts() << "]  ";
//        cout << " [" << P.rank() << "]  ";
//        cout << " [" << P.num_of(1) << "]  ";

        cout << setw(4) << n;

        const bool szq = false;  // whether to skip zeros with long format
        cout << " == ";
        P.print_long(szq);
        if ( szq )  cout  << endl << "         ";

        cout << "  ==  ";
        if ( sq )  P.print_falling();
        else       P.print();
        cout << endl;

//        {  // print cumulative sums
//            cout << "       sums: ";
//            for (ulong k=2; k<=n; ++k)  cout << setw(7) << P.s_[k];
//            cout << endl;
//            cout << endl;
//        }

//        for (ulong k=1; k<=n; ++k)
//        {
//            ulong c = P.numof();
//            for (ulong j=0; j<c; ++j)
//                cout << "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[k] << " ";
//        }
//        cout << endl;

        jjassert( P.OK() );
    }
    while ( P.next() );
#endif  // TIMING


    cout << " ct=" << (long)ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 110 0
forward:
  ct=607163746
./bin 110 0  3.02s user 0.00s system 99% cpu 3.032 total
 ==> 607163746/3.02 == 201,047,598 per second

// line  q = (z>=i ? z/i : 0);  :
 time ./bin 100 1
backward:
  ct=190569292
./bin 100 1  2.70s user 0.00s system 99% cpu 2.705 total
 ==> 190569292/2.70 == 70,581,219 per second

// line  q = z/i;  :
 time ./bin 100 1
backward:
  ct=190569292
./bin 100 1  3.03s user 0.01s system 99% cpu 3.055 total
 ==> 190569292/3.03 == 62,894,155 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 110 0
arg 1: 110 == n  [Partitions of n]  default=6
arg 2: 0 == sq  [Whether to generate in backward order]  default=0
forward:
  ct=607163746
./bin 110 0  2.51s user 0.00s system 99% cpu 2.518 total
 ==> 607163746/2.51 == 241,897,906 per second

 time ./bin 100 1
arg 1: 100 == n  [Partitions of n]  default=6
arg 2: 1 == sq  [Whether to generate in backward order]  default=0
backward:
  ct=190569292
./bin 100 1  1.08s user 0.00s system 99% cpu 1.080 total
 ==> 190569292/1.08 == 176,453,048 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-demo.cc DEMOFLAGS=-DTIMING"
/// End:

