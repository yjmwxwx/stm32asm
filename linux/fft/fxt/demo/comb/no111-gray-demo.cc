
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray code for binary words with no substring 111, recursive CAT algorithm


//#define TIMING  // define to disable printing

ulong n;   // number of bits in words
long *rv;  // bits of the word
long *rvo;  // count transitions
long *dlt;  // transitions

ulong ct;   // count objects

long xct = 0;

bool check_gray()
{
    xct = 0;
    if ( ct>1 )
    {
        for (ulong j=0; j<n; ++j)  xct += (rvo[j] != rv[j]);
        --xct;
//        if ( xct<=12 )  xct = 0;  // min >=two
    }

    for (ulong j=0; j<n; ++j)  dlt[j] = ( rvo[j] != rv[j] );
    for (ulong j=0; j<n; ++j)  rvo[j] = rv[j];

    return (xct==0);
}
// -------------------------

void print()
{
    cout << setw(4) << ct << ":";
    cout << "   ";
    ulong bct = 0;  // count nonzero elements
    for (ulong j=0; j<n; ++j)
    {
        cout << " ";
        if ( rv[j] )  cout << rv[j];
        else          cout << '.';
        bct += ( rv[j]!= 0 );
    }

//    cout << "   ";
//    for (ulong j=0; j<n; ++j)
//    {
//        cout << " ";
//        if ( dlt[j] )  cout << dlt[j];
//        else          cout << '.';
//    }

    cout << endl;
}
// -------------------------


void visit()
{
#ifndef TIMING
    jjassert(  check_gray() );
    print();
#endif
}
// -------------------------


void no111_rec(long p1, long p2, bool z)
{
    if ( p1>p2 )
    {
        ++ct;  // count objects
        visit();
        return;
    }

#define S1(a)  rv[p1+0]=a
#define S2(a, b)  S1(a); rv[p1+1]=b;
#define S3(a, b, c)  S2(a, b); rv[p1+2]=c;
    long d = p2 - p1;
    if ( z )  // no 111 alt-gray
    {
        if ( d >= 0 )  { S2(1, 0);         no111_rec(p1+2, p2, z); }
        if ( d >= 1 )  { S3(1, 1, 0);      no111_rec(p1+3, p2, !z); }
        if ( d >= 0 )  { S1(0);            no111_rec(p1+1, p2, z); }
    }
    else
    {
        if ( d >= 0 )  { S1(0);            no111_rec(p1+1, p2,  z); }
        if ( d >= 1 )  { S3(1, 1, 0);      no111_rec(p1+3, p2, !z); }
        if ( d >= 0 )  { S2(1, 0);         no111_rec(p1+2, p2,  z); }
    }
#undef S1
#undef S2
#undef S3
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 7;
    NXARG(n, "Length of words");
    rv = new long[n+15];
    rvo = new long[n+15];
    dlt = new long[n+15];

    for (ulong k=0; k<=n; ++k)  rv[k] = 0;
    bool z0 = 0;
//    NXARG(z0, "whether to reverse order");

    xct = 0;
    ct = 0;
    no111_rec(0, (long)n-1, z0);

    cout << "  n=" << n;
    cout << " ct=" << ct;
    cout << endl;

    delete [] rv;
    delete [] rvo;
    delete [] dlt;

    return 0;
}
// -------------------------


/*
Timing:
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/no111-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/no111-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

