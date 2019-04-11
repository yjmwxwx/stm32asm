
#include "comb/perm-lex2.h"  // with factorial numbers
#include "perm/permq.h"  // major_index()

#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% OEIS sequence A207018:
//% Number of permutations with major index equal to inversion number.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Permutations of n elements (n>=2)");
    jjassert( n>=2 );

    perm_lex2 P(n);

    ulong ct = 0;
    do
    {
        const ulong ni = P.num_inversions();
        const ulong mi = major_index(P.x_, n);
        if ( ni != mi )  continue;

        ++ct;
#ifndef TIMING
        cout << setw(4) << ct << ":";
        P.print("    ");
        cout << setw(4) << mi;
//        cout << setw(4) << ni;
        print_vec("    ", P.d_, n-1);
        cout << endl;
#endif
    }
    while ( P.next() );

    cout << " ct=" << ct;
    cout << endl;

    return 0;
}
// -------------------------



/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A207018-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A207018-demo.cc DEMOFLAGS=-DTIMING"
/// End:
