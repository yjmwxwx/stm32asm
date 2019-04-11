
#include "comb/perm-st-pref.h"
//demo-include "comb/endo-enup.h"


#include "comb/mixedradix.h"
#include "comb/comb-print.h"
#include "aux0/swap.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"


//% Single track ordering for permutations, swaps in prefix, CAT algorithm.

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

    bool iq = true;
    NXARG(iq, "Whether first permutation is the identical permutation");

    perm_st_pref P(n);
    P.first();


    ulong ct = 0;

#ifdef TIMING

    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    const bool dfz= true;  // whether to print dots for zeros

#ifdef SHOW_FACT
    ulong *rfc = new ulong[n];  // rising factorial
    const ulong *x = P.data();
    const ulong *xi = P.invdata();
#endif

    if ( iq )  P.first_id();
    else       P.first();

    do
    {
        cout << setw(4) << ct << ":";
        P.print("    ", dfz);

        P.print_inv("    ", dfz);

#ifdef SHOW_FACT
//        perm2ffact(x, n, rfc);
//        print_mixedradix("    ", rfc, n-1, dfz);
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
            for (ulong e1=j&1, e2=e1+1;  e1<=j;  e1+=2, e2+=2)
            {
                cout << "(" << e1 << "," << e2 << ") ";
            }
        }

        cout << endl;
        ++ct;
    }
    while ( P.next() );

#ifdef SHOW_FACT
    delete [] rfc;
#endif


#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

// using for-loop; in next():
% time  ./bin 12
arg 1: 12 == n  [Number of elements to permute]  default=4
arg 2: 1 == iq  [Whether first permutation is the identical permutation]  default=1
 ct=479001600
./bin 12  2.36s user 0.00s system 99% cpu 2.358 total
 ==> 12!/2.36 == 202,966,779 per second

// using do ... while in next():
% time  ./bin 12
arg 1: 12 == n  [Number of elements to permute]  default=4
arg 2: 1 == iq  [Whether first permutation is the identical permutation]  default=1
 ct=479001600
./bin 12  2.30s user 0.00s system 99% cpu 2.305 total
 ==> 12!/2.30 == 208,261,565 per second

*/

/*
Sequence(s):  (not in OEIS)  A000000

% echo $(./bin 5 | cut -b 12 | sed 's/\./0/g;') | sed 's/ /,/g;'
0,1,2,2,1,0,1,0,0,1,2,2,3,3,3,3,3,3,2,2,1,0,0,1,2,2,1,0,0,1,0,1,2,2,1,0,...

% echo $(./bin 5 | cut -b 12 | sed 's/\./0/g;') | sed 's/ /,/g;' | tr '0123456' '1234567'
1,2,3,3,2,1,2,1,1,2,3,3,4,4,4,4,4,4,3,3,2,1,1,2,3,3,2,1,1,2,1,2,3,3,2,1,...

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-st-pref-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-st-pref-demo.cc DEMOFLAGS=-DTIMING"
/// End:

