
#include "ds/ringbuffer.h"

#include "fxttypes.h"
#include "fxtio.h"

#include "jjassert.h"

#include "nextarg.h"

//% Demo of the ring buffer data structure.


typedef signed char  RBt;

static void
print_ringbuffer(ringbuffer<RBt> &R)
{
    cout << "    ";
    for (ulong j=0; j<R.n_; ++j)  cout << setw(3) << R.x_[j];
    for (ulong j=R.n_; j<R.s_; ++j)  cout << "   ";
    cout << "    ";

    ulong k = 0;
    RBt z;
    while ( (k = R.read(k, z)) )  { cout << setw(3) << z; }
    for (ulong j=R.n_; j<R.s_; ++j)  cout << "   ";
    cout << "  ";
    cout << "   #=" << setw(1) << R.num();
    cout << "   r=" << setw(1) << R.wpos_;
    cout << "   w=" << setw(1) << R.fpos_;
    cout << endl;
}
// -------------------------

static void
vinsert(ringbuffer<RBt> &R, RBt k)
{
    R.insert(k);
    cout << "insert(" << k << ")  ";
    print_ringbuffer(R);
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Size of the ringbuffer");

    ringbuffer<RBt> R(n);
    const char A[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//    for (ulong k=1;  k<5*n/2; ++k)  vinsert(R, k);  // for RBt == ulong
    for (ulong k=0;  k<5*n/2; ++k)  vinsert(R, A[(k%26)]);

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/ds"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/ds/ringbuffer-demo.cc"
/// make-target2: "1demo DSRC=demo/ds/ringbuffer-demo.cc DEMOFLAGS=-DTIMING"
/// End:

