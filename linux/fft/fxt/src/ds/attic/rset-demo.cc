
#include "ds/rset.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "nextarg.h"


//% Resizable set (rset) data structure.


static void
print_rset(rset<ulong> &f)
{
    cout << "  ";
    ulong *x = f.data();
    ulong k=0;
    for (  ; k<f.num(); ++k)
    {
        cout << setw(3) << x[k];
    }
    for (  ; k<f.size(); ++k)
    {
        cout << setw(3) << "-";
    }

    cout << "   #=" << setw(1) << f.num();
    cout << endl;
}
// -------------------------

static void
vinsert(rset<ulong> &f, ulong k)
{
    ulong n;
    if ( k&1 )  k += 10;
    n = f.insert(k);
    cout << "insert (" << setw(2) << k << ")  ";

    if ( 0==n )  cout << "  FAILED  ";
    print_rset(f);
}
// -------------------------

static void
vremove(rset<ulong> &f)
{
    ulong j = f.num()/2;
    ulong n;
    n = f.remove_at(j);
    cout << "remove_at(" << setw(2) << j << ")";
    print_rset(f);
    if ( 0==n )  cout << "  (rset was empty)  " << endl;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Size of the rset");

    rset<ulong> f(n, n);

    ulong k = 1;
    for (  ; k<2*n; ++k)  // trigger one resize
    {
        vinsert(f, k);
    }

    for (  ; k<4*n; ++k)
    {
        vremove(f);
        vremove(f);
        vinsert(f, k);
    }

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/ds"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/ds/rset-demo.cc"
/// make-target2: "1demo DSRC=demo/ds/rset-demo.cc DEMOFLAGS=-DTIMING"
/// End:

