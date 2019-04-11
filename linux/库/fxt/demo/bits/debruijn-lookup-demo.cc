
// demo-is-self-contained

#include "bits/bitlow.h"  // lowest_one_idx()
#include "bits/bitsperlong.h"
#include "bits/print-bin.h"

#include "fxtio.h"
#include "fxttypes.h"  // ulong
#include "jjassert.h"


//% Determination of the lowest bit in a word via De Bruijn sequences.

#define AS_FXTBOOK  // uncomment for output as in book

#ifdef AS_FXTBOOK
#undef BITS_PER_LONG
#define BITS_PER_LONG 8
#endif

#if BITS_PER_LONG == 8
const ulong db = 0x17UL;  // == 00010111
const ulong s = 8-3;
#define MASK  ( 7 )  // needed only for demo
#else
#if BITS_PER_LONG == 32
const ulong db = 0x4653ADFUL;
// == 00000100011001010011101011011111
const ulong s = 32-5;
#else
const ulong db = 0x218A392CD3D5DBFUL;
// == 0000001000011000101000111001001011001101001111010101110110111111
const ulong s = 64-6;
#endif
#endif

ulong dbt[BITS_PER_LONG];

static void dbt_setup()
{
    for (ulong i=0; i<BITS_PER_LONG; ++i)
    {
//        dbt[ (db<<i)>>s ] = i;
        ulong x = (db<<i)>>s;
        x &= MASK;  // allow for small words (for demo)
        dbt[x] = i;
    }
}
// -------------------------

inline ulong db_lowest_one_idx(ulong x)
{
    x &= -x;  // isolate lowest bit
    x *= db;  // multiplication by a power of 2 is a shift
    x >>= s;  // use log_2(BITS_PER_LONG) highest bits
    x &= MASK;  // allow for small words (for demo)
    return  dbt[x];  // lookup
}
// -------------------------

int
main()
{
    dbt_setup();

    // show the binary De Bruijn sequence:
    print_bin("db=", db, BITS_PER_LONG);
    cout << endl;

    // show the table:
    cout << "dbt[k]=" << endl;
    for (ulong k=0; k<BITS_PER_LONG; ++k) cout << " " << setw(2) << k;
    cout << endl;
    for (ulong k=0; k<BITS_PER_LONG; ++k) cout << " " << setw(2) << dbt[k];
    cout << endl;

    for (ulong k=0; k<BITS_PER_LONG; ++k)
    {
        cout << "Lowest bit == " << k << ":" << endl;
        ulong x = 1UL<<k;
        ulong z = x & -x;  // isolate lowets bit
        print_bin("       x = ", z, BITS_PER_LONG);
        cout << endl;
        z *= db;  // multiply by a power of 2 is a shift
        print_bin("  db * x = ", z, BITS_PER_LONG);
        cout << endl;
        z >>= s;
        z &= MASK;  // allow for small words (for demo)
        print_bin(" shifted = ", z, BITS_PER_LONG);
        cout << "  == " << z << endl;
        ulong i2 = dbt[z];
        cout << " ==> lookup = " << i2;
        cout << endl;
        ulong i1 = lowest_one_idx(x);
        jjassert( i1==i2 );
        cout << endl;
    }

    for (ulong k=0; k<BITS_PER_LONG; ++k)  // check
    {
        ulong x = 1UL<<k;
        ulong i1 = lowest_one_idx(x);
        ulong i2 = db_lowest_one_idx(x);
        jjassert( i1==i2 );
    }

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/debruijn-lookup-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/debruijn-lookup-demo.cc DEMOFLAGS=-DTIMING"
/// End:

