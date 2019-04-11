
#include "bits/bitcombcolex.h"
#include "bits/bitrotate.h"


#include "fxttypes.h"
#include "aux1/copy.h"
#include "bits/print-bin.h"

#include "fxtio.h"
#include "fxtalloca.h"

#include "nextarg.h"


//% Find all De Bruijn sequences (DBS) of given length 2^n (3<=n<=5).  Exhaustive search.


ulong
test_debruijn(ulong w, ulong n)
// return 0 if w is a DBS for length-n words
// else return k!=0
{
    ulong nn = 1UL<<n;
    ALLOCA(int, t, nn);
    null(t, nn);

    const ulong mask = first_comb(n);
    for (ulong k=0; k<nn; ++k)
    {
        ulong x = w & mask;
        if ( t[x] )  return  k;  // k!=0
        else         t[x] = 1;
        w = bit_rotate_right(w, 1, nn);
    }

    return 0;
}
// -------------------------


double
com(ulong f, ulong n)
// center of mass
{
    double m = 0.0;
    double c = 0.0;
    for (ulong k=0; k<n; ++k)
    {
        ulong e = f & 1;
        m += (double)e;
        c += (double)k * (double)e;
        f >>= 1;
    }
    return  c / m;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Search length-2**n De Bruijn sequences");

    const ulong nn = 1UL<<n, nnh = nn/2;
    cout << "n = " << n << "  nn = " << nn << endl;

    ulong N = nn-n-2,  K = nnh-2;
    ulong c = last_comb(K, N);
//    cout << "checking binomial(" << N << ", " << K << ")= "
//         << binomial(N,K) << " combinations ..." << endl;
    // n = 3:  binomial(3, 2)   = 3
    // n = 4:  binomial(10, 6)  = 210
    // n = 5:  binomial(25, 14) = 4,457,400
    // n = 6:  binomial(56, 30) = 6,646,448,384,109,072

    ulong ct = 0;     // # of DBS
    const ulong hilo = 1 | (1UL<<(nn-n-1));  // n=4 ==> hilo=....1..........1
    //                               combinations go here: .....**********.
    // the DBS are the cyclic minima, they have the form:  00001**********1

    do
    {
        ulong cc = (c<<1) | hilo;
        ulong q = test_debruijn(cc, n);
        if ( 0==q )  // found DBS
        {
            ++ct;
//            cout << setw(8) << cc << ":   ";
            print_bin("", cc, nn);
//            cout << "  " << (nn/2 - com(cc, nn));
            cout << endl;
        }
    }
    while ( (c=prev_colex_comb(c)) );

    cout << "total # of DBS found = " << ct << endl;

    return  0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/all-dbs-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/all-dbs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

