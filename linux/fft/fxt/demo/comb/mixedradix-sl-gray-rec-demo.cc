
// demo-is-self-contained

#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Recursive generation of mixed radix numbers in a minimal-change order
//% related so subset-lex order ("SL-Gray" order).


// Cf. comb/mixedradix-sl-gray-demo.cc for an iterative generator.


ulong N;
ulong K;
ulong *rv;  // digits of mixed radix number
ulong xv[32];  // save old digits (for delta-sequence)
ulong dir[32];  // directions in recursion

ulong ct;   // count objects

ulong xp = 0;  // position of last change
ulong md = 0;  // max diff between successive changes


void visit(ulong n)
{
    for (ulong i=n+1; i<N; ++i)  rv[i] = 0;
    for (ulong i=n+1; i<N; ++i)  dir[i] = 0;

#if 0  // Gray code for (weak) compositions; args = N, N-1
    { ulong s = 0;
        for (ulong i=0; i<N; ++i)  s += rv[i];
        if ( s != N )  return;
//        for (ulong i=0; i<N; ++i)
//            cout << " " << 1 + rv[i];
//        cout << endl;
//        return;
    }
#endif

    ++ct;

    cout << setw(4) << ct << ":";
    print_vec("  ", rv, N, 1);
    print_sign_vec("    ", dir, N );

    if ( ct > 1 )
    {
        cout << "    [ ";
        for (ulong j=0; j<N; ++j)  cout << (xv[j] != rv[j] ? '1' :'.' ) << " ";
        cout << "]";

        ulong ps = 0;  // position of change
        for (ulong j=0; j<N; ++j)  if ( xv[j] != rv[j] )  ps = j;
        ulong df = ( xp > ps ? xp - ps : ps - xp );
        xp = ps;
        if ( df > md )
        {
//            cout << "  df=" << df;
            md = df;
        }
    }

    cout << endl;

    for (ulong j=0; j<N; ++j)  xv[j] = rv[j];
}
// -------------------------

void
sl_gray_rec(ulong n, bool z=true)
{
    if ( n==N )
    {
        visit(n);
        return;
    }

    const ulong k = K;  // fixed radix
//    const ulong k = n + 2;  // rising factorial basis
//    const ulong k = N - n + 1;  // falling factorial basis

//    z = 1;  // generate subset-lex order

    // as is, md == 2 (i.e., two-close transitions) for all even radices >= 4 (and md==3 for rad. 2)
//    z = !z;  // md == 2 for odd radices (but only modular Gray code in last track)
//    if ( (n%2) == 0 )  z = !z;  // md == 3 for all rad. >= 3 (md==5 for rad. 2)
//    z ^= (k&1);  // md == 2 for ALL radices >= 3 (but for odd rad. only modular Gray code in last track)

    if ( z )  // forward:
    {
        dir[n] = +1;
        for (ulong j=1; j<k; ++j)  // rising nonzero values followed by zeros
        {
            rv[n] = j;
            visit(n);
        }

        dir[n] = -1UL;
        if ( n < N - 1 )  // only if not at end
        {
            for (ulong j=k-1; (long)j>=0; --j)  // falling values and recursion
            {
                rv[n] = j;
                sl_gray_rec(n+1, z);
                z = !z;
            }
        }
    }
    else     // backward:
    {
        dir[n] = +1;
        if ( n < N - 1 )  // only if not at end
        {
            z = k & 1;  // fixup for odd k: nine followed by forward list

            for (ulong j=0; j<k; ++j)  // rising values and recursion
            {
                z = !z;
                rv[n] = j;
                sl_gray_rec(n+1, z);
            }
        }

        dir[n] = -1UL;
        for (ulong j=k-1; j>0; --j)  // falling nonzero values followed by zeros
        {
            rv[n] = j;
            visit(n);
        }
    }
}
// -------------------------

int
main(int argc, char **argv)
{
    N = 3;
    NXARG(N, "Number of digits");
    K = 4;
    NXARG(K, "Radix");

    rv = new ulong[N];
    for (ulong j=0; j<N; ++j)  rv[j] = 0;
    for (ulong j=0; j<N; ++j)  dir[j] = +1;

    ct = 0;
    visit(-1UL);  // note
    sl_gray_rec(0, true);

    // max difference between positions of successive transitions:
//    cout << "md=" << md << endl;
    cout << "ct=" << ct << endl;

    delete [] rv;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-sl-gray-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-sl-gray-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:
