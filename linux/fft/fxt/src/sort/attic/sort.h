#if !defined HAVE_SORT_H__
#define      HAVE_SORT_H__

#include "fxttypes.h"
#include "inline.h"


template <typename Type>
void selection_sort(Type *f, ulong n)
{
    for (ulong i=0; i<n; ++i)
    {
        Type v = f[i];
        ulong m = i; // position of minimum
        ulong j = n;
        while ( --j > i )  // search (index of) minimum
        {
            if ( f[j]<v )
            {
                m = j;
                v = f[m];
            }
        }

        swap(f[i], f[m]);
    }
}
// -------------------------


template  <typename Type>
int is_sorted(const Type *f, ulong n)
{
    if ( 0==n )  return 1;

    while ( --n )  // n-1 ... 2
    {
        if ( f[n] < f[n-1] )  break;
    }

    return  !n;
}
// -------------------------


template  <typename Type>
int is_partitioned(const Type *f, ulong n, ulong k)
{
    ++k;
    Type lmax = max(f,   k);
    Type rmin = min(f+k, n-k);

    return  ( lmax<=rmin );
}
// -------------------------


template <typename Type>
ulong partition(Type *f, ulong n)
// rearrange array, so that for some index p
// max(f[0] ... f[p]) <= min(f[p+1] ... f[n-1])
{
    swap( f[0], f[n/2]);
    const Type v = f[0];

    ulong i = 0UL - 1;
    ulong j = n;
    while ( 1 )
    {
        do  { ++i; }  while ( f[i]<v );
        do  { --j; }  while ( f[j]>v );

        if ( i<j )  swap(f[i], f[j]);
        else        return j;
    }
}
// -------------------------


template <typename Type>
void quick_sort(Type *f, ulong n)
{
 start:
    if ( n<8 ) // parameter: threshold for nonrecursive algorithm
    {
        selection_sort(f, n);
        return;
    }

    ulong p = partition(f, n);
    ulong ln = p + 1;
    ulong rn = n - ln;

//    quick_sort(f,    ln);  // f[0]  ... f[ln-1]  left
//    quick_sort(f+ln, rn);  // f[ln] ... f[n-1]   right

    if ( ln>rn )  // recursion for shorter subarray
    {
//        if ( rn<8 )  selection_sort(f+ln, rn);
//        else
        quick_sort(f+ln, rn);  // f[ln] ... f[n-1]   right

        n = ln;
    }
    else
    {
//        if ( ln<8 )  selection_sort(f, ln);
//        else
        quick_sort(f, ln);  // f[0]  ... f[ln-1]  left
        n = rn;
        f += ln;
    }

    goto start;
}
// -------------------------


#endif // !defined HAVE_SORT_H__
