
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray code for Pell words, recursive CAT algorithm


//#define TIMING  // define to disable printing

ulong n;    // number of digits in words
ulong *rv;  // digits of the word

ulong ct;   // count objects
ulong rct;  // count recursions (==work)

bool zq;    // order: 0==>Lex,  1==>Gray


void visit()
{
#ifndef TIMING
    cout << setw(4) << ct << ":";
    cout << "   ";
    for (ulong j=0; j<n; ++j)
    {
        cout << " ";
        if ( 0==rv[j] )   cout << '.';
        else   cout << rv[j];
    }
    cout << endl;
#endif
}
// -------------------------


void pell_rec(ulong d, bool z)
{
    if ( d>=n )
    {
        ++ct;  // count objects
        visit();
    }
    else
    {
        ++rct;  // measure computational work
        if ( 0==z )
        {
            rv[d]=0;  pell_rec(d+1, z);
            rv[d]=1;  pell_rec(d+1, zq^z);
            rv[d]=2;  rv[d+1]=0;  pell_rec(d+2, z);
        }
        else
        {
            rv[d]=2;  rv[d+1]=0;  pell_rec(d+2, z);
            rv[d]=1;  pell_rec(d+1, zq^z);
            rv[d]=0;  pell_rec(d+1, z);
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 4;
    NXARG(n, "Length of words");
    rv = new ulong[n+2];
    zq = 1;
    NXARG(zq, " 0==>Lex order  1==>Gray code");
    bool rq = 0;
    NXARG(rq, "Whether to reverse order");

    ct = 0;
    rct = 0;
    pell_rec(0, rq);

    cout << "ct=" << ct << endl;
//    cout << "rct=" << rct << endl;
    cout << "work/object=" << (double)rct/(double)ct << endl;  // ratio <= 0.5

    delete [] rv;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 23 1
ct=768398401
work/object=0.5
./bin 23  6.94s user 0.03s system 99% cpu 6.971 total
 ==> 768398401/6.94 == 110,720,230 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 23 1
ct=768398401
work/object=0.5
./bin 23 1  3.40s user 0.00s system 99% cpu 3.402 total
 ==> 768398401/3.40 == 225,999,529 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/pellgray-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/pellgray-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

