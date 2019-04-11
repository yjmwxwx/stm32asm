
#include "comb/young-tab-rgs.h"
#include "comb/young-tab-rgs-descents.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% OEIS sequence A247386:
//% Sum of the major index over all standard Young tableaux with n cells.


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of cells");
    ulong m = 0;
//    NXARG(m, "Number of allowed values for digits\n"
//          "         == max height of tableaux, 0 ==> all");
//    if ( m>n )  m = n;
//    if ( m==0 )  m = n;

    young_tab_rgs Y(n, m);

    ulong ct = 0;
    do
    {
#if 0   // only chess tableaux
        if ( ! Y.is_chess_tableau() )  continue;
#endif

        ct += young_tab_rgs_major_index( Y.data(), n );;

    }
    while ( Y.next() );

    cout << " ct=" << ct;
    cout << endl;

    return 0;
}
// -------------------------


/*

echo $(for n in $(seq 0 100); do ./bin $n | g 'ct=' ; done) | sed 's/ ct=/, /g;'
0, 0, 1, 6, 30, 130, 570, 2436, 10696, 47160, 213660, 981640, 4625016, ...

for chess tableaux:
0, 0, 1, 3, 12, 30, 90, 210, 672, 1512, 4860, 11220, 36432, 88920, 286104, 741720, ...
A000000

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A247386-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A247386-demo.cc DEMOFLAGS=-DTIMING"
/// End:
