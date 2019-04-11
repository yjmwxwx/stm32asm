
#include "comb/subset-lex.h"

#include "comb/comb-print.h"
#include "fxttypes.h"

#include "fxtio.h"
#include "nextarg.h"

#include "jjassert.h"


//% OEIS sequence A206702:
//% Number of subsets of S of { 0, 1, 2, ..., n-1 } such that
//% for all u, v in S  u + v is not in S.


int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Size of the set (n>=1)");
    jjassert( n>=1 );
    subset_lex S(n);

    ulong ct = 0;
    ulong num = S.first();
    const ulong *x = S.data();
    do
    {
#if 1
        if ( x[0] == 0 )  goto next;

        for (ulong u=0; u<num; ++u)
        {
            for (ulong v=u; v<num; ++v)
            {
                ulong s = x[u] + x[v];
                if ( s >= n )  s -= n;
                for (ulong j=0; j<num; ++j)
                {
                    if ( s == x[j] )  goto next;
                }
            }
        }
#endif

        ++ct;
        cout << setw(4) << ct << ":";
        print_set_as_deltaset("    ", x, num, n);
        print_set("    ", x, num);
        cout << endl;

    next: ;
    }
    while ( (num = S.next()) );

    ++ct;  // add empty set

    cout << "ct=" << ct << endl;
    return 0;
}
// -------------------------

/*

1, 2, 3, 5, 7, 14, 16, 30, 38, 70, 81, 150, 164, 317, 365, 651, 693,
1376, 1357, 2728, 2647, 5458, 5094, 10645, 10098, 20657, 18208, 39071,
33615, 79672

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A206702-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A206702-demo.cc DEMOFLAGS=-DTIMING"
/// End:
