#if !defined HAVE_MATRIXSYMMETRYQ_H__
#define      HAVE_MATRIXSYMMETRYQ_H__


#include "matrix/matrix.h"

#include "fxttypes.h"

#include <cmath>  // fabs()

#define  MAT  matrix<Type>


template <typename Type>
bool is_toeplitz(const MAT &A, const Type eps=1e-8)
// Return whether A is a Toeplitz matrix
{
    ulong n = A.nrows();
    if ( n != A.ncols() )  return false;

    for (ulong k=0; k<n; ++k)  // check diagonal and above
    {
        const Type v = A[0][k];
        for (ulong j=1; j<n-k; ++j)
        {
            if ( fabs(A[j][k+j] - v) > eps )  return false;
        }
    }

    for (ulong k=1; k<n; ++k)  // check below diagonal
    {
        const Type v = A[k][0];
        for (ulong j=1; j<n-k; ++j)
        {
            if ( fabs(A[k+j][j] - v) > eps )  return false;
        }
    }

    return true;
}
// -------------------------


template <typename Type>
bool is_circulant(const MAT &A, const Type eps=1e-8)
// Return whether A is a symmetric Toeplitz matrix
{
    if ( 0==is_toeplitz(A, eps) )  return false;

    ulong n = A.nrows();
    for (ulong k=0, km=n-1;  k<km;  ++k, --km)  // check minor diagonal
    {
        if ( fabs(A[k][km] - A[km][k]) > eps )  return false;
    }

    return true;
}
// -------------------------


template <typename Type>
bool is_symmetric(const MAT &A, const Type eps=1e-8)
// Return whether A is symmetric
{
    ulong n = A.nrows();
    if ( n != A.ncols() )  return false;

    for (ulong j=1; j<n; ++j)  // check left upper triangle
    {
        for (ulong k=0, km=j;  k<km;  ++k, --km)
        {
            if ( fabs(A[k][km] - A[km][k]) > eps )  return false;
        }
    }

    for (ulong j=1; j<n-1; ++j)  // check right lower triangle
    {
        for (ulong k=j, km=n-1;  k<km;  ++k, --km)
        {
            if ( fabs(A[k][km] - A[km][k]) > eps )  return false;
        }
    }

    return true;
}
// -------------------------

template <typename Type>
bool is_anti_symmetric(const MAT &A, const Type eps=1e-8)
// Return whether A is anti symmetric
{
    ulong n = A.nrows();
    if ( n != A.ncols() )  return false;

    for (ulong j=0; j<n; ++j)  // check diagonal
    {
        if ( fabs(A[j][j]) > eps )  return false;
    }

    for (ulong j=1; j<n; ++j)  // check left upper triangle
    {
        for (ulong k=0, km=j;  k<km;  ++k, --km)
        {
            if ( fabs(A[k][km] + A[km][k]) > eps )  return false;
        }
    }

    for (ulong j=1; j<n-1; ++j)  // check right lower triangle
    {
        for (ulong k=j, km=n-1;  k<km;  ++k, --km)
        {
            if ( fabs(A[k][km] + A[km][k]) > eps )  return false;
        }
    }

    return true;
}
// -------------------------


template <typename Type>
bool is_minor_symmetric(const MAT &A, const Type eps=1e-8)
// Return whether A is symmetric wrt. minor diagonal
{
    ulong n = A.nrows();
    if ( n != A.ncols() )  return false;


    for (ulong k=0, km=n-1;  k<km;  ++k, --km)  // check diagonal
    {
        if ( fabs(A[k][k] - A[km][km]) > eps )  return false;
    }

    for (ulong j=1; j<n; ++j)  // check right upper triangle
    {
        for (ulong k=0, km=n-1, i=j, im=j;  i<im;  ++k, --km, ++i, --im)
        {
            if ( fabs(A[k][i] - A[km][im]) > eps )  return false;
        }
    }

    for (ulong j=1; j<n-1; ++j)  // check left lower triangle
    {
        for (ulong k=0, km=n-1, i=j, im=j;  i<im;  ++k, --km, ++i, --im)
        {
            if ( fabs(A[i][k] - A[im][km]) > eps )  return false;
        }
    }

    return true;
}
// -------------------------

template <typename Type>
bool is_minor_anti_symmetric(const MAT &A, const Type eps=1e-8)
// Return whether A is antisymmetric wrt. minor diagonal
{
    ulong n = A.nrows();
    if ( n != A.ncols() )  return false;


    for (ulong k=0, km=n-1;  k<km;  ++k, --km)  // check diagonal
    {
        if ( fabs(A[k][k] + A[km][km]) > eps )  return false;
    }

    for (ulong j=1; j<n; ++j)  // check right upper triangle
    {
        for (ulong k=0, km=n-1, i=j, im=j;  i<im;  ++k, --km, ++i, --im)
        {
            if ( fabs(A[k][i] + A[km][im]) > eps )  return false;
        }
    }

    for (ulong j=1; j<n-1; ++j)  // check left lower triangle
    {
        for (ulong k=0, km=n-1, i=j, im=j;  i<im;  ++k, --km, ++i, --im)
        {
            if ( fabs(A[i][k] + A[im][km]) > eps )  return false;
        }
    }

    return true;
}
// -------------------------



template <typename Type>
bool is_doubly_symmetric(const MAT &A, const Type eps=1e-8)
// Return whether A is symmetric wrt. to both major and minor diagonal
// i.e. looks like this:
//  0       1       2       3
//  1       5       6       2
//  2       6       5       1
//  3       2       1       0
{
    ulong n = A.nrows();
    if ( n != A.ncols() )  return false;

    // note: to be optimized
    if ( 0==is_symmetric(A, eps) )  return false;
    if ( 0==is_minor_symmetric(A, eps) )  return false;

    return true;
}
// -------------------------

#undef  MAT


#endif // !defined HAVE_MATRIXSYMMETRYQ_H__
