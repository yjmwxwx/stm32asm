#if !defined HAVE_SEARCHUNSORTED_H__
#define      HAVE_SEARCHUNSORTED_H__


#include "fxttypes.h"


template <typename Type>
ulong search_unsorted(const Type *f, ulong n, const Type v, ulong s=0)
//
// Return index (>=s) of first element in f[] that is == v
// Return ~0 if there is no such element
//
// Must have  n!=0
{
    ulong k;
    for (k=s; k<n; ++k)  if ( f[k] == v )  return k;
    return ~0UL;
}
// -------------------------


template <typename Type>
ulong search_unsorted_ge(const Type *f, ulong n, const Type v, ulong s=0)
//
// Return index (>=s) of first element in f[] that is >= v
// Return ~0 if there is no such element
//
// Must have  n!=0
{
    ulong k;
    for (k=s; k<n; ++k)  if ( f[k] >= v )  return k;
    return ~0UL;
}
// -------------------------


template <typename Type>
ulong search_unsorted_approx(const Type *f, ulong n, const Type v, Type da, ulong s=0)
//
// Return index (>=s) of first element x in f[] for which  |(x-v)| <= da
// Return ~0 if there is no such element
//
// Makes sense mostly with inexact types (float or double)
//
// Must have  n!=0
{
    if ( da<0 )  da = -da;
    ulong k;
    for (k=s; k<n; ++k)
    {
        Type d;
        d = ( f[k] > v ? f[k]-v : v-f[k]);
        if ( d <= da )  return k;
    }
    return ~0UL;
}
// -------------------------


#endif // !defined HAVE_SEARCHUNSORTED_H__
