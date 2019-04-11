
#include "comb/necklace.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "fxtio.h"

//% OEIS sequence A215327:
//% smooth necklaces with 3 colors.
//% Also A215328: smooth Lyndon words with 3 colors.
//% Also A215329: smooth necklaces, 4 colors.
//% Also A215330: smooth Lyndon words, 4 colors.
//% Also A215331: smooth necklaces, 5 colors.
//% Also A215332: smooth Lyndon words, 5 colors.
//% Also A215333: smooth necklaces, 7 colors.
//% Also A215334: smooth Lyndon words, 7 colors.
//% Also A208772: cyclically smooth necklaces, 3 colors.
//% Also A208773: cyclically smooth necklaces, 4 colors.
//% Also A208774: cyclically smooth necklaces, 5 colors.
//% Also A208775: cyclically smooth necklaces, 6 colors.
//% Also A208776: cyclically smooth necklaces, 7 colors.
//% Also A208777: array (cyclically smooth necklaces of k colors as column k).
//% Also A215335: cyclically smooth Lyndon words, 3 colors.
//% Also A215336: cyclically smooth Lyndon words, 4 colors.
//% Also A215337: cyclically smooth Lyndon words, 5 colors.
//% Also A215338: cyclically smooth Lyndon words, 7 colors.

// Cf. comb/necklace-demo.cc


#define PRX()  { if (x[k])  cout << x[k]; else cout << '.'; }

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "length of strings >=1");
    ulong m = 3;
    NXARG(m, "number of different beads >=2");
    ulong cq = 0;
    NXARG(cq, "whether cyclically smooth");

    necklace P(m, n);
    const ulong *x = P.data();

    ulong j = P.j_;  // ==1
    ulong pct = 0;  // count pre-necklaces (pre-prime strings)
    ulong ct = 0;   // count necklaces (prime strings)
    ulong lct = 0;  // count Lyndon words
    do
    {
        { // only transitions by +-1 (smooth necklaces):
            bool q = true;
            for (ulong w=1; w<n; ++w)
            {
                ulong d = x[w] - x[w-1];
                if ( (long)d < 0 )  d = -d;
                if ( d > 1 )  { q=false; break; }
            }
//            cout << (q ? " " : "!");
            if ( ! q )  continue;
        }

        if ( cq )  // only transitions by +-1 also from first to last
        {
            ulong d = x[0] - x[n-1];
            if ( (long)d < 0 )  d = -d;
            if ( d > 1 )  continue;
        }


#if 0
        { // no zero after first nonzero element:
            ulong w = 0;
            while ( x[w]==0 )  ++w;
            for ( ++w ; w<n; ++w )  if ( x[w]==0 )  break;
            if ( w < n )  continue;
            // With this condition, try
            // %  for n in $(seq 1 20) ; do ./bin $n 3 0 | grep Lyn ; done
            // A000000 (3 sequences not in the OEIS)
        }
#endif


        ++pct;

        bool nq = P.is_necklace();

#ifdef TIMING

        if ( nq )
        {
            ++ct;
            if ( P.is_lyn() )  ++lct;
        }

#else
        cout << "    ";
        // print full string:
        for (ulong k=0; k<n; ++k)  PRX();
        cout << "  " << setw(2) << j;  // period

        // print string in minimal period:
        cout << "    ";
        ulong k;
        for (k=0; k<n-j; ++k)  cout << " ";
        for (  ; k<n; ++k)  PRX();

        if ( nq )
        {
            ++ct;
            cout << "  N";  // is a necklace
            if ( P.is_lyn() )
            {
                ++lct;
                cout << " L";  // is a Lyndon word
            }
        }
        cout << endl;
#endif  // TIMING
    }
    while ( (j=P.next_pre()) );

    cout << "  # pre-necklaces = " << pct << endl;
    cout << "  # necklaces = " << ct << endl;
    cout << "  # Lyndon words = " << lct << endl;
    cout << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A215327-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A215327-demo.cc DEMOFLAGS=-DTIMING"
/// End:

