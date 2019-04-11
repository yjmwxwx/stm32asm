
#include "comb/ordered-tree-branching-seq.h"


#include "fxtio.h"

#include "fxttypes.h"
#include "nextarg.h" // NXARG()
#include "jjassert.h"

//% Branching sequences for ordered rooted trees:
//%   words [s(0), s(1), ..., s(n)] with s(n)=0, sum(j=0..n, s(j)) = n,
//%   sum(j=0..k, s(j)-1 ) >= 0 for k<n-1, and sum(j=0..n-1, s(j)-1 ) = 0.
//% Lexicographic order.
//% Cf. OEIS sequence A000108.

// Cf. comb/ordered-tree-lev-seq-demo.cc for level sequences of (ordered) trees.
// Cf. comb/tree-lev-seq-demo.cc for unordered trees.
// Cf. comb/catalan-demo.cc for Catalan RGS.


//#define TIMING // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of non-root nodes");

//    bool aa = false;
//    NXARG(aa, "Whether to render trees as ASCII art");

    ordered_tree_branching_seq T(n);
#ifdef TIMING
#ifdef ORDERED_TREE_BRANCHING_SEQ_FIXARRAYS
    cout << "ORDERED_TREE_BRANCHING_SEQ_FIXARRAYS defined." << endl;
#endif
#endif

    ulong ct = 0;
    do
    {
#if 0
        {
            ulong k;
            const ulong N = T.size();
            const ulong* x = T.data();

//            for (k=1; k+1 <= N; ++k)  if ( x[k]==1 )  break;  // A001006
//            for (k=0; k+1 <= N; ++k)  if ( x[k]==1 )  break;  // A005043
            for (k=0; k+1 <= N; ++k)  if ( x[k] > 2 )  break;  // A001006

            // no odd out-degrees:
//            for (k=1; k+1 <= N; ++k)  if ( (x[k]&1)==1 )  break;  // A047749
//            for (k=0; k+1 <= N; ++k)  if ( (x[k]&1)==1 )  break;  // A001764 with zeros

            // no even out-degrees for internal nodes:
//            for (k=1; k+1 <= N; ++k)  if ( (x[k]!=0) && (x[k]&1)==0 )  break;  // A143017
//            for (k=0; k+1 <= N; ++k)  if ( (x[k]!=0) && (x[k]&1)==0 )  break;  // A101785

            if ( k+1 <= N )  continue;
        }
#endif

#if 0
        {
//            const ulong mb = T.max_branching_number();
//            if ( mb > 2 )  continue;  // A001006
//            if ( mb > 3 )  continue;  // A036765
//            if ( mb > 4 )  continue;  // A036766
//            if ( mb > 5 )  continue;  // A036767
//            if ( mb > 6 )  continue;  // A036768
//            if ( mb > 7 )  continue;  // A036769
//            if ( mb > 8 )  continue;  // A000000

//            const ulong mb = T.min_branching_number();
//            if ( mb < 2 )  continue;  // A001006
//            if ( mb > 2 )  continue;  // A000000

//            if ( mb < 3 )  continue;  // A000000
//            if ( mb > 3 )  continue;  // A000000


//            if ( (x[0] & 1) == 0 )  continue;  // A000958
//            if ( (x[0] & 1) == 1 )  continue;  // A000957
        }
#endif
        ++ct;
#ifndef TIMING


        cout << setw(4) << ct << ":";
        T.print("  ", true);

        T.print_level_seq("    ", true);

//        cout << "  " << n - T.e_;  // A007001
        // (morphism 1 -> 12, 2 -> 123, 3 -> 1234, etc.)

//        if ( aa )
//        {
//            cout << endl;
//            T.print_aa("");
//            cout << endl;
//        }

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

 time ./bin 19
arg 1: 19 == n  [Number of non-root nodes]  default=5
 ct=1767263190
./bin 19  4.98s user 0.00s system 99% cpu 4.978 total
 ==> 1767263190/4.98 == 354,872,126 per second

 time ./bin 19
arg 1: 19 == n  [Number of non-root nodes]  default=5
ORDERED_TREE_BRANCHING_SEQ_FIXARRAYS defined.
 ct=1767263190
./bin 19  4.39s user 0.00s system 99% cpu 4.388 total
 ==> 1767263190/4.39 == 402,565,646 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ordered-tree-branching-seq-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ordered-tree-branching-seq-demo.cc DEMOFLAGS=-DTIMING"
/// End:
