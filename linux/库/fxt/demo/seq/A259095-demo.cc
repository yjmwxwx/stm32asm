
#include "comb/partition-dist-asc.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A259095:
//% Number of arrangements of n pennies in rows, r pennies in the bottom row, and each higher row consisting of contiguous pennies.
//% Computed via integer partitions into distinct parts as ascending list of parts.

// Cf. comb/partition-dist-asc-demo.cc

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 15;
    NXARG(n, "compute row n of the triangle");

    partition_dist_asc P(n);

    ulong ct = 0;


    ulong m = P.num_parts();
    ulong *bct = new ulong[n+1];
    for (ulong j=0; j<=n; ++j)  bct[j] = 0;

    const ulong *x = P.data();
    do
    {
        ulong y = 1;
        for (ulong j=1; j<m; ++j)  y *= ( x[j] - x[j-1] );
        bct[ x[m-1] ] += y;


        ++ct;

#ifndef TIMING
        cout << setw(4) << ct << ":";
//        cout << " [" << setw(2) << m << "] ";
        P.print("  ");

//        ulong mt = partition_asc_dist_to_odd(P.data(), m, T);
//        print_vec("\n  T: ", T, mt);
//        ulong mx = partition_asc_odd_to_dist(T, mt, X);
//        print_vec("\n  X: ", X, mx);
//        for (ulong i=0; i<m; ++i)  jjassert( X[i] == P.data()[i] );
//        cout << endl;


        cout << "  ==> " << y;

        cout << endl;

        jjassert( P.OK() );
#endif
    }
    while ( (m=P.next()) );

//    cout << " ct=" << ct << endl; // A0000009

    for (ulong j=1; j<=n; ++j)  cout << bct[j] << ", ";  // A259095
    cout << endl;

//    ulong sm = 0;
//    for (ulong j=0; j<=n; ++j)  sm += bct[j];
//    cout << " sm=" << sm << endl; // A001524
    // row maxima give A005577

    delete [] bct;

    return 0;
}
// -------------------------

/*
  for n in $(seq 1 100); do ./bin $n; done

  for n in $(seq 1 20); do ./bin $n; done | grep sm
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A259095-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A259095-demo.cc DEMOFLAGS=-DTIMING"
/// End:
