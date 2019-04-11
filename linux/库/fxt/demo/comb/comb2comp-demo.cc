
#include "comb/combination-revdoor.h"
#include "comb/comp2comb.h"

#include "comb/comb-print.h"

#include "nextarg.h"

#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"


//% Relation between combinations and compositions.


int
main(int argc, char **argv)
{
    ulong N = 7;
    NXARG(N, "Combinations (N choose K), N>=1");
    ulong K = 3;
    NXARG(K, " ... K<=N.");

    combination_revdoor C(N, K);
    const ulong *c = C.data();  // combination data

//    ulong n = K;
    ulong k = N-K+1;
    ulong *p = new ulong[k];  // composition data

    ulong ct = 0;
    do
    {
        ++ct;

        cout << setw(4) << ct << ":";
        print_vec("    ", c, K, false);
        print_set_as_deltaset("        ", c, K, N);

        comb2comp(c, N, K, p);
        print_vec("        ", p, k, true);

        cout << endl;
    }
    while ( C.next() );

    cout << "ct=" << ct << endl;

    delete [] p;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/comb2comp-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/comb2comp-demo.cc DEMOFLAGS=-DTIMING"
/// End:

