
#include "comb/composition-dist-unimodal.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Strongly unimodal compositions into distinct parts.
//% Internal representation as list of parts in increasing order,
//%   with each part except for the last of 2 sorts.
//% Cf. OEIS sequence A072706.

// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 12;
    NXARG(n, "Strongly unimodal compositions of n into distinct parts");

    composition_dist_unimodal P(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
    do
    {
#if 0
        bool q = true;
        for (ulong j=1; j<m; ++j)  // min diff
            if ( P.data()[j] - P.data()[j-1] < 2 )
            { q=0;  break; }
        if ( ! q )  continue;
#endif
        ++ct;

        cout << setw(3) << ct << ":";
//        cout << " [" << setw(2) << m << "] ";

//        P.print_with_sorts("  ");
        P.print("  ");

        cout << endl;

        jjassert( P.OK() );
    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 130
arg 1: 130 == n  [integer compositions of n into distinct parts]  default=13
 ct=1704945753
./bin 130  7.64s user 0.00s system 99% cpu 7.648 total
 ==> 1704945753/7.64 == 223,160,438 per second
*/




/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-dist-unimodal-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-dist-unimodal-demo.cc DEMOFLAGS=-DTIMING"
/// End:

