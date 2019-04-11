
// demo-is-self-contained

#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"

#include "nextarg.h"


//% Gray code for strings with no two consecutive nonzero digits.
//% These are non-adjacent forms (NAF).

// Cf. comb/mixedradix-naf-gray-demo.cc for an iterative version.

//#define TIMING  // uncomment to disable printing


ulong n;     // length of strings
ulong *rv;   // digits of strings
ulong mr;    // max digit

ulong *rvo;  // last string

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

    print_vec("    ", rv, n, true);
//    cout << "  ";
//    for (ulong j=0; j<n; ++j)
//    {
//        if ( rv[j] )  cout << rv[j];
//        else          cout << '.';
//    }

    ulong tct = chk_gray();

    if ( tct>1 )  cout << "  X " << tct;
    cout << endl;
#endif  // TIMING
}
// -------------------------


void ntnz_rec(ulong d, bool z)
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
            rv[d]=0;  ntnz_rec(d+1, 1);
            for (ulong t=1; t<=mr; ++t)
            {
                rv[d]=t;  rv[d+1]=0;  ntnz_rec(d+2, t&1);
            }
        }
        else
        {
            for (ulong t=mr; t>0; --t)
            {
                rv[d]=t;  rv[d+1]=0;  ntnz_rec(d+2, !(t&1));
            }
            rv[d]=0;  ntnz_rec(d+1, 0);
        }
    }
}
// -------------------------

int
main(int argc, char **argv)
{
    n = 5;
    NXARG(n, "Length of strings");
    mr = 2;
    NXARG(mr, "max. digit");
    bool rq = 0;
    NXARG(rq, "Whether to reverse order");

    rv = new ulong[n+1];
    rvo = new ulong[n+1];
    ct = 0;
    ngct = 0;
    ntnz_rec(0, rq);

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

 time ./bin 40 1
arg 1: 40 == n  [Length of strings]  default=5
arg 2: 1 == mr  [max. digit]  default=2
arg 3: 0 == rq  [Whether to reverse order]  default=0
ct=267914296
./bin 40 1  3.64s user 0.02s system 99% cpu 3.684 total
 ==> 267914296/3.64 == 73,602,828 per second

 time ./bin 21 4
arg 1: 21 == n  [Length of strings]  default=5
arg 2: 4 == mr  [max. digit]  default=2
arg 3: 0 == rq  [Whether to reverse order]  default=0
ct=603054709
./bin 21 4  5.37s user 0.03s system 99% cpu 5.411 total
 ==> 603054709/5.37 == 112,300,690 per second
*/

/*
OEIS sequences:

r=1; echo $(for n in $(seq 1 23); do ./bin $n $r | g ct= ; done | cut -d= -f2)

r=1:
2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765 10946 17711 28657 46368
A000045 Fibonacci numbers: F(n) = F(n-1) + F(n-2), F(0) = 0, F(1) = 1,

r=2:
3 5 11 21 43 85 171 341 683 1365 2731 5461 10923 21845 43691 87381 174763 349525 699051
A001045 Jacobsthal sequence: a(n) = a(n-1) + 2a(n-2).

r=3:
4 7 19 40 97 217 508 1159 2683 6160 14209 32689 75316 173383 399331 919480 2117473
A006130 a(n) = a(n-1) + 3a(n-2), a(0) = a(1) = 1.


r=4:
5 9 29 65 181 441 1165 2929 7589 19305 49661 126881 325525 833049 2135149 5467345
A006131 a(n) = a(n-1) + 4*a(n-2)

r=5:
6 11 41 96 301 781 2286 6191 17621 48576 136681 379561 1062966 2960771 8275601 23079456
A015440 Generalized Fibonacci numbers. [a(n-1) + 5*a(n-2)]

r=6: A015441
r=7: A015442
r=8: A015443
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ntnz-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ntnz-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

