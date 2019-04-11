
#include "comb/fact2perm.h"
#include "perm/perminvert.h"
#include "perm/reverse.h"


#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray code for permutations where i-1<=p(i)<=i+1 for all i, generated via
//% Gray code for falling factorial numbers that are Fibonacci numbers

//#define TIMING  // define to disable printing

#define CHK_GRAY  // define to check minimal-change (Gray) property

//#define INVERSE  // define to also compute inverse permutations

ulong n;    // number of digits in words
ulong *ff;  // digits of the word (falling factorial power)
ulong *pp;  // permutation corresponding to the word
#ifdef INVERSE
ulong *ppi;  // inverse permutation
ulong *ffi;  // falling factorial word for inverse permutation
#endif  // INVERSE
ulong ct;   // count objects


ulong *ffo;  // last string
ulong ngct;  // count non-Gray transitions

ulong chk_gray()
{
    ulong tct = 0;
    if ( ct>1 )  // check whether Gray transition
    {
        for (ulong j=0; j<n; ++j)  tct += (ff[j]!=ffo[j]);
        if ( tct!=1 )
        {
            ++ngct;
        }
    }
    for (ulong j=0; j<n; ++j)  ffo[j] = ff[j];
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
        if ( ff[j] )  cout << ff[j];
        else          cout << '.';
    }

//    reverse(ff, n);  rfact2perm(ff, n+1, pp); reverse(ff, n);  // as rising factorial
//    ffact2perm_swp(ff, n+1, pp);  // also Gray
//    ffact2perm_rev(ff, n+1, pp);  // also Gray
    ffact2perm(ff, n+1, pp);
    cout << "    [";
    for (ulong j=0; j<=n; ++j)
    {
        cout << " ";
        cout << pp[j];
    }
    cout << " ]";

#ifdef INVERSE
    make_inverse(pp, ppi, n+1);
    cout << "    [";
    for (ulong j=0; j<=n; ++j)
    {
        cout << " ";
        cout << ppi[j];
    }
    cout << " ]";


    perm2ffact(ppi, n+1, ffi);
    cout << "    ";
    for (ulong j=0; j<n; ++j)
    {
        cout << " ";
        if ( ffi[j] )  cout << ffi[j];
        else           cout << '.';
    }
#endif  // INVERSE

#ifdef CHK_GRAY
    ulong tct = chk_gray();
#else
#warning "no checking for Gray-ness"
    ulong tct = 0;
#endif  // CHK_GRAY

    if ( tct>1 )  cout << "  X " << tct;

    cout << endl;
#endif  // TIMING
}
// -------------------------


void Y_rec(ulong d, bool z)
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
            ff[d]=1; ff[d+1]=0; Y_rec(d+2,  !z);
            ff[d]=0;  Y_rec(d+1,  !z);
        }
        else
        {
            ff[d]=0;  Y_rec(d+1,  !z);
            ff[d]=1; ff[d+1]=0; Y_rec(d+2,  !z);
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 8;
    NXARG(n, "Number of elements");
    --n;
    ff = new ulong[n+1];
    ffo = new ulong[n+1];
    pp = new ulong[n+1];
#ifdef INVERSE
    ppi = new ulong[n+1];
    ffi = new ulong[n+1];
#endif  // INVERSE
    bool rq = 1;
//    NXARG(rq, "Whether to reverse order");

    ct = 0;
    Y_rec(0, rq);

    cout << "ct=" << ct << endl;
    if ( ngct )  cout << " ***** ngct=" << ngct << endl;
    jjassert( 0==ngct );

    delete [] ff;
    delete [] ffo;
    delete [] pp;
#ifdef INVERSE
    delete [] ppi;
    delete [] ffi;
#endif

    return 0;
}
// -------------------------

/*
 time ./bin 40
arg 1: 40 == n  [Number of elements]  default=8
ct=165580141
./bin 40  2.61s user 0.00s system 100% cpu 2.616 total
 ==> 165580141/2.61 == 63,440,667 per second

for n in $(seq 0 13); do ./bin $n  | g ct | cut -d= -f2 ; done

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-dist1-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-dist1-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

