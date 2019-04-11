
#include "comb/mset-perm-gray.h"

#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
//#include "jjassert.h"

#include <cstdlib>  // strtoul()


//% All multiset permutations in minimal-change order (Fred Lunnon's Gray code).
//% Same as: all strings with fixed content.


//#define TIMING  // uncomment to disable printing

//#define DETAILS  // define to print full internal state of the class


int
main(int argc, char **argv)
{
    ulong k;   // number of sorts of elements
    ulong *r;  // element i is repeated r[i] times

    cout << "args: multiplicities of elements" << endl;
    if ( argc<=1 )
    {
        ulong t[]={2, 2, 1, 0};  // proper multisets  ct=30
//        ulong t[]={2, 2, 2, 0};  // proper multisets  ct=90
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

    mset_perm_gray P(r, k);

    cout << "multiplicities: ( ";
    for (ulong i=0; i<k; ++i)  cout << P.r_[i] << (i<k-1?", ":" ");
    cout << ")";
    cout << "  k=" << P.k_ << "  n=" << P.n_;
    cout << endl;

    ulong ct = 0;

#ifdef TIMING

    do
    {
        ++ct;
    }
    while ( P.next() );

#else  // TIMING

    const bool dfz = true;  // whether to print dots for zeros
    const ulong n = P.n_;

    const ulong *x = P.data();

    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

#ifndef DETAILS
        print_perm("  ", x, n, dfz);
#else  // DETAILS
        { const ulong nn = n + 4;
            print_perm("  ms=", P.ms_, nn, dfz);
            print_perm("  P=", P.P_, nn, dfz);
            print_perm("  Q=", P.Q_, nn, dfz);
            cout << "  D=[";
            for (ulong j=0; j<nn; ++j)
            {
                ulong d = P.D_[j];
                cout << " ";
                if ( (long)d < 0 )  cout << '-';
                if ( (long)d > 0 )  cout << '+';
                if ( d==0 )  cout << '.';
            }
            cout << " ]";
        }
#endif  // DETAILS
        if ( ct>1 )
        {
            ulong s1, s2;
            P.get_swaps(s1, s2);
            cout << "  (" << s1 << ", " << s2 << ")";
        }

        cout << endl;
    }
    while ( P.next() );

    delete [] r;

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 2 2 2 3 3 3
args: multiplicities of elements
multiplicities: ( 2, 2, 2, 3, 3, 3 )  k=6  n=15
ct=756756000
./bin 2 2 2 3 3 3  19.80s user 0.03s system 100% cpu 19.821 total
 ==> 756756000/19.80 == 38,220,000 per second

 time ./bin 3 3 3 2 2 2 ## reordered
args: multiplicities of elements
multiplicities: ( 3, 3, 3, 2, 2, 2 )  k=6  n=15
ct=756756000
./bin 3 3 3 2 2 2  20.37s user 0.04s system 100% cpu 20.399 total
 ==> 756756000/20.37 == 37,150,515 per second

 time ./bin 1 1 1 1 1 1 1 1 1 1 1 1  ## permutations of 12
args: multiplicities of elements
multiplicities: ( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 )  k=12  n=12
ct=479001600
./bin 1 1 1 1 1 1 1 1 1 1 1 1  11.24s user 0.03s system 100% cpu 11.272 total
 ==> 479001600/11.24 == 42,615,800 per second

 time ./bin 15 15  ## combination (30 choose 15)
args: multiplicities of elements
multiplicities: ( 15, 15 )  k=2  n=30
ct=155117520
./bin 15 15  5.75s user 0.00s system 99% cpu 5.757 total
 ==> 155117520/5.75 == 26,976,960 per second

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
/// make-target: "1demo DSRC=demo/comb/mset-perm-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mset-perm-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:
