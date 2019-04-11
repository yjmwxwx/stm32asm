
#include "comb/necklace.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "fxtio.h"

//% Generate all pre-necklaces, necklaces, and Lyndon words with a given number of colors.


// OEIS sequences:
//
// A062692 (pre-necklaces, 2 cols.)
// A000031 (necklaces, 2 cols.)
// A001037 (Lyndon words, 2 cols.)
//
// A114945 (pre-necklaces, 3 cols.)
// A001867 (necklaces, 3 cols.)
// A027376 (Lyndon words, 3 cols.)

// cf. http://oeis.org/wiki/Index_to_OEIS:_Section_Lu#Lyndon
// cf. http://oeis.org/wiki/Index_to_OEIS:_Section_Ne#necklaces

// Cf. seq/A215327-demo.cc


#define PRX()  { if (x[k])  cout << x[k]; else cout << '.'; }

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "length of strings >=1");
    ulong m = 3;
    NXARG(m, "number of different beads >=2");

    necklace P(m, n);
#ifndef TIMING
    const ulong *x = P.data();
#endif

    ulong j = P.j_;  // ==1
    ulong pct = 0;  // count pre-necklaces (pre-prime strings)
    ulong ct = 0;   // count necklaces (prime strings)
    ulong lct = 0;  // count Lyndon words
    do
    {
#if 0  // OEIS sequences:
        { // no two adjacent elements identical:
            // A106365 (m=3), A106366 (m=4), A106367 (m=5), A106368 (m=6)
            if ( n>1 ) if ( x[0] == x[n-1] )  continue;
            bool q = true;
            for (ulong k=1; k<n; ++k)  if ( x[k]==x[k-1] )  { q=false; break; }
            if ( !q )  continue;
        }
#endif

        ++pct;


#ifdef TIMING
        // all timings were done *without( these tests!
        if (  P.is_necklace() )
        {
            ++ct;
            if ( P.is_lyn() )  ++lct;
        }
#else  // TIMING

        cout << "    ";
        // print full string:
        for (ulong k=0; k<n; ++k)  PRX();
        cout << "  " << setw(2) << j;  // period

        // print string in minimal period:
        cout << "    ";
        ulong k;
        for (k=0; k<n-j; ++k)  cout << " ";
        for (  ; k<n; ++k)  PRX();

        if ( P.is_necklace() )
        {
            ++ct;
            cout << "  N";  // is a necklace
            if ( P.is_lyn() )
            {
                ++lct;
                cout << " L";  // is a Lyndon word
            }
        }
        cout << endl;
#endif  // TIMING
    }
    while ( (j=P.next_pre()) );

    cout << "  # pre-necklaces = " << pct;
    cout << "  # necklaces = " << ct;
    cout << "  # Lyndon words = " << lct;
    cout << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 32 2
  #pre = 277737797
./bin 32 2  2.82s user 0.02s system 99% cpu 2.840 total
 ==> 277737797/2.81 == 98,839,073 per second
with NECKLACE_MAX_ARRAY_LEN defined:
./bin 32 2  2.59s user 0.02s system 99% cpu 2.618 total


 time ./bin 21 3
  #pre = 766918996
./bin 21 3  5.43s user 0.03s system 99% cpu 5.462 total
 ==> 766918996/5.43 == 141,237,384 per second

 time ./bin 16 4
  #pre = 366273464
./bin 16 4  2.03s user 0.00s system 99% cpu 2.032 total
 ==> 366273464/2.03 == 180,430,277 per second
with NECKLACE_MAX_ARRAY_LEN defined:
./bin 16 4  1.81s user 0.02s system 99% cpu 1.837 total

*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32 2
arg 1: 32 == n  [length of strings >=1]  default=4
arg 2: 2 == m  [number of different beads >=2]  default=3
arg 3: 1 == pq  [whether to also print pre-necklaces]  default=1
  # pre-necklaces = 277737797
./bin 32 2  1.26s user 0.00s system 99% cpu 1.264 total
 ==> 277737797/1.26 == 220,426,823 per second
with NECKLACE_MAX_ARRAY_LEN defined:
./bin 32 2  1.22s user 0.00s system 99% cpu 1.220 total

 time ./bin 21 3
arg 1: 21 == n  [length of strings >=1]  default=4
arg 2: 3 == m  [number of different beads >=2]  default=3
arg 3: 1 == pq  [whether to also print pre-necklaces]  default=1
  # pre-necklaces = 766918996
./bin 21 3  3.14s user 0.00s system 99% cpu 3.145 total
 ==> 766918996/3.14 == 244,241,718 per second

 time ./bin 16 4
arg 1: 16 == n  [length of strings >=1]  default=4
arg 2: 4 == m  [number of different beads >=2]  default=3
arg 3: 1 == pq  [whether to also print pre-necklaces]  default=1
  # pre-necklaces = 366273464
./bin 16 4  1.38s user 0.00s system 99% cpu 1.378 total
 ==> 366273464/1.38 == 265,415,553 per second
with NECKLACE_MAX_ARRAY_LEN defined:
./bin 16 4  1.36s user 0.00s system 99% cpu 1.357 total

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/necklace-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/necklace-demo.cc DEMOFLAGS=-DTIMING"
/// End:

