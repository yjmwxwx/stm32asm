
#include "comb/partition-dist-asc.h"
#include "comb/partition-boundary.h"

#include "fxtio.h"

//#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A186053:
//% Smallest perimeter among all sets of non-negative integers whose volume is n.

// Cf. seq/A182372-demo.cc for number of sets with fixed perimeter
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 19;
    NXARG(n, "partitions of n into distinct parts");

    partition_dist_asc P(n);

    ulong ct = 0;

    const ulong *x = P.data();
    ulong sp = n + 99;  // smallest perimeter
//    ulong ms = 0;  // how many partitions of smallest perimeter occur
    ulong m = P.num_parts();
    do
    {
        ulong p;

#if 1 // default (part 0 implied)
        if ( m > 1 )
        {
            p = 0;
            if ( x[0] > 1 )  p += x[0];
            else  if ( x[1] - x[0] > 1 )  p += x[0];

            for (ulong j=1; j<m-1; ++j)
            {
                bool q1 = ( (x[j] - x[j-1]) > 1 );
                bool q2 = ( (x[j+1] - x[j]) > 1 );
                if ( q1 || q2 )  p += x[j];
            }

            p += x[m-1];
        }
        else  p = n; // ==x[0];
#else  // no part 0

        p = partition_asc_perimeter(x, m);
//        p = x[0];
//        if ( m != 1 )  p += x[m-1];
//
//        for (ulong j=1; j<m-1; ++j)
//        {
//            bool q1 = ( (x[j] - x[j-1]) > 1 );
//            bool q2 = ( (x[j+1] - x[j]) > 1 );
//            if ( q1 || q2 )  p += x[j];
//        }

#endif

//        ms += ( p == sp );
        if ( p < sp )
        {
//            ms = 1;
            sp = p;
        }

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

#ifndef TIMING
//    cout << " ms=" << ms << endl;
    cout << " sp=" << sp << endl;
    cout << " ct=" << ct << endl;
#else
//    cout << n << " " << sp << endl;  // b-file
    cout << " sp=" << sp << endl;
#endif  // TIMING

    return 0;
}
// -------------------------

/*
 echo $(for n in $(seq 0 40); do ./bin $n ; done | grep sp= ) | sed 's/ sp=/, /g;'

part 0 implied:
0, 1, 2, 2, 4, 5, 3, 6, 7, 6, 4, 8, 8, 9, 7, 5, 10, 11, 9, 10, 8, 6,
  11, 12, 13, 10, 11, 9, 7, 14, 12, 13, 14, 11, 12, 10, 8, 16, 16, 13, 14
(sequence A186053)

part 0 not implied:
1, 2, 3, 4, 5, 4, 7, 8, 6, 5, 9, 8, 9, 7, 6, 11, 12, 9, 10, 8, 7, 11,
  12, 13, 10, 11, 9, 8, 15, 12, 13, 14, 11, 12, 10, 9, 16, 17, 13, 14
(not in the OEIS A000000)
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A186053-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A186053-demo.cc DEMOFLAGS=-DTIMING"
/// End:

