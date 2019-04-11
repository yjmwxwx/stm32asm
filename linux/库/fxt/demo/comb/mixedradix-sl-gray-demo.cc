
#include "comb/mixedradix-sl-gray.h"

#include "comb/check-mixedradix.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix numbers in a minimal-change order
//% related so subset-lex order ("SL-Gray" order).
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

// Cf. comb/mixedradix-sl-gray-rec-demo.cc for recursive generation.
// Cf. comb/binary-sl-gray-demo.cc for the binary case.
// Cf. bits/bit-sl-gray-demo.cc for generation in a binary word.


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Number of digits (n>=1)");
    jjassert( n>=1 );

    ulong rr = 4;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");

#ifdef TIMING
    mixedradix_sl_gray M(n, rr);

#else
    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply radix for all digits (rr ignored)");
    if ( argc>3 )  jjassert( argc == (int)n+3 );

    for (ulong i=3;  i<(ulong)argc; ++i)  r[i-3] = strtoul(argv[i], 0, 10);

    mixedradix_sl_gray M(n, rr, (argc>3? r:0) );

    check_mixedradix chk( M.m1_, M.n_ );
    chk.first( M.data() );
    M.print_nines("Nines: ");
    cout << endl;
#endif


    ulong ct = 0;
#ifdef TIMING
    M.first();
    do  { ++ct; }  while ( M.next() );

#else

    const ulong *x = M.data();
    do
    {
#if 0  // weak compositions:  enup order (Gray code)
        ulong s = 0;
        for (ulong j=0; j<n; ++j)
            s += x[j];
        if ( s != n )  continue;
#endif
        cout << setw(4) << ct << ":";
        M.print("  ", true );

        cout << "  ";
        cout << "  " << M.pos();
        cout << "  " << (M.dir() > 0 ? '+' : '-');
        print_sign_vec("    ", M.d_, n );
        cout << "  " << M.tr_;
        print_multi_deltaset_as_set("    ", x, n, true );
//        print_multi_deltaset_as_set_alph("    ", M.data(), n, false );

        cout << endl;

        jjassert( ! chk.is_repeat() );

        ++ct;
    }
    while ( M.next() );

    jjassert( chk.all_seen() );

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

----- args=30 2 ## binary is worst case
 ct=1073741824
./bin 30 2  6.80s user 0.00s system 99% cpu 6.809 total
 ==> 1073741824/6.80 == 157,903,209 per second

----- args=19 3
 ct=1162261467
./bin 19 3  5.88s user 0.00s system 99% cpu 5.884 total
 ==> 1162261467/5.88 == 197,663,514 per second

----- args=16 4
 ct=4294967296
./bin 16 4  14.27s user 0.00s system 99% cpu 14.276 total
 ==> 4294967296/14.27 == 300,978,787 per second

----- args=8 16
 ct=4294967296
./bin 8 16  9.86s user 0.00s system 99% cpu 9.860 total
 ==> 4294967296/9.86 == 435,595,060 per second

## factorial bases:
----- args=12 0
 ct=6227020800
./bin 12 0  25.62s user 0.00s system 99% cpu 25.629 total
 ==> 13!/25.62 == 243,053,114 per second

----- args=12 1
 ct=6227020800
./bin 12 1  15.61s user 0.00s system 99% cpu 15.615 total
 ==> 13!/15.61 == 398,912,286 per second

*/


/*
BENCHARGS=30 2
BENCHARGS=19 3
BENCHARGS=16 4
BENCHARGS=8 16

BENCHARGS=12 0
BENCHARGS=12 1

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-sl-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-sl-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

