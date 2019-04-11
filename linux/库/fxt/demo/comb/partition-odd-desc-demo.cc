
#include "comb/partition-odd-desc.h"

//#include "comb/partition-desc.h"

#include "comb/partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions into odd parts as weakly descending list of parts.
//% Cf. OEIS sequence A000009.

// Cf. comb/partition-desc-demo.cc for partitions as weakly descending lists
// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts as weakly ascending lists
// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending lists

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 18;
    NXARG(n, "integer partitions of n");

//    partition_desc P(n);
    partition_odd_desc P(n);

    ulong ct = 0;


#ifdef TIMING
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ulong m = P.num_parts();
    do
    {
#if 0  // only into distinct parts
        const ulong *x = P.data();
        bool q = true;
        for (ulong j = 1; j<m; ++j)
            if ( x[j]==x[j-1] )  { q=false; break; }
        if ( !q )  continue;
#endif
#if 0  // only into self-conjugate partitions
        if ( !partition_desc_is_self_conj( P.data(), m ) )  continue;
#endif

        ++ct;
        cout << setw(3) << ct << ": ";

        cout << " [" << setw(2) << m << "] ";

//        cout << " d=" << setw(2) << P.durfee_n() << " ";


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

 time ./bin 220
arg 1: 220 == n  [integer partitions of n]  default=18
  ct=1586861606
./bin 220  10.15s user 0.00s system 99% cpu 10.152 total
 ==> 1586861606/10.15 == 156,341,044 per second

*/

/*
BENCHARGS=220
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-odd-desc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-odd-desc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

