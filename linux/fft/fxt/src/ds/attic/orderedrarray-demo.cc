
#include "ds/orderedrarray.h"
#include "ds/rarray.h"

#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Demo of the ordered resizable array data structure.


static void
print_ordered_rarray(ordered_rarray<ulong> &f)
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
vinsert(ordered_rarray<ulong> &f, ulong k)
{
    k = k/3 + (k&1?k/2:0);
    ulong n = f.insert(k);
    if ( 0==n )  cout << "  FAILED  ";
    cout << "insert(" << setw(2) << k << ")";
    print_ordered_rarray(f);
}
// -------------------------

static void
vremove(ordered_rarray<ulong> &f)
{
    ulong n = f.num();
    ulong j = n/2;
//    ulong z = f.get(j);
    f.remove_at(j);
    cout << "remove @" << setw(2) << j << "";
    print_ordered_rarray(f);
    if ( 0==n )  cout << "  (ordered_rarray was empty)  " << endl;
//    if ( n )  { jjassert( z ); }
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Size of the ordered resizable array");

    ordered_rarray<ulong> f(n, n);

    ulong k = 1;
    for (  ; k<2*n; ++k)
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
/// make-target: "1demo DSRC=demo/ds/orderedrarray-demo.cc"
/// make-target2: "1demo DSRC=demo/ds/orderedrarray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

