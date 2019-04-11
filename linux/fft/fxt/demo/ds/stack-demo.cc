
#include "ds/stack.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "jjassert.h"
#include "nextarg.h"


//% Demo of the stack (LIFO) data structure.

static void
print_stack(stack<ulong> &f)
{
    ulong *x = f.x_;
    ulong k=0;
    for (  ; k<f.p_; ++k)
    {
        cout << setw(3) << x[k];
    }
    for (  ; k<f.s_; ++k)
    {
        cout << setw(3) << "-";
    }

    cout << "   #=" << setw(1) << f.num();
    cout << endl;
}
// -------------------------

static void
vpush(stack<ulong> &f, ulong k)
{
    ulong n = f.push(k);
    if ( 0==n )  cout << "  FAILED  ";
    cout << "push(" << setw(2) << k << ")";
    print_stack(f);
}
// -------------------------

static void
vpop(stack<ulong> &f)
{
    ulong z = 0;
    ulong n = f.pop(z);
    cout << "pop==" << setw(2) << z << " ";
    print_stack(f);
    if ( 0==n )  cout << "  (stack was empty)  " << endl;
    if ( n )  { jjassert( z ); }
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Size of stack");

    stack<ulong> f(n, n);

    ulong k = 1;
    for (  ; k<2*n; ++k)  // trigger one resize
    {
        vpush(f, k);
    }

    for (  ; k<4*n; ++k)
    {
        vpop(f);
        vpop(f);
        vpush(f, k);
    }

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/ds"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/ds/stack-demo.cc"
/// make-target2: "1demo DSRC=demo/ds/stack-demo.cc DEMOFLAGS=-DTIMING"
/// End:

