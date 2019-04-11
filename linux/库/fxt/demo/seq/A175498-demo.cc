
#include "ds/bitarray.h"

#include "comb/comb-print.h"
#include "perm/permq.h"

#include "fxtio.h"
#include "aux0/swap.h"
#include "fxttypes.h"

//#include "perm/permq.h"  // is_involution(), is_connected()
#include "jjassert.h"

#include "nextarg.h"  // NXARG()

//% OEIS sequence A175498:
//% Greedily choose next n (minimal) such that all differences in prefix are distinct.

//#define BFILE

int
main()
{
#ifdef BFILE
    const ulong off = 1;
#endif
    const ulong aoff = 1;

    const ulong n = 150;  // set to 1500 for more than 100 terms
    ulong *a = new ulong[n];  // sequence

    const ulong N = 32*1024;
    bitarray T(N);  // which n are Taken
    T.clear_all();

    const ulong N2 = 2 * N;
    bitarray D(N2);  // which Differences we have seen so far
    D.clear_all();

    ulong p = 0;
    a[p] = 0;
    T.set(p);

#ifdef BFILE
    cout << p+off << " " << a[p]+aoff << endl;
#else
    cout << a[p]+aoff << ", ";
#endif
    while ( p<n )
    {
        ulong j, d;
        for (j=0; j<n; ++j)
        {
            if ( T.test(j) )  continue;  // element already taken

            d = j - a[p];
//            if ( j < a[p] )  d = -d;  // A081145

            jjassert( d + N < N2 );
            if ( ! D.test(d+N) )  break;  // difference already taken
        }
        if ( j==n )  break;

        D.set(d+N);
        T.set(j);

        ++p;
        a[p] = j;
//        if ( is_valid_permutation(a, p) )  print_perm("P=",a,p);

#ifdef BFILE
        cout << p+off << " " << a[p]+aoff << endl;
#else
        cout << a[p]+aoff << ", ";
#endif
    }
    cout << endl;
//    cout << " ct=" << p+1 << endl;

    delete [] a;
    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A175498-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A175498-demo.cc DEMOFLAGS=-DTIMING"
/// End:

