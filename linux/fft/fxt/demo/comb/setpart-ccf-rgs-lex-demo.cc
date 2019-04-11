
#include "comb/setpart-ccf-rgs-lex.h"
#include "comb/is-setpart-ccf-perm.h"

#include "comb/fact2perm.h"
#include "perm/perm2ccf.h"
#include "perm/printcycles.h"

#include "comb/comb-print.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% Restricted growth strings (RGS) for set partitions:
//%   each digit a[k] < k and a[k-1] != 0 implies a[k] <= a[k-1].
//% The RGS correspond to permutations in canonical cycle form (CCF)
//%   that are valid set partitions.
//% Same as: maps from {1, 2, 3, ..., n} to {0, 1, 2, 3, ..., n}
//%   such that f(x) < x and f(x-1) != 0 implies f(x) <= f(x-1).

//#define TIMING  // uncomment to disable printing



int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "RGS of length n");

    setpart_ccf_rgs_lex P(n);

    ulong *F = new ulong[n];
    ulong *Z = new ulong[n];

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else

    do
    {
#if 0   // no succession v, v:  A000000
        // 1, 1, 1, 1, 3, 6, 19, 64, 235, 982, 4430, 21583, 113115, 632230, 3750449
        { const ulong *x = P.data();
            bool q = true;
            for (ulong k=1; k<n; ++k)
                if ( x[k] == x[k-1] )  { q=0;  break; }
            if ( !q )  continue;
        }
#endif

        ++ct;
        cout << setw(4) << ct << ":";

        rfact2perm(P.data()+1, n, Z);
        perm_rev_compl(Z, n);  // reversed complement

        P.print("    ", true);  // RGS
//        print_vec("    ", Z, n, true);  // as perm
//        print_ccf("    ", Z, n);  // set partition with last elements minimal
        bool q = is_setpart_ccf_perm(Z, n);
        ccf2perm(Z, n, F);  // make that a permutation
//        print_vec("    ", F, n);
        print_cycles("    ", F, n);  // cycles are a set partition

        cout << endl;
        jjassert( q );

        jjassert( P.OK() );
    }
    while ( (P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;  // A000110

    delete [] F;
    delete [] Z;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 15
arg 1: 15 == n  [RGS of length n]  default=4
  ct=1382958545
./bin 15  4.36s user 0.00s system 99% cpu 4.364 total
 ==> 1382958545/4.36 == 317,192,326 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/setpart-ccf-rgs-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/setpart-ccf-rgs-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

