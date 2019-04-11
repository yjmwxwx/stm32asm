
#include "comb/young-tab-rgs.h"
#include "comb/young-tab-rgs-descents.h"
// demo-include "comb/print-young-tab-rgs-aa.cc"
// demo-include "comb/is-shifted-young-tab-rgs.h"

#include "comb/comb-print.h"  // print_set()
#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% OEIS sequence A225616:
//% Tableaux of size n with major index equal to 1 mod n.
//% A descent in a standard Young tableau is a entry i such that i+1 lies
//% strictly below and weakly left of i.
//% The major index is the sum of all such i.
//% Also sequences A161125 (descent numbers), A225617 (strict inversions),
//%   and A225618 (weak inversions).

// Cf. comb/young-tab-rgs-demo.cc

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Length of strings");
    ulong m = 0;
    NXARG(m, "Number of allowed values for digits\n"
          "         == max height of tableaux, 0 ==> all");
    if ( m > n )  m = n;
    if ( m==0 )  m = n;

    young_tab_rgs Y(n, m);

    ulong ct = 0;
    ulong sct = 0;


    bool tq = 1;
    NXARG(tq, "Whether do draw tableaux (as ASCII art)");

    ulong j = 0;
    do
    {
        ++ct;

        if ( (Y.major_index() % n) == 1 )  ++sct;  // major index == 1 (mod n): A225616

//        sct += Y.major_index();  // A000000
//        sct += Y.descent_number();  // A161125

//        sct += Y.number_strict_inversions();  // A225617
//        sct += Y.number_weak_inversions();  // A225618

#ifndef TIMING
        cout << setw(4) << ct << ":  ";

        Y.print("  ");  // RGS

//        Y.print_stats("  ");  // aux: partition
//        Y.print_r("  ");  // aux:  r[i] is the row (>=1) the entry i lies in
//        cout << setw(3) << j << " ";  // leftmost change

//        Y.print_stats("    ");  // stats: partition of n
//        cout << setw(3) << Y.height();  // height


        if ( tq )
        {
            cout << endl;
            Y.print_aa( 1 );  // arg is offset (0 or 1)
            ulong D[128];
            const ulong dn = Y.descent_set( D );
            print_set("  ", D, dn);
            cout << endl;
        }


        cout << endl;

        jjassert( Y.OK() );
#endif  // TIMING
    }
    while ( (j=Y.next()) );



#ifndef TIMING
    cout << " ct=" << ct;
    cout << "    sct=" << sct;
#else
    cout << " ct=" << sct;
#endif
    cout << endl;

    return 0;
}
// -------------------------

/*
 echo $(for n in $(seq 1 15); do ./bin $n ; done | g ct=) | sed 's/ ct=/, /g;'
ct=0, 1, 1, 2, 5, 12, 33, 94, 290, 949, 3245, 11666, 43731, 170748, 689957
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A225616-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A225616-demo.cc DEMOFLAGS=-DTIMING"
/// End:

