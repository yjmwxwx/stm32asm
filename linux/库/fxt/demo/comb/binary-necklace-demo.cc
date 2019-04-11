
#include "comb/binary-necklace.h"

#include "fxtio.h"
#include "fxttypes.h"  // ulong

#include "nextarg.h"  // NXARG()

//% Binary pre-necklaces, necklaces, and Lyndon words: CAT generation.
//% Cf. OEIS sequences A062692 (pre-necklaces), A000031 (necklaces),
//% and A001037 (Lyndon words).

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Number of bits");

    binary_necklace P(n);

    ulong pct = 0;  // count pre-necklaces (pre-prime strings)
    ulong j = 1;  // first string is zero word (period==1)

#ifdef TIMING

#ifdef BINARY_NECKLACE_MAX_ARRAY_LEN
    cout << "BINARY_NECKLACE_MAX_ARRAY_LEN is defined" << endl;
#endif
    do  { ++pct; }  while ( ( j=P.next_pre() ) );
    cout << "  # pre-necklaces = " << pct;

#else  // TIMING

    const ulong *x = P.data();

    ulong nct = 0;  // count necklaces (prime strings)
    ulong lct = 0;  // count lyndon words
    do
    {
#if 0
        // with even n: A003239 (necklaces), A022553 (Lyndon words)
        // with odd n: A000108 (necklaces == Lyndon words)
        { ulong i,  s = 0;
            for (i=0; i<n; ++i)  s += ( P.data()[i] == 1 );
            if ( s != n/2 ) continue;
        }
#endif

        ++pct;
        cout << setw(4) << pct << ": ";
        for (ulong i=0; i<n; ++i)  cout << (x[i] ? '1' : '.' );
        cout << "  ";
        cout << setw(2) << j;
        cout << "  ";
        if ( P.is_necklace() )
        {
            ++nct;
            cout << "  N";  // necklace
            if ( P.is_lyn() )
            {
                ++lct;
                cout << "  L";  // Lyndon word
            }
        }
        cout << endl;
    }
    while ( ( j=P.next_pre() ) );

    cout << " n = " << n << ":  ";
//    cout << endl;
    cout << "  # pre-necklaces = " << pct;
    cout << "  # necklaces = " << nct;
    cout << "  # Lyndon words = " << lct;
#endif  // TIMING

    cout << endl;


    return 0;
}
// -------------------------

/*
Timing:

with BINARY_NECKLACE_MAX_ARRAY_LEN defined:
 time ./bin 34
arg 1: 34 == n  [Number of bits]  default=8
 n = 34:    # pre-necklaces = 1043325198
./bin 34  8.07s user 0.00s system 99% cpu 8.069 total
 ==> 1043325198/8.07 == 129,284,411 per second

with pointers:
 time ./bin 34
arg 1: 34 == n  [Number of bits]  default=8
 n = 34:    # pre-necklaces = 1043325198
./bin 34  8.14s user 0.00s system 100% cpu 8.139 total
 ==> 1043325198/8.14 == 128,172,628 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

with BINARY_NECKLACE_MAX_ARRAY_LEN defined:
 time ./bin 34
arg 1: 34 == n  [Number of bits]  default=8
  # pre-necklaces = 1043325198
./bin 34  5.25s user 0.00s system 99% cpu 5.251 total
 ==> 1043325198/5.25 == 198,728,609 per second

 time ./bin 34
arg 1: 34 == n  [Number of bits]  default=8
  # pre-necklaces = 1043325198
./bin 34  4.20s user 0.00s system 99% cpu 4.197 total
 ==> 1043325198/4.20 == 248,410,761 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/binary-necklace-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/binary-necklace-demo.cc DEMOFLAGS=-DTIMING"
/// End:

