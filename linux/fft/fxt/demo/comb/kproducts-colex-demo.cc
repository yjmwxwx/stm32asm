
#include "comb/combination-colex.h"
#include "mod/primes.h"

#include "comb/comb-print.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "nextarg.h"

//% Generating all k-products of the n smallest primes
//% via combinations in co-lexicographic order.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 7, k = 3;
    NXARG(n, "All products of k of the n smallest primes");
    NXARG(k, " 0 < k <= n");

    combination_colex C(n, k);

    ulong ct = 0;

    const ulong *c = C.data();  // combinations as sets

    ulong *tf = new ulong[n];  // table of Factors (primes)
    // fill in small primes:
    for (ulong j=0, f=2;  j<n;  ++j)  { tf[j] = f;  f=next_small_prime(f+1); }
    print_set(" F=", tf, n);  cout << endl;

    ulong *tp = new ulong[k+1];  // table of Products
    tp[k] = 1;  // one appended (sentinel)

    ulong j = k-1;
    do
    {
        // update products from right:
        ulong x = tp[j+1];
        { ulong i = j;
            do
            {
                ulong f = tf[ c[i] ];
                //            cout << "( " << x << "*=" << f << ") ";
                x *= f;
                tp[i] = x;
            }
            while ( i-- );
        }  // here: final product is x == tp[0]

        ++ct;
#ifndef TIMING
        cout << setw(4) << ct << ":";
        C.print_set("    ");
        cout << "  " << j << "  ";
        C.print_deltaset("    ");

//        print_vec("    ", tp, k+1);
        cout << "    [";
        for (ulong i=0; i<=k; ++i)  cout << setw(5) << tp[i];
        cout << " ]";

        cout << endl;
#endif  // TIMING

        j = C.next();
    }
    while ( j < k );
    cout << endl;

    cout << " ct = " << ct << endl;

    delete [] tf;
    delete [] tp;

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 32 20
 ==> 225792840/3.37 == 67,000,842 prod/sec
 ==> 225792840/1.60 == 141,120,525 comb/sec

 time ./bin 32 12
 ==> 225792840/2.43 == 92,918,864  prod/sec
 ==> 225792840/1.19 == 189,741,882 comb/sec

 time ./bin 64 7
 ==> 621216192/4.98 == 124,742,207 prod/sec
 ==> 621216192/2.97 == 209,163,701 comb/sec

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/kproducts-colex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/kproducts-colex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

