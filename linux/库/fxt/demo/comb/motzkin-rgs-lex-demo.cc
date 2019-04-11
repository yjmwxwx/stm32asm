
#include "comb/motzkin-rgs-lex.h"
#include "comb/paren-string-to-rgs.h"

#include "comb/comb-print.h"

//#include "comb/fact2perm.h"
//#include "perm/permq.h"
//#include "perm/perm-genus.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Motzkin restricted growth strings (RGS):
//% words a[0,1,...,n-1] where a[0] = 0, a_[k] <= a[k-1] + 1,
//%  and there are no two consecutive up-steps.
//% lexicographic order.
//% Cf. OEIS sequence A001006.

// Cf. comb/motzkin-nonflat-rgs-lex-demo.cc for Motzkin (nonflat) RGS.
// Cf. comb/motzkin-path-lex-demo.cc for Motzkin paths.
// Cf. comb/catalan-rgs-demo.cc for Catalan RGS.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Length of RGS");
    ulong i = 1;
    NXARG(i, "At most i rises in a row; at most i+1 consecutive ones in the Dyck word");
    // 0 ==> only the all-zero word
    // 1 ==> Motzkin RGS (OEIS sequence A001006)
    // 2 ==> (A036765)
    // 3 ==> (A036766),  4 ==> (A036767)
    // 5 ==> (A036768),  6 ==> (A036769)
    // i ==> g.f. A(x) where x*A(x) is the series reversion of x/(1+x+x^2+...+x^(i+1)).
    // i>=n-1 ==> Catalan RGS (A000108)

    motzkin_rgs_lex M(n, i);

    ulong ct = 0;

#ifdef TIMING
#ifdef MOTZKIN_RGS_LEX_FIXARRAYS
    cout << "MOTZKIN_RGS_LEX_FIXARRAYS is defined" << endl;
#endif

    M.first();
    do  { ++ct; }  while ( M.next() );

#else  // TIMING

//    ulong Z[64];  // for permutation
//    ulong W[64];  // for genus computation
    ulong j = 0;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":  ";

        M.print("  ", true );

        cout << setw(4) << j;

//        print_vec("  ", M.s_, n, true );  // internal data

        cout << "    " << M.bit_string();
//        cout << "    " << M.paren_string();

//        rfact2perm( M.data()+1, n, Z);
//        perm_rev_compl(Z, n);  // reversed complement
//        print_vec("    ", Z, n );
//        ulong g = perm_genus(Z, n, W);
//        cout << "  " << g;

        cout << endl;

        jjassert( M.OK() );
//        jjassert( is_involution(Z, n) );  // not true

    }
    while ( (j=M.next()) );

#endif  // TIMING

    cout << " ct=" << ct;  // Motzkin number
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 24
arg 1: 24 == n  [Length of RGS]  default=6
arg 2: 1 == i  [At most i rises in a row]  default=1
 ct=3192727797
./bin 24  15.14s user 0.00s system 99% cpu 15.142 total
 ==> 3192727797/15.14 == 210,880,303 per second


GCC 4.8.0:

 time ./bin 23
arg 1: 23 == n  [Length of RGS]  default=6
arg 2: 1 == i  [At most i rises in a row; at most i+1 consecutive ones in the Dyck word]  default=1
 ct=1129760415
./bin 23  5.06s user 0.00s system 99% cpu 5.058 total
 ==> 1129760415/5.06 == 223,272,809 per second

 time ./bin 23
arg 1: 23 == n  [Length of RGS]  default=6
arg 2: 1 == i  [At most i rises in a row; at most i+1 consecutive ones in the Dyck word]  default=1
MOTZKIN_RGS_LEX_FIXARRAYS is defined
 ct=1129760415
./bin 23  6.08s user 0.00s system 99% cpu 6.079 total
 ==> 1129760415/6.08 == 185,815,857 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/motzkin-rgs-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/motzkin-rgs-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

