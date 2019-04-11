
#include "comb/balanced-ordered-tree-lev-seq.h"

#include "fxtio.h"

#include "fxttypes.h"
#include "nextarg.h" // NXARG()
#include "jjassert.h"

//% Level sequences for ordered balanced rooted trees.
//% Lexicographic order.
//% See OEIS sequences A079500 and A007059.

// Cf. comb/composition-nz-first-max-demo.cc for all compositions with fist part maximal
// Cf. comb/ordered-tree-lev-seq-demo.cc for all ordered trees.
// Cf. comb/tree-lev-seq-demo.cc for unordered trees.


//#define TIMING // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Number of non-root nodes");

    bool aa = false;
    NXARG(aa, "Whether to render trees as ASCII art");

    balanced_ordered_tree_lev_seq T(n);
#ifdef TIMING
#endif

    ulong ct = 0;
    do
    {
        ++ct;
#ifndef TIMING


        cout << setw(4) << ct << ":";
        T.print("  ");

//        T.print_branching_numbers("    ");

//        T.print_paren_word("    ", "()");
//        T.print_paren_word("    ", "1.");

//        T.print_composition("    ");


        if ( aa )
        {
            cout << endl;
            T.print_aa("");
            cout << endl;
        }

        cout << endl;

        jjassert( T.OK() );
#endif
    }
    while ( 0 != T.next() );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.1:

% time ./bin 33
arg 1: 33 == n  [Number of non-root nodes]  default=8
arg 2: 0 == aa  [Whether to render trees as ASCII art]  default=0
 ct=369393466
./bin 33  5.68s user 0.00s system 99% cpu 5.684 total
 ==> 369393466/5.68 == 65,034,060 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/balanced-ordered-tree-lev-seq-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/balanced-ordered-tree-lev-seq-demo.cc DEMOFLAGS=-DTIMING"
/// End:
