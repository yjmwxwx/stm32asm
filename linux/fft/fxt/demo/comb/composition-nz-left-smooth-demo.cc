
#include "comb/composition-nz-left-smooth.h"

#include "comb/is-unimodal.h"

//#include "comb/is-smooth.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Left-smooth compositions: compositions of n
//% with maximal up-step <= 1 and first part 1.
//% Lexicographic order.
//% Same as "fountains of coins", see OEIS sequence A005169.


// Cf. comb/composition-nz-left-2smooth-demo.cc for left-2smooth compositions
// Cf. comb/composition-nz-smooth-demo.cc for smooth compositions
// Cf. comb/composition-nz-i-smooth-demo.cc for internally smooth compositions
// Cf. comb/composition-nz-demo.cc for all compositions
// Cf. comb/composition-nz-max-demo.cc for compositions into parts <= mx
// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 9;
    NXARG(n, "Left-smooth compositions of n");
    // jjassert( n>=1 );  // composition of n=0 as one part ==0

    ulong aa = 0;
    NXARG(aa, "If aa!=0, render as compositions (1) or fountains of coins (2)");

    composition_nz_left_smooth C(n);

    ulong ct = 0;

#ifdef TIMING
    C.first();
    do  { ++ct; }  while ( C.next() );
#else  // TIMING

    ulong m = C.num_parts();
    do
    {
#if 0
        // OEIS sequence A053260: Coefficients of the '5th order' mock theta function psi_0(q)
        // Partitions of n such that each part occurs at most twice,
        //   the largest part is unique and if k occurs as a part then
        //   all smaller positive integers occur.
        // G.f.: psi_0(q) = sum(n>=0, q^((n+1)*(n+2)/2) * prod(k=1..n, 1 + q^k ) )
//        if ( ! is_strongly_unimodal(C.data(), m) )  continue;

        // OEIS sequence A001524: stacks with strictly receding left wall.
        // G.f.: 1 + sum(n>=1, z^(n*(n+1)/2) / ( (1-z^n) * prod(i=1..n-1, (1-z^i) )^2)
//        if ( ! is_weakly_unimodal(C.data(), m) )  continue;

        if ( n>=2 )  { // even smoother
            bool q = true;
            const ulong *x = C.data();
            if ( x[0] != x[1] )  continue;
            for (ulong k=1; k<=n-1; ++k)
//                if ( (x[k-1]!=x[k]) && (x[k]!=x[k+1]) )  // A000000
                if ( (x[k-1] < x[k]) && (x[k] < x[k+1]) )  // A186085 left-2smooth
                { q = false;  break; }
            if ( ! q )  continue;
        }
        // 1, 1, 1, 1, 1, 1, 2, 3, 5, 7, 10, 13, 19, 26, 38, 54, 79, 111, 161, 227, 327, 464, 668

#endif

#if 0  // no successive parts equal: A238870
        { bool q = true;
            const ulong *x = C.data();
            for (ulong k=1; k<m; ++k)
                if ( x[k-1]==x[k] )
                { q = false; break; }
            if ( ! q )  continue;
            // Disallow lone part one at end:
//            if ((m>=2) && (x[m-1]==1) )  continue;
        }
#endif

#if 0  // only rises or drops down to 1: A023361
        { bool q = true;
            const ulong *x = C.data();
            for (ulong k=1; k<m; ++k)
                if ( x[k-1] >= x[k] )
                    if ( x[k] != 1 )  { q = false; break; }
            if ( ! q )  continue;
        }
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

    cout << " ct=" << ct;  // A005169 fountains of n coins.
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 42
arg 1: 42 == n  [Left-smooth compositions of n]  default=9
arg 2: 0 == aa  [Whether to render as compositions (1) or fountains of coins (2)]  default=0
 ct=3566196321
./bin 42  12.60s user 0.00s system 99% cpu 12.608 total
 ==> 3566196321/12.60 == 283,031,454 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-left-smooth-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-left-smooth-demo.cc DEMOFLAGS=-DTIMING"
/// End:

