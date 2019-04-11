
#include "comb/perm-rev.h"

#include "comb/comb-print.h"
#include "comb/mixedradix.h"
#include "perm/perminvert.h"

//#include "comb/fact2perm.h"
//#include "aux1/copy.h"

#include "aux0/factorial.h"
#include "comb/check-permgen.h"
#include "jjassert.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"

//#include "perm/perminvert.h"


//% Permutations by prefix reversals, CAT algorithm.

//#define TIMING  // uncomment to disable printing



int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements to permute");

    perm_rev P(n);
    P.first();
//    P.last();

    ulong ct = 0;
    ulong *t1 = new ulong[n];  // aux
//    ulong *t2 = new ulong[n];  // aux

#ifdef TIMING
    do
    {
        ++ct;
    }
    while ( P.next() );
//    while ( P.prev() );

#else  // TIMING

    const ulong nfh = factorial(n)/2;

    check_permgen C(n);
    C.first(t1);  // inverse permutations(!)

    const bool dfz= true;  // whether to print dots for zeros
    const ulong *x = P.data();

    do
    {
        cout << setw(4) << ct << ":";
        P.print("    ", dfz);
        print_mixedradix("    ", P.d_, n-1, dfz);

        make_inverse(x, t1, n);
        print_perm("        ", t1, n, dfz);

        if ( ct<nfh )
        {
            jjassert( ! C.is_repeat() );
            jjassert( ! C.is_repeat_rev() );
        }

//        acopy(x, t1, n);
//        reverse(t1, n);
//        perm2ffact_rev(t1, n, t2);
//        print_mixedradix("    ", t2, n-1, dfz);

        cout << endl;
        ++ct;
    }
    while ( P.next() );

#endif // TIMING

    cout << " ct=" << ct << endl;

    delete [] t1;
//    delete [] t2;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 12
arg 1: 12 == n  [Number of elements to permute]  default=4
 ct=479001600
./bin 12  3.39s user 0.05s system 100% cpu 3.439 total
 ==> 479001600/3.39 == 141,298,407 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12
./bin 12  2.24s user 0.02s system 99% cpu 2.255 total
 ==> 479001600/2.24 == 213,840,000 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-rev-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-rev-demo.cc DEMOFLAGS=-DTIMING"
/// End:

