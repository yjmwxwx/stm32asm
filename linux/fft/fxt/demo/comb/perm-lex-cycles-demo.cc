
#include "comb/perm-lex.h"
#include "perm/printcycles.h"
#include "comb/fact2perm.h"

#include "ds/bitarray.h"

#include "comb/comb-print.h"
#include "comb/mixedradix.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Generate all permutations in lexicographic order, show cycles and inversion tables.


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements.");

    perm_lex P(n);

    bool dfz= true;  // whether to print dots for zeros
    const ulong *x = P.data();

    bitarray B(n);
    ulong f[32];

    ulong ct = 0;
    do
    {
        cout << setw(4) << ct << ":";
        ++ct;

        P.print("    ", dfz);
        print_cycles("    ", x, n, &B);
        perm2ffact(x, n, f);
        print_mixedradix("  ", f, n-1, dfz);

        ulong i = 0;  // number of inversions
        for (ulong j=0; j<n-1; ++j)  i += f[j];
        cout << "  " << setw(2) << i;

        cout << endl;
    }
    while ( P.next() );

    return 0;
}
// -------------------------




/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-lex-cycles-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-lex-cycles-demo.cc DEMOFLAGS=-DTIMING"
/// End:

