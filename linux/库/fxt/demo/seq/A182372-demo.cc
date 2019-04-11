
// demo-is-self-contained

#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "bits/bitsperlong.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A182372:
//% Number of distinct sets of non-negative integers with perimeter n.

// Cf. comb/partition-asc-perim-demo.cc
// Cf. comb/partition-asc-sorts2-pp-demo.cc

//#define TIMING  // uncomment to disable printing

static inline ulong bit_volume(ulong x, ulong v=0)
// Volume of a bit set:
//   sum( k>=0, (k+v) * (b_k!=0) ), especially
//   sum( k>=0, k * (b_k!=0) )  for v == 0
//   sum( k>=0, (k+1) * (b_k!=0) )  for v == 1
// v gives the value of the first bit.
// Naive implementation.
{
    ulong r = 0;
    while ( x )
    {
        if ( x & 1UL )  r += v;
        v += 1;
        x >>= 1;
    }
    return r;
}
// -------------------------

static inline ulong bit_perimeter(ulong x)
{
    ulong t = x & (x>>1) & (x<<1);  // interior_ones(x)
    return x ^ t;  // border_ones(x)
}
// -------------------------


#define USE_TABLE

#ifdef USE_TABLE
typedef unsigned char TABLE_TYPE;
//typedef ulong TABLE_TYPE;
static TABLE_TYPE table[256 * BYTES_PER_LONG];

void init_table(ulong v=0)
{
    for (ulong j=0, s=0;  j<BITS_PER_LONG;  j+=8, s+=256)
    {
        for (ulong x=0; x<256; ++x)
        {
            table[s+x] = (TABLE_TYPE)bit_volume( x<<j, v );
//            cout << (ulong)table[x+s] << " ";
        }
//        cout << endl;
//        cout << endl;
    }
}
// -------------------------


static inline ulong bit_volume_table(ulong x)
{
    ulong r = 0;
    ulong s = 0;  // offset
    do
    {
        r += table[s+(x&255)];
        x >>= 8;
        s += 256;
    }
    while ( x );
    return r;
}
// -------------------------
#endif  // USE_TABLE


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Compute terms up to perimeter n");
//    n += 1;

    const ulong v0 = 0;
#ifdef USE_TABLE
    init_table(v0);
#endif // USE_TABLE


    ulong *stats = new ulong[n];
    for (ulong j=0; j<n; ++j) stats[j] = 0;

    const ulong N = 1UL << n;
    for (ulong k0=0; k0<N; ++k0)
    {
        const ulong k = k0;  // default
//        const ulong k = k0 << 1;  // positive parts only ==> A122129
//        const ulong k = k0 << 2;  // parts >=2 only ==> A000000

        const ulong p = bit_perimeter(k);
//        ulong p = k;

#ifdef USE_TABLE
        const ulong v = bit_volume_table(p);
#else
        const ulong v = bit_volume(p, v0);
#endif
        if ( v < n )  stats[v] += 1;


#ifndef TIMING
        cout << setw(4) << k << ":";
        print_bin("  ", k, n+1);  // set (bits)
        print_bin("  ", p, n+1);  // perimeter (bits)
        cout << setw(4) << v;  // perimeter (volume)
//        cout << setw(4) << p;  // perimeter (value)  // A000000
        print_bit_set("    ", p); // perimeter (as set)
        cout << endl;
#endif  // TIMING
    }

    print_vec("  ", stats, n);
    cout << endl;

    delete [] stats;

    return 0;
}
// -------------------------

/*
gcc 4.8.0:

 time ./bin 28
arg 1: 28 == n  [Compute terms up to perimeter n]  default=6
  [ 2 2 3 4 6 8 11 14 19 24 31 39 50 61 77 94 117 141 173 208 253 302 363 431 516 609 723 850 ]
./bin 28  6.87s user 0.00s system 99% cpu 6.874 total
 ==> 2^28/6.87 == 39,073,574 per second

 time ./bin 35
arg 1: 35 == n  [Compute terms up to perimeter n]  default=6
  [ 2 2 3 4 6 8 11 14 19 24 31 39 50 61 77 94 117 141 173 208 253 302 363 431 516 609 723 850
   1003 1174 1379 1607 1878 2181 2537 ]
./bin 35  1038.90s user 0.21s system 99% cpu 17:19.34 total


with USE_TABLE:

 time ./bin 28
arg 1: 28 == n  [Compute terms up to perimeter n]  default=6
  [ 2 2 3 4 6 8 11 14 19 24 31 39 50 61 77 94 117 141 173 208 253 302 363 431 516 609 723 850 ]
./bin 28  1.51s user 0.00s system 99% cpu 1.509 total
 ==> 2^28/1.51 == 177,771,825 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A182372-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A182372-demo.cc DEMOFLAGS=-DTIMING"
/// End:
