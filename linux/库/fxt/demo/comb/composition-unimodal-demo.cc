
#include "comb/composition-unimodal.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% Strongly unimodal compositions.
//% Internal representation as list of parts in weakly ascending
//%   order, with each part except for the last of 2 sorts and no
//%   repeated parts of the same sort.
//% Cf. OEIS sequence A059618.

// Cf. comb/composition-dist-unimodal-demo.cc for unimodal compositions into distinct parts
// Cf. comb/partition-asc-2rep-demo.cc for partitions with mulitplicities of parts <= 2

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 12;
    NXARG(n, "Strongly unimodal compositions of n");

    composition_unimodal P(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
    do
    {
#if 0  // due to the internal representation the following is slightly nontrivial:
        const ulong *x = P.data();
        bool q = true;
        for (ulong j=1; j<m; ++j)
//            if ( x[j] - x[j-1] < 2 )   // min diff
            if ( x[j] - x[j-1] > 1 )   // max diff
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

 time ./bin 100
arg 1: 100 == n  [Strongly unimodal compositions of n]  default=19
 ct=336831405
./bin 100  2.54s user 0.00s system 99% cpu 2.547 total
  ==> 336831405/2.54 == 132,610,789 per second
*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-unimodal-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-unimodal-demo.cc DEMOFLAGS=-DTIMING"
/// End:

