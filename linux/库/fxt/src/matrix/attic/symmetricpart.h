#if !defined HAVE_SYMMETRICPART_H__
#define      HAVE_SYMMETRICPART_H__

#include "matrix/matrix.h"

#include "fxttypes.h"

#include "aux1/copy.h"

#define  MAT  matrix<Type>

template <typename Type>
int make_symmetric(MAT &A)
// Discard anti-symmetric part of A
{
    ulong n = A.nrows();
    if ( n != A.ncols() )  return 0;

    // diagonal needs no modification

    for (ulong j=1; j<n; ++j)  // make left upper triangle symmetric
    {
        for (ulong k=0, km=j;  k<km;  ++k, --km)
        {
            Type v = 0.5 * (A[k][km] + A[km][k]);
            A[k][km] = v;
            A[km][k] = v;
        }
    }

    for (ulong j=1; j<n-1; ++j)  // make right lower triangle symmetric
    {
        for (ulong k=j, km=n-1;  k<km;  ++k, --km)
        {
            Type v = 0.5 * (A[k][km] + A[km][k]);
            A[k][km] = v;
            A[km][k] = v;
        }
    }

    return 0;
}
// -------------------------


template <typename Type>
int symmetric_part(const MAT &A, MAT &B)
// B = symmetric part of A
{
    ulong n = A.nrows();
    if ( n != A.ncols() )  return 0;

    acopy(A, B);

    return  make_symmetric( B );
}
// -------------------------


template <typename Type>
int make_anti_symmetric(MAT &A)
// Discard symmetric part of A
{
    ulong n = A.nrows();
    if ( n != A.ncols() )  return 0;

    A.set_diag(0.0);

    for (ulong j=1; j<n; ++j)  // make left upper triangle symmetric
    {
        for (ulong k=0, km=j;  k<km;  ++k, --km)
        {
            Type v = 0.5 * (A[k][km] - A[km][k]);
            A[k][km] = v;
            A[km][k] = -v;
        }
    }

    for (ulong j=1; j<n-1; ++j)  // make right lower triangle symmetric
    {
        for (ulong k=j, km=n-1;  k<km;  ++k, --km)
        {
            Type v = 0.5 * (A[k][km] - A[km][k]);
            A[k][km] = v;
            A[km][k] = -v;
        }
    }

    return 0;
}
// -------------------------


template <typename Type>
int anti_symmetric_part(const MAT &A, MAT &B)
// B = anti-symmetric part of A
{
    ulong n = A.nrows();
    if ( n != A.ncols() )  return 0;
    acopy(A, B);
    return  make_anti_symmetric( B );
}
// -------------------------


#undef  MAT


#endif // !defined HAVE_SYMMETRICPART_H__
