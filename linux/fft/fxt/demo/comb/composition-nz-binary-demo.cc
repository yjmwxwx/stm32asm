
#include "comb/composition-nz-binary.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into powers of 2, lexicographic order.
//% Cf. OEIS sequence A023359.

// Cf. comb/partition-binary-asc-demo.cc for partitions (as weakly ascending lists)
// Cf. comb/partition-binary-desc-demo.cc for partitions (as weakly descending lists)
// Cf. comb/composition-nz-odd-demo.cc for odd parts
// Cf. comb/composition-nz-demo.cc for all compositions


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "compositions of n into powers of 2");

    composition_nz_binary P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef COMPOSITION_NZ_BINARY_FIXARRAYS
    cout << "COMPOSITION_NZ_BINARY_FIXARRAYS defined." << endl;
#endif
    do  { ++ct; }  while ( P.next() );
#else

    ulong m = P.num_parts();
    do
    {
        ++ct;
//        cout <<  P.last_part() << ", ";  continue;  // A000000
//        cout <<  n-m << ", ";  continue;  // A000000

        cout << setw(3) << ct << ": ";
        cout << "[" << setw(2) << m << "]  ";
//        cout << "[" << setw(2) << (n-m)/2 << "]  ";
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

gcc 4.5.0:

 time ./bin 38
arg 1: 38 == n  [compositions of n into powers of 2]  default=8
 ct=1438308328
./bin 38  4.16s user 0.00s system 99% cpu 4.165 total
 ==> 1438308328/4.16 == 345,747,194 per second

 time ./bin 38
arg 1: 38 == n  [compositions of n into powers of 2]  default=8
COMPOSITION_NZ_BINARY_FIXARRAYS defined.
 ct=1438308328
./bin 38  4.41s user 0.00s system 99% cpu 4.415 total
 ==> 1438308328/4.41 == 326,147,013 per second


gcc 4.8.0:

 time ./bin 38
arg 1: 38 == n  [compositions of n into powers of 2]  default=8
 ct=1438308328
./bin 38  4.52s user 0.00s system 99% cpu 4.517 total
 ==> 1438308328/4.52 == 318,209,807 per second

 time ./bin 38
arg 1: 38 == n  [compositions of n into powers of 2]  default=8
COMPOSITION_NZ_BINARY_FIXARRAYS defined.
 ct=1438308328
./bin 38  4.32s user 0.00s system 99% cpu 4.318 total
 ==> 1438308328/4.32 == 332,941,742 per second

*/

/*
BENCHARGS=38
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-binary-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-binary-demo.cc DEMOFLAGS=-DTIMING"
/// End:

