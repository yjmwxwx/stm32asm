
#include "comb/partition-binary-desc.h"

//#include "comb/partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Binary partitions as weakly descending list of parts.
//% Lexicographic order.
//% Cf. OEIS sequences A018819 and A000123.

// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending lists
// Cf. comb/composition-nz-binary-demo.cc for compositions into powers of 2

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 20;
    NXARG(n, "binary integer partitions of n");

    partition_binary_desc P(n);

    ulong ct = 0;


#ifdef TIMING
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ulong m = P.num_parts();
    do
    {
        ++ct;
        cout << setw(3) << ct << ": ";

        cout << " [" << setw(2) << m << "] ";

//        cout << " [" << setw(2) << n-m << "] ";
//        cout << " [" << setw(2) << P.data()[m-1] << "] ";
//        cout << " [" << setw(2) << P.s_ << "] ";

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

 time ./bin 1000
arg 1: 1000 == n  [binary integer partitions of n]  default=31
 ct=1981471878
./bin 1000  6.24s user 0.00s system 99% cpu 6.240 total
 ==> 1981471878/6.24 == 317,543,570 per second

*/


/*
BENCHARGS=1000
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-binary-desc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-binary-desc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

