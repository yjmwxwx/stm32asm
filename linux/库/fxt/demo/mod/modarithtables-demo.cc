
#include "mod/mod.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "fxtio.h"


//% Addition-, multiplication- and power tables with modular arithmetic.



void
arith_table(int q, int gq)
{
    const int pw = 3;  // print width
    umod_t m = mod::modulus;

    switch ( q )
    {
    case 1:  cout << " Addition:";  gq = 0; break;
    case 2:  cout << " Subtraction:";  gq = 0; break;
    case 3:  cout << " Multiplication:";  break;
    case 4:  cout << " Powers and order:";  break;
    default: cout << " Test:";  break;
    }
    cout << endl;

#define GC(x)  ( gq || (1==gcd(x, (ulong)m)) )

    cout << "       ";
    for (ulong i=0; i<m; ++i) if GC(i) { cout << setw(pw) << i; }
    cout << endl;

    cout << "    ----";
    for (ulong i=0; i<m; ++i) if GC(i)  cout << "---";
    cout << endl;


    mod x(0);
    for (ulong i=0; i<m; ++i, ++x)
    {
        if ( !GC(i) )  continue;
        cout << "   ";  cout << setw(pw) << i << " ";

        mod y(0);
        for (ulong k=0;  k<m;  ++k, ++y)
        {
            if ( !GC(k) )  continue;
            umod_t  z = 0;
            switch ( q )
            {
            case 1:  z = (x + y).x_;  break;  // addition
            case 2:  z = (x - y).x_;  break;  // addition
            case 3:  z = (x * y).x_;  break;  // multiplication
            case 4:  z = (x.pow(k)).x_;  break;  // powers
            default: z = ((x * y).order());  // (test)
            }

            cout << setw(pw) << z;
//            if ( 0!=z ) cout << z;  else cout << '.';
        }

        if ( 4==q )  // with powers give order
        {
            cout << "   ";
            ulong r = x.order();
            cout << "["; cout << setw(pw);
            if ( r )  cout << r;
            else      cout << " --";
            cout << "]";
        }
        cout << endl;
    }
    cout << endl;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong m = 13;
    NXARG(m, "Modulus");

    ulong wh = 0;
    NXARG(wh, "Which table: 1=add 2=sub 3=mul 4=pow 0=all");
    if ( 0==wh )  wh=~0UL;
    else          wh = 1UL << wh;

    int gq = 0;
    NXARG(gq, "Whether to show noninvertible elements with mul/pow tables");

    mod::init(m);
    mod::print_info();  cout << endl;

    wh >>= 1;
    if ( wh&1 )  arith_table(1, gq);  // addition
    wh >>= 1;
    if ( wh&1 )  arith_table(2, gq);  // subtraction
    wh >>= 1;
    if ( wh&1 )  arith_table(3, gq);  // multiplication
    wh >>= 1;
    if ( wh&1 )  arith_table(4, gq);  // powers

    //    arith_table(99);  // test

    mod_reset();  // we want to keep valgrind happy
//    delete [] mod::mtab;  // this is what mod_reset() does for valgrind

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/mod"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/mod/modarithtables-demo.cc"
/// make-target2: "1demo DSRC=demo/mod/modarithtables-demo.cc DEMOFLAGS=-DTIMING"
/// End:

