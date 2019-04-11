
#include "comb/perm-ives.h"

#include "comb/fact2perm.h"

#include "comb/comb-print.h"
#include "comb/check-permgen.h"

#include "nextarg.h"
#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"




//% Permutations in the order c by Ives (inverse permutations are Ives' order a).

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements to permute");

    perm_ives P(n);
    P.first();

    check_permgen C(n);
    C.first( P.data() );

    ulong ct = 0;

#ifdef TIMING

#ifdef PERM_IVES_OPT
    cout << "PERM_IVES_OPT is defined." << endl;
#endif
#ifdef PERM_IVES_OPT2
    cout << "PERM_IVES_OPT2 is defined." << endl;
#endif
#ifdef PERM_IVES_FIXARRAYS
    cout << "PERM_IVES_FIXARRAYS is defined." << endl;
#endif

    do
    {
        ++ct;
    }
    while ( P.next() );


#else  // TIMING

    const bool dfz= true;  // whether to print dots for zeros
    ulong fc[32];  // factorial number
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
        P.print("  ", dfz);
        P.print_inv("    ", dfz);
//        cout << "  ctm=" << setw(3) << P.ctm_;

//        perm2ffact(P.data(), n, fc);
        perm2ffact(P.invdata(), n, fc);
        print_mixedradix("    ", fc, n-1, dfz);

        cout << endl;
        jjassert( ! C.is_repeat() );
    }
    while ( P.next() );

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 12
 ct=479001600
./bin 12  2.65s user 0.06s system 99% cpu 2.717 total
 ==> 479001600/2.65 == 180,755,320 per second

with PERM_IVES_FIXARRAYS defined:
 time ./bin 12
./bin 12  2.51s user 0.05s system 99% cpu 2.590 total
 ==> 479001600/2.51 == 190,837,290 per second

with PERM_IVES_OPT defined:
 time ./bin 12
./bin 12  2.94s user 0.05s system 99% cpu 2.989 total
 ==> 479001600/2.94 == 162,925,714 per second

with both defined:
 time ./bin 12
./bin 12  2.49s user 0.07s system 99% cpu 2.559 total
 ==> 479001600/2.49 == 192,370,120 per second


with PERM_IVES_OPT2 defined (alternative branch code):
 time ./bin 12
arg 1: 12 == n  [Number of elements to permute]  default=4
./bin 12  2.47s user 0.06s system 99% cpu 2.531 total
 ==> 479001600/2.47 == 193,927,773 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-ives-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-ives-demo.cc DEMOFLAGS=-DTIMING"
/// End:
