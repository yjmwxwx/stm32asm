
#include "comb/mixedradix-naf-gray.h"

#include "comb/mixedradix-naf.h"
#include "comb/mixedradix-naf-subset-lex.h"

#include "perm/printcycles.h"
#include "perm/permq.h"
#include "comb/comb-print.h"


#include "aux0/swap.h"
#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"


//% Self-inverse permutations (involutions) from falling factorial numbers
//% that are non-adjacent forms (NAF).
//% Cf. OEIS sequence A000085.



static bool qq[32];  // whether element is unused

ulong find_mark_idx(ulong d)
// Find index of d-th unused element.
{
    ulong i = 0;
    while ( ! qq[i] )  ++i;  // skip over used elements
    // here i points to the first unused element
    while ( d )  { ++i;  d -= ( qq[i] ); }
    qq[i] = false;  // mark as used
    return i;
}
// -------------------------


void ffact_naf_to_invol(const ulong *x, ulong nd, ulong *p)
{
    const ulong n = nd + 1;  // permutation of n elements
    for (ulong j=0; j<n; ++j)  p[j] = j;  // identical permutation
    for (ulong j=0; j<n; ++j)  qq[j] = true;  // mark all as unused

    for (ulong j=0; j<nd; ++j)
    {
        const ulong d = x[j];
        const ulong k = find_mark_idx(0);  // next free element

        if ( d )  // Find d-th unused element to the right
        {
            const ulong i = find_mark_idx(d-1);
            swap2( p[k], p[i] );

            ++j;  // skip over next digit, which is zero
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Self-inverse permutations of n elements.");
    const ulong nd = (n>=1 ? n - 1 : 0 );

//    mixedradix_naf M(nd, 0);  // lexicographic order
    mixedradix_naf_gray M(nd, 0);  // Gray code
//    mixedradix_naf_subset_lex M(nd, 0);  // subset-lex order

    const ulong *x = M.data();

    ulong p[32];  // permutation
    ulong ct = 0;
    do
    {
        ffact_naf_to_invol(x, nd, p);

#if 0  // disallow fixed points (even n only): pairings, cf. OEIS sequence A001147
        bool q = true;
        for (ulong k=0; k<n; ++k)
            if ( p[k]==k )  { q=false; break; }
        if ( !q )  continue;
#endif

        cout << setw(4) << ct << ":";
        M.print("    ", true );

        print_cycles("    ", p, n);
        print_vec("    ", p, n);
        cout << endl;

        jjassert( is_involution(p, n) );

        ++ct;
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
/// make-target: "1demo DSRC=demo/comb/perm-involution-naf-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-involution-naf-demo.cc DEMOFLAGS=-DTIMING"
/// End:

