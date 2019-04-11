
// demo-is-self-contained

#include "fxttypes.h"
#include "fxtio.h"
#include "aux0/binomial.h"
#include "aux1/auxprint.h"
#include "jjassert.h"
#include "demo/nextarg.h"

#include <cstdlib>  // rand(), srand()


inline bool rand_bit()
{
    uint r = rand();
    r ^= r>>16;
    r ^= r>>8;
    r ^= r>>4;
    return  r & 1;
}
// -------------------------

ulong n, k; // (n choose k)
ulong *rv;  // record of visits in graph

ulong ct;   // count combinations
ulong rct;  // count recursions (==work)
ulong rq;   // condition that determines the order
ulong nq;   // whether to reverse order


void visit()
{
    cout << setw(4) << ct << ":";
    print_set_as_bitset("    ", rv, k, n);
    cout << "   ";
    for (ulong j=0; j<k; ++j)  cout << " " << rv[j];
    cout << endl;
}
// -------------------------


void next_rec(ulong d)
{
    ulong r = k - d;  // number of elements remaining
    ulong rv1 = rv[d-1];  // left neighbor

    if ( (rv1==n-1-r) || (0==r) )
    {
        ++ct;  // count objects
        visit();
    }
    else
    {
        ++rct;  // measure computational work
        bool q;
        switch ( rq )
        {
        case 0:  q = 1;  break;   // lex order
        case 1:  q = !(d&1);  break;   // gray order
        case 2:  q = rv1&1;  break;  // near-perfect order
        case 3:  q = (d^rv1)&1;  break;  // diagonal gray order
        default: q = rand_bit();  // "random" order
        }

        if ( nq )  q = !q;

        if ( q )
        {
            for (ulong x=rv1+1; x<=n-r; ++x)  // forward
            {
                rv[d] = x;
                next_rec(d+1);
            }
        }
        else
        {
            for (ulong x=n-r; (long)x>=(long)rv1+1; --x)  // backward
            {
                rv[d] = x;
                next_rec(d+1);
            }
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 7;
    NXARG(n, "Combination (n choose k)");
    k = 3;
    NXARG(k, " 0 < k <= n");
    rq = 2;
    NXARG(rq, "Order: 0==>lex,  1==>Gray,  2==>near-perfect,  3==>diagonal Gray");
    nq = 0;
    NXARG(nq, "Whether to reverse order.");
    srand(rq);

    rv = new ulong[k+1];
    ++rv;
    rv[-1] = -1UL;
    for (ulong j=0; j<k; ++j)  rv[j] = n-k+j;

    ct = 0;
    rct = 0;
    next_rec(0);

//    cout << "rct=" << rct << endl;
    cout << "work/object=" << 1.0*(rct)/(ct) << endl;  // ratio <= 1

    jjassert( ct==binomial(n,k) );

    --rv;
    delete [] rv;

    return 0;
}
// -------------------------

// ./bin 7 4 | tr '.1' '1.' | tac | rev
// n=10; for (( k=0; k<=n; ++k )); do ./bin $n $k 0 | grep work ; done


//  for (( n=0; n<=7; ++n )); do echo "$n:  "; for (( k=0; k<=n; ++k )); do ./bin $n $k 0 | grep rct | sed -r 's/rct=/ /;' ; done; done
//
//  0:   0
//  1:   0 0
//  2:   0 1 0
//  3:   0 1 2 0
//  4:   0 1 3 3 0
//  5:   0 1 4 6 4 0
//  6:   0 1 5 10 10 5 0
//  7:   0 1 6 15 20 15 6 0

