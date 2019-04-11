
#include "comb/change-rgs.h"

#include "comb/comb-print.h"

//#include "comb/is-change-rgs.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Change sequences (restricted growth strings, RGS), lexicographic order.
//% A change sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0,
//%   d(k)>=0, and d(k) <= 1 + chg([d(1), d(2), ..., d(k-1)]) and chg(.)
//%   counts the number of changes of its argument.
//% See OEIS sequence A000522.

// Cf. comb/descent-rgs-demo.cc for descent RGS
// Cf. comb/ascent-rgs-demo.cc for ascent RGS

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Length of strings");

    change_rgs C(n);

    ulong ct = 0;


#ifdef TIMING
    bool bw = 0;
    NXARG(bw, "Whether to generate in backward order");
#ifdef CHANGE_RGS_FIXARRAYS
    cout << "CHANGE_RGS_FIXARRAYS defined." << endl;
#endif
    if ( bw )
    {
        cout << "backward:" << endl;
        C.last();
        do  { ++ct; }  while ( C.prev() );
    }
    else
    {
        cout << "forward:" << endl;
        C.first();
        do  { ++ct; }  while ( C.next() );
    }
#else

    ulong j = 0;
    do
    {
#if 0  // no flat-steps:
        {
            const ulong *x = C.data();
            bool q = true;
            for (ulong i=1; i<n; ++i)
                if ( 0==( x[i] - x[i-1] ) )  { q=false;  break; }
            if ( ! q )  continue;  // factorial, A000142
//            if ( q )  continue;  // A002627
        }
#endif

        ++ct;


#if 1
        cout << setw(4) << ct << ":  ";

        // print RGS:
        C.print("  ", true );
        print_vec("  ", C.m_, n, true );

        cout << setw(4) << j;

        cout << endl;
        jjassert( C.OK() );
#endif
    }
    while ( (j=C.next()) );

#endif  // TIMING

    cout << " ct=" << ct;  // OEIS sequence A000522
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.8.0:

 time ./bin 13 0
arg 1: 13 == n  [Length of strings]  default=5
arg 2: 0 == bw  [Whether to generate in backward order]  default=0
CHANGE_RGS_FIXARRAYS defined.
forward:
 ct=1302061345
./bin 13 0  5.66s user 0.00s system 99% cpu 5.659 total
 ==> 1302061345/5.66 == 230,046,174 per second

 time ./bin 13 1
arg 1: 13 == n  [Length of strings]  default=5
arg 2: 1 == bw  [Whether to generate in backward order]  default=0
CHANGE_RGS_FIXARRAYS defined.
backward:
 ct=1302061345
./bin 13 1  4.89s user 0.00s system 99% cpu 4.896 total
 ==> 1302061345/4.89 == 266,270,213 per second


 time ./bin 13 0
arg 1: 13 == n  [Length of strings]  default=5
arg 2: 0 == bw  [Whether to generate in backward order]  default=0
forward:
 ct=1302061345
./bin 13 0  6.75s user 0.00s system 99% cpu 6.753 total
 ==> 1302061345/6.75 == 192,897,977 per second

 time ./bin 13 1
arg 1: 13 == n  [Length of strings]  default=5
arg 2: 1 == bw  [Whether to generate in backward order]  default=0
backward:
 ct=1302061345
./bin 13 1  6.51s user 0.00s system 99% cpu 6.514 total
 ==> 1302061345/6.51 == 200,009,423 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/change-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/change-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

