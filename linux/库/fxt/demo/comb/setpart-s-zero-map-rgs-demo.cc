
#include "comb/setpart-s-zero-map-rgs.h"
#include "comb/is-zero-map-rgs.h"
#include "comb/print-zero-map-rgs.h"

#include "comb/comb-print.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Set partitions into sets of size <= s+1 represented as
//% restricted growth strings (RGS):
//%   each digit a[k] is either zero or the (one-based) index
//%   of a zero in the prefix and there are at most s digits pointing
//%   to the same zero in the prefix.
//% Same as: maps from {1, 2, 3, ..., n} to {0, 1, 2, 3, ..., n}
//%   such that f(x) < x and f(f(x)) == 0 and there are at most s
//%   values t such that f(t) = f(x).
//% Lexicographic order.
//% Cf. OEIS sequences A000085 (for s=1), A001680 (s=2), A001681 (s=3),
//%   A110038 (s=4), and A000110 (for s>=n-1).


// Cf. comb/setpart-zero-map-rgs-demo.cc for RGS with s=n (set partitions)
// Cf. comb/involution-zero-map-rgs-demo.cc for RGS with s=1 (involutions)

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "set partitions (as RGS) of length n");
    ulong s = 2;
    NXARG(s, "sets in the partitions of size at most s+1");

    setpart_s_zero_map_rgs P(n, s);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else

    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

        P.print("    ", true);

//        print_vec("    ", P.z_+1, n, true);  // internal data

        P.print_fp_rgs("    ", true, true);  // RGS as fixed-point RGS

        P.print_setpart("    ");

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

 time ./bin 15 15
arg 1: 15 == n  [RGS of length n]  default=5
arg 2: 15 == s  [at most s digits with the same non-zero value]  default=2
 ct=1382958545
./bin 15 15  11.02s user 0.00s system 99% cpu 11.023 total
  ==> 1382958545/11.02 == 125,495,330 per second

 time ./bin 17 1
arg 1: 17 == n  [RGS of length n]  default=5
arg 2: 1 == s  [at most s digits with the same non-zero value]  default=2
 ct=211799312
./bin 17 1  3.32s user 0.00s system 99% cpu 3.324 total
  ==> 211799312/3.32 == 63,794,973 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/setpart-s-zero-map-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/setpart-s-zero-map-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

