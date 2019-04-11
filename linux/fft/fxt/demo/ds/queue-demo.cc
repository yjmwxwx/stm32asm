
#include "ds/queue.h"

#include "aux1/copy.h"  // null()

#include "fxttypes.h"
#include "fxtio.h"

#include "jjassert.h"

#include "nextarg.h"


//% Demo of the queue (FIFO) data structure.


static void
clear_unused(queue<ulong> &f)
// Clear unused entries.
{
    ulong s = f.rpos_, e = f.wpos_;

//    cout << "   s=" << setw(1) << s;
//    cout << "   e=" << setw(1) << e;
//    cout << endl;

    ulong *x = f.x_;
    if ( f.n_==0 )  { null(x, f.s_); return; }
    if ( s==e )  { return; }

    if ( s>e )  null(x+e, s-e);
    else
    {
        null(x, s);
        null(x+e , f.s_-e);
    }
}
// -------------------------

static void
print_queue(queue<ulong> &f)
{
    clear_unused(f);
    ulong *x = f.x_;
    for (ulong k=0; k<f.s_; ++k)
    {
        ulong z = x[k];
        cout << setw(3);
        if ( 0!=z )  cout << z;
        else         cout << "-";
    }
    cout << "   #=" << setw(1) << f.num();
    cout << "   r=" << setw(1) << f.rpos_;
    cout << "   w=" << setw(1) << f.wpos_;
    cout << endl;
}
// -------------------------

static void
vpush(queue<ulong> &f, ulong k)
{
    ulong n = f.push(k);
    if ( 0==n )  cout << "  FAILED  ";
    cout << "push(" << setw(2) << k << ")";
    print_queue(f);
}
// -------------------------

static void
vpop(queue<ulong> &f)
{
    ulong z = 0;
    ulong n = f.pop(z);
    cout << "pop==" << setw(2) << z << " ";
    print_queue(f);
    if ( 0==n )  cout << "  (queue was empty)  " << endl;
    if ( n )  { jjassert( z ); }
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Initial size of queue");

    queue<ulong> f(n, n);

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
/// make-target: "1demo DSRC=demo/ds/queue-demo.cc"
/// make-target2: "1demo DSRC=demo/ds/queue-demo.cc DEMOFLAGS=-DTIMING"
/// End:

