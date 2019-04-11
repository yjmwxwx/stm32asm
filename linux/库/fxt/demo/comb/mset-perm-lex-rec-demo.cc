
// demo-is-self-contained

#include "comb/comb-print.h"

#include "fxttypes.h"
#include "jjassert.h"
#include "fxtio.h"

#include <cstdlib>  // strtoul()


//% All multiset permutations in lexicographic order, recursive generation.
//% Same as: all strings with fixed content.

ulong n;    // number of objects
ulong *ms;  // multiset data in ms[0], ..., ms[n-1]

ulong k;    // number of different sorts of objects
ulong *r;   // number of elements '0' in r[0], '1' in r[1], ..., 'k-1' in r[k-1]

ulong ct;   // count objects
ulong rct;  // count recursions
ulong wct;  // count work

const bool dfz = true;  // whether to print dots for zeros

void visit()
{
    cout << setw(4) << ct << ":";
    print_perm("  ", ms, n, dfz);
    cout << endl;
//    for (ulong j=0; j<k; ++j)  jjassert( r[j]==0 );
}
// -------------------------


void mset_perm_rec(ulong d)
{
    if ( d>=n )
    {
        ++ct;
        visit();
    }
    else
    {
        for (ulong j=0; j<k; ++j)  // for all buckets
        {
            ++wct;
            if ( r[j] )    // bucket has elements left
            {
                ++rct;
                --r[j];     // take element from bucket
                ms[d] = j;  // put element in place
                mset_perm_rec(d+1);  // recursion
                ++r[j];     // put element back
            }
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    cout << "args: multiplicities of elements" << endl;
    if ( argc<=1 )
    {
        ulong t[]={2, 2, 1, 0};  // proper multisets  ct=30
//        ulong t[]={6, 2, 0};  // combinations  ct=28
//        ulong t[]={1, 1, 1, 1, 0};  // permutations  ct=24
        k=0;  while ( t[k] )  { ++k; }
        r = new ulong[k];
        for (ulong j=0; j<k; ++j)  r[j] = t[j];
    }
    else
    {
        k = (ulong)argc - 1;
        r = new ulong[k];
        for (ulong j=0; j<k; ++j)
        {
            ulong t = strtoul(argv[j+1], 0, 10);
            r[j] = t;
        }
    }

    n = 0;
    for (ulong j=0; j<k; ++j)  n += r[j];
    ms = new ulong[n];


    cout << "multiplicities: ( ";
    for (ulong i=0; i<k; ++i)  cout << r[i] << (i<k-1?", ":" ");
    cout << ")";
    cout << "  k=" << k << "  n=" << n;
    cout << endl;

    ct = 0;
    rct = 0;
    wct = 0;
    mset_perm_rec(0);

    cout << "ct=" << ct << endl;
    cout << "wct=" << wct << endl;  // rct == ct-1
    cout << "work/object=" << (double)wct/(double)ct << endl;
    cout << "rct=" << rct << endl;  // rct == ct-1
    cout << "rec/object=" << (double)rct/(double)ct << endl;

    delete [] ms;
    delete [] r;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mset-perm-lex-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mset-perm-lex-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:
