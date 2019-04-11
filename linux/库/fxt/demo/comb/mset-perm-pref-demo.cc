
#include "comb/mset-perm-pref.h"

#include "comb/comb-print.h"
#include "fxtio.h"
#include "fxttypes.h"

#include <cstdlib>  // strtoul()



//% All multiset permutations via prefix shifts ("cool-lex" order)
//% Same as: all strings with fixed content.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong k;   // number of sorts of elements
    ulong *r;  // element i is repeated r[i] times

    cout << "args: multiplicities of elements" << endl;
    if ( argc<=1 )
    {
        ulong t[]={2, 2, 1, 0};  // proper multisets  ct=30
//        ulong t[]={1, 1, 1, 1, 0};  // permutations  ct = 24
//        ulong t[]={6, 2, 0};  // combinations  ct=28
        k=0;  while ( t[k] )  { ++k; }
        r = new ulong[k];
        for (ulong j=0; j<k; ++j)  r[j] = t[j];
    }
    else
    {
        k = (ulong)argc - 1;
        r = new ulong[k];
        for (ulong j=0; j<k; ++j)
        {
            ulong t = strtoul(argv[j+1], 0, 10);
            r[j] = t;
        }
    }

    mset_perm_pref P(r, k);

    cout << "multiplicities: ( ";
    for (ulong i=0; i<k; ++i)  cout << P.r_[i] << (i<k-1?", ":" ");
    cout << ")";
    cout << "  k=" << P.k_ << "  n=" << P.n_;
    cout << endl;

    const ulong n = P.n_;
    // inversion table:


    ulong ct = 0;
    ulong i = P.n_;
    do
    {
        ++ct;
#ifndef TIMING
        const ulong *x = P.data();
        const bool dfz = true;  // whether to print dots for zeros

        cout << setw(4) << ct << ":";
        print_perm("  ", x, n, dfz);
        cout << "  " << i;

        cout << endl;
#endif
//        break;
        i = P.next();
    }
    while ( i );


    cout << " ct=" << ct << endl;

    delete [] r;

    return 0;
}
// -------------------------

/*
Timing:

 ============ MSET_PERM_PREF_LEN #defined, O(1) update of prefix length:

time ./bin 2 2 2 3 3 3
args: multiplicities of elements
multiplicities: ( 2, 2, 2, 3, 3, 3 )  k=6  n=15
ct=756756000
./bin 2 2 2 3 3 3  10.71s user 0.03s system 100% cpu 10.736 total
 ==> 756756000/10.71 == 70,658,823 per second

time ./bin 3 3 3 2 2 2 ## reordered
args: multiplicities of elements
multiplicities: ( 3, 3, 3, 2, 2, 2 )  k=6  n=15
ct=756756000
./bin 3 3 3 2 2 2  10.94s user 0.02s system 100% cpu 10.967 total
 ==> 756756000/10.94 == 69,173,308 per second

time  ./bin 1 1 1 1 1 1 1 1 1 1 1 1  ## permutations of 12
args: multiplicities of elements
multiplicities: ( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 )  k=12  n=12
ct=479001600
./bin 1 1 1 1 1 1 1 1 1 1 1 1  6.71s user 0.02s system 100% cpu 6.730 total
 ==> 479001600/6.71 == 71,386,229 per second

time  ./bin 15 15  ## combinations (30 choose 15)
args: multiplicities of elements
multiplicities: ( 15, 15 )  k=2  n=30
ct=155117520
./bin 15 15  2.50s user 0.00s system 99% cpu 2.505 total
 ==> 155117520/2.50 == 62,047,008 per second


 ============ MSET_PERM_PREF_LEN not #defined:

time ./bin 2 2 2 3 3 3
multiplicities: ( 2, 2, 2, 3, 3, 3 )  k=6  n=15
ct=756756000
./bin 2 2 2 3 3 3  11.97s user 0.01s system 99% cpu 11.977 total
 ==> 756756000/11.97 == 63,221,052 per second

 time ./bin 3 3 3 2 2 2 ## reordered
args: multiplicities of elements
multiplicities: ( 3, 3, 3, 2, 2, 2 )  k=6  n=15
ct=756756000
./bin 3 3 3 2 2 2  12.22s user 0.00s system 99% cpu 12.226 total
 ==> 756756000/12.22 == 61,927,659 per second

time  ./bin 1 1 1 1 1 1 1 1 1 1 1 1  ## permutations of 12
args: multiplicities of elements
multiplicities: ( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 )  k=12  n=12
ct=479001600
./bin 1 1 1 1 1 1 1 1 1 1 1 1  7.02s user 0.02s system 99% cpu 7.042 total
 ==> 479001600/7.02 == 68,233,846 per second

time  ./bin 15 15  ## combinations (30 choose 15)
args: multiplicities of elements
multiplicities: ( 15, 15 )  k=2  n=30
ct=155117520
./bin 15 15  3.35s user 0.00s system 99% cpu 3.357 total
 ==> 155117520/3.35 == 46,303,737 per second
*/

/*
BENCHARGS= 2 2 2 3 3 3
BENCHARGS= 3 3 3 2 2 2 ## reordered
BENCHARGS= 1 1 1 1 1 1 1 1 1 1 1 1  ## permutations of 12
BENCHARGS= 15 15  ## combinations (30 choose 15)

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mset-perm-pref-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mset-perm-pref-demo.cc DEMOFLAGS=-DTIMING"
/// End:
