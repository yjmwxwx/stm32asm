
#include "comb/composition-nz-odd.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive odd parts, lexicographic order.
//% Loopless algorithm.
//% Cf. OEIS sequence A000045.

// Cf. comb/composition-nz-odd-subset-lex-demo.cc for subset-lex order
// Cf. comb/composition-nz-demo.cc for all compositions
// Cf. comb/composition-nz-left-smooth-demo.cc for left-smooth compositions
// Cf. comb/composition-nz-smooth-demo.cc for smooth compositions
// Cf. comb/composition-nz-max-demo.cc for compositions into parts <= mx
// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "compositions of n into odd parts");

    composition_nz_odd P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef COMPOSITION_NZ_ODD_FIXARRAYS
    cout << "COMPOSITION_NZ_ODD_FIXARRAYS defined." << endl;
#endif
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
    do
    {
        ++ct;

//        cout <<  P.last_part() << ", ";  continue;  // A000000
//        cout <<  (n-m) << ", ";  continue;  // A007895

        cout << setw(3) << ct << ": ";
        cout << "[" << setw(2) << m << "]  ";

        P.print("");
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

 time ./bin 47
arg 1: 47 == n  [compositions of n into odd parts]  default=12
  ct=2971215073
./bin 47  8.10s user 0.00s system 99% cpu 8.105 total
 ==> 2971215073/8.10 == 366,816,675 per second


With COMPOSITION_NZ_ODD_FIXARRAYS defined:
 time ./bin 47
arg 1: 47 == n  [compositions of n into odd parts]  default=12
COMPOSITION_NZ_ODD_FIXARRAYS defined.
  ct=2971215073
./bin 47  6.70s user 0.00s system 99% cpu 6.706 total
 ==> 2971215073/6.70 == 443,464,936 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-odd-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-odd-demo.cc DEMOFLAGS=-DTIMING"
/// End:

