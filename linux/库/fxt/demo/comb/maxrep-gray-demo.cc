
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray code for generalized Fibonacci words, recursive CAT algorithm

//#define TIMING  // define to disable printing


ulong n;    // number of bits in words
ulong *rv;  // bits of the word
ulong *rvo;  // bits of the last word

ulong ct;   // count objects
ulong rct;  // count recursions (==work)

ulong mr;    // maximum number of consecutive ones
bool zq;    // order: 0==>Lex  1==>Gray


void visit()
{
#ifndef TIMING
    cout << setw(4) << ct << ":";
    cout << "   ";
    for (ulong j=0; j<n; ++j)  cout << " " << (rv[j] ? '1' : '.');

//    cout << "   ";
//    ulong ig = 0;
//    for (ulong j=0; j<n; ++j)  { ig^=rv[j]; cout << " " << (ig ? '1' : '.'); }

    cout << endl;
    if ( ct>1 )
    {
        ulong xct = 0;
        for (ulong j=0; j<n; ++j)   xct += (rvo[j] != rv[j]);
        jjassert( xct==1 );
    }
    for (ulong j=0; j<n; ++j)   rvo[j] = rv[j];
#endif
}
// -------------------------


void maxrep_rec(ulong d, bool z)
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

        ulong km = mr;
        if ( d+km > n )  km = n - d;

        if ( z )
        {
            // words: 0, 10, 110, 1110, ...
            for (ulong k=0; k<=km; ++k)
            {
//                jjassert ( d+k <= n );
                rv[d+k] = 0;
                maxrep_rec(d+1+k, z);
                rv[d+k] = 1;
            }
        }
        else
        {
            // words: ... 1110, 110, 10, 0
            for (ulong k=0; k<km; ++k)  rv[d+k] = 1;
            for (ulong k=km; (long)k>=0; --k)  // jjcast
            {
//                jjassert ( d+k <= n );
                rv[d+k] = 0;
                maxrep_rec(d+1+k, z);
            }
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 5;
    NXARG(n, "Length of words");
    mr = 2;
    NXARG(mr, "Max number of consecutive ones");
    rv = new ulong[n+1];
    rvo = new ulong[n+1];

    zq = 1;
    NXARG(zq, " 0==>Lex order  1==>Gray code");
    bool rq = 0;
    NXARG(rq, "Whether to reverse order");
    rq = !rq;

    ct = 0;
    rct = 0;
    maxrep_rec(0, rq);

    cout << "ct=" << ct << endl;
//    cout << "rct=" << rct << endl;  // rct == ct-1
//    cout << "work/object=" << (double)rct/(double)ct << endl;  // ratio <= 1

    delete [] rv;
    delete [] rvo;

    return 0;
}
// -------------------------

// OEIS sequences:
// mr = 1:
// A000045 ,0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,
// A000045 Fibonacci numbers: F(n) = F(n-1) + F(n-2)

// mr = 2:
// A000073 ,0,0,1,1,2,4,7,13,24,44,81,149,274,504,927,1705,3136,5768,10609,19513,35890,
// A000073 Tribonacci numbers: a(n) = a(n-1) + a(n-2) + a(n-3).

// mr = 3:
// A000078 ,0,0,0,1,1,2,4,8,15,29,56,108,208,401,773,1490,2872,5536,10671,20569,39648,
// A000078 Tetranacci numbers: a(n) = a(n-1) + a(n-2) + a(n-3) +a(n-4).

// mr = 4:
// A001591 ,0,0,0,0,1,1,2,4,8,16,31,61,120,236,464,912,1793,3525,6930,13624,26784,
// A001591 Pentanacci numbers: a(n+1)=a(n)+...+a(n-4).

// mr = 5:
// A001592 ,0,0,0,0,0,1,1,2,4,8,16,32,63,125,248,492,976,1936,3840,7617,15109,29970,
// A001592 Hexanacci numbers: a(n+1)=a(n)+...+a(n-5).

/*
Timing:
 time ./bin 40 1 1
arg 1: 40 == n  [Length of words]  default=5
arg 2: 1 == mr  [Max number of consecutive ones]  default=2
arg 3: 1 == zq  [ 0==>Lex order  1==>Gray code]  default=1
arg 4: 0 == rq  [Whether to reverse order]  default=0
ct=267914296
./bin 40 1 1  5.48s user 0.02s system 99% cpu 5.507 total
 ==> 267914296/5.48 == 48,889,470 per second

 time ./bin 30 3 1
arg 1: 30 == n  [Length of words]  default=5
arg 2: 3 == mr  [Max number of consecutive ones]  default=2
arg 3: 1 == zq  [ 0==>Lex order  1==>Gray code]  default=1
arg 4: 0 == rq  [Whether to reverse order]  default=0
ct=387559437
./bin 30 3 1  6.42s user 0.04s system 99% cpu 6.468 total
 ==> 387559437/6.42 == 60,367,513 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/maxrep-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/maxrep-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

