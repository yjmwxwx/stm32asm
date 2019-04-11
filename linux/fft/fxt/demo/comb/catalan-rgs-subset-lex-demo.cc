
#include "comb/catalan-rgs-subset-lex.h"

#include "comb/reverse-paren-string.h"
#include "comb/is-paren-string.h"
#include "comb/is-catalan-rgs.h"

#include "comb/paren-string-to-rgs.h"
#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Catalan restricted growth strings (RGS):
//% strings a[0,1,...,n-1] where a[0]=0 and a[k] <= a[k-1] + 1.
//% Subset-lex order.

// Cf. comb/catalan-rgs-gslex-demo.cc for gslex order

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
#ifdef CATALAN_RGS_SUBSET_LEX_SC
    NXARG(n, "Number of paren pairs");
#else
    NXARG(n, "Number of paren pairs (n>=2)");
    jjassert( n>=2 );
#endif

    catalan_rgs_subset_lex C(n);
    bool bw = 0;
    NXARG(bw, "Whether to generate backward order");
    if ( bw )  C.last();

    ulong ct = 0;
#ifdef TIMING
#ifdef CATALAN_RGS_SUBSET_LEX_SC
    cout << "CATALAN_RGS_SUBSET_LEX_SC is defined" << endl;
#endif
    if ( bw )
    {
        cout << "backward:" << endl;
        do  { ++ct; }  while ( C.prev() );
    }
    else
    {
        cout << "forward:" << endl;
        do  { ++ct; }  while ( C.next() );
    }

#else  // TIMING

    ulong *rgs2 = new ulong[n];  // RGS for reversed strings
    const ulong n2 = 2*n;
    char *str2 = new char[n2+1];  // for reversed strings
    str2[n2] = 0;

    bool q;
    do
    {
        ++ct;

        cout << setw(4) << ct << ":";

        C.print("    ", true);

        cout << setw(4) << C.tr_;

        const char *str = C.bit_string();
        cout << "    " << str;

//        cout << "    " << C.paren_string();

#if 1  // show reversed paren-string and its RGS
        reverse_paren_string(str, n2, str2);  // reversed string
        paren_string_to_rgs( str2, rgs2 );  // "reversed" RGS
        print_vec("    ", rgs2, n, true);
        cout << "    ";
        cout << str2;
        jjassert( is_catalan_rgs(rgs2, n) );
        jjassert( is_paren_string(str2, n2) );
#endif

        cout << endl;

        jjassert( C.OK() );

        q = ( bw ? C.prev() : C.next() );
    }
    while ( q );

    delete [] rgs2;
    delete [] str2;

#endif  // TIMING

    cout << " ct=" << ct;  // Catalan number n
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 19 0
CATALAN_RGS_SUBSET_LEX_SC is defined
forward:
 ct=1767263190
./bin 19 0  4.34s user 0.00s system 99% cpu 4.346 total
 ==> 1767263190/4.34 == 407,203,500 per second

// when CATALAN_RGS_SUBSET_LEX_SC is not defined:
./bin 19 0  4.52s user 0.00s system 99% cpu 4.529 total


 time ./bin 19 1
CATALAN_RGS_SUBSET_LEX_SC is defined
backward:
 ct=1767263190
./bin 19 1  3.31s user 0.00s system 99% cpu 3.312 total
 ==> 1767263190/3.31 == 533,916,371 per second

// when CATALAN_RGS_SUBSET_LEX_SC is not defined:
./bin 19 1  3.55s user 0.00s system 99% cpu 3.549 total


GCC 4.8.0:

 time ./bin 19 0
CATALAN_RGS_SUBSET_LEX_SC is defined
forward:
 ct=1767263190
./bin 19 0  4.60s user 0.00s system 99% cpu 4.606 total
 ==> 1767263190/4.60 == 384,187,650 per second

 time ./bin 19 0
forward:
 ct=1767263190
./bin 19 0  4.91s user 0.00s system 99% cpu 4.907 total
 ==> 1767263190/4.91 == 359,931,403 per second


 time ./bin 19 1
CATALAN_RGS_SUBSET_LEX_SC is defined
backward:
 ct=1767263190
./bin 19 1  3.76s user 0.00s system 99% cpu 3.766 total
 ==> 1767263190/3.76 == 470,016,805 per second

 time ./bin 19 1
backward:
 ct=1767263190
./bin 19 1  3.60s user 0.01s system 99% cpu 3.608 total
 ==> 1767263190/3.60 == 490,906,441 per second

*/

/*
BENCHARGS=19 0
BENCHARGS=19 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-rgs-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-rgs-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

