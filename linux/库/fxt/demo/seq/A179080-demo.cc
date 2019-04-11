
#include "comb/partition-dist-asc.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A179080:
//% Integer partitions into distinct parts where adjacent parts have different parity.
//% Also A179049 and A218355: first part respectively odd and even.

// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 20;
    NXARG(n, "partitions of n");
    ulong eo = 0;
    NXARG(eo, "if !=0 then first part has same parity as eo");

    partition_dist_asc P(n);

    ulong ct = 0;
    const ulong *x = P.data();
    ulong m = P.m_;
    do
    {
        // adjacent parts must have different parity
        bool q = true;
        for (ulong j = 1; j<m; ++j)
            if ( 0 == ( 1UL & (x[j]^x[j-1]) ) )  { q=false; break; }
        if ( !q )  continue;

        if ( eo )
        {
            const ulong pr = eo & 1;
            // pr == 0 ==>  A179049: parts are odd, even, odd, even, ...
            // pr == 1 ==>  A218355: parts are even, odd, even, odd, ...

            for (ulong j = 0; j<m; ++j)
                if ( pr != ( 1UL & (x[j]^j) ) )  { q=false; break; }
            if ( !q )  continue;
        }

        ++ct;

#ifndef TIMING
        cout << setw(3) << ct << ": ";
        for (ulong k=0; k<m; ++k)  cout << " " << x[k];
        cout << endl;
#endif  // TIMING

        jjassert( P.OK() );
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
/// make-target: "1demo DSRC=demo/seq/A179080-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A179080-demo.cc DEMOFLAGS=-DTIMING"
/// End:

