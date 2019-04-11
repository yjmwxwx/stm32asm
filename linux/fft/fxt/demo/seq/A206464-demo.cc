
#include "comb/catalan-rgs-subset-lex.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% OEIS sequence A206464:
//% Number of length-n Catalan-RGS (restricted growth strings) such that
//% the RGS is a valid mixed radix number in falling factorial basis.


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

    const ulong nh = n/2;
    ulong ct = 0;
    do
    {
        bool  qq = true;
        for (ulong j=nh, k=nh+(n&1);  j<n;  ++j, --k)
            if ( C.data()[j] > k )  { qq = false; break; }

        if ( qq )
        {
            ++ct;
#if 1
            cout << setw(4) << ct << ":";

            // print RGS:
            print_vec("    ", C.data(), n, true);

            cout << setw(4) << C.tr_;

            // print paren string:
            const char *str = C.paren_string();
            cout << "    " << str;

            // print delta set (2-ary Dyck word):
            cout << "    ";
            for (ulong k=0; k<2*n; ++k)  cout << ( str[k]=='(' ? '1' : '.' );

            cout << endl;
#endif
        }
    }
    while ( C.next() );

    cout << " ct=" << ct;
    cout << endl;

    return 0;
}
// -------------------------

/*
 for n in $(seq 15); do ./bin $n | g ct= ; done
 ct=1
 ct=2
 ct=4
 ct=10
 ct=26
 ct=74
 ct=218
 ct=672
 ct=2126
 ct=6908
 ct=22876
 ct=77100
 ct=263514
 ct=911992
 ct=3189762
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A206464-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A206464-demo.cc DEMOFLAGS=-DTIMING"
/// End:
