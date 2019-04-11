
#include "bpol/clhca.h"

#include "bpol/bitpol-irred.h"
#include "bpol/bitpol-degree.h"
#include "mod/mersenne.h"
#include "bpol/bitpol-order.h"

#include "bits/bitcount.h"
#include "bits/bittransforms.h"
#include "bits/revbin.h"

#include "fxttypes.h"
#include "bits/print-bin.h"
#include "jjassert.h"
#include "fxtio.h"
#include "nextarg.h"


//% Cyclic (additive) Linear Hybrid Cellular Automata (CLHCA).

bool max_order_q(ulong r, ulong n)
// Return whether CLHCA has maximal period.
// Exhaustive search.
{
    const ulong end = (1UL<<n)-1;
    ulong x = 1;
    ulong k = 0;
    do
    {
        ++k;
        x = clhca_next(x, r, n);
        if ( k>end )  return false;
    }
    while ( x!=1 );
    return (k==end);
}
// -------------------------

bool show(ulong r, ulong n)
// Print all words in period.
{
    const ulong end = (1UL<<n)-1;
    ulong x = 1;
    ulong k = 0;
    do
    {
        ++k;
        cout << setw(4) << k << ":  ";
        print_bin("    ", x, n);
        cout << endl;
        x = clhca_next(x, r, n);
        if ( k>end )  return false;
    }
    while ( x!=1 );
//    cout << setw(4) << k << ":  ";  print_bin("  ", x, n);  cout << endl;
    return (k==end);
}
// -------------------------



int
main(int argc, char **argv)
{
    ulong n = 17;
    NXARG(n, "Number of bits");  // <= BITS_PER_LONG
    jjassert( n <= BITS_PER_LONG );
    const ulong pn  = n;
    const ulong h = 1UL << (n-1);

    factorization F;
    ulong m = mersenne_factorization(n, &F);

    ulong ct = 0;
    const ulong end = mersenne(n);

    ulong tr = 0;   // rules 000001111
    do
//    for (ulong tr=1; tr<=end; ++tr)
    {
        tr|=(tr<<1);  tr|=1;  // next rule
        ulong r = tr;
//        ulong r = bit_rotate_right(tr, 1, n);

        ulong c = clhca2poly(r, n);
        cout << setw(4) << n;
        cout << setw(3) << bit_count(r) << ": ";
        print_bin("    r = ", r, pn);
        print_bin("    c = ", c, pn+1);

//        print_bin("    b = ", blue_code(c), pn+1);  // C(x+1)
//        print_bin("   b2 = ", blue_code(revbin(c,n+1)), pn+1);

        bool iq = bitpol_irreducible_q(c, h);
        if ( iq )  // poly irreducible
        {
            cout << " I";
            ulong rc = bitpol_order(c, h, F);
            bool pq = ( rc==m );
            if ( pq )
            {
                cout << " P";  // max period
                ++ct;
            }
            cout << "  /rc = " << m/rc;
        }
//        bool pq = max_order_q(r, n);
        cout << endl;

        // computation fails for n==BITS_PER_LONG:
        if ( n<BITS_PER_LONG)  jjassert( clhca2poly_too(r, n)==c );

//        if ( q )  { show(r, n); cout << endl; }
    }
    while ( tr!=end );

    return 0;
}
// -------------------------

/*
 for n in $(seq 1 64); do ./bin $n | g P | cut -d: -f1; done
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/clhca-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/clhca-demo.cc DEMOFLAGS=-DTIMING"
/// End:

