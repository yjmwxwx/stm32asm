
#include "comb/cayley-perm.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Cayley permutations:  Length-n words such that all elements
//%   from 0 to the maximum value occur at least once.
//% Same as: permutations of the (RGS for) set partitions of n.
//% Same as: weak orders on n elements (weak orders are
//%   relations that are transitive and complete).
//% Same as: preferential arrangements of n labeled elements.
//% Generation such that the major order is by content, and minor order lexicographic.
//% Cf. OEIS sequence A000670.

// 1, 1, 3, 13, 75, 541, 4683, 47293, 545835, 7087261, 102247563, 1622632573, ...

// mi=mx=1: A000217
// mi=mx=2: A000000
// mi=mx=3: A000000
// mi=0, mx=1: A000124
// mi=0, mx=2: A000000
// mi=0, mx=3: A000000
// mi=0, mx=n-2: A019472
// mi=0, mx=n-3: A000000
// mi=1: A052875
// mi=2: A000000

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Length of words");

    ulong mi = 0;
    NXARG(mi, "Minimal value of max digit");

    ulong mx = n-1;
    NXARG(mx, "Max allowed digit");

    cayley_perm W(n);
    W.first(mi, mx);

    ulong ct = 0;


#ifdef TIMING

    W.first(mi, mx);
    do  { ++ct; }  while ( W.next() );

#else  // TIMING

    do
    {
        ++ct;

        cout << setw(4) << ct << ":  ";
        W.print("  ", true );
        cout << "  " << W.max_digit();
//        cout << endl;
        W.print_arrangement("       " );
        cout << endl;
    }
    while ( W.next() );


#endif  // TIMING

    cout << " ct=" << ct;
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 11
arg 1: 11 == n  [Length of words (n>=1)]  default=4
arg 2: 0 == mi  [Minimal value of max digit]  default=0
arg 3: 10 == mx  [Max allowed digit]  default=10
 ct=1622632573
./bin 11  11.58s user 0.00s system 99% cpu 11.586 total
 ==> 1622632573/11.58 == 140,123,710 per second

*/

/*
Cf. OEIS sequence A019538 (cf. A131689):
 for n in $(seq 1 10); do for m in $(seq 0 $((n-1))); \
    do ./bin $n $m $m | g "ct=" ; done; echo ; done

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/cayley-perm-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/cayley-perm-demo.cc DEMOFLAGS=-DTIMING"
/// End:

