

#include "comb/partition-asc.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% OEIS sequence A178715:
//% Maximal value of prod(k=1..m, p_k-1 ) over all partitions
//% p_1 + p_2 + ... + p_m  of  n+1.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "Number of parts");

    partition_asc P(n);

    ulong mx = 0;  // max product

    const ulong *x = P.data();
    do
    {
        ulong m = P.num_parts();
        ulong t = 1;
        while ( m-- )  t *= (x[m] - 1);  // A178715
//        while ( m-- )  t *= (x[m] + 1);  // A000079 (powers of two)
//        while ( m-- )  t *= (x[m] - 0);  // A000792
//        while ( m-- )  t *= (x[m] - 2);  // A193286

#ifndef TIMING
        if ( t != 0 )  { P.print("");  cout << "  " << t << endl; }
#endif  // TIMING
        if ( t > mx )  mx = t;
    }
    while ( P.next() );

    cout << " " << mx << endl;

    return 0;
}
// -------------------------

/*
echo $(for n in $(seq 2 33); do ./bin $n ; done | grep '^ ') | sed 's/ /, /g'

1, 2, 3, 4, 5, 6, 9, 12, 16, 20, 27, 36, 48, 64, 81, 108, 144, 192,
256, 324, 432, 576, 768, 1024, 1296, 1728, 2304, 3072, 4096, 5184,
6912, 9216, 12288, 16384, 20736, 27648, 36864, 49152, 65536, 82944

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A178715-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A178715-demo.cc DEMOFLAGS=-DTIMING"
/// End:
