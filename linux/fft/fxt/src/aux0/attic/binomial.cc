
#include "fxttypes.h"

#include <cmath>  // floor()

ulong
binomial(ulong n, ulong k)
// trivial algorithm
{
    if ( k>n )  return  0;
    if ( (k==0) || (k==n) )  return  1;
    if ( 2*k > n )  k = n-k;

    double  b = 1.0;
    do
    {
        b *= n;
        b /= k;
        --k;
        --n;
    }
    while ( k!=0 );

    return  (ulong)floor(b+0.5);
}
// -------------------------
