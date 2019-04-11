
#include "ds/deque.h"

#include "fxtio.h"
#include "fxttypes.h"

#include "jjassert.h"

#include "nextarg.h"

//% Demo of the double ended queue (deque) data structure.

static void
print_deque(deque<ulong> &f)
{
    ulong z;
    cout << "    ";
    ulong k = 0;
    while ( (k = f.read(k, z)) )  cout << setw(3) << z;

//    cout << endl;
//    ulong *x = f.x_;
//    for (ulong k=0; k<f.s_; ++k)  cout << setw(3) << x[k];

//    cout << "       ";
//    cout << "   #=" << setw(1) << f.num();
//    cout << "   f=" << setw(1) << f.fpos_;
//    cout << "   l=" << setw(1) << f.lpos_;

    cout << endl;
}
// -------------------------

void
vinsert(deque<ulong> &f, ulong k)
{
    f.insert_first(k);
    cout << "insert_first(" << setw(2) << k << ")  ";
    print_deque(f);

    k += 50;

    f.insert_last(k);
    cout << "insert_last(" << setw(2) << k << ")   ";
    print_deque(f);
}
// -------------------------


void
vextract(deque<ulong> &f)
{
    ulong r=0, z;
    ulong n;

    f.read_first(r);
    n = f.extract_first(z);
    cout << "extract_first()=";
    if ( 0==n )  cout << " (deque is empty) ";
    else         cout << setw(2) << z << "";
    print_deque(f);
    if ( n )  jjassert( r==z );

    f.read_last(r);
    n = f.extract_last(z);
    cout << "extract_last()= ";
    if ( 0==n )  cout << " (deque is empty) ";
    else         cout << setw(2) << z << "";
    print_deque(f);
    if ( n )  jjassert( r==z );
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "size of deque");

    deque<ulong> f(n, n);
    print_deque(f);

    ulong k = 1;
    for (  ; k<n+1; ++k)
    {
        vinsert(f, k);
    }

    for (  ; k<2*n; ++k)
    {
        vextract(f);
        vinsert(f, k);
        vextract(f);
        vextract(f);
    }

    vinsert(f, ++k);

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/ds"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/ds/deque-demo.cc"
/// make-target2: "1demo DSRC=demo/ds/deque-demo.cc DEMOFLAGS=-DTIMING"
/// End:

