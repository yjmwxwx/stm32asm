
#include "comb/involution-zero-map-rgs.h"
#include "comb/is-zero-map-rgs.h"

#include "comb/comb-print.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% Restricted growth strings (RGS):
//%   each digit a[k] is either zero or a[k] < k, a[a[k]] == 0,
//%   and there is at most one digit a[k] in the RGS.
//% Same as: maps from {1, 2, 3, ..., n} to {0, 1, 2, 3, ..., n}
//%   such that f(x) < x and f(f(x)) == 0 and there is no t!=x with f(t) = f(x).
//% Lexicographic order.
//% Cf. OEIS sequence A000085.

// Cf. comb/setpart-s-zero-map-rgs-demo.cc for set partitions into parts <= s+1
// Cf. comb/setpart-zero-map-rgs-demo.cc for set partitions

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "RGS of length n");

    involution_zero_map_rgs P(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else

    do
    {
        ++ct;
        cout << setw(3) << ct << ":";
        P.print("    ", true);
//        print_vec("    ", P.z_+1, n, true);  // internal data
        P.print_zero_dist_rgs("    ", true);

//        const bool zb = false;  // wether next two RGS are zero-based
//        P.print_fp_rgs("    ", true, zb);
//        P.print_fp_dist_rgs("    ", true, zb);

        P.print_involution("    ", true);

        cout << endl;

        jjassert( P.OK() );
    }
    while ( (P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 17
arg 1: 17 == n  [RGS of length n]  default=6
 ct=211799312
./bin 17  3.32s user 0.00s system 99% cpu 3.322 total
  ==> 211799312/3.32 == 63,794,973 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/involution-zero-map-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/involution-zero-map-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

