
#include "comb/setpart-rgs-subset-lex.h"

//#include "comb/is-setpart-rgs.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Set partitions of the n-set as restricted growth strings (RGS):
//% strings s[0, 1, ..., n-1] such that s[k] <= max(s[0], s[1], ..., s[k-1]) + 1.
//% Subset-lex order.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
#ifdef SETPART_RGS_SUBSET_LEX_SC
    NXARG(n, "Length of RGS");
#else
    NXARG(n, "Length of RGS (n>=2)");
    jjassert( n>=2 );
#endif

    setpart_rgs_subset_lex P(n);
    bool bw = 0;
    NXARG(bw, "Whether to generate backward order");
    if ( bw )  P.last();

    ulong ct = 0;
#ifdef TIMING
#ifdef SETPART_RGS_SUBSET_LEX_SC
    cout << "SETPART_RGS_SUBSET_LEX_SC is defined" << endl;
#endif
    if ( bw )
    {
        cout << "backward:" << endl;
        do  { ++ct; }  while ( P.prev() );
    }
    else
    {
        cout << "forward:" << endl;
        do  { ++ct; }  while ( P.next() );
    }

#else

    do
    {
//        if ( P.num_sets() != 4 )  continue;

        cout << setw(4) << ct << ":";
        ++ct;

        // print RGS:
        P.print("  ", true);
        cout << setw(4) << P.tr_;
        print_vec("    ", P.m_, n, true);
        P.print_sets("    ", true);
        cout << endl;

        jjassert( P.OK() );
    }
    while ( bw ? P.prev() : P.next() );
#endif  // TIMING

    cout << " ct=" << ct;
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 15 0
SETPART_RGS_SUBSET_LEX_SC is defined
forward:
 ct=1382958545
./bin 15 0  2.78s user 0.00s system 99% cpu 2.786 total
 ==> 1382958545/2.78 == 497,467,102 per second

 time ./bin 15 1
SETPART_RGS_SUBSET_LEX_SC is defined
backward:
 ct=1382958545
./bin 15 1  2.43s user 0.00s system 99% cpu 2.433 total
 ==> 1382958545/2.43 == 569,118,742 per second

*/

/*
BENCHARGS=15 0
BENCHARGS=15 1
*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/setpart-rgs-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/setpart-rgs-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

