
#include "bpol/gf2n.h"
//demo-include "bpol/gf2n.cc"
#include "ds/bitarray.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "jjassert.h"


//% OEIS sequence A213243:
//% Number of nonzero elements in GF(2^n) that are cubes.
//% Also A213244: 5th powers.
//% Also A213245: 7th powers.
//% Also A213246: 9th powers.
//% Also A213247: 11th powers.
//% Also A213248: 13th powers.

// We have a(n) = M / gcd( M, r ) where M=2^n-1 and r = 3 (or 5, 7, 9, 11, 13).

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "degree of field (n>=1)");
    jjassert( n>=1 );
    const ulong N = 1UL << n;

    ulong p = 3;
    NXARG(p, "exponent");


    bitarray B(N);  B.clear_all();

    GF2n::init(n);

    GF2n f(1);
    GF2n g( GF2n::g_ );
    for (ulong e=1; e<N; ++e)
    {
        GF2n x( f.pow(p) );  // default
//        GF2n x( f*f*f + f );  // A001045
//        GF2n x( f + f.inv() );  // 2^(n-1)
//        GF2n x( f*f + GF2n::one );  // 2^n-1
//        GF2n x( f*f + f.inv() );  // A000000:
        // expansion of (-4*x^3 + 6*x^2 - 2*x + 1)/(4*x^4 - 6*x^3 + 4*x^2 - 3*x + 1)

        B.set( x.v_ );
        f *= g;
    }

#ifndef TIMING
    B.dump_bits( );
    cout << endl;
#endif  // TIMING
    ulong ct = B.count_ones();
    cout << "ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
echo $(for n in $(seq 1 27); do ./bin $n 3; done | g ct=) | sed 's/ct=//g;s/ /, /g;'

1, 1, 7, 5, 31, 21, 127, 85, 511, 341, 2047, 1365, 8191, 5461, 32767,
21845, 131071, 87381, 524287, 349525, 2097151, 1398101, 8388607,
5592405, 33554431, 22369621, 134217727

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A213243-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A213243-demo.cc DEMOFLAGS=-DTIMING"
/// End:
