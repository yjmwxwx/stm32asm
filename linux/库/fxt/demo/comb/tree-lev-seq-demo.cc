
#include "comb/tree-lev-seq.h"
#include "comb/tree-lev-seq-aux.h"

#include "fxtio.h"

#include "fxttypes.h"
#include "nextarg.h" // NXARG()
#include "jjassert.h"

//% Level sequences for unordered rooted trees.
//% Cf. OEIS sequence A000081.

// Cf. comb/id-tree-lev-seq-demo.cc for identity trees
// Cf. comb/ordered-tree-lev-seq-demo.cc for ordered trees
// Cf. comb/balanced-ordered-tree-lev-seq-demo.cc for blanced trees
// Cf. comb/ordered-tree-branching-seq-demo.cc branching sequences for ordered trees


//#define TIMING // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n,"Number of non-root nodes");

    bool aa = false;
    NXARG(aa,"Whether to render trees as ASCII art");

    tree_lev_seq T(n);
#ifdef TIMING
#endif

    ulong ct = 0;
    do
    {
#if 0
        {  bool q = true;  const ulong N = T.size();
#define NXT { q=false;  break; }  if ( ! q )  continue;

            // series-reduced trees:
//            for (ulong k=1; k+1 < N; ++k)  if ( T.valency(k)==2 )  NXT;  // A198518
            for (ulong k=0; k+1 < N; ++k)  if ( T.valency(k)==2 )  NXT;  // A001679

//            for (ulong k=0; k+1 < N; ++k)  // cf. A000598 (rooted ternary trees)
//            {
//                ulong v = T.valency(k);
//                if ( k==0 && v!=1 )  NXT;
//                if ( v==2 )  NXT;
//                if ( v==3 )  NXT;
//                if ( v>=5 )  NXT;
//            }  /**/ if ( ! q )  continue;

//            for (ulong k=1; k+1 < N; ++k)  if ( T.lev(k) == T.lev(k+1) )  NXT;  // A002955
            // cf. A255636

//            for (ulong k=1; k+1 < N; ++k)  if ( T.lev(k) == T.lev(k+1) + 1 )  NXT;  // A000000

            // no non-root branchings:
//            for (ulong k=1; k < N; ++k)  if ( T.branching_number(k) > 1 )  NXT;  // A000041

//            for (ulong k=1; k+1 < N; ++k)  if ( T.branching_number(k)==1 )  NXT;  // A198518

//            for (ulong k=0; k+1 < N; ++k)  if ( T.branching_number(k)==1 )  NXT;  // A001678

            // rooted forests without 1-trees:
//            for (ulong k=0; k < N; ++k)  if ( T.lev(k)==1 && T.lev(k+1)!=2 )  NXT;  // A174145

            // level sequence drops by at most 1:
//            for (ulong k=0; k+1 < N; ++k)  if ( T.lev(k) > T.lev(k+1)+1 )  NXT;  // A000000

            // no odd out-degrees:
//            for (ulong k=1; k+1 < N; ++k)  if ( (T.branching_number(k)&1)==1 )  NXT;  // A195865
//            for (ulong k=0; k+1 < N; ++k)  if ( (T.branching_number(k)&1)==1 )  NXT;  // A000000

            // no even out-degrees for internal nodes:
//            for (ulong k=1; k+1 < N; ++k)
//            { ulong b = T.branching_number(k);  if ( (b!=0) && (b&1)==0 )  NXT; }  // A000000
//            for (ulong k=0; k+1 < N; ++k)
//            { ulong b = T.branching_number(k);  if ( (b!=0) && (b&1)==0 )  NXT; }  // A000000


//            for (ulong k=0; k+1 < N; ++k)  if ( T.branching_number(k) > 2 )  NXT;  // A001190
//            for (ulong k=0; k+1 < N; ++k)  if ( T.branching_number(k) > 3 )  NXT;  // A000598
//            for (ulong k=0; k+1 < N; ++k)  if ( T.branching_number(k) > 4 )  NXT;  // A036718
//            for (ulong k=0; k+1 < N; ++k)  if ( T.branching_number(k) > 5 )  NXT;  // A036721
        }
#endif
#if 0
        // only odd/even branching number at root:
//        if ( (T.branching_number(0) & 1) == 0 )  continue;  // A000000
//        if ( (T.branching_number(0) & 1) == 1 )  continue;  // A000000

//        if ( ! T.is_identity_tree() )  continue;  // A004111
        if ( ! T.is_balanced() )  continue;  // A048816

//        if ( T.max_limb_length() >= 2 )  continue;  // A002955
//        if ( T.max_limb_length() > 2 )  continue;  // A052321, cf. A003006
//        if ( T.max_limb_length() > 3 )  continue;  // A052327
//        if ( T.max_limb_length() > 4 )  continue;  // A052328
//        if ( T.max_limb_length() > 5 )  continue;  // A052329

//        if ( T.min_limb_length() <= 1 )  continue;  // A001678(!)
//        if ( T.min_limb_length() <= 2 )  continue;  // A000000

//        if ( T.min_limb_length() != 1 )  continue;  // A244455(!)
//        if ( T.min_limb_length() != 2 )  continue;  // A000000 (not: A155099)
#endif

        ++ct;

#ifndef TIMING

        cout << setw(4) << ct << ":";
        T.print("  ");

//        cout << "    Bq =[ "; for (ulong i=0; i<n; ++i)  cout << T.is_branch(i) << " "; cout << "]";
//        cout << "    Lq =[ "; for (ulong i=0; i<n; ++i)  cout << T.is_leaf(i) << " "; cout << "]";
//        cout << "    LL =[ "; for (ulong i=0; i<n; ++i)  cout << T.limb_length(i) << " "; cout << "]";
//        cout << setw(4) << T.min_limb_length();
//        cout << setw(4) << T.max_limb_length();
//        cout << setw(4) << T.height();

//        T.print_branching_numbers("    ");
//        T.print_base_seq("    ");

//        T.print_paren_word("    ", "()");
//        T.print_paren_word("    ", "1.");

//        T.print_composition("    ");  // for balanced trees only

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
Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)

GCC 4.9.2:

 time ./bin 23
arg 1: 23 == n  [Number of non-root nodes]  default=6
arg 2: 0 == aa  [Whether to render trees as ASCII art]  default=0
 ct=743724984
./bin 23  2.84s user 0.00s system 99% cpu 2.839 total
 ==> 743724984/2.84 == 261,874,994 per second

*/

/*

Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.1:

// with easy case optimization:

 time ./bin 23
arg 1: 23 == n  [Number of non-root nodes]  default=6
arg 2: 0 == aa  [Whether to render trees as ASCII art]  default=0
 ct=743724984
./bin 23  5.38s user 0.00s system 99% cpu 5.386 total
 ==> 743724984/5.38 == 138,238,844 per second


// without easy case optimization:

 time ./bin 23
arg 1: 23 == n  [Number of non-root nodes]  default=6
arg 2: 0 == aa  [Whether to render trees as ASCII art]  default=0
 ct=743724984
./bin 23  10.65s user 0.00s system 99% cpu 10.656 total
 ==> 743724984/10.65 == 69,833,331 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/tree-lev-seq-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/tree-lev-seq-demo.cc DEMOFLAGS=-DTIMING"
/// End:
