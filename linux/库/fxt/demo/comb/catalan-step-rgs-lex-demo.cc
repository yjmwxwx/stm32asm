
#include "comb/catalan-step-rgs-lex.h"
#include "comb/is-catalan-step-rgs.h"
#include "comb/catalan-step-rgs-to-paren-string.h"

#include "comb/is-paren-string.h"


#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Catalan (step-)RGS for lattice paths from (0,0) to (n,n)
//% that do not go below the diagonal (k, k) for 0 <= k <= n.
//% Lexicographic order.
//% Cf. OEIS sequence A000108.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Catalan (step-)RGS for paths from (0,0) to (n,n)");

    catalan_step_rgs_lex C(n);

    ulong ct = 0;

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "With benchmark: whether do generate in backward order");
    if ( !bq )
    {
        C.first();
        cout << "forward:" << endl;
        do  { ++ct; }  while ( C.next() );
    }
    else
    {
        C.last();
        cout << "backward:" << endl;
        do  { ++ct; }  while ( C.prev() );
    }
#else

    bool pq = 0;
    NXARG(pq, "Whether do draw path (as ASCII art)");

    char * str = new char[2*n+1];  // parenthesis string

    ulong j = 0;  // position of leftmost change
    do
    {
#if 0
        const ulong *x = C.data();
        bool q = true;
        for (ulong k=1; k<n; ++k)
//            if ( x[k]-x[k-1] > 2 )  // A005773
            if ( x[k]-x[k-1] == 1 )  // A001006 (Motzkin numbers)
            { q=false; break; }
        if ( ! q )  continue;
        // A005773: directed animals of size n (or directed n-ominoes in standard position).
#endif
#if 0
        const ulong *x = C.data();
        bool q = true;
        for (ulong k=1; k<n; ++k)
            if ( (x[k]-x[k-1]) % 3 == 2 )  // A000000
            { q=false; break; }
        if ( ! q )  continue;
        // 1, 2, 4, 9, 23, 62, 170, 476, 1366, 3992, 11806, 35268, ...
#endif
        ++ct;

        cout << setw(4) << ct << ":";
        C.print("  ", true);
        cout << "  " << j;

        catalan_step_rgs_to_paren_string(C.data(), n,  str);
        cout << "    " << str;

        cout << endl;

        if ( pq )
        {
            C.print_aa();
            cout << endl;
        }

        jjassert( C.OK() );
        jjassert( is_paren_string(str, 2*n) );
    }
    while ( (j=C.next()) );


    delete [] str;

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 19 0
arg 1: 19 == n  [Catalan (step-)RGS for paths from (0,0) to (n,n)]  default=5
arg 2: 0 == bq  [With benchmark: whether do generate in backward order]  default=0
forward:
 ct=1767263190
./bin 19 0  4.27s user 0.00s system 99% cpu 4.269 total
 ==> 1767263190/4.27 == 413,878,967 per second

 time ./bin 19 1
arg 1: 19 == n  [Catalan (step-)RGS for paths from (0,0) to (n,n)]  default=5
arg 2: 1 == bq  [With benchmark: whether do generate in backward order]  default=0
backward:
 ct=1767263190
./bin 19 1  4.71s user 0.00s system 99% cpu 4.711 total
 ==> 1767263190/4.71 == 375,215,114 per second
*/

/*
BENCHARGS=19
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-step-rgs-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-step-rgs-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

