
#include "comb/isoscent-rgs.h"

#include "comb/comb-print.h"

//#include "comb/is-isoscent-rgs.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Isoscent sequences (restricted growth strings, RGS).
//% An isoscent sequence is a sequence [d(1), d(2), ..., d(n)] where
//%  d(1)=0, d(k)>=0, and d(k) <= 1 + eq([d(1), d(2), ..., d(k-1)])
//%  where eq(.) counts the number of flat steps of its argument.
//% Lexicographic order.
//% See OEIS sequence A000110.

// Cf. comb/isoscent-rgs-stats-demo.cc for stats for isoscent RGS
// Cf. comb/ascent-rgs-demo.cc for ascent RGS

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Length of strings");

    isoscent_rgs D(n);

    ulong ct = 0;


#ifdef TIMING
//    bool bw = 0;
//    NXARG(bw, "Whether to generate in backward order");
#ifdef ISOSCENT_RGS_FIXARRAYS
    cout << "ISOSCENT_RGS_FIXARRAYS defined." << endl;
#endif
//    if ( bw )
//    {
//        cout << "backward:" << endl;
//        D.last();
//        do  { ++ct; }  while ( D.prev() );
//    }
//    else
    {
//        cout << "forward:" << endl;
        D.first();
        do  { ++ct; }  while ( D.next() );
    }
#else

    ulong j = 0;
    do
    {
#if 0
        {  // limit max digit:
            const ulong *x = D.data();
            bool q = true;
            const ulong b = 3;
            // b = 1 ==>
            // b = 2 ==>
            // b = 3 ==>
            for (ulong i=0; i<n; ++i)
                if ( x[i] > b )  { q=false;  break; }
            if ( ! q )  continue;
        }
#endif

        ++ct;


#if 1
        cout << setw(4) << ct << ":  ";

        // print RGS:
        D.print("  ", true );
        print_vec("  ", D.m_, n, true );

        cout << setw(4) << j;

        cout << endl;
        jjassert( D.OK() );
#endif
    }
    while ( (j=D.next()) );

#endif  // TIMING

    cout << " ct=" << ct;  // OEIS sequence A000110
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.0:

 % time ./bin 15
arg 1: 15 == n  [Length of strings]  default=5
 ct=1382958545
./bin 15  7.09s user 0.00s system 99% cpu 7.097 total
 == 1382958545/7.09 == 195,057,622 per second

 time ./bin 15
arg 1: 15 == n  [Length of strings]  default=5
ISOSCENT_RGS_FIXARRAYS defined.
 ct=1382958545
./bin 15  5.08s user 0.00s system 99% cpu 5.080 total
 == 1382958545/5.08 == 272,235,934 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/isoscent-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/isoscent-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

