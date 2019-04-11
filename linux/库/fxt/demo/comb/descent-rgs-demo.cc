
#include "comb/descent-rgs.h"

#include "comb/comb-print.h"

//#include "comb/is-descent-rgs.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Descent sequences (restricted growth strings, RGS).
//% A descent sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0,
//%   d(k)>=0, and d(k) <= 1 + desc([d(1), d(2), ..., d(k-1)]) and desc(.)
//%   counts the number of descents of its argument.
//% Lexicographic order.
//% See OEIS sequence A225588.

// Cf. comb/descent-rgs-stats-demo.cc for stats for descent RGS
// Cf. comb/ascent-rgs-demo.cc for ascent RGS

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Length of strings");

    descent_rgs D(n);

    ulong ct = 0;


#ifdef TIMING
    bool bw = 0;
    NXARG(bw, "Whether to generate in backward order");
#ifdef DESCENT_RGS_FIXARRAYS
    cout << "DESCENT_RGS_FIXARRAYS defined." << endl;
#endif
    if ( bw )
    {
        cout << "backward:" << endl;
        D.last();
        do  { ++ct; }  while ( D.prev() );
    }
    else
    {
        cout << "forward:" << endl;
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
            // b = 1 ==> 2^(n-1)
            // b = 2 ==> A164039: a(n+1) = 3*a(n) - n
            // b = 3 ==> A000000
            for (ulong i=0; i<n; ++i)
                if ( x[i] > b )  { q=false;  break; }
            if ( ! q )  continue;
        }
#endif
#if 0  // no flat-steps: A238425:
        {
            const ulong *x = D.data();
            bool q = true;
            for (ulong i=1; i<n; ++i)
                if ( 0==( x[i] - x[i-1] ) )  { q=false;  break; }
            if ( ! q )  continue;
        }
#endif
//        if ( is_ascent_rgs( D.data(), n) )  continue;
        // such descent RGS exists for n>=7

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

    cout << " ct=" << ct;  // OEIS sequence A022493
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)


 time ./bin 16 0
arg 1: 16 == n  [Length of strings]  default=6
arg 2: 0 == bw  [Whether to generate in backward order]  default=0
forward:
 ct=1146389206
./bin 16 0  4.17s user 0.00s system 99% cpu 4.171 total
 ==> 1146389206/4.17 == 274,913,478 per second

 time ./bin 16 1
arg 1: 16 == n  [Length of strings]  default=6
arg 2: 1 == bw  [Whether to generate in backward order]  default=0
backward:
 ct=1146389206
./bin 16 1  4.98s user 0.00s system 99% cpu 4.982 total
 ==> 1146389206/4.98 == 230,198,635 per second


 time ./bin 16 0
arg 1: 16 == n  [Length of strings]  default=6
arg 2: 0 == bw  [Whether to generate in backward order]  default=0
DESCENT_RGS_FIXARRAYS defined.
forward:
 ct=1146389206
./bin 16 0  4.04s user 0.00s system 99% cpu 4.039 total
 ==> 1146389206/4.04 == 283,759,704 per second

 time ./bin 16 1
arg 1: 16 == n  [Length of strings]  default=6
arg 2: 1 == bw  [Whether to generate in backward order]  default=0
DESCENT_RGS_FIXARRAYS defined.
backward:
 ct=1146389206
./bin 16 1  4.93s user 0.00s system 99% cpu 4.933 total
 ==> 1146389206/4.93 == 232,533,307 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/descent-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/descent-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

