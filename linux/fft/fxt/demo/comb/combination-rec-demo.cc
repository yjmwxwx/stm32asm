
#include "comb/combination-rec.h"
// demo-include "comb/combination-rec.cc"

#include "comb/comp2comb.h"

#include "comb/comb-print.h"
#include "aux0/binomial.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"

//% Combinations in lexicographic, Gray code,
//% complemented enup, and complemented Eades-McKay order.

//#define TIMING  // uncomment to disable printing


ulong *p;  // composition
ulong kp;  // number of elements in composition

#ifdef TIMING
void visit(const comb_rec &) { ; }

#else  // TIMING
void visit(const comb_rec &C)
{
    cout << setw(4) << C.ct_ << ":";
    C.print_set("    ");
    C.print_deltaset("    ");

    comb2comp(C.rv_, C.n_, C.k_, p);
    print_vec("    ", p, kp, true);

    cout << endl;
}
// -------------------------
#endif  // TIMING


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Combination (n choose k)");
    ulong k = 3;
    NXARG(k, " 0 < k <= n");
    ulong rq = 2;
    NXARG(rq, "Order:"
          "\n    0 ==> lexicographic order"
          "\n    1 ==> Gray code"
          "\n    2 ==> complemented enup order"
          "\n    3 ==> complemented Eades-McKay sequence");
    ulong nq = 0;
    NXARG(nq, "Whether to reverse order.");

    kp = n-k+1;
    p = new ulong[kp];

    comb_rec C(n, k);
    C.generate(visit, rq, nq);

#ifndef TIMING
    ulong rct = C.rct_;
    cout << "rct=" << rct << endl;
    cout << "work/object=" << (double)(rct)/(double)(C.ct_) << endl;  // ratio <= n
    jjassert( C.ct_==binomial(n, k) );
#else
    cout << " ct = " << C.ct_ << endl;
#endif

    delete [] p;

    return 0;
}
// -------------------------

/*
Timing:

 % time ./bin 32 20
arg 1: 32 == n  [Combination (n choose k)]  default=7
arg 2: 20 == k  [ 0 < k <= n]  default=3
arg 3: 2 == rq  [Order:
    0 ==> lexicographic order
    1 ==> Gray code
    2 ==> complemented enup order
    3 ==> complemented Eades-McKay sequence]  default=2
arg 4: 0 == nq  [Whether to reverse order.]  default=0
 ct = 225792840
./bin 32 20  6.32s user 0.02s system 99% cpu 6.347 total
 ==> binomial(32, 20)/6.32 == 35,726,715 per second

% time ./bin 32 12
arg 1: 32 == n  [Combination (n choose k)]  default=7
arg 2: 12 == k  [ 0 < k <= n]  default=3
arg 3: 2 == rq  [Order:
    0 ==> lexicographic order
    1 ==> Gray code
    2 ==> complemented enup order
    3 ==> complemented Eades-McKay sequence]  default=2
arg 4: 0 == nq  [Whether to reverse order.]  default=0
 ct = 225792840
./bin 32 12  3.53s user 0.00s system 100% cpu 3.532 total
 ==> binomial(32, 12)/3.52 == 64,145,693 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/combination-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/combination-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

