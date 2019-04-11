
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"

#include "nextarg.h"


//% Near Gray code for sparse signed binary representations (nonadjacent form, NAF)
//% of the positive numbers.  Recursive CAT algorithm.

ulong n;  // length of strings
int *rv;  // string
int *rvo;  // last string

ulong ct;   // count objects
ulong ngct;  // count non-Gray transitions
ulong xct;   // count additional (wrt. Gray) transitions

//#define TIMING  // uncomment to disable printing

void visit()
{
    ++ct;  // count objects

#ifndef TIMING
//    ulong dct = 0;  // count nonzero digits
    cout << setw(4) << ct << ":";
    cout << "   ";
    long val = 0, dig = 1L<<(n-1);
    for (ulong j=0; j<n; ++j)
    {
        int x = rv[j];
        cout << " " << (0==x ? '.' : (x>0?'P':'M'));
        val += (x * dig);
        dig >>= 1;
//        dct += (x!=0);
    }

    cout << "    " << setw(3) << val;
//    cout << "   % " << dct;
//#endif

    ulong tct = 0;
    if ( ct>1 )  // check whether Gray transition
    {
        for (ulong j=0; j<n; ++j)  tct += (rv[j]!=rvo[j]);
        if ( tct!=1 )
        {
            ++ngct;
            xct += (tct-1);
        }
//#ifndef TIMING
        if ( tct!=1 )  cout << "  <<+ " << tct-1;
//#endif
    }
    for (ulong j=0; j<n; ++j)  rvo[j]=rv[j];
//#ifndef TIMING
    cout << endl;
#endif
}
// -------------------------


void sb_rec(ulong d, bool z)
{
    if ( d>=n )  visit();
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


void pos_AAA(ulong d, bool z);
void pos_BBB(ulong d, bool z);

void pos_AAA(ulong d, bool z)
{
    if ( d>=n )  visit();
    else
    {
        if ( 0==z )
        {
            rv[d]=+1;  rv[d+1]=0;  sb_rec(d+2, 0);  // 0
            rv[d]=0;  pos_AAA(d+1, 1);  // 1
        }
        else
        {
            rv[d]=0;  pos_BBB(d+1, 0);  // 0
            rv[d]=+1;  rv[d+1]=0;  sb_rec(d+2, 1);  // 1
        }
    }
}
// -------------------------


void pos_BBB(ulong d, bool z)
{
    if ( d>=n )  visit();
    else
    {
        if ( 0==z )
        {
            rv[d]=+1;  rv[d+1]=0;  sb_rec(d+2, 1);  // 1
            rv[d]=0;  pos_BBB(d+1, 1);  // 1
        }
        else
        {
            rv[d]=0;  pos_AAA(d+1, 0);  // 0
            rv[d]=+1;  rv[d+1]=0;  sb_rec(d+2, 0);  // 0
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 7;
    NXARG(n, "Length of sparse signed binary words");
    bool rq = 0;
    NXARG(rq, "Whether to reverse order");
    bool aq = 1;
    NXARG(aq, "Whether pos_AAA(), else pos_BBB()");

    rv = new int[n+1];
    rvo = new int[n+1];
    ct = 0;
    ngct = 0;
    xct = 0;

    if ( aq )  pos_AAA(0, rq);
    else       pos_BBB(0, rq);

    cout << " ct=" << ct << endl;
#ifndef TIMING
    cout << n << ":  ngct = " << ngct << "  xct = " << xct << endl;
#endif

    delete [] rv;
    delete [] rvo;

    return 0;
}
// -------------------------

/*
Timing:
 time ./bin 30 0 1
arg 1: 30 == n  [Length of sparse signed binary words]  default=7
arg 2: 0 == rq  [Whether to reverse order]  default=0
arg 3: 1 == aq  [Whether pos_AAA(), else pos_BBB()]  default=1
ct=715827883
./bin 30 0 1  7.06s user 0.00s system 99% cpu 7.083 total
 ==> 715827883/7.06 == 101,392,051 per second

BENCHARGS=30 0 1

*/


/*
    pos_AAA(0, 0):

% for n in $(seq 1 30); do ./bin $n  | g xct ; done
1:  ngct = 0  xct = 0
2:  ngct = 0  xct = 0
3:  ngct = 0  xct = 0
4:  ngct = 0  xct = 0
5:  ngct = 1  xct = 1
6:  ngct = 2  xct = 3
7:  ngct = 2  xct = 4
8:  ngct = 2  xct = 4
9:  ngct = 3  xct = 5
10:  ngct = 4  xct = 7
11:  ngct = 4  xct = 8
12:  ngct = 4  xct = 8
13:  ngct = 5  xct = 9
14:  ngct = 6  xct = 11
15:  ngct = 6  xct = 12
16:  ngct = 6  xct = 12
17:  ngct = 7  xct = 13
18:  ngct = 8  xct = 15
19:  ngct = 8  xct = 16
20:  ngct = 8  xct = 16
21:  ngct = 9  xct = 17
22:  ngct = 10  xct = 19
23:  ngct = 10  xct = 20
24:  ngct = 10  xct = 20
25:  ngct = 11  xct = 21
26:  ngct = 12  xct = 23
27:  ngct = 12  xct = 24
28:  ngct = 12  xct = 24
29:  ngct = 13  xct = 25
30:  ngct = 14  xct = 27

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/naf-pos-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/naf-pos-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:
