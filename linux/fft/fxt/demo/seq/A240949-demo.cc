
#include "comb/partition-asc.h"

#include "comb/partition-conj.h"
#include "comb/print-partition-conj.h"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions where the parities of all even parts must be
//% equal and the parities of all odd parts must be equal.
//% Cf. OEIS sequence A240949.

// Cf. comb/partition-asc-demo.cc for all partitions



int
main(int argc, char **argv)
{
    ulong n = 11;
    NXARG(n, "integer partitions of n");

    partition_asc P(n);

    ulong ct = 0;

    bool aa = 0;
//    NXARG(aa, "Whether to render as ASCII art");


    ulong m = P.num_parts();
    do
    {
#if 1 // A240949
        { ulong h[256];  // histogram
            for (ulong i=0; i<=n; ++i)  h[i] = 0;
            for (ulong i=0; i<m; ++i)  h[P.data()[i]] += 1;
            { ulong i, pr;  bool q = 0;
                for (i=0; i<=n; i+=2)
                    if ( h[i] != 0 )
                    {
                        if ( q == 0 )  { q=1;  pr = h[i] & 1;  continue; }
                        if ( ( h[i] & 1 ) != pr )  break;
                    }
                if ( i < n + 1 )  continue;
            }
            { ulong i, pr;  bool q = 0;
                for (i=1; i<=n; i+=2)
                    if ( h[i] != 0 )
                    {
                        if ( q == 0 )  { q=1;  pr = h[i] & 1;  continue; }
                        if ( ( h[i] & 1 ) != pr )  break;
                    }
                if ( i < n + 1 )  continue;
            }
        }
#endif
        ++ct;

#if 1  // allow/suppress printing

        cout << setw(4) << ct << ": ";

//        { ulong j=m; do { --j; cout << " " << x[j]; } while (j); }  // weakly descending list
        cout << " [" << setw(2) << m << "] ";

        P.print("  ");

//        print_partition_asc_conj("    ", P.data(), m);

        if ( aa )  // ASCII art
        {
            P.print_aa();
//            P.print_conj_aa();
            cout << endl;
            cout << endl;
        }

        cout << endl;

        jjassert( P.OK() );
#endif  // allow/suppress printing
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
/// make-target: "1demo DSRC=demo/seq/A240949-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A240949-demo.cc DEMOFLAGS=-DTIMING"
/// End:
