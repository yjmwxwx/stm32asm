
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray codes for certain ternary words counted by Fibonacci numbers

ulong n;    // number of bits in words
ulong *rv;  // bits of the word
ulong *rvo;  // count transitions

ulong ct;   // count objects

ulong xct = 0;
bool gpq;

void visit()
{
    if ( ct>1 )
    {
        xct = 0;
        for (ulong j=0; j<n; ++j)  xct += (rvo[j] != rv[j]);
        jjassert( xct>0 );
        --xct;
//        if ( xct<=12 )  xct = 0;  // min >=two
    }
    for (ulong j=0; j<n; ++j)  rvo[j] = rv[j];

    if ( gpq )
    {
        cout << setw(4) << ct << ":";
        cout << "   ";
        for (ulong j=0; j<n; ++j)
        {
            cout << " ";
            if ( rv[j] )  cout << rv[j];
            else          cout << '.';
        }
//        cout << setw(3) << xct;
        cout << endl;
    }

    jjassert( 0==xct );
}
// -------------------------


void X_rec(ulong d, bool z)
{
    if ( d>=n )
    {
        if ( d<=n+1 )  // avoid duplicates
        {
            ++ct;  // count objects
            visit();
        }
    }
    else
    {
        if ( z )
        {
            rv[d]=0;  rv[d+1]=0;  X_rec(d+2, z);
            rv[d]=1;  rv[d+1]=0;  X_rec(d+2,  ! z);
            rv[d]=1;  rv[d+1]=2;  rv[d+2]=0;  X_rec(d+3, z);
        }
        else
        {
            rv[d]=1;  rv[d+1]=2;  rv[d+2]=0;  X_rec(d+3, z);
            rv[d]=1;  rv[d+1]=0;  X_rec(d+2,  ! z);
            rv[d]=0;  rv[d+1]=0;  X_rec(d+2, z);
        }
    }
}
// -------------------------

int
main(int argc, char **argv)
{
    n = 7;
    NXARG(n, "Length of words");
    rv = new ulong[n+3];
    rvo = new ulong[n+3];
    bool rq = 0;
//    NXARG(rq, "Whether to reverse order");


    gpq = 1;
    xct = 0;
    ct = 0;
    X_rec(0, rq);
    cout << "ct=" << ct << endl;
    cout << endl;

    delete [] rv;
    delete [] rvo;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/fib-alt-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/fib-alt-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

