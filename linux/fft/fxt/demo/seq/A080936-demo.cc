
#include "comb/catalan-rgs-subset-lex.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% OEIS sequence A080936:
//% Triangle read by rows: T(n,k) is the number of Dyck paths of semilength n and height k (1<=k<=n).
//% Same as: Catalan restricted growth strings (RGS) by max digit.


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

    ulong ct = 0;
    ulong md[64];
    for (ulong j=0; j<n; ++j)  md[j] = 0;

    do
    {
        ++ct;
        ulong m = 0;  // max digit
        for (ulong j=0; j<n; ++j)
            if ( C.data()[j] > m )  m = C.data()[j];
        ++md[m];
#if 1
        cout << setw(4) << ct << ":";

        // print RGS:
        print_vec("    ", C.data(), n, true);

        cout << setw(4) << m;

        // print paren string:
        const char *str = C.paren_string();
        cout << "    " << str;

        // print delta set (2-ary Dyck word):
        cout << "    ";
        for (ulong k=0; k<2*n; ++k)  cout << ( str[k]=='(' ? '1' : '.' );

        cout << endl;
#endif
    }
    while ( C.next() );

//    for (ulong j=0,s=0; j<n; ++j)  { s+=md[j]; cout << s << ", "; }  // A080935

    for (ulong j=0; j<n; ++j)  cout << md[j] << ", ";  // A080936
    cout << " ct=" << ct;  // Catalan number n
    cout << endl;


    return 0;
}
// -------------------------

/*
 for n in $(seq 10); do ./bin $n | g ct= ; done

A080935:
1,  ct=1
1, 1,  ct=2
1, 3, 1,  ct=5
1, 7, 5, 1,  ct=14
1, 15, 18, 7, 1,  ct=42
1, 31, 57, 33, 9, 1,  ct=132
1, 63, 169, 132, 52, 11, 1,  ct=429
1, 127, 482, 484, 247, 75, 13, 1,  ct=1430
1, 255, 1341, 1684, 1053, 410, 102, 15, 1,  ct=4862
1, 511, 3669, 5661, 4199, 1975, 629, 133, 17, 1,  ct=16796


A080936:
1,  ct=1
1, 2,  ct=2
1, 4, 5,  ct=5
1, 8, 13, 14,  ct=14
1, 16, 34, 41, 42,  ct=42
1, 32, 89, 122, 131, 132,  ct=132
1, 64, 233, 365, 417, 428, 429,  ct=429
1, 128, 610, 1094, 1341, 1416, 1429, 1430,  ct=1430
1, 256, 1597, 3281, 4334, 4744, 4846, 4861, 4862,  ct=4862
1, 512, 4181, 9842, 14041, 16016, 16645, 16778, 16795, 16796,  ct=16796

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A080936-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A080936-demo.cc DEMOFLAGS=-DTIMING"
/// End:
