
#include "comb/perm-rec.h"
#include "comb/fact2perm.h"

#include "perm/perminvert.h"

#include "comb/comb-print.h"
#include "comb/mixedradix.h"
#include "perm/printcycles.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"


//% All cyclic permutations by an recursive algorithm.

//#define TIMING  // uncomment to disable printing

static ulong ct = 0;
bool cq;

#ifdef TIMING
void visit(const perm_rec &)  { ++ct; }
#else
void visit(const perm_rec &P)  // function to call with each permutation
{
    bool dfz = true;  // whether to print dots for zeros

    static ulong ff[32];

    cout << setw(4) << ct << ":";
    ++ct;

    ulong n = P.n_;
    const ulong * p = P.data();

    print_perm("    ", p, n, dfz);

    print_cycles("  ", p, n);

    static ulong ii[32];
    make_inverse(p, ii, n);
    print_perm("    ", ii, n, dfz);

    perm2ffact_swp(p, n, ff);
    print_mixedradix("    ", ff, n-1, dfz);

    cout << endl;
}
// -------------------------
#endif


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of elements to permute");
    cq = 1;
    NXARG(cq, "Whether to generate only cyclic permutations");

    perm_rec P(n);

    if ( cq )  P.generate_cyclic(visit);
    else       P.generate(visit);

    cout << "ct=" << ct << endl;
//    cout << "rct=" << P.rct_ << endl;

    return 0;
}
// -------------------------

/*
Timing:

all:
time ./bin 12 0
ct=479001600
./bin 12 0  8.39s user 0.04s system 99% cpu 8.433 total
 ==> 12!/8.39 == 57,091,966 per second

cyclic:
 time ./bin 13 1
ct=479001600
./bin 13 1  12.87s user 0.07s system 99% cpu 12.937 total
 ==> 12!/12.87 == 37,218,461 per second

BENCHARGS=12 0
BENCHARGS=13 1

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

