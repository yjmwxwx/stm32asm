
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray code for Fibonacci words, recursive CAT algorithm

//#define TIMING  // define to disable printing


ulong n;    // number of bits in words
ulong *rv;  // bits of the word

ulong ct;   // count objects
ulong rct;  // count recursions (==work)

bool zq;    // order: 0==>Lex  1==>Gray


void visit()
{
#ifndef TIMING
    cout << setw(4) << ct << ":";
    cout << "   ";
    for (ulong j=0; j<n; ++j)  cout << "" << (rv[j] ? '1' : '.');
    cout << endl;
#endif
}
// -------------------------


void fib_rec(ulong d, bool z)
{
    if ( d>=n )
    {
        ++ct;  // count objects
        visit();
    }
    else
    {
        ++rct;  // measure computational work
        z ^= zq;  // change direction for Gray code
#if 1
        if ( z )
        {
            rv[d]=0;  fib_rec(d+1, z);
            rv[d]=1;  rv[d+1]=0;  fib_rec(d+2, z);
        }
        else
        {
            rv[d]=1;  rv[d+1]=0;  fib_rec(d+2, z);
            rv[d]=0;  fib_rec(d+1, z);
        }
#else
        rv[d]=!z;  rv[d+1]=z;  fib_rec(d+1+!z, z);
        rv[d]=z;  rv[d+1]=!z;  fib_rec(d+1+z, z);
#endif
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 8;
    NXARG(n, "Length of Fibonacci words");
    rv = new ulong[n+1];  // incl. sentinel rv[n]

    zq = 1;
    NXARG(zq, " 0==>Lex order  1==>Gray code");
    bool rq = 0;
    NXARG(rq, "Whether to reverse order");

    ct = 0;
    rct = 0;
    fib_rec(0, rq);

    cout << " ct=" << ct << endl;
//    cout << " rct=" << rct << endl;  // rct == ct-1
    cout << "work/object=" << (double)rct/(double)ct << endl;  // ratio <= 1

    delete [] rv;

    return 0;
}
// -------------------------

/*
Timing:

time ./bin 40
arg 1: 40 == n  [Length of Fibonacci words]  default=7
arg 2: 1 == zq  [ 0==>Lex order  1==>Gray code]  default=1
arg 3: 0 == rq  [Whether to reverse order]  default=0
ct=267914296
work/object=1
./bin 40  3.82s user 0.00s system 99% cpu 3.822 total
 ==> 267914296/3.82 == 70,134,632 per second

time ./bin 42
arg 1: 42 == n  [Length of Fibonacci words]  default=7
arg 2: 1 == zq  [ 0==>Lex order  1==>Gray code]  default=1
arg 3: 0 == rq  [Whether to reverse order]  default=0
ct=701408733
work/object=1
./bin 42  10.01s user 0.00s system 99% cpu 10.023 total
 ==> 701408733/10.01 == 70,070,802 per second

BENCHARGS=42

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/fibgray-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/fibgray-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

