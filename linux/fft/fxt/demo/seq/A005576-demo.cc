
#include "comb/partition-dist-desc.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A005576:
//% The limiting sequence [A259095(r(r+1)/2-s,r), s=0,1,2,...,r-1] for very large r.


// Cf. seq/A259095-demo.cc

//#define TIMING  // uncomment to disable printing

const bool D = false;  // for debug

int
main(int argc, char **argv)
{
    ulong n = 33;
    NXARG(n, "compute first n terms");

    const ulong t = n*(n-1)/2;
    if ( D )  cout << " :: t = " << t << endl;
    for (ulong j=0; j<n; ++j)
    {
        const ulong r = t - j;
        // partitions of r with first part n:
        partition_dist_desc P(r);
        P.first();
        const ulong *x = P.data();

        ulong z = 0;
        ulong m = P.num_parts();
        do
        {
            if ( x[0] >= n )  break;  // need second part < n

            ulong y = n - x[0]; // n is first part
            for (ulong k=1; k<m; ++k)  y *= ( x[k-1] - x[k] );
            z += y;

            if ( D )
            { cout << " :: [" << n << "]"; P.print("");  cout << "  y = " << y << endl; }
        }
        while ( (m=P.next()) );

        if ( D )  cout << " :: j = " << j << "  z = " << z << ", " << endl;
        else      cout << z << ", ";
        cout.flush();
    }
    cout << endl;


    return 0;
}
// -------------------------

/*
  for n in $(seq 1 25); do ./bin $n; done

  for n in $(seq 1 25); do ./bin $n; done | grep -v arg
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A005576-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A005576-demo.cc DEMOFLAGS=-DTIMING"
/// End:
