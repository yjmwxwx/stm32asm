#if !defined HAVE_MISC_H__
#define      HAVE_MISC_H__


#include "fxttypes.h"


template <typename Type>
inline int compare(const Type *f, const Type *g, ulong n)
// compare f[], g[] up to length n
// if for f[k]!=g[k] for any k<n
// then return sign(f[k]-g[k])
{
    for (ulong k=0; k<n; ++k)
    {
        if ( f[k]==g[k] )  continue;

        if ( f[k]>g[k] )  return   1;
        else              return  -1;
    }
    return  0;
}
// -------------------------


template <typename Type>
inline ulong sequency(Type *f, ulong n)
// return the number of sign changes in f[]
{
    ulong sq = 0;
    ulong s1 = (f[0] < 0 ? 0 : 1);
    for (ulong k=1; k<n; ++k)
    {
        ulong s2 = (f[k] < 0 ? 0 : 1);
        sq += (s1 ^ s2);
        s1 = s2;
    }

    return  sq;
}
// -------------------------


//void make_sincos_table(ulong n, ulong m, double **s, double **c);

// aux1/str2ulong.cc:
ulong str2ulong(const char *p);


#endif // !defined HAVE_MISC_H__
