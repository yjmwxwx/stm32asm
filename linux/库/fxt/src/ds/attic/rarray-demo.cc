
#include "ds/rarray.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "nextarg.h"

//% Demo of the resizable array (rarray) data structure.


static void
print_rarray(rarray<ulong> &f)
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
vinsert(rarray<ulong> &f, ulong k)
{
    ulong n;
    if ( k&1 )
    {
        n = f.append(k);
        cout << "append (" << setw(2) << k << ") ";
    }
    else
    {
        n = f.prepend(k);
        cout << "prepend(" << setw(2) << k << ") ";
    }

    if ( 0==n )  cout << "  FAILED  ";
    print_rarray(f);
}
// -------------------------

static void
vremove2(rarray<ulong> &f)
{
    ulong n;
    n = f.remove_last();
    cout << "remove_last " << "";
    print_rarray(f);
    if ( 0==n )  cout << "  (rarray was empty)  " << endl;

    n = f.remove_first();
    cout << "remove_first" << "";
    print_rarray(f);
    if ( 0==n )  cout << "  (rarray was empty)  " << endl;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Size of the rarray");

    rarray<ulong> f(n, n);

    ulong k = 1;
    for (  ; k<2*n; ++k)  // trigger one resize
    {
        vinsert(f, k);
    }

    for (  ; k<4*n; ++k)
    {
        vremove2(f);
        vinsert(f, k);
    }

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/ds"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/ds/rarray-demo.cc"
/// make-target2: "1demo DSRC=demo/ds/rarray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

