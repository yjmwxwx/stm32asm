
#include "comb/partition-dist-asc.h"

#include "fxttypes.h"

#include "jjassert.h"
#include "nextarg.h"  // NXARG()

#include "fxtio.h"

//% OEIS sequence A179009:
//% Maximally refined partitions into distinct parts.
//% A partition (into distinct parts) can be refined if any part
//%   can be split into two parts not in the partition.
//% A maximally refined partition cannot be refined.

//#define TIMING  // uncomment to disable printing


const ulong *a = 0;

bool is_part(ulong p, ulong m)
// Return whether p is a part in the partition a[].
{
    for (ulong k=0; k<m; ++k)  // check against all parts
        if ( p==a[k] )  return true;
    return false;
}
// -------------------------

bool can_refine(ulong m)
// Return whether partition can be refined.
{
    for (ulong k=0; k<m; ++k)  // all parts p
    {
        const ulong p = a[k];
        for (ulong i=1, j=p-1;  i<j;  ++i, --j)  // all splittings of p
        {
            if ( !is_part(i, m) && !is_part(j, m) )
                return true;
        }
    }
    return false;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 35;
    NXARG(n, "Partitions of n");

    partition_dist_asc P(n);
    a = P.data();
    P.first();

    ulong ct = 0;
    ulong m = P.num_parts();
    do
    {
        if ( can_refine(m) )  continue;

        ++ct;
        cout << setw(4) << ct << ":";
        P.print("    ");
        cout << endl;

    }
    while ( (m=P.next()) );


    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A179009-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A179009-demo.cc DEMOFLAGS=-DTIMING"
/// End:
