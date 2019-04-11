
#include "comb/composition-nz-superdiagonal.h"

//#include "comb/partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Superdiagonal compositions: compositions a[1] + a[2] + ... + a[m] = n
//%   such that a[k] >= k.
//% Lexicographic order.
//% Same as: superdiagonal bargraphs, see
//%   Emeric Deutsch, Emanuele Munarini, Simone Rinaldi:
//%   "Skew Dyck paths, area, and superdiagonal bargraphs",
//%   Journal of Statistical Planning and Inference,
//%   vol.140, no.6, pp.1550-1562, (June-2010).
//% Cf. OEIS sequence A219282.

// Cf. comb/partition-strongly-decr-desc-demo.cc for strongly decreasing partitions
// Cf. comb/partition-nonsquashing-desc-demo.cc for non-squashing partitions

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 13;
    NXARG(n, "superdiagonal compositions of n");

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    composition_nz_superdiagonal P(n);

    ulong ct = 0;


#ifdef TIMING
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ulong m = P.num_parts();
    do
    {
//        cout << m << ", ";  continue;  // A000000
//        cout << P.data()[m-1] << ", ";  continue;  // A000000

        ++ct;
        cout << setw(4) << ct << ": ";

        cout << " [" << setw(2) << m << "] ";

//        cout << " [" << setw(2) << n-m << "] ";
//        cout << " [" << setw(2) << P.data()[m-1] << "] ";

        P.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
            cout << endl;
            cout << endl;
        }

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

 time ./bin 90
arg 1: 90 == n  [superdiagonal compositions of n]  default=13
arg 2: 0 == aa  [Whether to render as ASCII art]  default=0
 ct=2291164450
./bin 90  9.24s user 0.00s system 99% cpu 9.247 total
 ==> 2291164450/9.24 == 247,961,520 per second

// with code for easy case:
 time ./bin 90
arg 1: 90 == n  [superdiagonal compositions of n]  default=13
arg 2: 0 == aa  [Whether to render as ASCII art]  default=0
 ct=2291164450
./bin 90  11.11s user 0.00s system 99% cpu 11.112 total
 ==> 2291164450/11.11 == 206,225,423 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-superdiagonal-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-superdiagonal-demo.cc DEMOFLAGS=-DTIMING"
/// End:

