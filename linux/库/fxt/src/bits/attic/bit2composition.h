#if !defined HAVE_BIT2COMPOSITION_H__
#define      HAVE_BIT2COMPOSITION_H__

#include "fxttypes.h"

static inline void bit2comb(ulong w, ulong *x/*, ulong n*/)
// example: "5 out of 7" combinations:
// #  0:   0 1 2 3 4    ..11111
// #  1:   0 1 2 4 5    .11.111
// #  2:   0 2 3 4 5    .1111.1
// #  3:   1 2 3 4 5    .11111.
// #  4:   0 1 3 4 5    .111.11
// #  5:   0 1 2 3 5    .1.1111
// #  6:   0 1 2 5 6    11..111
// #  7:   0 2 3 5 6    11.11.1
// #  8:   1 2 3 5 6    11.111.
// #  9:   0 1 3 5 6    11.1.11
// # 10:   0 3 4 5 6    1111..1
// # 11:   1 3 4 5 6    1111.1.
// # 12:   2 3 4 5 6    11111..
// # 13:   0 2 4 5 6    111.1.1
// # 14:   1 2 4 5 6    111.11.
// # 15:   0 1 4 5 6    111..11
// # 16:   0 1 2 4 6    1.1.111
// # 17:   0 2 3 4 6    1.111.1
// # 18:   1 2 3 4 6    1.1111.
// # 19:   0 1 3 4 6    1.11.11
// # 20:   0 1 2 3 6    1..1111
{
    ulong k = 0, i = 0;
    while ( w )
    {
        if ( w & 1 )  x[k++] = i;
        w >>= 1;
        ++i;
    }
}
// -------------------------

static inline ulong comb2bit(const ulong *x, ulong n)
// inverse of bit2comb()
{
    ulong w = 0;
    for (ulong k=0; k<n; ++k)  w |= (1UL<<x[k]);
    return w;
}
// -------------------------

static inline void bit2composition(ulong w, ulong *x, ulong n)
// example:  compositions(5, 3)  (n=5, k=3)
//          x[]         w
// #  0:   5 0 0    ..11111
// #  1:   4 1 0    .1.1111
// #  2:   3 2 0    .11.111
// #  3:   2 3 0    .111.11
// #  4:   1 4 0    .1111.1
// #  5:   0 5 0    .11111.
// #  6:   4 0 1    1..1111
// #  7:   3 1 1    1.1.111
// #  8:   2 2 1    1.11.11
// #  9:   1 3 1    1.111.1
// # 10:   0 4 1    1.1111.
// # 11:   3 0 2    11..111
// # 12:   2 1 2    11.1.11
// # 13:   1 2 2    11.11.1
// # 14:   0 3 2    11.111.
// # 15:   2 0 3    111..11
// # 16:   1 1 3    111.1.1
// # 17:   0 2 3    111.11.
// # 18:   1 0 4    1111..1
// # 19:   0 1 4    1111.1.
// # 20:   0 0 5    11111..
//  tot. #= 21  = binomial(7, 5) = binomial(n+k-1,n)
{
    for (ulong k=0; k<n; ++k)
    {
        ulong ct = 0;
        ulong b;
        do
        {
            b = w & 1;
            ct += b;
            w >>= 1;
        }
        while ( 0!=b );
        x[k] = ct;
    }
}
// -------------------------


static inline ulong composition2bit(const ulong *x, ulong n)
// inverse of bit2composition()
{
    ulong m = 1,  w = 0;
    for (ulong k=0; k<n; ++k)
    {
        ulong ct = x[k];
        while ( ct-- )
        {
            w |= m;
            m <<= 1;
        }
        m <<= 1;
    }
    return w;
}
// -------------------------


#endif  // !defined HAVE_BIT2COMPOSITION_H__
