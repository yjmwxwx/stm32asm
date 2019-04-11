
#include "comb/ksubset-twoclose.h"

#include "comb/comb-print.h"  // print_deltaset_as_set()
#include "aux0/binomial.h"

#include "bits/bitset2set.h"  // deltaset2bitset()
#include "bits/bitcount.h"
#include "bits/bit2pow.h"
#include "bits/bitlow.h"
#include "bits/print-bin.h"

#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"
#include "fxttypes.h"


//% k-subsets (kmin<=k<=kmax) in two-close order.
//% Recursive algorithm.

// With kmin==kmax one obtains a two-close order for combinations (n choose k).


//#define TIMING  // uncomment to disable printing

ulong ct;

#ifdef TIMING
void visit(const ksubset_twoclose &)  { ++ct; }

#else
void visit(const ksubset_twoclose &C)
{
    ++ct;
    static ulong bo = 0;  // bitset
    const ulong *rv = C.rv_;
    ulong n = C.n_;
//    ulong ne = C.k_;  // number of elements
    ulong b = deltaset2bitset(rv, n);   // bitset
    if ( ct==1 )  bo = b;

#if 1
    cout << setw(4) << ct << ":";
    cout << "    ";
    for (ulong j=0; j<C.n_; ++j)  cout << "" << (rv[j] ? '1' : '.');
//    cout << "  #" << ne;
    // =^= print_bin_vec("  ", b, C.n_);
    print_bin_vec_diff("    ", bo, b, C.n_, "..PM");
    print_deltaset_as_set("    ", rv, C.n_);
    cout << endl;
#endif

    // check whether changes are two-close:
    ulong x = bo ^ b;  // changes
    jjassert( bit_count(x)<=2 );  // at most 2 changes
    if ( ! one_bit_q(x) )  // check that change is two-close
    {
        ulong x1 = lowest_one_idx(x);
        x ^= (1UL<<x1);
        ulong x2 = lowest_one_idx(x);  // x2>x1
        jjassert( (x2-x1)<=2 );
        if ( (x2-x1)==2 )  jjassert( 0==(b & (1UL<<(x1+1))) );  // homogenous
    }
    bo = b;
}
// -------------------------
#endif  // TIMING


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Subsets of n-element set.");
    ulong kmin = 2;
    NXARG(kmin, "Minimal number of elements in subsets.");
    ulong kmax = 4;
    NXARG(kmax, "Maximal number of elements in subsets.");

    if ( kmin > kmax )  swap2(kmin, kmax);
    if ( kmax > n )  kmax = n;
    if ( kmin > n )  kmin = n;

    ksubset_twoclose C(n);
    ct = 0;
    C.generate(visit, kmin, kmax);

    cout << "ct=" << ct << endl;

    ulong z = 0;
    for (ulong k=kmin; k<=kmax; ++k)  z += binomial(n, k);
    jjassert( ct==z );

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 29 0 29
arg 1: 29 == n  [Subsets of n-element set.]  default=5
arg 2: 0 == kmin  [Minimal number of elements in subsets.]  default=2
arg 3: 29 == kmax  [Maximal number of elements in subsets.]  default=4
ct=536870912
./bin 29 0 29  7.14s user 0.00s system 100% cpu 7.140 total
 ==> 536870912/7.14 == 75,192,004 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ksubset-twoclose-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ksubset-twoclose-demo.cc DEMOFLAGS=-DTIMING"
/// End:

