
#include "bits/bitcyclic-minmax.h"
#include "bits/bitcyclic-period.h"

#include "bits/revbin.h"
#include "bits/bitcount.h"

#include "fxttypes.h"
#include "bits/printbin.h"

#include "demo/nextarg.h"
#include "fxtio.h"


//% Find binary necklaces and Lyndon words via exhaustive search.

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Number of bits");
    ulong nn = 1UL << n;

    ulong ct = 0;  // count necklaces
    ulong cto = 0;  // count necklaces of odd weight
    ulong cte = 0;  // count necklaces of even weight
    ulong ctmo = 0; // count Lyndon words of odd weight
    ulong ctme = 0; // count Lyndon words of even weight
    for (ulong k=0; k<nn; ++k)
    {
        if ( k==bit_cyclic_min(k, n) )
        {
            cout << "  " << setw(4) << ct;
            ++ct;
            print_bin("  ", k, n);

            ulong p = bit_cyclic_period(k, n);
            cout << "  " << setw(2) << p;

            ulong b = bit_count(k);
            cout << " " << setw(2) << b;
            if ( b&1 )  { ++cto;  cout << "   o"; }
            else        { ++cte;  cout << "   e"; }
            if ( n==p )
            {
                cout << "  L";
                if ( b&1 )  ++ctmo;
                else        ++ctme;
            }

            cout << endl;
        }
        if ( 0!=k )  ++k;
    }
    cout << " n = " << n << ":  ";
    cout << endl;
    cout << "  #necklaces=" << (cte+cto);
    cout << "  #even=" << cte << "  #odd=" << cto;
    cout << endl;
    cout << "  #Lyndon="<< (ctme+ctmo) ;  // Lyndon words
    cout << "  #even=" << ctme << "  #odd=" << ctmo;
    cout << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bit-necklace-demo.cc"
/// End:

