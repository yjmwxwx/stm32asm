
#include "comb/composition-nz-smooth.h"

#include "comb/is-unimodal.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Smooth compositions: compositions of n with first and last part 1
//% and maximal absolute difference 1 between consecutive parts.
//% Lexicographic order.
//% Same as "1-dimensional sand piles", see OEIS sequence A186085.

// Cf. comb/composition-nz-left-2smooth-demo.cc for left-2smooth compositions
// Cf. comb/composition-nz-left-smooth-demo.cc for left-smooth compositions
// Cf. comb/composition-nz-demo.cc for all compositions
// Cf. comb/composition-nz-max-demo.cc for compositions into parts <= mx
// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 11;
    NXARG(n, "Smooth compositions of n");
    // works for n==0

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    composition_nz_smooth C(n);

    ulong ct = 0;

#ifdef TIMING
    C.first();
    do  { ++ct; }  while ( C.next() );
#else  // TIMING

    ulong m = C.num_parts();
    do
    {
#if 0  // OEIS sequence A001522: smooth weakly unimodal compositions
        // G.f.: sum(k>=1, -(-1)^k * x^(k*(k+1)/2) ) / prod(k>=1, 1 - x^k ).
//        if ( ! is_weakly_unimodal(C.data(), m) )  continue;  // A001522
        // strongly unimodal: ==1 for triangular numbers, else zero:
//        if ( ! is_strongly_unimodal(C.data(), m) )  continue;

        { // even smoother:  A000000
            bool q = true;
            const ulong *x = C.data();
            if ( x[0] != x[1] )  continue;
            if ( x[m-2] != x[m-1] )  continue;
            for (ulong k=1; k<=m-1; ++k)
                if ( (x[k-1]!=x[k]) && (x[k]!=x[k+1]) )  { q = false;  break; }
            if ( ! q )  continue;
        }
#endif

#if 0  // no successive parts equal: A227310: rough sand piles
        // G.f.: 1/G(0) where G(k) = 1 + (-q)^(k+1) / (1 - (-q)^(k+1)/G(k+1) ).
        { bool q = true;
            const ulong *x = C.data();
            for (ulong k=1; k<m; ++k)
                if ( x[k-1]==x[k] )
                { q = false; break; }
            if ( ! q )  continue;
        }
#endif


#if 0  // successive maxima weakly/strictly increasing:
        { bool q = true;
            ulong mx = 0;
            const ulong *x = C.data();
            for (ulong k=1; k+1<m; ++k)
            {
                ulong v = x[k];
                if ( v > x[k-1] && v > x[k+1] )  // max
                {
//                    if ( v < mx )  { q=0; break; }  // weakly
                    if ( v <= mx )  { q=0; break; }  // strictly
                    mx = v;
                }
            }
            if ( ! q )  continue;
        }
#endif

        ++ct;
#if 1  // whether to print anything
        cout << setw(4) << ct << ":";

//        cout << "[" << setw(2) << m << "]" ;
//        cout << " [" << setw(2) << n-m << "]" ;

        C.print("  ", true);

        cout << endl;

        if ( aa )  // ASCII art
        {
            C.print_aa();
            cout << endl;
            cout << endl;
        }

        jjassert( C.OK() );
#endif
    }
    while ( (m=C.next()) );
#endif  // TIMING

    cout << " ct=" << ct;  // A186085 1-dimensional sand piles with n grains.
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 43
arg 1: 43 == n  [Smooth compositions of n (n>=1)]  default=12
arg 2: 0 == aa  [Whether to render as ASCII art]  default=0
 ct=768425125
./bin 43  5.24s user 0.00s system 99% cpu 5.247 total
 ==> 768425125/5.24 == 146,646,016 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-smooth-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-smooth-demo.cc DEMOFLAGS=-DTIMING"
/// End:

