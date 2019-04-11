
// demo-is-self-contained

#include "bits/bitcount.h"
#include "bits/print-bin.h"
#include "fxtio.h"
#include "jjassert.h"

//#include "bits/graycode.h"
//#include "bits/bittransforms.h"
//#include "bits/bitlex.h"
//#include "bits/parenwords.h"

#include "fxttypes.h"
#include "nextarg.h"


//% Shifts-order for subsets of a binary word.

ulong n;  // number of bits
ulong N;  // 2**n
ulong c, ct=1;

void visit(ulong x)
{
//    static ulong z = 0;
//    if ( 1!=bit_count(x^z) )  return;
    if ( c && (c!=bit_count(x)) )  return;
//    if ( !is_parenword(x) )  return;

    cout << setw(4) << ct++;
    print_bin(":  ", x, n);
//    print_bin("    ", gray_code(x), n);
    cout << "  " << setw(2) << bit_count(x);
//    print_bin_diff("  ", z, x, n, "..PM");
    cout << endl;
//    z = x;
}
// -------------------------


void A(ulong x)  // shifts-order for subsets
{
    if ( x>=N )  return;
    visit(x);
    A(2*x);
    A(2*x+1);
}
// -------------------------


void G(ulong x);  // F() and G():  Gray shifts-order for subsets
void F(ulong x)
{
    if ( x>=N )  return;
    visit(x);
    F(2*x);
    G(2*x+1);
}
// -------------------------
void G(ulong x)
{
    if ( x>=N )  return;
    F(2*x+1);
    G(2*x);
    visit(x);
}
// -------------------------


void B(ulong x)  // shifts-order for Fibonacci words
{
    if ( x>=N )  return;
    visit(x);
    B(2*x);
    B(4*x+1);
}
// -------------------------


//#define C(x) negidx2lexrev(x)
//#define C(x) inverse_gray_code(negidx2lexrev(x))
//#define C(x) inverse_gray_code(x)
//#define C(x) (x)
//#define C(x) lexrev2negidx(x)
//void V(ulong x);  // U() and V(): playground
//void U(ulong x)
//{
//    if ( x>=N )  return;
//    visit(C(x));
//    U(2*x);
//    V(2*x+1);
//}
//// -------------------------
//
//void V(ulong x)
//{
//    if ( x>=N )  return;
//    U(2*x+1);
//    V(2*x);
//    visit(C(x));
//}
//// -------------------------


int
main(int argc, char **argv)
{
    n = 6;
    NXARG(n, "Number of bits");
    N = 1UL<<n;
    ulong q = 1;
    NXARG(q, "what to generate:"
          "  0==>shifts-order, 1==>Gray shifts-order, 2==>Fibonacci words");
    c = 0;
    NXARG(c, "c-subsets (0==>all)");

    cout << endl;
    ct = 1;
    switch ( q )
    {
    case 0:  A(1);  break;
    case 1:  F(1);  break;
    case 2:  B(1);  break;
//    case 3:  U(1);  break;
    }
    cout << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/shift-subsets-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/shift-subsets-demo.cc DEMOFLAGS=-DTIMING"
/// End:
