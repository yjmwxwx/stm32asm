
#include "comb/mixedradix-sod-lex.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()


//% k-subsets (combinations) of a multiset.
//% Essentially the same as mixed radix numbers with fixed sum of digits.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of types of elements in multiset");

    ulong k = 3;
    NXARG(k, "Subsets with k elements");

    ulong rr = 2;
    NXARG(rr, "Multiplicity of elements in multiset: (0==>[1,2,3,...,n])");
    if ( rr!=0 )  rr += 1;  // radix == 1 + multiplicity

    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply multiplicity for all types (rr ignored)");
    if ( argc>4 )  jjassert( argc == (int)n+4 );

    // radix == 1 + multiplicity:
    for (ulong i=4;  i<(ulong)argc; ++i)  r[i-4] = strtoul(argv[i], 0, 10) + 1;

    mixedradix_sod_lex M(n, rr, (argc>4? r:0) );
    jjassert( M.first(k) );
//    M.print_nines("Nines: ");
//    cout << endl;

    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(4) << ct << ":";
        M.print("  ", true );

//        cout << setw(6) << M.to_num();  // == ct
        cout << setw(4) << M.pos();  // == rightmost position of change

        // print as set (as opposed to multi delta set above):
        M.print_as_combination("   ");

        cout << endl;
        jjassert( M.OK() );
#endif  // TIMING
    }
    while ( M.next() );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mset-ksubset-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mset-ksubset-demo.cc DEMOFLAGS=-DTIMING"
/// End:

