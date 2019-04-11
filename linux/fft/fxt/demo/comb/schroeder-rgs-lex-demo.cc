
#include "comb/schroeder-rgs-lex.h"
#include "comb/is-schroeder-rgs.h"

#include "comb/comb-print.h"

//#include "comb/fact2perm.h"
//#include "perm/permq.h"
//#include "perm/perm-genus.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Schroeder restricted growth strings (RGS):
//% a Schroeder RGS is a word a[0,1,2,...,n-1] where
//% a[k] <= k + 1 (rising factorial numbers),
//% a[0] <= m0 and  a[k] + 1 >= max(j=1..k-1, a[j]).
//% m0 == 0  ==> little Schroeder numbers, A001003.
//% m0 == 1  ==> large Schroeder numbers, A006318.
//% Lexicographic order.

// m0 == 0 ==> ,  g.f. (1 + x - sqrt(1 - 6*x + x^2))/(4*x) = 2/(1 + x + sqrt(1 - 6*x + x^2)).
// m0 == 1 ==> ,  g.f. (1 - x - sqrt(1 - 6*x + x^2))/(2*x)
// m0 == 2 ==> A177010,  g.f. ((1-x)^2+(1+x)*sqrt(1-6*x+x^2))/2 (abs. values)
// m0 == 3 ==> A000000

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Length of RGS");
    ulong m0 = 1;
    NXARG(m0, "Max value of first digit: 0 or 1");

    schroeder_rgs_lex S(n, m0);

    ulong ct = 0;

#ifdef TIMING
#ifdef SCHROEDER_RGS_LEX_FIXARRAYS
    cout << "SCHROEDER_RGS_LEX_FIXARRAYS is defined" << endl;
#endif
    S.first();
    do  { ++ct; }  while ( S.next() );

#else  // TIMING

    ulong j = 0;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

        S.print("  ", true );

//        cout << setw(4) << j;
//        print_vec("  ", S.m_+1, n, true );  // internal data

        cout << endl;

        jjassert( S.OK() );
    }
    while ( (j=S.next()) );

#endif  // TIMING

    cout << " ct=" << ct;  // Schroeder number
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.8.0:

 time ./bin 14
arg 1: 14 == n  [Length of RGS]  default=4
arg 2: 1 == m0  [Max value of first digit: 0 or 1]  default=1
 ct=745387038
./bin 14  4.08s user 0.00s system 99% cpu 4.086 total
 ==> 745387038/4.08 == 182,692,901 per second


 time ./bin 14
arg 1: 14 == n  [Length of RGS]  default=4
arg 2: 1 == m0  [Max value of first digit: 0 or 1]  default=1
SCHROEDER_RGS_LEX_FIXARRAYS is defined
 ct=745387038
./bin 14  2.32s user 0.00s system 99% cpu 2.327 total
 ==> 745387038/2.32 == 321,287,516 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/schroeder-rgs-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/schroeder-rgs-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

