
// demo-is-self-contained

#include "bits/bitlow.h"  // lowest_one_idx()
#include "bits/bitsperlong.h"
#include "bits/print-bin.h"

#include "fxtio.h"
#include "fxttypes.h"  // ulong
#include "jjassert.h"

//% Determination of the lowest bit in a word via modular arithmetic.

//#define BITS_PER_LONG 8  // uncomment for output as in book

// Output dependent on BITS_PER_LONG

#if BITS_PER_LONG == 8
const ulong m = 11;
#else
#if BITS_PER_LONG == 32
const ulong m = 37;
#else
const ulong m = 67;
#endif
#endif

ulong mt[m+1];

static void mt_setup()
{
    mt[0] = 0;  // special value for the zero word
    ulong t = 1;
    for (ulong i=1; i<m; ++i)
    {
        mt[t] = i-1;
        t *= 2;
        if ( t>=m )  t -= m;  // modular reduction
    }
}
// -------------------------

inline ulong m_lowest_one_idx(ulong x)
{
    x &= -x;  // isolate lowest bit
    x %= m;   // power of 2 modulo m
    return  mt[x];  // lookup
}
// -------------------------

int
main()
{
    mt_setup();

    // show the binary de table of powers:
    cout << "modulus m=" << m << endl;

    // show the table:
    cout << "mt[k]=" << endl;
    for (ulong k=0; k<BITS_PER_LONG; ++k) cout << " " << setw(2) << k;
    cout << endl;
    for (ulong k=0; k<BITS_PER_LONG; ++k) cout << " " << setw(2) << mt[k];
    cout << endl;

    for (ulong k=0; k<BITS_PER_LONG; ++k)
    {
        cout << "Lowest bit == " << k << ":" << endl;
        ulong x = 1UL<<k;
        ulong z = x & -x;  // isolate lowets bit
        print_bin("       x= ", z, BITS_PER_LONG);
        cout << " = " << z << endl;
        z %= m;
        cout << "   x % m= " << z;
        ulong i2 = mt[z];
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
        ulong i2 = m_lowest_one_idx(x);
        jjassert( i1==i2 );
    }

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/modular-lookup-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/modular-lookup-demo.cc DEMOFLAGS=-DTIMING"
/// End:

