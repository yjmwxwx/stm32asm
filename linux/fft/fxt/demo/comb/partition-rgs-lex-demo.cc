
#include "comb/partition-rgs-lex.h"
#include "comb/is-partition-rgs.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% Restricted growth strings (RGS) for partitions as descending lists,
//% lexicographic order.
//% Same as: least Young tableaux (as RGS) with fixed shape (partition).
//% Cf. OEIS sequence A000041.

// Cf. comb/partition-desc-demo.cc for the corresponding partitions as weakly descending lists
// Cf. comb//young-tab-rgs-demo.cc for all Young tableaux (as RGS)

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "length of RGS (n>=1)");

    partition_rgs_lex R(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( R.next() );
#else

//    const ulong *x = R.data();
    ulong j = 0;  // position of leftmost change
    do
    {
        ++ct;

//        cout << R.data()[n-1]+1 << ", " ;  continue;  // A000000

        cout << setw(4) << ct << ":";
        R.print("  ", true);
//        R.print_sym("  ");
        cout << setw(4) << j;

        R.print_partition("    ");

        cout << endl;

        jjassert( R.OK() );
    }
    while ( (j=R.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)


 time ./bin 110
arg 1: 110 == n  [length of RGS (n>=1)]  default=10
  ct=607163746
./bin 110  18.22s user 0.00s system 99% cpu 18.227 total
 ==> 607163746/18.22 == 33,324,025 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-rgs-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-rgs-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

