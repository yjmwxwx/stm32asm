
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"

#include "nextarg.h"


//% Gray code for sparse signed binary representation (nonadjacent form, NAF).
//% Recursive CAT algorithm.


//#define TIMING  // uncomment to disable printing

ulong n;   // number of digits of the string
int *rv;   // the string
int *rvo;  // last string

ulong ct;    // count objects
ulong ngct;  // count non-Gray transitions

ulong chk_gray()
{
    ulong tct = 0;
    if ( ct>1 )  // check whether Gray transition
    {
        for (ulong j=0; j<n; ++j)  tct += (rv[j]!=rvo[j]);
        if ( tct!=1 )
        {
            ++ngct;
        }
    }
    for (ulong j=0; j<n; ++j)  rvo[j] = rv[j];
    return  tct;
}
// -------------------------

void visit()
{
#ifndef TIMING
    cout << setw(4) << ct << ":";
    cout << "   ";
    long val = 0, dig = 1L<<(n-1);
    for (ulong j=0; j<n; ++j)
    {
        int x = rv[j];
        cout << " " << (0==x ? '.' : (x>0?'P':'M'));
        val += (x * dig);
        dig >>= 1;
    }
    cout << "    " << setw(3) << val;

    ulong tct = chk_gray();

    if ( tct>1 )  cout << "  X " << tct;
    cout << endl;
#endif  // TIMING
}
// -------------------------


void sb_rec(ulong d, bool z)
{
    if ( d>=n )
    {
        ++ct;  // count objects
        visit();
    }
    else
    {
        if ( 0==z )
        {
            rv[d]=0;  sb_rec(d+1, 1);
            rv[d]=-1;  rv[d+1]=0;  sb_rec(d+2, 1);
            rv[d]=+1;  rv[d+1]=0;  sb_rec(d+2, 0);
        }
        else
        {
            rv[d]=+1;  rv[d+1]=0;  sb_rec(d+2, 1);
            rv[d]=-1;  rv[d+1]=0;  sb_rec(d+2, 0);
            rv[d]=0;  sb_rec(d+1, 0);
        }
    }
}
// -------------------------


void sbx_rec(ulong d, bool z, int x)
{
    if ( d>=n )
    {
        ++ct;  // count objects
        visit();
    }
    else
    {
        if ( 0==z )
        {
            rv[d]=0;  sbx_rec(d+1, 1, -x);
            rv[d]=+x;  rv[d+1]=0;  sbx_rec(d+2, 1, x);
            rv[d]=-x;  rv[d+1]=0;  sbx_rec(d+2, 0, x);
        }
        else
        {
            rv[d]=-x;  rv[d+1]=0;  sbx_rec(d+2, 1, x);
            rv[d]=+x;  rv[d+1]=0;  sbx_rec(d+2, 0, x);
            rv[d]=0;  sbx_rec(d+1, 0, -x);
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 5;
    NXARG(n, "Length of sparse signed binary words");
    int x = 0;
    NXARG(x, "x!=0 ==> use alternative order");
    if ( x )  x = (x>0?+1:-1);
    bool rq = 0;
//    NXARG(rq, "Whether to reverse order");

    rv = new int[n+1];
    rvo = new int[n+1];
    ct = 0;
    ngct = 0;
    if ( 0==x ) sb_rec(0, rq);
    else        sbx_rec(0, rq, x);

    cout << "ct=" << ct << endl;
    if ( ngct )
    {
        cout << "# of non-Gray transitions = " << ngct << endl;
        jjassert( 0==ngct );
    }

    delete [] rv;
    delete [] rvo;

    return 0;
}
// -------------------------

/*
Timing:
 time ./bin 29
ct=715827883
work/object=0.5
./bin 29  5.88s user 0.02s system 100% cpu 5.903 total
 ==> 715827883/5.88 == 121,739,435 per second
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/naf-gray-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/naf-gray-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

