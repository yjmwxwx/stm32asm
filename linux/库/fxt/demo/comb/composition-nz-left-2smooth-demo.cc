
#include "comb/composition-nz-left-2smooth.h"

#include "comb/is-unimodal.h"

//#include "comb/is-smooth.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Left-2smooth compositions:
//% compositions of n with maximal up-step 1,
//% no consecutive up-steps, and first part 1.
//% Lexicographic order.
//% Cf. OEIS sequence A186085.

// Cf. comb/composition-nz-left-smooth-demo.cc for left-smooth compositions
// Cf. comb/composition-nz-demo.cc for all compositions
// Cf. comb/composition-nz-smooth-demo.cc for smooth compositions
// Cf. comb/composition-nz-max-demo.cc for compositions into parts <= mx
// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 11;
    NXARG(n, "Left-2smooth compositions of n");
    // jjassert( n>=1 );  // composition of n=0 as one part ==0

    ulong aa = 0;
    NXARG(aa, "If aa!=0, render as compositions (1) or fountains of coins (2)");

    composition_nz_left_2smooth C(n);

    ulong ct = 0;

#ifdef TIMING
    C.first();
    do  { ++ct; }  while ( C.next() );
#else  // TIMING

    ulong m = C.num_parts();
    do
    {
#if 0
        if ( n>=2 )  { // no two consecutive changes
            bool q = true;
            const ulong *x = C.data();
            if ( x[0] != x[1] )  continue;
            for (ulong k=1; k<=n-1; ++k)
                if ( (x[k-1]!=x[k]) && (x[k]!=x[k+1]) )  // A000000
                { q = false;  break; }
            if ( ! q )  continue;
        }
        // 1, 1, 1, 1, 1, 1, 2, 3, 5, 7, 10, 13, 19, 26, 38, 54, 79, 111, 161, 227, 327, 464, 668
#endif
#if 0  // A001522
        if ( ! is_weakly_unimodal( C.data(), C.num_parts() ) )  continue;
#endif

        ++ct;

#if 1  // whether to print anything
        cout << setw(4) << ct << ":";

//        cout << "[" << setw(2) << m << "]";
//        cout << " [" << setw(2) << n-m << "]";


        C.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            if ( aa & 1 )  C.print_composition_aa();
            if ( aa & 2 )  C.print_fountain_aa();
            cout << endl;
            cout << endl;
        }

        jjassert( C.OK() );
#endif
    }
    while ( (m=C.next()) );
#endif  // TIMING

    cout << " ct=" << ct;  // A186085
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.8.0:

 time ./bin 43
arg 1: 43 == n  [Left-2smooth compositions of n]  default=9
arg 2: 0 == aa  [If aa!=0, render as compositions (1) or fountains of coins (2)]  default=0
 ct=768425125
./bin 43  3.95s user 0.00s system 99% cpu 3.954 total
 ==> 768425125/3.95 == 194,538,006 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-left-2smooth-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-left-2smooth-demo.cc DEMOFLAGS=-DTIMING"
/// End:

