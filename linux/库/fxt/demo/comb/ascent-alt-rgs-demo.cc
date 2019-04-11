
#include "comb/ascent-alt-rgs.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Restricted growth strings (RGS) a[1,..,n], where a[k] < k and
//%   no digit a[j] in prefix such that a[j] == a[k] + 1
//% Lexicographic order.
//% Cf. OEIS sequence A022493.

// Cf. comb/ascent-rgs-demo.cc for ascent RGS


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Length of strings");
    ascent_alt_rgs A(n);

    ulong ct = 0;

#ifdef TIMING
//    bool bw = 0;
//    NXARG(bw, "Whether to generate in backward order");
#ifdef ASCENT_ALT_RGS_FIXARRAYS
    cout << "ASCENT_ALT_RGS_FIXARRAYS defined." << endl;
#endif

//    if ( bw )
//    {
//        cout << "backward:" << endl;
//        A.last();
//        do  { ++ct; }  while ( A.prev() );
//    }
//    else
//    {
//        cout << "forward:" << endl;
        A.first();
        do  { ++ct; }  while ( A.next() );
//    }
#else

    ulong j = n;
    do
    {
#if 0
        { // no down-steps: Catalan numbers (A000108)
            bool q = true;
            const ulong *x = A.data();
            for (ulong i=1; i<=n; ++i)
                if ( x[i] < x[i-1] )
                { q = false;  break; }
            if ( ! q )  continue;
        }
#endif
        ++ct;
        cout << setw(4) << ct << ":";
        A.print("  ", true ); // RGS
        cout << setw(4) << j;
//        print_vec("    ", A.p_, n, true );  // stats
        cout << endl;

        jjassert( A.OK() );
    }
    while ( (j=A.next()) );

#endif  // TIMING

    cout << " ct=" << ct;  // OEIS sequence A022493
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)


gcc 4.8.0:

 time ./bin 14
arg 1: 14 == n  [Length of strings]  default=5
 ct=796713190
./bin 14  6.71s user 0.00s system 99% cpu 6.714 total
 ==> 796713190/6.71 == 118,735,199 per second

 time ./bin 14
arg 1: 14 == n  [Length of strings]  default=5
ASCENT_ALT_RGS_FIXARRAYS defined.
 ct=796713190
./bin 14  5.36s user 0.00s system 99% cpu 5.366 total
 ==> 796713190/5.36 == 148,640,520 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ascent-alt-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ascent-alt-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

