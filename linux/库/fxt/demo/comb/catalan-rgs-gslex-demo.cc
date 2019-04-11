
#include "comb/catalan-rgs-gslex.h"

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
//% Ordering similar to gslex (and subset-lex) order.
//% Loopless algorithm.

// Cf. comb/catalan-rgs-subset-lex-demo.cc for subset-lex order

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of paren pairs");

    catalan_rgs_gslex C(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( C.next() );

#else  // TIMING

    const ulong * rgs = C.data();
    ulong *rgs2 = new ulong[n];  // RGS for reversed strings
    const ulong n2 = 2*n;
    char *str2 = new char[n2+1];  // for reversed strings
    str2[n2] = 0;

    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

        print_vec("    ", rgs, n, true);

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
        jjassert( is_paren_string(str, n2) );
    }
    while ( C.next() );

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

 time ./bin 19
 ct=1767263190
./bin 19  5.73s user 0.00s system 99% cpu 5.735 total

 ==> 1767263190/5.73 == 308,422,895 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-rgs-gslex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-rgs-gslex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

