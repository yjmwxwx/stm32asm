
#include "comb/binary-huffman.h"

#include "comb/comb-print.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Partitions of 1 into n powers of 1/2:
//%   1 == a[0]/1 + a[1]/2 + a[2]/4 + a[3]/8 + ... a[m]/(2^m)  (for n>=1),
//%   n == a[0] + a[1] + a[2] + a[3] + ... + a[m].
//% Same as: binary Huffman codes (canonical trees) with n terminal nodes,
//%   a[k] is the number of terminal nodes of depth k.
//% Reversed lexicographic order.
//% See:
//%   Christian Elsholtz, Clemens Heuberger, Helmut Prodinger:
//%   "The number of Huffman codes, compact trees, and sums of unit fractions",
//%   arXiv:1108.5964 [math.CO], (30-August-2011).
//%
//% Cf. OEIS sequence A002572.


// Cf. comb/composition-nz-minc-demo.cc with restricted growths conditions

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "partitions of 1 into n powers of 1/2");

    bool sq = true;
    NXARG(sq, "whether to print sums");

    binary_huffman H(n);

    ulong ct = 0;

#ifdef TIMING
    H.first();
    do  { ++ct; }  while ( H.next() );

#else  // TIMING

    ulong m = ( n ? n-1 : 0 );
    do
    {
//        cout << "[" << setw(2) << ct << "]";

        cout << setw(4) << ct << ":";
        ++ct;

//        cout << "  [" << setw(2) << m << "]";

        H.print("  ", true);

        if ( sq )  H.print_unit_sum("    1 = ");

        cout << endl;

        jjassert( H.OK() );
    }
    while ( (m=H.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 39
arg 1: 39 == n  [partitions of 1 into n powers of 1/2]  default=10
arg 2: 1 == sq  [whether to print sums]  default=1
 ct=1127987211
./bin 39  6.96s user 0.00s system 99% cpu 6.969 total
 ==> 1127987211/6.96 == 162,067,128 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/binary-huffman-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/binary-huffman-demo.cc DEMOFLAGS=-DTIMING"
/// End:

