
#include "comb/partition-dist-asc.h"
#include "comb/partition-boundary.h"

//#include "comb/partition-asc.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A227344:
//% Triangle, partitions into distinct parts by perimeter.
//% Also A227345:
//% Triangle, partitions into distinct parts by boundary size.
//% Also A227426:
//% Partitions into distinct parts with maximal perimeter.

// Cf. seq/A182372-demo.cc for number of sets with fixed perimeter


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 19;
    NXARG(n, "partitions of n into distinct parts");

    partition_dist_asc P(n);
//    partition_asc P(n);

    ulong ct = 0;

    const ulong N = 1024;
    ulong *st = new ulong[N];  // stats
    for (ulong j=0; j<N; ++j)  st[j] = 0;

    const ulong *x = P.data();
    ulong m = P.num_parts();
    do
    {
        ulong p = partition_asc_perimeter(x, m);
//        ulong p = partition_asc_boundary_size(x, m);
        st[p] += 1;
        ++ct;

#ifndef TIMING

        cout << setw(4) << ct << ":";
        cout << setw(4) << p;
//        cout << " [" << setw(2) << m << "] ";
        P.print("  ");
        cout << endl;
#endif  // TIMING
    }
    while ( (m=P.next()) );

    ulong z = 0;
    for (ulong j=0; j<N; ++j)  if ( st[j] )  z = j;
    if ( z < n )  z = n;  // make regular triangle
    for (ulong j=1; j<=z; ++j)
    {
        ct -= st[j];
        cout << st[j] << ", ";
    }
    cout << endl;
    jjassert( ct == 0 );  // triggers if N is too small

//    cout << " z=" << st[z] << endl;  // A227426
//    cout << " z=" << z << endl;  // A000000

//    ulong a = 0;
//    for (ulong j=0; j<N; ++j)  if ( st[j] )  { a = j; break; }
//    cout << " a=" << st[a] << endl;  // A000000
//    cout << " a=" << a << endl;  // A000000

    delete [] st;

    return 0;
}
// -------------------------

/*
 for n in $(seq 0 40); do ./bin $n ; done

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A227344-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A227344-demo.cc DEMOFLAGS=-DTIMING"
/// End:

