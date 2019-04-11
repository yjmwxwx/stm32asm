
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray code for r-ary words where digit x is followed by x or more zeros.

//#define TIMING  // define to disable printing

#define CHK_GRAY  // define to check minimal-change (Gray) property


ulong n;    // number of digits in words
ulong *rv;  // digits of the word
ulong mr;   // radix== mr+1

ulong ct;   // count objects


ulong *rvo;  // last string
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
    for (ulong j=0; j<n; ++j)
    {
        cout << " ";
        if ( rv[j] )  cout << rv[j];
        else          cout << '.';
    }

#ifdef CHK_GRAY
    ulong tct = chk_gray();
#else
#warning "no checking for Gray-ness"
    ulong tct = 0;
#endif

    if ( tct>1 )  cout << "  X " << tct;

    cout << endl;
#endif  // TIMING
}
// -------------------------


void gexz_rec(ulong d, bool z)
{
    if ( d>=n )
    {
        ++ct;  // count objects
        visit();
    }
    else
    {
        if ( z )
        {
            // words 0, 10, 200, 3000, 40000, ...
            ulong k = 0;
            do
            {
                rv[d]=k;
                for (ulong j=1; j<=k; ++j)   rv[d+j] = 0;
                gexz_rec(d+k+1, !z);
            }
            while ( ++k <= mr );
        }
        else
        {
            // words ..., 40000, 3000, 200, 10, 0
            ulong k = mr + 1;
            do
            {
                --k;
                rv[d]=k;
                for (ulong j=1; j<=k; ++j)   rv[d+j] = 0;
                gexz_rec(d+k+1, !z);
            }
            while ( k != 0 );
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 5;
    NXARG(n, "Length of words");
    mr = 3;
    NXARG(mr, "max digit (radix = mr+1)");
    rv = new ulong[n+mr+1];
    rvo = new ulong[n+mr+1];

    bool rq = 0;
//    NXARG(rq, "Whether to reverse order");
    rq = !rq;

    ct = 0;
    gexz_rec(0, rq);

    cout << "ct=" << ct << endl;
    if ( ngct )  cout << " ***** ngct=" << ngct << endl;
    jjassert( 0==ngct );

    delete [] rv;
    delete [] rvo;

    return 0;
}
// -------------------------

/*

for n in $(seq 1 11); do for r in $(seq 1 11); do ./bin $n $r || break 2 ; done; done

r=2; oeis $(for n in $(seq 0 13); do ./bin $n $r  | g ct | cut -d= -f2 ; done)

// mr = 1:
 A000045 ,0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,
 A000045 Fibonacci numbers: F(n) = F(n-1) + F(n-2), F(0) = 0, F(1) = 1

// mr = 2:
A000213 ,1,1,1,3,5,9,17,31,57,105,193,355,653,1201,2209,4063,7473,13745,25281,46499,
A000213 Tribonacci numbers: a(n) = a(n-1) + a(n-2) + a(n-3).

// mr = 3:
A000288 ,1,1,1,1,4,7,13,25,49,94,181,349,673,1297,2500,4819,9289,17905,34513,66526,
A000288 Tetranacci numbers: a(n) = a(n-1) + a(n-2) + a(n-3) +a(n-4).

// mr = 4:
A000322 ,1,1,1,1,1,5,9,17,33,65,129,253,497,977,1921,3777,7425,14597,28697,56417,
A000322 Pentanacci numbers.

// mr = 5:
A000383 ,1,1,1,1,1,1,6,11,21,41,81,161,321,636,1261,2501,4961,9841,19521,38721,76806,
A000383 Hexanacci numbers.

// mr = 6:
A060455 ,1,1,1,1,1,1,1,7,13,25,49,97,193,385,769,1531,3049,6073,12097,24097,48001,95617,
A060455 7th order Fibonacci numbers.

// mr = 7:
A123526 ,1,1,1,1,1,1,1,1,8,15,29,57,113,225,449,897,1793,3578,7141,14253,28449,56785,
A123526 Octanacci numbers.

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/gexz-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/gexz-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

