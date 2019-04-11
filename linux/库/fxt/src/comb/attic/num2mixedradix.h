#if !defined  HAVE_NUM2MIXEDRADIX_H__
#define       HAVE_NUM2MIXEDRADIX_H__


#include "fxttypes.h"
#include "restrict.h"


inline void num2mixedradix(ulong n, const ulong *r, ulong k, ulong * restrict d)
// Compute digits d[0,1,...,k-1] so that
// n == d[0]+r[0]*(d[1]+r[1]*(d[2]+...)))
// That is, set d[] to the mixed radix representation of n
// with k digits r[0,1,...,k-1].
{
    for (ulong j=0; j<k; ++j)
    {
        ulong d[j] = n % r[j];
        n /= r[j];
    }
}
// -------------------------


inline ulong mixedradix2num(const ulong *r, ulong k, const ulong *d)
// Return  n := d[0]+r[0]*(d[1]+r[1]*(d[2]+...)))
// Inverse of num2mixedradix()
{
    ulong n=0, p=1;
    for (ulong j=0; j<k; ++j)
    {
        n += p*d[j];
        p *= r[j];
    }
    return n;
}
// -------------------------


#endif  // !defined HAVE_NUM2MIXEDRADIX_H__
