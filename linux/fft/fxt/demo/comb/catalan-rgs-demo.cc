
#include "comb/catalan-rgs.h"
#include "comb/paren-string-to-rgs.h"
// demo-include "comb/paren-string-to-rgs.cc"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Catalan restricted growth strings (RGS):
//% strings a[0,1,...,n-1] where a[0]=0 and a[k] <= a[k-1] + 1.
//% Lexicographic order.
//% See OEIS sequences A000108 (Catalan numbers) and A239903 (Catalan RGS).

// Cf. comb/motzkin-nonflat-rgs-lex-demo.cc for Motzkin (nonflat) RGS.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of paren pairs");

    catalan_rgs C(n);

    ulong ct = 0;

#ifdef TIMING

#ifdef CATALAN_RGS_FIXARRAYS
    cout << "CATALAN_RGS_FIXARRAYS is defined" << endl;
#endif
    C.first();
    do  { ++ct; }  while ( C.next() );
#else  // TIMING

    bool rq = 1;
    NXARG(rq, "whether to show RGS for reversed string");

//    C.last();
    const ulong n2 = 2*n;
    ulong j = 0;
    do
    {
#if 0 // disallow flat steps: A086246 and A001006 (Motzkin numbers)
        bool q = 1;
        const ulong *a = C.data();
        for (ulong k=1; k<n; ++k)
            if ( a[k] == a[k-1])  { q=0;  break; };
        if ( ! q )  continue;

#endif

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


//        ulong w2 = 0;  // bit-string representation
//        for (ulong k=0, m=(1UL<<(n2-1));  k<n2;  ++k, m>>=1)
//            if ( str[k]=='(' )  w2 |= m;

        if ( rq )
        {
            char str2[64];
            ulong rgs2[32];

            jjassert( paren_string_to_rgs(str, rgs2) );
            rgs_to_paren_string(rgs2, n, str2, true);
            jjassert( paren_string_to_rgs(str2, rgs2) );

            cout << "    ";
            print_vec("    ", rgs2, n, true);
//            cout << "    " << str2;
            cout << "    ";
            for (ulong k=0; k<n2; ++k)  cout << ( str2[k]=='(' ? '1' : '.' );
            jjassert( paren_string_to_rgs(str2, rgs2) );
        }

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

GCC 4.9.1:

 time ./bin 19
arg 1: 19 == n  [Number of paren pairs]  default=5
 ct=1767263190
./bin 19  5.90s user 0.00s system 99% cpu 5.901 total
 ==> 1767263190/5.90 == 299,536,133 per second


// with CATALAN_RGS_FIXARRAYS:

 time ./bin 19
arg 1: 19 == n  [Number of paren pairs]  default=5
CATALAN_RGS_FIXARRAYS is defined
 ct=1767263190
./bin 19  5.58s user 0.00s system 99% cpu 5.582 total
 ==> 1767263190/5.58 == 316,713,833 per second

*/

/*
BENCHARGS=19
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

