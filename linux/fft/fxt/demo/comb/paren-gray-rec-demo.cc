
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"
#include "jjassert.h"


//% Gray code for paren strings via restricted growth strings (RGS), recursive algorithm.

//#define TIMING  // uncomment to disable printing


ulong n;    // Number of paren pairs
ulong *rv;  // restricted growth strings

ulong ct;   // count combinations
ulong rct;  // count recursions (==work)

char str[64];
char stro[64];

void make_str()
{
    for (ulong k=0; k<2*n; ++k)  str[k] = '.';
    for (ulong k=0, j=0;  k<n;  ++k, j+=2)  str[ j-rv[k] ] = '1';
    str[2*n] = 0;
}
// -------------------------

void visit()
{
    cout << setw(4) << ct << ":";
    cout << "  ";
    for (ulong j=0; j<n; ++j)  cout << " " << rv[j];
    cout << "    ";
    for (ulong j=0; j<=2*n; ++j)  stro[j] = str[j];
    make_str();
    cout << str;
    if ( ct>1 )
    {
        ulong xct = 0;
        for (ulong j=0; j<2*n; ++j)  xct += (stro[j] != str[j]);
        xct -= 2;
        if ( xct )  cout << "  << " << xct;
        jjassert( xct==0 );
    }
    cout << endl;
}
// -------------------------


void next_rec(ulong d, bool z)
{
    if ( d==n )
    {
        ++ct;  // count objects
#ifndef TIMING
        visit();
#endif
    }
    else
    {
        ++rct;  // measure computational work

        const ulong rv1 = rv[d-1];  // left neighbor
        if ( 0==z )  // forward
        {
            for (ulong x=0; x<=rv1+1; ++x)
            {
                rv[d] = x;
                next_rec(d+1, (x&1));
            }
        }
        else  // backward
        {
            for (ulong x=rv1+1; (long)x>=0; --x)
            {
                rv[d] = x;
                next_rec(d+1, !(x&1));
            }
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 5;
    NXARG(n, "Number of paren pairs");

    rv = new ulong[n+1];
    ++rv;
    rv[-1] = -1UL;

    ct = 0;
    rct = 0;
    next_rec(0, 0);

    cout << " ct=" << ct << endl;
//    cout << "rct=" << rct << endl;
    cout << "work/object=" << (double)rct/(double)ct << endl;  // <=1, and <0.5 for n>=6

    --rv;
    delete [] rv;

    return 0;
}
// -------------------------


/*
Timing:

  time ./bin 18
arg 1: 18 == n  [Number of paren pairs]  default=5
 ct=477638700
work/object=0.373515
./bin 18  5.89s user 0.02s system 99% cpu 5.912 total
 ==> 477638700/5.89 == 81,093,157 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

  time ./bin 18
arg 1: 18 == n  [Number of paren pairs]  default=5
 ct=477638700
work/object=0.373515
./bin 18  4.37s user 0.00s system 99% cpu 4.373 total
 ==> 477638700/4.37 == 109,299,473 per second
*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/paren-gray-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/paren-gray-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:
