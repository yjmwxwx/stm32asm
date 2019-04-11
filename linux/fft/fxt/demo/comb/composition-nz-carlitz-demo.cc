
#include "comb/composition-nz-carlitz.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"



//% Compositions of n into positive parts such that
//% adjacent parts are different (Carlitz compositions).
//% Cf. OEIS sequence A003242.


// Cf. comb/composition-nz-demo.cc


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Carlitz compositions of n");

    composition_nz_carlitz P(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
    do
    {
#if 0
        const ulong *x = P.data();
        bool q = true;
        for (ulong j = 0; j<m; ++j)
            if ( 0 == (x[j] & 1UL) )  { q=false; break; }
        if ( !q )  continue;
#endif
#if 0  // A155822
        const ulong *x = P.data();
        bool q = true;
        for (ulong j = 0; j<m; ++j)
            if ( x[j] > 3 )  { q=false; break; }
        if ( !q )  continue;
#endif

        ++ct;

        cout << setw(3) << ct << ": ";
        cout << "[" << m << "]  ";
//        cout << "[" << n-m << "]  ";
        P.print("");
        cout << endl;

        jjassert( P.OK() );
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 40
arg 1: 40 == n  [Carlitz compositions of n]  default=8
  ct=2416728950
./bin 40  15.70s user 0.00s system 99% cpu 15.706 total
 ==> 2416728950/15.70 == 153,931,780 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-carlitz-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-carlitz-demo.cc DEMOFLAGS=-DTIMING"
/// End:

