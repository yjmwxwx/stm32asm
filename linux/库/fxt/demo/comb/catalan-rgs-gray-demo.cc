
#include "comb/catalan-rgs-gray.h"
#include "comb/paren-string-to-rgs.h"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Catalan restricted growth strings (RGS):
//% strings a[0,1,...,n-1] where a[0]=0 and a[k] <= a[k-1] + 1.
//% Gray code for parenthesis strings (but not for the RGS).

//#define TIMING  // uncomment to disable printing

#define SHOW_REVERSED  // to show RGS for reversed string


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of paren pairs");
    bool dr0 = true;
    NXARG(dr0, "Whether to start with ()()()...(), else (((...)))");
//    NXARG(dr0, "Starting direction in recursion");

    catalan_rgs_gray C(n);
    C.first(dr0);

    ulong ct = 0;

#ifdef TIMING
//    bool bw = 0;
//    NXARG(bw, "Whether to generate backward order");
//
//    if ( bw )
//    {
//        C.last();
//        do  { ++ct; }  while ( C.prev() );
//    }
//    else
    {
        C.first(dr0);
        do  { ++ct; }  while ( C.next() );
    }
#else

//    C.last();

    const ulong n2 = 2*n;
    ulong j = 0;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

        // print RGS:
        C.print("  ", true );

        cout << setw(4) << j;

        // print paren string:
        const char *str = C.paren_string();
        cout << "    " << str;

        // print delta set:
        cout << "    ";
        for (ulong k=0; k<n2; ++k)  cout << ( str[k]=='(' ? '1' : '.' );

//        // The (reversed and) complemented bit string is homogeneous:
//        cout << "    ";
//        for (ulong k=n2-1; (long)k>=0; --k)  cout << ( str[k]=='(' ? '.' : '1' );


        ulong w2 = 0;  // bit-string representation
        for (ulong k=0, m=(1UL<<(n2-1));  k<n2;  ++k, m>>=1)
            if ( str[k]=='(' )  w2 |= m;

#ifdef SHOW_REVERSED
        char str2[64];
        ulong rgs2[32];
        // only one position changes at each step,
        // but in general by more than one unit.
        // All changes are homogeneous
        jjassert( paren_string_to_rgs(str, rgs2) );
        rgs_to_paren_string(rgs2, n, str2, true);
        jjassert( paren_string_to_rgs(str2, rgs2) );

        cout << "    ";
        print_vec("    ", rgs2, n, true);
        cout << "    ";
        for (ulong k=0; k<n2; ++k)  cout << ( str2[k]=='(' ? '1' : '.' );
        jjassert( paren_string_to_rgs(str2, rgs2) );
#endif

        cout << endl;
        jjassert( C.OK() );
    }
    while ( (j=C.next()) );
//    while ( (j=C.prev()) );

#endif  // TIMING

    cout << " ct=" << ct;  // Catalan number n
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 18 0
arg 1: 18 == n  [Number of paren pairs]  default=5
arg 2: 0 == dr0  [Starting direction in recursion]  default=1
 ct=477638700
./bin 18 0  2.98s user 0.00s system 99% cpu 2.985 total
 ==> 477638700/2.98 == 160,281,442 per second

 time ./bin 18 1
same (as the very same update step is used)

*/


/*
BENCHARGS=18 0
BENCHARGS=18 1
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-rgs-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-rgs-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

