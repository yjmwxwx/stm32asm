
#include "comb/ksubset-rec.h"
// demo-include "comb/ksubset-rec.cc"

#include "aux0/binomial.h"
#include "bits/print-bin.h"
#include "bits/bitcount.h"
#include "comb/comb-print.h"

#include "jjassert.h"
#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"


//% k-subsets where kmin<=k<=kmax in various orders.
//% Recursive CAT algorithm.

//#define TIMING  // uncomment to disable printing

inline bool max2adj(ulong x)
{
    ulong c = bit_count(x);
    if ( c<=1 )  return true;
    if ( c>2 )  return false;
    if ( x&(x>>1) ) return true;
    if ( x&(x<<1) ) return true;
    return false;
}
// -------------------------

#ifdef TIMING
void visit(const ksubset_rec &, ulong ) {;}

#else

ulong bo=0;
void visit(const ksubset_rec &C, ulong k)
{
    cout << setw(4) << C.ct_ << ":";
    const ulong n = C.n_;
    const ulong *x = C.rv_;
//    print_set_as_deltaset("    ", x, k, n);
    ulong b = 0;  for (ulong j=0; j<k; ++j)  b |= (1UL<<(n-1-x[j]));
    print_bin("   ", b, n);
    if ( C.ct_==0 )  bo = b;
    print_bin_diff("   ", bo, b, n, "..PM");
//    cout << "   %" << k;

    print_set("   ", x, k);

//    ulong x = b ^ bo;
//    if ( 2 < bit_count(x) )  cout << " %";
//    if ( !max2adj(x) )  cout << " %";
    cout << endl;
    bo = b;
}
// -------------------------
#endif  // TIMING


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Subsets of n-element set.");
    ulong rq = 7;
    NXARG(rq, "Type of ordering 0<=rq<16.");
    ulong kmin = 0;
    NXARG(kmin, "Minimal number of elements in subsets.");
    ulong kmax = n;
    NXARG(kmax, "Maximal number of elements in subsets.");
    ulong nq = 0;
    NXARG(nq, "Whether to reverse order (zero or one).");

    ksubset_rec C(n);

    C.generate(visit, kmin, kmax, rq, nq);

    cout << "num=" << C.ct_ << endl;

    ulong rct = C.rct_;
    cout << "rct=" << rct << endl;
    cout << "work/object=" << (double)rct/(double)C.ct_ << endl;  // ratio <= n

    ulong z = 0;
    for (ulong k=kmin; k<=kmax; ++k)  z += binomial(n, k);
    jjassert( C.ct_==z );

    return 0;
}
// -------------------------

/*
 ./bin n rq kmin kmax nq

Try these:

 ./bin 6  4
 ./bin 6  7
 ./bin 6  8
 ./bin 6  9
 ./bin 6 10
 ./bin 6 11

 ./bin 7  0 3 3
 ./bin 7  1 3 3
 ./bin 7  2 3 3
 ./bin 7  3 3 3

 ./bin 7  6 2 3
 ./bin 7  7 2 3
 ./bin 7  9 2 3
 ./bin 7 10 2 3
*/

/*
Timing:

 time ./bin 27
arg 1: 27 == n  [Subsets of n-element set.]  default=6
arg 2: 7 == rq  [Type of ordering.]  default=7
arg 3: 0 == kmin  [Minimal number of elements in subsets.]  default=0
arg 4: 27 == kmax  [Maximal number of elements in subsets.]  default=27
arg 5: 0 == nq  [Whether to reverse order.]  default=0
num=134217728
rct=134217728
work/object=1
./bin 27  2.76s user 0.02s system 99% cpu 2.777 total
 ==> 134217728/2.777 == 48,331,915.016 per second

without conditional print statements in recursion:
 ==> 134217728/2.300 == 58,355,533.9130 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ksubset-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ksubset-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

