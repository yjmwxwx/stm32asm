
#include "comb/schroeder-path-lex.h"

#include "comb/is-motzkin-path.h"
#include "comb/is-schroeder-path.h"


#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"


//% Schroeder paths in lexicographic order, CAT algorithm.
//% Cf. OEIS sequence A006318: large Schroeder numbers.

//  1, 2, 6, 22, 90, 394, 1806, 8558, 41586, 206098, 1037718, ...


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Length of paths is 2*n (n>=1)");
    jjassert( n>=1 );

    schroeder_path_lex M(n);

    ulong ct = 0;

#ifdef TIMING
    do { ++ct; } while ( M.next() );
#else

    ulong j = 0;

    const ulong *x = M.data();
    const ulong n2 = 2 * n;

    do
    {
#if 0  // A001003: little Schroeder numbers, 1, 1, 3, 11, 45, 197, 903, 4279, ...
        if ( ! M.is_little_schroeder_path() )  continue;
#endif

        ++ct;
        cout << setw(4) << ct << ":  ";
        M.print("    ", true );
        cout << "    " << setw(2) << j;

        cout << "    ";
        for (ulong i=1; i<=n2; ++i)
        {
            ulong d = x[i] - x[i-1] + 1;
            cout << " " << "-0+"[d];
//            cout << " " << ")x("[d];
//            cout << " " << "DhU"[d];
//            cout << " " << "\\-/"[d];
        }

        cout << endl;

        jjassert( is_motzkin_path(x, n2) );
        jjassert( is_schroeder_path(x, n2) );
    }
    while ( (j=M.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 14
arg 1: 14 == n  [Length of paths is 2*n (n>=1)]  default=4
 ct=745387038
./bin 14  6.63s user 0.00s system 99% cpu 6.634 total
 ==> 745387038/6.63 == 112,426,400 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/schroeder-path-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/schroeder-path-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

