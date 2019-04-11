
#include "comb/composition-nz-i-smooth.h"

#include "comb/is-unimodal.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Internally smooth compositions:
//% consecutive parts differ by at most 1.
//% Lexicographic order.
//% See OEIS sequence A034297.

// Cf. comb/composition-nz-smooth-demo.cc for smooth compositions
// Cf. comb/composition-nz-left-smooth-demo.cc for left-smooth compositions
// Cf. comb/composition-nz-demo.cc for all compositions

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Internally smooth compositions of n");
    // jjassert( n>=1 );  // composition of n=0 as one part ==0

    ulong aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    composition_nz_i_smooth C(n);

    ulong ct = 0;

#ifdef TIMING
    C.first();
    do  { ++ct; }  while ( C.next() );
#else  // TIMING

    ulong m = C.num_parts();
    do
    {
#if 0
//        if ( ! is_weakly_unimodal(C.data(), m) )  continue;  // A238871
        if ( ! is_strongly_unimodal(C.data(), m) )  continue;  //A238872
#endif

        ++ct;
#if 1
        cout << setw(4) << ct << ":  ";
        cout << "[" << setw(2) << m << "]" ;
        C.print("    ");
        cout << endl;

        if ( aa )  // ASCII art
        {
            C.print_aa();
            cout << endl;
            cout << endl;
        }
#endif
        jjassert( C.OK() );
    }
    while ( (m=C.next()) );
#endif  // TIMING

    cout << " ct=" << ct;  // A034297
#ifdef COMPOSITION_NZ_I_SMOOTH_WRK
    cout << "    mwrk=" << C.mwrk_;
    cout << "    twrk=" << C.twrk_;
    cout << "    rat==" << (double)C.twrk_ / (double)ct;
#endif
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

gcc 4.5.0:

 time ./bin 40
arg 1: 40 == n  [Internally smooth compositions of n]  default=8
arg 2: 0 == aa  [Whether to render as ASCII art]  default=0
 ct=591766826
./bin 40  7.10s user 0.00s system 99% cpu 7.103 total
  ==> 591766826/7.10 == 83,347,440 per second


gcc 4.8.0:

 time ./bin 40
arg 1: 40 == n  [Internally smooth compositions of n]  default=5
arg 2: 0 == aa  [Whether to render as ASCII art]  default=0
 ct=591766826
./bin 40  6.84s user 0.00s system 99% cpu 6.844 total
  ==> 591766826/6.84 == 86,515,617 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-i-smooth-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-i-smooth-demo.cc DEMOFLAGS=-DTIMING"
/// End:

