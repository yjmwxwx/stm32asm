
#include "comb/mixedradix-subset-lex.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Subsets of a multiset in lexicographic order with respect to subsets,
//% generated as (multi-)delta sets (that is, mixed radix numbers).
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Number of types of elements in multiset");

    ulong rr = 3;
    NXARG(rr, "Multiplicity of elements in multiset: (0==>[1,2,3,...,n])");
    if ( rr!=0 )  rr += 1;  // radix == 1 + multiplicity

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "Benchmark: whether to generate in backward order");
    mixedradix_subset_lex M(n, rr);

#else
    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply multiplicity for all types (rr ignored)");
    if ( argc>4 )  jjassert( argc == (int)n+3 );

    // radix == 1 + multiplicity:
    for (ulong i=3;  i<(ulong)argc; ++i)  r[i-3] = strtoul(argv[i], 0, 10) + 1;

    mixedradix_subset_lex M(n, rr, (argc>3? r:0) );

#endif
//    M.print_nines("Multiplicities (nines): ");
    cout << endl;


    ulong ct = 0;
#ifdef TIMING
    if ( ! bq )
    {
        cout << "forward:" << endl;
        M.first();
        do  { ++ct; }  while ( M.next() );
    }
    else
    {
        cout << "backward:" << endl;
        M.last();
        do  { ++ct; }  while ( M.prev() );
    }

#else
    do
    {
        cout << " " << setw(4) << ct << ":";
        M.print("    ", true );

        // Print set:
        print_multi_deltaset_as_set("    ", M.data(), n );
//        const char *alph = "abcdefghijklmnopqrstuvwxyz";
//        cout << "    ";
//        for (ulong k=0; k<n; ++k)
//            for (ulong j=0; j<M.data()[k]; ++j)
//                cout << alph[k];
//        // ./bin 3 3 | grep ':   ' | rev | sort | rev  # delta-lex order

        cout << endl;
        ++ct;
    }
    while ( M.next() );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:
 (see mixedradix-subset-lex-demo.cc)

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mset-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mset-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

