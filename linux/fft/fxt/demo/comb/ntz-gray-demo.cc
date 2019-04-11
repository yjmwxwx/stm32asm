
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray code for words without two consecutive zeros, recursive CAT algorithm

//#define TIMING  // define to disable printing

#define CHK_GRAY  // define to check minimal-change (Gray code) property


ulong n;    // number of digits in words
ulong *rv;  // digits of the word (radix r+1)

ulong ct;   // count objects

ulong r;     // Forbidden substrings are [r, x] where x!=0

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


void ntz_rec(ulong d, bool z)
{
    if ( d>=n )
    {
        ++ct;  // count objects
        visit();
    }
    else
    {
        bool w = 0;  // r-parity:  w depends on z ...
        if ( r&1 )  w = !z;   // ... if r odd

        if ( z )
        {
            // words 0X:
            rv[d] = 0;
            if ( d+2<=n )
            {
                for (ulong k=1; k<=r; ++k, w=!w)  { rv[d+1]=k;  ntz_rec(d+2, w); }
            }
            else
            {
                ntz_rec(d+1, w);
                w = !w;
            }

            w ^= (r&1);  //  r-parity:  change direction if r odd

            // words X:
            for (ulong k=1; k<=r; ++k, w=!w)  { rv[d]=k;  ntz_rec(d+1, w); }
        }
        else
        {
            // words X:
            for (ulong k=r; k>=1; --k, w=!w)  { rv[d]=k;  ntz_rec(d+1, w); }

            w ^= (r&1);  //  r-parity:  change direction if r odd

            // words 0X:
            rv[d] = 0;
            if ( d+2<=n )
            {
                for (ulong k=r; k>=1; --k, w=!w)  { rv[d+1]=k;  ntz_rec(d+2, w); }
            }
            else
            {
                ntz_rec(d+1, w);
                w = !w;
            }
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 3;
    NXARG(n, "Length of words");
    r = 3;
    NXARG(r, "Forbidden substrings are [r, x] where x!=0");
    rv = new ulong[n+1];
    rvo = new ulong[n+1];

    bool rq = 0;
    NXARG(rq, "Whether to reverse order");
    rq = !rq;

    ct = 0;
    ntz_rec(0, rq);

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

// r = 1:
 A000045 ,0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,
 A000045 Fibonacci numbers: F(n) = F(n-1) + F(n-2), F(0) = 0, F(1) = 1

// r = 2:
 A028859 ,1,3,8,22,60,164,448,1224,3344,9136,24960,68192,186304,508992,1390592,
 A028859 a(n+2) = 2 a(n+1) + 2 a(n).

// r = 3:
 A125145 ,1,4,15,57,216,819,3105,11772,44631,169209,641520,2432187,9221121,34959924,
 A125145 a(n) = 3a(n-1) + 3a(n-2). a(0) = 1, a(1) = 4.

// r = 4:
 A086347 ,1,5,24,116,560,2704,13056,63040,304384,1469696,7096320,34264064,165441536,
 A086347 On a 3 X 3 board, number of n-move routes of chess king ending at a given side cell.

// r = 5:
 1 6 35 205 1200 7025 41125 240750 1409375 8250625 48300000

// r = 6:
 1 7 48 330 2268 15588 107136 736344 5060880 34783344 239065344

// r = 7:
 1 8 63 497 3920 30919 243873 1923544 15171919

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ntz-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ntz-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

