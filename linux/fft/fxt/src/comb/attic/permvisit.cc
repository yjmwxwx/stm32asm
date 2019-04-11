
#include "perm/permvisit.h"
#include "aux0/funcemu.h"

#include "fxttypes.h"


perm_visit::perm_visit(ulong nn)
{
    n = ( nn<1 ? 1 : nn );
    x = new ulong[2*n+1];
    xi = x + n + 1; // allow for write to xi[-1]

    fe = new funcemu<ulong>(64, 256);

    first();
}
// -------------------------

perm_visit::~perm_visit()
{
    delete [] x;
    delete fe;
}
// -------------------------


void
perm_visit::first()
{
    for (ulong i=0; i<n; i++)  x[i] = -1UL;

    fe->stpush(0);
    fe->push(0, 0, 0);

    idx = 0;
    q = next_recursion();
}
// -------------------------

ulong
perm_visit::next_recursion()
{
    ulong  k, j, i;

 redo:
    fe->peek(k, j, i);

    switch ( fe->stpeek() )
    {
    case 0:
        x[k] = j - 1;
        xi[j-1] = k;  // can have j==0
        if ( j==n )
        {
            fe->stnext(99);
            return  1;
        }
//        else  fe->stnext(2);

//    case 2:
        while ( i != n )
        {
            if ( -1UL == x[i] )
            {
                fe->poke(/*k, j,*/ i+1);

                fe->stpush(0);  fe->push(i, j+1, 0);  goto redo;  // == visit(i, j+1);
            }
            else  ++i;
        }

    default:
        x[k] = -1UL;
    }

    fe->pop(3);  fe->stpop();  // return to caller in funcemu

    if ( fe->more() )  goto redo;

    return 0;  // return from top level call
}
// -------------------------



//recursive version that prints permutations
// (idea given in Sedgewick's "Algorithms in C")
//
//int n;
//int v[n];
//
//int main()
//{
//    for (ulong k=0; k<n; ++k)  v[k] = -1;
//    visit(0, 0);
//    return 0;
//}
//
//void visit(int k, int j)
//{
//    int i;
//    v[k] = j - 1;
//
//    if ( j==n )
//    {
//        for (i=0; i<n; i++) printf ("%2d", v[i]);
//        printf ("\n");
//    }
//    else
//    {
//        for (i=0; i<n; i++)
////        for (i=n-1; i>=0; i--)
//        {
//            if ( -1 == v[i] )  visit(i, j+1);
//        }
//    }
//
//    v[k] = -1;
//}
//// -------------------------

