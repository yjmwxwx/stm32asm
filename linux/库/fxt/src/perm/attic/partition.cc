
#include "partition.h"


partition::partition(int nn)
{
    n = ( nn<1 ? 1 : nn );
    x = new int[n+1];
    init();
}
//---------------------

partition::~partition()
{
    delete [] x;
}
//---------------------

void
partition::init()
{
    x[0] = n;
    k = 0;
    i = 0;
    idx = 0;
}
//---------------------

void
partition::make_next()
// based on code by Helmut Herold
{
    ++idx;

    int n1 = k-i;
    k = i;

    x[i]--;

    while ( x[k]<=n1 )
    {
        n1 -= x[k];
        k++;
        x[k] = x[k-1];
    }

    k++;
    x[k] = n1 + 1;

    if ( x[i]!=1 )  i = k;


   if ( x[i]==1 )  i--;

//   if ( i<0 )  return 0;
//   return 1;

   // here: n1 == number of ones in partition
}
//---------------------

