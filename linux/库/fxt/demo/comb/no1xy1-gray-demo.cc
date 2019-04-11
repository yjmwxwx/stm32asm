
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray code for binary words with no substring 1xy1, recursive CAT algorithm

//#define ALT_REC  // Gray code for (neither no1x1 nor no1xy1)


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


void Y_rec(long p1, long p2, bool z)
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
#define S4(a, b, c, d)  S3(a, b, c); rv[p1+3]=d;
#define S5(a, b, c, d, e)  S4(a, b, c, d); rv[p1+4]=e;
#define S6(a, b, c, d, e, f)  S5(a, b, c, d, e); rv[p1+5]=f;

    long d = p2 - p1;
    if ( z )
    {
        if ( d >= 0 )  { S4(1, 0, 0, 0);      Y_rec(p1+4, p2,  z); }   // 1 0 0 0
#ifndef ALT_REC
        if ( d >= 2 )  { S6(1, 0, 1, 0, 0, 0);  Y_rec(p1+6, p2, !z); }   // 1 0 1 0 0 0
        if ( d >= 2 )  { S6(1, 1, 1, 0, 0, 0);  Y_rec(p1+6, p2,  z); }   // 1 1 1 0 0 0
#endif
        if ( d >= 1 )  { S5(1, 1, 0, 0, 0);    Y_rec(p1+5, p2, !z); }   // 1 1 0 0 0
        if ( d >= 0 )  { S1(0);            Y_rec(p1+1, p2,  z); }   // 0
    }
    else
    {
        if ( d >= 0 )  { S1(0);            Y_rec(p1+1, p2,  z); }   // 0
        if ( d >= 1 )  { S5(1, 1, 0, 0, 0);    Y_rec(p1+5, p2, !z); }   // 1 1 0 0 0
#ifndef ALT_REC
        if ( d >= 2 )  { S6(1, 1, 1, 0, 0, 0);  Y_rec(p1+6, p2,  z); }   // 1 1 1 0 0 0
        if ( d >= 2 )  { S6(1, 0, 1, 0, 0, 0);  Y_rec(p1+6, p2, !z); }   // 1 0 1 0 0 0
#endif
        if ( d >= 0 )  { S4(1, 0, 0, 0);      Y_rec(p1+4, p2,  z); }   // 1 0 0 0
    }
#undef S1
#undef S2
#undef S3
#undef S4
#undef S5
#undef S6
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 7;
    NXARG(n, "Length of words");
    rv = new long[n+5];
    rvo = new long[n];
    dlt = new long[n];

    for (ulong k=0; k<n; ++k)  rv[k] = 0;
    bool z0 = 0;
//    NXARG(z0, "whether to reverse order");

    xct = 0;
    ct = 0;
    Y_rec(0, (long)(n-1), z0);  // jjcast

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

 time ./bin 40
arg 1: 40 == n  [Length of words]  default=7
  n=40  ct=212091637
./bin 40  2.62s user 0.02s system 99% cpu 2.634 total
 ==> 212091637/2.62 == 80,951,006 per second

with ALT_REC defined:
 time ./bin 46
arg 1: 46 == n  [Length of words]  default=7
  n=46  ct=181556353
./bin 46  2.13s user 0.03s system 99% cpu 2.154 total
 ==> 181556353/2.13 == 85,237,724 per second

*/

/*
% echo $(for n in $(seq 0 21); do ./bin $n | g ct | cut -d= -f3 ; done)
1 2 4 8 12 17 25 41 69 114 180 280 440 705 1137 1825 2905 4610 7332 11704 18708 29873
OGF == (2*x^5 + 3*x^4 + 4*x^3 + 2*x^2 + x + 1)/(-2*x^6 - x^5 - x^4 - x + 1)

ALT_REC: no1x1 and no1xy1:
1 2 4 6 8 11 17 27 41 60 88 132 200 301 449 669 1001 1502
 == OEIS sequence A079972

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/no1xy1-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/no1xy1-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

