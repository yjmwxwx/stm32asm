
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray code for binary words with no substring 1x1, recursive CAT algorithm

//#define TIMING  // define to disable printing


ulong n;    // number of bits in words
ulong *rv;  // bits of the word
ulong *rvo;  // bits of previous word

ulong ct;   // count objects

ulong xct;   // count transitions

void visit()
{
    if ( ct>1 )
    {
        xct = 0;
        for (ulong j=0; j<n; ++j)  xct += (rvo[j] != rv[j]);
        --xct;
    }
    for (ulong j=0; j<n; ++j)  rvo[j] = rv[j];

#ifndef TIMING
    cout << setw(4) << ct << ":";
    cout << "   ";
    for (ulong j=0; j<n; ++j)  cout << " " << (rv[j] ? '1' : '.');
//    cout << setw(3) << xct;
    cout << endl;
#endif

    jjassert( 0==xct );
}
// -------------------------


void
no1x1_rec(ulong d, bool z)
{
    if ( d>=n )
    {
        if ( d<=n+2 )
        {
            ++ct;  // count objects
            visit();
        }
    }
    else
    {
        if ( z )
        {
            rv[d]=1;  rv[d+1]=0;  rv[d+2]=0;  no1x1_rec(d+3, z);
            rv[d]=1;  rv[d+1]=1;  rv[d+2]=0;  rv[d+3]=0;  no1x1_rec(d+4, !z);
            rv[d]=0;  no1x1_rec(d+1, z);
        }
        else
        {
            rv[d]=0;  no1x1_rec(d+1, z);
            rv[d]=1;  rv[d+1]=1;  rv[d+2]=0;  rv[d+3]=0;  no1x1_rec(d+4, !z);
            rv[d]=1;  rv[d+1]=0;  rv[d+2]=0;  no1x1_rec(d+3, z);
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


    xct = 0;
    ct = 0;
    no1x1_rec(0, rq);

    cout << "ct=" << ct << endl;

    delete [] rv;
    delete [] rvo;

    return 0;
}
// -------------------------

/*
// 1 2 3 4  5  6  7  8   9  10
// 2 4 6 9 15 25 40 64 104 169 273 441 714 1156 1870 3025 4895
// OEIS sequence A006498 ,1,1,1,2,4,6,9,15,25,40,64,104,169,273,441
// A006498 a(n) = a(n-1)+a(n-3)+a(n-4).
// == A074677 a(n)=Sum((-1)^(i+Floor(n/2))F(2i+e),(i=0,..,Floor(n/2))), where F(n) = Fib(n)

no1x1 and no1xy1:
% echo $(for n in $(seq 0 17); do ./bin $n | grep -vE '1 .? .? 1' | grep ':  ' | wc -l; done)
1 2 4 6 8 11 17 27 41 60 88 132 200 301 449 669 1001 1502
 == A079972
*/

/*
Timing:

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/no1x1-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/no1x1-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

