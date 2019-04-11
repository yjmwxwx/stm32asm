
#include "comb/ordered-tree-lev-seq.h"
#include "comb/tree-lev-seq-aux.h"

#include "fxtio.h"

#include "fxttypes.h"
#include "nextarg.h" // NXARG()
#include "jjassert.h"

//% Level sequences for ordered rooted trees.
//% Cf. OEIS sequence A000108.

// Cf. comb/tree-lev-seq-demo.cc for unordered trees.
// Cf. comb/catalan-demo.cc for Catalan RGS.


//#define TIMING // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of non-root nodes");

    bool aa = false;
    NXARG(aa, "Whether to render trees as ASCII art");

    ordered_tree_lev_seq T(n);
#ifdef TIMING
#endif

    ulong ct = 0;
    do
    {
#if 0
        if ( ! T.is_balanced() )  continue;  // A079500 and A007059
#endif
#if 0
        {  ulong k;
            const ulong N = T.size();
#define NXT { break; }  if ( k+1 <= N )  continue;

            const ulong *x = T.data();  (void)x;
            for (k=1; k+1 <= N; ++k)  if ( x[k] == x[k+1] )  NXT;  // A001006
//            for (k=1; k+1 <= N; ++k)  if ( x[k] == x[k+1] + 1 )  NXT;  // A000000

//            for (k=1; k+1 <= N; ++k)  if ( T.branching_number(k)==1 )  NXT;  // A001006
//            for (k=0; k+1 <= N; ++k)  if ( T.branching_number(k)==1 )  NXT;  // A005043

            // no odd out-degrees:
//            for (k=1; k+1 <= N; ++k)  if ( (T.branching_number(k)&1)==1 )  NXT;  // A047749
//            for (k=0; k+1 <= N; ++k)  if ( (T.branching_number(k)&1)==1 )  NXT;  // A001764 with zeros

            // no even out-degrees for internal nodes:
//            for (k=1; k+1 <= N; ++k)
//            { ulong b = T.branching_number(k);  if ( (b!=0) && (b&1)==0 )  NXT; }  // A143017
//            for (k=0; k+1 <= N; ++k)
//            { ulong b = T.branching_number(k);  if ( (b!=0) && (b&1)==0 )  NXT; }  // A101785
        }
#endif
#if 0
//        if ( ! T.is_balanced() )  continue;  // A079500 and A007059

//        if ( (T.branching_number(0) & 1) == 0 )  continue;  // A000958
//        if ( (T.branching_number(0) & 1) == 1 )  continue;  // A000957

        if ( T.max_limb_length() > 1 )  continue;  // A082582 (Dyck paths w/o UUDD)
        // cf. A086581 (no DDUU) and A025242
//        if ( T.max_limb_length() > 2 )  continue;  // A178520 (no UUUDDD)
//        if ( T.max_limb_length() > 3 )  continue;  // A000000
//        if ( T.max_limb_length() > 4 )  continue;  // A000000

//        if ( T.max_limb_length() == 1 )  continue;  // A071740
//        if ( T.max_limb_length() == 2 )  continue;  // A000000
//        if ( T.max_limb_length() == 3 )  continue;  // A000000

//        if ( T.min_limb_length() <= 1 )  continue;  // A004148 (no UUU and no DDD; all pyramid sizes >= 2)
//        if ( T.min_limb_length() <= 2 )  continue;  // A023432
//        if ( T.min_limb_length() <= 3 )  continue;  // A023427, A216116

//        if ( T.min_limb_length() != 1 )  continue;  // A000000
//        if ( T.min_limb_length() != 2 )  continue;  // A000000
//        if ( T.min_limb_length() != 3 )  continue;  // A000000

#endif

        ++ct;

#ifndef TIMING


        cout << setw(4) << ct << ":";
        T.print("  ");

//        cout << "    Bq =[ "; for (ulong i=0; i<=n; ++i)  cout << T.is_branch(i) << " "; cout << "]";
//        cout << "    Bn =[ "; for (ulong i=0; i<=n; ++i)  cout << tree_lev_seq_branching_number(T.data(), n, i) << " "; cout << "]";
//        cout << "    Lq =[ "; for (ulong i=0; i<=n; ++i)  cout << T.is_leaf(i) << " "; cout << "]";
//        cout << "    LL =[ "; for (ulong i=0; i<=n; ++i)  cout << T.limb_length(i) << " "; cout << "]";
//        cout << setw(4) << T.min_limb_length();
//        cout << setw(4) << T.max_limb_length();
//        cout << setw(4) << T.height();

//        T.print_branching_numbers("    ");

//        T.print_paren_word("    ", "()");
//        T.print_paren_word("    ", "1.");


        if ( aa )
        {
            cout << endl;
            T.print_aa("");
            cout << endl;
        }

        cout << endl;

//        { const ulong N=n+1;   ulong b[N] , s[N];
//            tree_lev_seq_branching_numbers(T.data(), N, b, s);
//            for (ulong j=0; j<N; ++j)  jjassert( b[j] == T.branching_number(j) );
//        }

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

GCC 4.9.0:

 time ./bin 19
arg 1: 19 == n  [Number of nodes, n>=1]  default=4
arg 2: 0 == aa  [Whether to render trees as ASCII art]  default=0
 ct=1767263190
./bin 19  5.24s user 0.00s system 99% cpu 5.245 total
 ==> 1767263190/5.24 == 337,263,967 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ordered-tree-lev-seq-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ordered-tree-lev-seq-demo.cc DEMOFLAGS=-DTIMING"
/// End:
