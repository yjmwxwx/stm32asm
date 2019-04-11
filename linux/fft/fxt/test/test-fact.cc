
#include <cmath>
#include <cstdlib>  // strtoul()

#include "comb/num2perm.h"
#include "comb/mixedradix-lex.h"
//#include "comb/perm-lex.h"
#include "comb/fact2perm.h" // perm2ffact()
#include "comb/fact2num.h" // ffact2num()

#include "comb/num2perm.h"

#include "aux0/factorial.h"  // ffactpow()
//#include "ds/bitarray.h"

#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"


bool test_eq(const ulong *a, const ulong *b, ulong n)
{
    bool q = true;
    for (ulong j=0; j<n; ++j)  q &= (a[j]==b[j]);
    return  q;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong minn = 1, maxn = 7;
    if ( argc>1 )  minn = strtoul(argv[1], 0, 10);
    if ( argc>2 )  maxn = strtoul(argv[2], 0, 10);

    cout << "Running tests for factorial, fact2perm, fact2num ... " << endl;

    ulong tt[32];
    ulong pp[32];


    for (ulong n=minn; n<=maxn; ++n)  // rising fact
    {
        mixedradix_lex P(n, 1);  // rising fact
        const ulong N = factorial(n+1);
//        cout << "  N=" << setw(4) << N;
//        print_mixedradix("  nines=", P.m1_, n, true);
//        cout << endl;

        P.first();
        ulong ct = 0;
        const ulong *fc = P.data();
        do
        {
            ulong r = rfact2num(fc, n);
            ulong w = P.to_num();
            num2rfact(r, tt, n);
            num2perm_rfact(r, pp, n+1);
            ulong z = perm2num_rfact(pp, n+1);

//            print_mixedradix("  fc=", fc, n, true);
//            print_mixedradix("  tt=", tt, n, true);
//            print_mixedradix("  pp=", pp, n, true);
//            cout << "  ct=" << setw(4) << ct;
//            cout << "  r=" << setw(4) << r;
//            cout << "  w=" << setw(4) << w;
//            cout << "  z=" << setw(4) << z;
//            cout << endl;

//            jjassert( r < N );
            jjassert( r == ct );
            jjassert( r == w );
            jjassert( r == z );
            jjassert( test_eq(fc, tt, n) );
            jjassert( test_eq(fc, tt, n) );
            ++ct;
        }
        while ( P.next() );
        jjassert( N == ct );
    }


    for (ulong n=minn; n<=maxn; ++n)  // falling fact
    {
        mixedradix_lex P(n, 0);  // falling fact
        const ulong N = factorial(n+1);
//        cout << "  N=" << setw(4) << N;
//        print_mixedradix("  nines=", P.m1_, n, true);
//        cout << endl;

        P.first();
        ulong ct = 0;
        const ulong *fc = P.data();
        do
        {
            ulong r = ffact2num(fc, n);
            ulong w = P.to_num();
            num2ffact(r, tt, n);
            num2perm_ffact(r, pp, n+1);
            ulong z = perm2num_ffact(pp, n+1);

//            print_mixedradix("  fc=", fc, n, true);
//            print_mixedradix("  tt=", tt, n, true);
//            print_mixedradix("  pp=", pp, n, true);
//            cout << "  ct=" << setw(4) << ct;
//            cout << "  r=" << setw(4) << r;
//            cout << "  w=" << setw(4) << w;
//            cout << "  z=" << setw(4) << z;
//            cout << endl;

            jjassert( r == w );
            jjassert( r == ct );
            jjassert( r == z );
            jjassert( test_eq(fc, tt, n) );
            ++ct;
        }
        while ( P.next() );
        jjassert( N == ct );
    }


    cout << "\nOK, all passed." << endl;
    return 0;
}
// -------------------------
