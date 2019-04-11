
#include "comb/perm-st.h"
//demo-include "comb/endo-enup.h"


#include "comb/mixedradix.h"
#include "comb/comb-print.h"
#include "aux0/swap.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"


//% Single track ordering for permutations, CAT algorithm.

//#define TIMING  // uncomment to disable printing


//#define SHOW_FACT  // uncomment to show factorial representations
#ifdef SHOW_FACT
#include "comb/fact2perm.h"
#endif


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of elements to permute");

    bool iq = false;
    NXARG(iq, "Whether first permutation is the identical permutation");

    perm_st P(n);
    P.first();

#ifdef SHOW_FACT
    ulong *rfc = new ulong[n];  // rising factorial
    const ulong *x = P.data();
    const ulong *xi = P.invdata();
#endif

    if ( iq )  P.first_id();
    else       P.first();

    ulong ct = 0;

#ifdef TIMING

    do  { ++ct; }  while ( P.next() );

#else  // TIMING
    const bool dfz= true;  // whether to print dots for zeros

    do
    {
        cout << setw(4) << ct << ":";
        P.print("    ", dfz);
        P.print_inv("    ", dfz);

#ifdef SHOW_FACT
        perm2rfact(x, n, rfc);
        print_mixedradix("    ", rfc, n-1, dfz);
        perm2rfact(xi, n, rfc);
        print_mixedradix("    ", rfc, n-1, dfz);
#else
        print_mixedradix("    ", P.d_, n-1, dfz);
#endif

        if ( ct != 0 )
        {
            // print swaps:
            // (positions in inverse permutation, or elements in permutation)
            ulong j = 0;
            while ( P.d_[j] == 0 )  { ++j; }
            cout << "    " << j << ": ";
            for (ulong e1=n-2-j, e2=e1+1;  e2<n;  e1+=2, e2+=2)
            {
                cout << "(" << e1 << "," << e2 << ") ";
            }
        }

        cout << endl;
        ++ct;
    }
    while ( P.next() );

#endif  // TIMING

    cout << " ct=" << ct << endl;

#ifdef SHOW_FACT
    delete [] rfc;
#endif

    return 0;
}
// -------------------------

/*
Timing:

% time  ./bin 12
arg 1: 12 == n  [Number of elements to permute]  default=4
arg 2: 0 == iq  [Whether first permutation is the identical permutation]  default=0
 ct=479001600
./bin 12  3.88s user 0.00s system 99% cpu 3.893 total
 ==> 12!/3.88 == 123,454,020 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

// using for-loop; in next():
% time  ./bin 12
arg 1: 12 == n  [Number of elements to permute]  default=4
arg 2: 0 == iq  [Whether first permutation is the identical permutation]  default=0
 ct=479001600
./bin 12  2.47s user 0.00s system 99% cpu 2.472 total
 ==> 12!/2.47 == 193,927,773 per second

// using do ... while in next():
% time  ./bin 12
arg 1: 12 == n  [Number of elements to permute]  default=4
arg 2: 0 == iq  [Whether first permutation is the identical permutation]  default=0
 ct=479001600
./bin 12  2.10s user 0.00s system 99% cpu 2.102 total
 ==> 12!/2.10 == 228,096,000 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-st-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-st-demo.cc DEMOFLAGS=-DTIMING"
/// End:

