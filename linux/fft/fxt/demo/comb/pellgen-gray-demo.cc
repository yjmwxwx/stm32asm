
// demo-is-self-contained

#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray code for generalized Pell words, recursive CAT algorithm


//#define TIMING  // define to disable printing


ulong n;    // number of digits in words
ulong *rv;  // digits of the word (radix r+1)

ulong ct;   // count objects

ulong r;     // Forbidden substrings are [r, x] where x!=0


void visit()
{
#ifndef TIMING
    cout << setw(4) << ct << ":";
//    cout << "   ";
//    for (ulong j=0; j<n; ++j)
//    {
//        cout << " ";
//        if ( rv[j] )  cout << rv[j];
//        else          cout << '.';
//    }
    print_vec("    ", rv, n, true);

    cout << endl;
#endif
}
// -------------------------


void pellgen_rec(ulong d, bool z)
{
    if ( d>=n )
    {
        ++ct;  // count objects
        visit();
    }
    else
    {
        const bool p = r & 1;  // parity of r

        rv[d] = 0;
        if ( z )
        {
            for (ulong k=0; k<r; ++k)
            {
                rv[d] = k;
                pellgen_rec(d+1, z ^ p ^ (k&1));
            }

            { rv[d] = r;  rv[d+1] = 0;  pellgen_rec(d+2, p ^ z); }
        }
        else
        {
            { rv[d] = r;  rv[d+1] = 0;  pellgen_rec(d+2, p ^ z); }

            for (ulong k=r-1; (long)k>=0; --k)  // jjcast
            {
                rv[d] = k;
                pellgen_rec(d+1, z ^ p ^ (k&1));
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
    rv = new ulong[n+4];

    bool rq = 0;
    NXARG(rq, "Whether to reverse order");
    rq = !rq;

    ct = 0;
    pellgen_rec(0, rq);

    cout << "ct=" << ct << endl;

    delete [] rv;

    return 0;
}
// -------------------------

/*
Timing:

% time ./bin 14 4
arg 1: 14 == n  [Length of words]  default=3
arg 2: 4 == r  [Forbidden substrings are [r, x] where x!=0]  default=3
arg 3: 0 == rq  [Whether to reverse order]  default=0
ct=701408733
./bin 14 4  6.84s user 0.04s system 100% cpu 6.874 total
 ==> 701408733/6.84 == 102,545,136 per second

% time ./bin 40 1
arg 1: 40 == n  [Length of words]  default=3
arg 2: 1 == r  [Forbidden substrings are [r, x] where x!=0]  default=3
arg 3: 0 == rq  [Whether to reverse order]  default=0
ct=267914296
./bin 40 1  4.60s user 0.02s system 100% cpu 4.626 total
 ==> 267914296/4.60 == 58,242,238 per second
 */

// OEIS sequences:
// r = 1:
// A000045 ,0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,
// A000045 Fibonacci numbers: F(n) = F(n-1) + F(n-2)

// A001333 ,1,1,3,7,17,41,99,239,577,1393,3363,8119,19601,47321,114243,
// A001333 Numerators of continued fraction convergents to sqrt(2). [a(n) = 2*a(n-1) + a(n-2)]

// r = 3:
// A003688 ,1,4,13,43,142,469,1549,5116,16897,55807,184318,608761,2010601,
// A003688 a(n) = 3*a(n-1) + a(n-2).

// r = 4:
// A015448 ,1,1,5,21,89,377,1597,6765,28657,121393,514229,2178309,
// A015448 Generalized Fibonacci numbers: a(n) = 4*a(n-1) + a(n-2).

// r = 5:
// A015449 ,1,1,6,31,161,836,4341,22541,117046,607771,3155901,16387276,
// A015449 Generalized Fibonacci numbers. [a(n) = 5*a(n-1) + a(n-2)]

// r = 6:
// A015451 ,1,1,7,43,265,1633,10063,62011,382129,2354785,14510839
// A015451 a(n) = 6 a(n-1) + a(n-2).


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/pellgen-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/pellgen-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

