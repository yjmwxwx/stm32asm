
#include "comb/mixedradix-gslex-alt.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Mixed radix numbers in alternative gslex (generalized subset lex) order.

// Cf. comb/mixedradix-gslex-alt2-demo.cc for a better optimized version.
// Cf. comb/mixedradix-gslex-demo.cc for a similar order.
// Cf. comb/mixedradix-lex-demo.cc for lexicographic order (wrt. delta sets).
// Cf. comb/mixedradix-subset-lex-demo.cc for subset-lex order.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Number of digits");

    ulong rr = 4;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "Benchmark: whether to generate in backward order");
    mixedradix_gslex_alt M(n, rr);

#else
    ALLOCA(ulong, r, n);
    fill(r, n, rr);
    RESTARGS("Optionally supply radix for all digits (rr ignored)");
    if ( argc>3)  jjassert( argc == (int)n+3 );
    for (ulong k=3;  k<(ulong)argc; ++k)  r[k-3] = strtoul(argv[k], 0, 10);

    mixedradix_gslex_alt M(n, rr, (argc>3? r:0) );
    M.print_nines("Nines: ");
    cout << endl;
#endif


    ulong ct = 0;
#ifdef TIMING
//#ifdef MIXEDRADIX_NAF_MAX_ARRAY_LEN
//    cout << "MIXEDRADIX_NAF_MAX_ARRAY_LEN is defined." << endl;
//#endif
    if ( ! bq )
    {
        cout << "forward:" << endl;
        M.first();
        do  { ++ct; }  while ( M.next() );
    }
    else
    {
        cout << "backward:" << endl;
        M.last();
        do  { ++ct; }  while ( M.prev() );
    }

#else

//    M.last();
    do
    {
        cout << " " << setw(4) << ct << ":  ";
        M.print("    ", true );

        // Print as multiset:
        print_multi_deltaset_as_set("    ", M.data(), n, 0 );

        cout << endl;
        ++ct;
    }
    while ( M.next() );
//    while ( M.prev() );

#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 30 2  ## binary is worst case
 ct=1073741824
./bin 30 2  8.98s user 0.05s system 99% cpu 9.041 total
 ==> 1073741824/8.98 == 119,570,359 per second

 time ./bin 16 4
 ct=4294967296
./bin 16 4  23.33s user 0.12s system 97% cpu 23.990 total
 ==> 4294967296/23.33 == 184,096,326 per second

 time ./bin 10 8
 ct=1073741824
./bin 10 8  4.74s user 0.04s system 99% cpu 4.783 total
 ==> 1073741824/4.74 == 226,527,810 per second

 time ./bin 8 16
 ct=4294967296
./bin 8 16  13.76s user 0.06s system 99% cpu 13.902 total
 ==> 4294967296/13.76 == 312,134,251 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

  time ./bin 30 2 0 ## binary is worst case
forward:
 ct=1073741824
./bin 30 2 0  5.04s user 0.00s system 99% cpu 5.038 total
 ==> 1073741824/5.04 == 213,044,012 per second

 time ./bin 30 2 1
backward:
 ct=1073741824
./bin 30 2 1  5.19s user 0.00s system 99% cpu 5.190 total
 ==> 1073741824/5.19 == 206,886,671 per second


 time ./bin 19 3 0
forward:
 ct=1162261467
./bin 19 3 0  3.85s user 0.00s system 99% cpu 3.852 total
 ==> 1162261467/3.85 == 301,886,095 per second

 time ./bin 19 3 1
backward:
 ct=1162261467
./bin 19 3 1  4.83s user 0.00s system 99% cpu 4.830 total
 ==> 1162261467/4.83 == 240,633,844 per second


  time ./bin 16 4 0
forward:
 ct=4294967296
./bin 16 4 0  12.45s user 0.00s system 99% cpu 12.451 total
 ==> 4294967296/12.45 == 344,977,292 per second

 time ./bin 16 4 1
backward:
 ct=4294967296
./bin 16 4 1  17.43s user 0.00s system 99% cpu 17.432 total
 ==> 4294967296/17.43 == 246,412,352 per second


 time ./bin 10 8 0
forward:
 ct=1073741824
./bin 10 8 0  2.87s user 0.00s system 99% cpu 2.876 total
 ==> 1073741824/2.87 == 374,126,071 per second

 time ./bin 10 8 1
backward:
 ct=1073741824
./bin 10 8 1  4.37s user 0.00s system 99% cpu 4.370 total
 ==> 1073741824/4.37 == 245,707,511 per second


  time ./bin 8 16 0
forward:
 ct=4294967296
./bin 8 16 0  9.06s user 0.00s system 99% cpu 9.059 total
 ==> 4294967296/9.06 == 474,058,200 per second

 time ./bin 8 16 1
backward:
 ct=4294967296
./bin 8 16 1  15.64s user 0.00s system 99% cpu 15.639 total
 ==> 4294967296/15.64 == 274,614,277 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-gslex-alt-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-gslex-alt-demo.cc DEMOFLAGS=-DTIMING"
/// End:

