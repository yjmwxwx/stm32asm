
#include "comb/id-tree-lev-seq.h"
#include "comb/tree-lev-seq-aux.h"


#include "comb/comb-print.h"

//#include "aux0/factorial.h"

#include "fxtio.h"

#include "fxttypes.h"
#include "nextarg.h" // NXARG()
#include "jjassert.h"

//% Level sequences for unordered rooted identity trees.
//% Cf. OEIS sequence A004111.

// Cf. comb/tree-lev-seq-demo.cc for all unordered trees
// Cf. comb/ordered-tree-lev-seq-demo.cc for ordered trees
// Cf. comb/ordered-tree-branching-seq-demo.cc branching sequences for ordered trees


//#define TIMING // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n,"Number of non-root nodes");

    bool aa = false;
    NXARG(aa,"Whether to render trees as ASCII art");

    id_tree_lev_seq T(n);
#ifdef TIMING
#endif

    ulong ct = 0;
//    ulong fct = 0;
    do
    {
#if 0
        {  ulong k;  const ulong N = T.size();
            // no non-root branchings:
//            for (k=1; k < N; ++k)  if ( T.branching_number(k) > 1 )  break;  // A000009
//            if ( k != N )  continue;

//            const ulong *x = T.data();
//            for (k=1; k+1 < N; ++k)  if ( x[k] == x[k+1] + 1 )  break;  // A000000


            // no even out-degrees for internal nodes:
//            for (k=1; k+1 < N; ++k)
//            { ulong b = T.branching_number(k);  if ( (b!=0) && (b&1)==0 )  break; }  // A000000

            // no even out-degrees for non-terminal nodes:
//            for (k=0; k+1 < N; ++k)
//            { ulong b = T.branching_number(k);  if ( (b!=0) && (b&1)==0 )  break; }  // A000000


//            for (k=0; k+1 < N; ++k)  if ( T.branching_number(k) > 2 )  break;  // A063895
//            for (k=0; k+1 < N; ++k)  if ( T.branching_number(k) > 3 )  break;  // A116379
//            for (k=0; k+1 < N; ++k)  if ( T.branching_number(k) > 4 )  break;  // A116380
//            for (k=0; k+1 < N; ++k)  if ( T.branching_number(k) > 5 )  break;  // A000000

//            if ( k != N )  continue;


//            for (k=1; k+1 < N; ++k)  if ( T.branching_number(k) > 2 )  break;  // A000000
            for (k=0; k+1 < N; ++k)  if ( T.branching_number(k) > 2 )  break;  // A063895
            if ( k+1 != N )  continue;
        }
#endif

#if 0
//        if ( (T.branching_number(0) & 1) == 0 )  continue;  // A000000
//        if ( (T.branching_number(0) & 1) == 1 )  continue;  // A000000

//        if ( T.max_limb_length() > 1 )  continue;  // 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, ...
//        if ( T.max_limb_length() > 2 )  continue;  // A052325
//        if ( T.max_limb_length() > 3 )  continue;  // A000000

//        if ( T.max_limb_length() == 2 )  continue;  // A000000

//        if ( T.min_limb_length() <= 1 )  continue;  // A000000
//        if ( T.min_limb_length() > 1 )  continue;  // A000000
//        if ( T.min_limb_length() == 1 )  continue;  // A000000

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

//        { ulong b[n] , s[n];
//            tree_lev_seq_branching_numbers(T.data(), n, b, s);
//            for (ulong j=0; j<n; ++j)  jjassert( b[j] == T.branching_number(j) );
//        }


//        T.print_paren_word("    ", "()");
//        T.print_paren_word("    ", "1.");

        if ( aa )
        {
            cout << endl;
            T.print_aa("");
            cout << endl;
        }

        cout << endl;

        jjassert( T.OK() );

//        fct += factorial( T.num_leaves() );  // A000000
        // 1, 1, 1, 1, 3, 5, 15, 43, 145, 457, 1671, 6323, 25263, 104335, 451501, 2014747
#endif
    }
    while ( 0 != T.next() );

    cout << " ct=" << ct << endl;
//    cout << " ct=" << fct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.0:

 time ./bin 28
arg 1: 28 == n  [Number of nodes, n>=1]  default=9
arg 2: 0 == aa  [Whether to render trees as ASCII art]  default=0
 ct=408310668
./bin 28  7.54s user 0.00s system 99% cpu 7.540 total
 ==> 408310668/7.54 == 54,152,608 per second


*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/id-tree-lev-seq-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/id-tree-lev-seq-demo.cc DEMOFLAGS=-DTIMING"
/// End:
