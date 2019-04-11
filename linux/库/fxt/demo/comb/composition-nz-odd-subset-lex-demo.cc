
#include "comb/composition-nz-odd-subset-lex.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive odd parts, subset-lex order.
//% Loopless algorithm.
//% Cf. OEIS sequence A000045.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

// Cf. comb/composition-nz-odd-demo.cc for lexicographic order
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

    composition_nz_odd_subset_lex P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef COMPOSITION_NZ_ODD_SUBSET_LEX_FIXARRAYS
    cout << "COMPOSITION_NZ_ODD_SUBSET_LEX_FIXARRAYS defined." << endl;
#endif
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
    do
    {
        ++ct;

        cout << setw(3) << ct << ":";
//        cout << "[" << setw(2) << m << "]";
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

 time ./bin 47
arg 1: 47 == n  [compositions of n into odd parts]  default=10
 ct=2971215073
./bin 47  7.78s user 0.00s system 99% cpu 7.781 total
 ==> 2971215073/7.78 == 381,904,251 per second


 time ./bin 47
arg 1: 47 == n  [compositions of n into odd parts]  default=10
COMPOSITION_NZ_ODD_SUBSET_LEX_FIXARRAYS defined.
 ct=2971215073
./bin 47  6.35s user 0.00s system 99% cpu 6.350 total
 ==> 2971215073/6.35 == 467,907,885 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-odd-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-odd-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

