
#include "comb/perm-rot.h"
#include "perm/perminvert.h"
// demo-include "perm/perminvert.cc"

#include "perm/permq.h"

#include "comb/comb-print.h"

#include "aux1/copy.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"

#include "nextarg.h"  // NXARG()


#define CHECK_UNRANK  // define to check the unranking method

#ifdef CHECK_UNRANK
#include "comb/mixedradix-lex.h"
#endif  // CHECK_UNRANK


//% All permutations, by rotations (cyclic shifts).

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements");

    perm_rot P(n);

    ulong ct = 0;
#ifdef TIMING

    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    const bool dfz = true;  // whether to print dots for zeros
    const ulong *x = P.data();
    ulong *xi = new ulong[n];  // inverse permutation
//    ulong *a = new ulong[n-1];  // mixed radix number
    ulong *t = new ulong[n];  // aux
    ulong ndt = 0;  // number of transitions that are no derangements

#ifdef CHECK_UNRANK
    mixedradix_lex M(n-1, 0);  // falling factorial
#endif
    do
    {
        cout << setw(4) << ct << ":";
        P.print("    ", dfz);

        make_inverse(x, xi, n);
        print_perm("    ", xi, n, dfz);

//        cout << setw(3) << P.k_;

        if ( ct>0 )
        {
            if ( !is_derangement(x, t, n) )  { cout << " N"; ++ndt; }
        }
        for (ulong j=0; j<n; ++j)  t[j] = x[j];  // last perm in t[]

#ifdef CHECK_UNRANK
        P.goto_ffact( M.data() );  // "nop"
//        print_perm("    ", x, n, dfz);
        for (ulong j=0; j<n; ++j)  jjassert( t[j] == x[j] );
        M.next();
#endif

        cout << endl;
        ++ct;
    }
    while ( P.next() );

    delete [] xi;
    delete [] t;
//    delete [] a;

    cout << " # non-derangement transitions = " << ndt << endl;
#endif  // TIMING

    cout << " num = " << ct << endl;


    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 12
arg 1: 12 == n  [Number of elements]  default=4
 num = 479001600  // == 12!
./bin 12  12.77s user 0.06s system 99% cpu 12.837 total
 ==> 479001600/12.77 == 37,509,913 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-rot-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-rot-demo.cc DEMOFLAGS=-DTIMING"
/// End:

