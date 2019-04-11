
#include "comb/motzkin-nonflat-rgs-lex.h"

#include "comb/comb-print.h"

//#include "comb/fact2perm.h"
//#include "perm/permq.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Motzkin (nonflat) restricted growth strings (RGS).
//% Same as: Catalan RGS with no flat steps.
//% Cf. OEIS sequences A086246 and A001006.

// The number of length-n RGS is
//  1, 1, 1, 2, 4, 9, 21, 51, 127, 323, 835, 2188, 5798, 15511, 41835, ...
// G.f. is (1+x-sqrt(1-2*x-3*x^2))/(2*x)

//#define TIMING  // uncomment to disable printing

// Cf. comb/motzkin-rgs-lex-demo.cc for Motzkin RGS.
// Cf. comb/catalan-rgs-demo.cc for Catalan RGS.


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Number of digits");

    motzkin_nonflat_rgs_lex M(n);

    ulong ct = 0;

#ifdef TIMING
    bool bw = 0;
    NXARG(bw, "With benchmark: whether to generate backward order");

#ifdef MOTZKIN_NONFLAT_RGS_LEX_FIXARRAYS
    cout << "MOTZKIN_NONFLAT_RGS_LEX_FIXARRAYS is defined" << endl;
#endif
    if ( bw )
    {
        cout << "backward:" << endl;
        M.last();
        do  { ++ct; }  while ( M.prev() );
    }
    else
    {
        cout << "forward:" << endl;
        M.first();
        do  { ++ct; }  while ( M.next() );
    }
#else  // TIMING

//    M.last();
//    ulong Z[64];  // for permutation
    ulong j = 0;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

        // print RGS:
        M.print("    ", true );
        cout << setw(4) << j;

//        rfact2perm( M.data()+1, n, Z);
//        perm_rev_compl(Z, n);  // reversed complement
//        print_vec("    ", Z, n );

        cout << endl;

        jjassert( M.OK() );
//        jjassert( is_involution(Z, n) );  // not true
    }
    while ( (j=M.next()) );
//    while ( (j=M.prev()) );

#endif  // TIMING

    cout << " ct=" << ct;  // Motzkin number n
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 24 0
arg 1: 24 == n  [Number of digits]  default=7
arg 2: 0 == bw  [With benchmark: whether to generate backward order]  default=0
forward:
 ct=1129760415
./bin 24 0  5.23s user 0.00s system 99% cpu 5.235 total
 ==> 1129760415/5.23 == 216,015,375 per second

 time ./bin 24 1
arg 1: 24 == n  [Number of digits]  default=7
arg 2: 1 == bw  [With benchmark: whether to generate backward order]  default=0
backward:
 ct=1129760415
./bin 24 1  7.36s user 0.00s system 99% cpu 7.366 total
 ==> 1129760415/7.36 == 153,500,056 per second


 time ./bin 24 0
arg 1: 24 == n  [Number of digits]  default=7
arg 2: 0 == bw  [With benchmark: whether to generate backward order]  default=0
MOTZKIN_NONFLAT_RGS_LEX_FIXARRAYS is defined
forward:
 ct=1129760415
./bin 24 0  6.28s user 0.00s system 99% cpu 6.282 total
 ==> 1129760415/6.28 == 179,898,155 per second

 time ./bin 24 1
arg 1: 24 == n  [Number of digits]  default=7
arg 2: 1 == bw  [With benchmark: whether to generate backward order]  default=0
MOTZKIN_NONFLAT_RGS_LEX_FIXARRAYS is defined
backward:
 ct=1129760415
./bin 24 1  6.88s user 0.00s system 99% cpu 6.881 total
 ==> 1129760415/6.88 == 164,209,362 per second


*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/motzkin-nonflat-rgs-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/motzkin-nonflat-rgs-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

