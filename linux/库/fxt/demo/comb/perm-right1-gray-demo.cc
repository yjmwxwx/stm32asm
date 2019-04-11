
#include "comb/fact2perm.h"
#include "perm/perminvert.h"
#include "perm/reverse.h"


#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"


//% Gray code for permutations where p(i)<=i+1 for all i, generated via
//% Gray code for falling factorial numbers where digit x is followed by x or more zeros.

//#define TIMING  // define to disable printing

#define CHK_GRAY  // define to check minimal-change (Gray) property


ulong n;    // number of digits in words
ulong *ff;  // digits of the word (falling factorial power)
ulong *pp;  // permutation corresponding to the word
ulong *ppi;  // inverse permutation
ulong *ffi;  // falling factorial word for inverse permutation

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
//    ffact2perm_swp(ff, n+1, pp);  // ==> perm == inverse perm
//    ffact2perm_rev(ff, n+1, pp);  // ==> perm == inverse perm
    ffact2perm(ff, n+1, pp);
    cout << "    [";
    for (ulong j=0; j<=n; ++j)
    {
        cout << " ";
        cout << pp[j];
    }
    cout << " ]";

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


#ifdef CHK_GRAY
    ulong tct = chk_gray();
#else
#warning "no checking for Gray-ness"
    ulong tct = 0;
#endif

    if ( tct>1 )  cout << "  X " << tct;

    cout << endl;
#endif
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
        if ( z )  // forward:
        {
            // words 0, 10, 200, 3000, 40000, ...
            ulong k = 0;
            do
            {
                ff[d] = k;
                Y_rec(d+k+1, !z);
            }
            while ( ++k <= (n-d) );
        }
        else      // backward:
        {
            // words ..., 40000, 3000, 200, 10, 0
            ulong k = n-d+1;
            do
            {
                --k;
                ff[d] = k;
                Y_rec(d+k+1, !z);
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
    NXARG(n, "Number of elements");
    ff = new ulong[n];
    for (ulong k=0; k<n; ++k)  ff[k] = 0;
    ffo = new ulong[n];
    pp = new ulong[n+1];
    ppi = new ulong[n+1];
    ffi = new ulong[n+1];

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
    delete [] ppi;
    delete [] ffi;

    return 0;
}
// -------------------------

/*

 time ./bin 28
arg 1: 28 == n  [Number of elements]  default=5
ct=268435456
./bin 28  3.11s user 0.02s system 99% cpu 3.141 total
 ==> 268435456/3.11 == 86,313,651  per second

for n in $(seq 0 13); do ./bin $n  | g ct | cut -d= -f2 ; done

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-right1-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-right1-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

