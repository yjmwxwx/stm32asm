
#include "comb/ordered-tree-branches.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

#include "sort/sort.h"

//% Ordered trees with n non-root nodes by branches:
//% branch lengths are a composition of n (array a[]) and
//% branch heights (height of base of branch, array b[]) are such that
//% b[j] < a[j-1] + b[j-1] for j>=2 (and b[1]=0).

// Cf. comb/ordered-tree-branching-seq-demo.cc
// Cf. comb/ordered-tree-lev-seq-demo.cc

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "number of non-root nodes");


#ifndef TIMING
    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");
#endif


    ordered_tree_branches T(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef ORDERED_TREE_BRANCHES_FIXARRAYS
    cout << "ORDERED_TREE_BRANCHES_FIXARRAYS defined." << endl;
#endif
    T.first();
    do  { ++ct; }  while ( T.next() );

#else  // TIMING

    ulong m = T.num_branches();
//    ulong C[64];
    do
    {
#if 0
        if ( ! is_sorted( T.length_data(), T.num_branches() ) )  continue;  // A246565
//        if ( ! is_sorted( T.height_data(), T.num_branches() ) )  continue;  // A001519
//        // both: A193196

//        if ( ! is_sorted_desc( T.length_data(), T.num_branches() ) )  continue;  // A246566
//        if ( ! is_sorted_desc( 1 + T.height_data(), T.num_branches() ) )  continue;  // A192243
//        // both: A000000
#endif
#if 0
        { const ulong *b = T.height_data();  // absolute branching heights
            bool q = 1;
            for (ulong j=1; j<m; ++j)
                if ( b[j-1] < b[j] )  // A011782
//                if ( b[j-1] + 1 < b[j] )  // A086581, cf. A082582 and A025242
//                if ( b[j-1] > b[j] )  // A244885
//                if ( b[j-1] > b[j] + 1 )  // A000000, cf. A196417
                { q=0;  break; }
            if ( ! q )  continue;
        }
#endif

        ++ct;

#if 1  // allow/suppress printing

        cout << setw(4) << ct << ":";

        cout << endl;
        T.print("  ");  cout << endl;

//        T.print_level_seq("    ");

        if ( aa )  // ASCII art
        {
            cout << endl;
            T.print_aa();
            cout << endl;
        }

        cout << endl;

        jjassert( T.OK() );

#endif  // allow/suppress printing
    }
    while ( (m=T.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;  // A000108

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.1:

 time ./bin 19
arg 1: 19 == n  [number of non-root nodes]  default=5
 ct=1767263190
./bin 19  7.59s user 0.00s system 99% cpu 7.595 total
 ==> 1767263190/7.59 == 232,841,000 per second


With ORDERED_TREE_BRANCHES_FIXARRAYS defined:

 time ./bin 19
arg 1: 19 == n  [number of non-root nodes]  default=5
ORDERED_TREE_BRANCHES_FIXARRAYS defined.
 ct=1767263190
./bin 19  7.01s user 0.00s system 99% cpu 7.019 total
 ==> 1767263190/7.01 == 252,106,018 per second


*/

/*
OEIS example file:
 for n in $(seq 0 4); do ./bin $n 1 ; done | perl -w ~/bin/tree-example.pl
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ordered-tree-branches-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ordered-tree-branches-demo.cc DEMOFLAGS=-DTIMING"
/// End:

