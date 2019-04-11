
#include "comb/setpart.h"
// demo-include "comb/setpart.cc"

//#include "jjassert.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"

//% Set partitions.


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    int n = 5;
    NXARG(n, "Partition set of n elements");
    bool xdr = true;
    NXARG(xdr, "Change direction in recursion ==> minimal-change order");
    int dr0 = +1;
    NXARG(dr0, "Starting direction in recursion (+-1)");
    dr0 = ( (dr0>0) ? +1 : -1 );
    long px = 0;
    NXARG(px, "If !=0, only list partitions into exactly nx sets");
//    ulong maxct = 0;
//    NXARG(maxct, "Stop after maxct partitions (0: never stop)");
    bool priq = true;
    NXARG(priq, "Option: print internal state with each partition");

    setpart P(n, xdr, dr0);

    ulong ct = 0;
    do
    {
#ifndef TIMING
        if ( px && (P.ns_[n]!=px) )  continue;
        ++ct;
        cout << setw(3) << ct << ":  ";
        if ( priq )  P.print_internal();
        P.print();
        cout << endl;
//        if ( maxct && (ct>maxct) )  break;

#else  // TIMING
        ++ct;
#endif  // TIMING
    }
    while ( P.next() );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:
  % time ./bin 13
arg 1: 13 == n  [Partition set of n elements]  default=4
arg 2: 1 == xdr  [Change direction in recursion ==> minimal-change order]  default=1
arg 3: 1 == dr0  [Starting direction in recursion (+-1)]  default=1
arg 4: 0 == maxct  [Stop after maxct partitions (0: never stop)]  default=0
arg 5: 1 == priq  [Option: print internal state with each partition]  default=1
 ct = 27644437
./bin 13  2.40s user 0.02s system 99% cpu 2.419 total
 ==> 11,428,043 setpart/sec

 % time ./bin 14
 ct = 190899322
./bin 14  17.17s user 0.09s system 99% cpu 17.287 total
 ==> 11,042,941 setpart/sec
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/setpart-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/setpart-demo.cc DEMOFLAGS=-DTIMING"
/// End:

