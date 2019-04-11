#if !defined HAVE_CHOLESKY_H__
#define      HAVE_CHOLESKY_H__


#include "fxttypes.h"
#include "aux1/arith1.h"
#include "matrix/matrix.h"

#include <cmath>  // sqrt()

#define  MAT  matrix<Type>

template <typename Type>
ulong cholesky(MAT &A, Type *v=0)
// Replaces the symmetric matrix A by its left (lower)
// cholesky factor L (incl. diagonal).
// The inverses of the diagonal elements are put into v[]
// A = L^T * L
{
    if ( 0==v )  v = A.tmp_;

    ulong ret = 0;
    ulong n = A.nrows();
    for (ulong i=0; i<n; ++i)
    {
        for (ulong j=i; j<n; ++j)
        {
            Type s = A[i][j];
            for (long k=i-1; k>=0; --k)  s -= A[i][k] * A[j][k];

            if ( i==j )
            {
                if ( s<=0.0 )
                {
                    ++ret;
                    s = 0.0;
                    v[i] = 0.0;
                }
                else
                {
                    s = sqrt( s );
                    v[i] = 1.0 / s;
                }

                A[i][i] = s;
            }
            else  A[j][i] = s * v[i];
        }
    }

    for (ulong i=0; i<n; ++i)  null(A[i]+i+1, n-i-1);  // clear upper part

    return  ret;
}
// -------------------------


template <typename Type>
void cholesky_solve(const MAT &L, const Type *v, const Type *b, Type *x)
// Solves A * x = b;
// with L the left (lower) cholesky factor of A
{
    long n = L.nrows();
    for (long i=0; i<n; ++i)  // solve L*y=b, (y stored in x)
    {
        Type s = b[i];
        for (long k=i-1; k>=0; --k)  s -= L[i][k] * x[k];
        x[i] = s * v[i];
    }

    for (long i=n-1; i>=0; --i)  // solve L^t*x=y
    {
        Type s = x[i];
        for (long k=i+1; k<n; ++k)  s -= L[k][i] * x[k];
        x[i] = s * v[i];
    }
}
// -------------------------


template <typename Type>
void cholesky_invert(const MAT &L, const Type *v, MAT &A)
// Compute (L * L^T)-1
{
    ulong n = L.nrows();
    for (ulong i=0; i<n; ++i)
    {
        Type *rp = A[i];
        delta(rp, n, i);
        cholesky_solve(L, v, rp, rp);
    }
//    A.transpose();  // is symmetric anyway
}
// -------------------------


template <typename Type>
ulong cholesky_pseudo_inverse(const MAT &X, MAT &J)
// Compute the pseudo-inverse J of X
// J * X == 1 == X * J  for invertible X
{
    mmulttr1(X, X, J);
    Type *v = J.tmp_;
    ulong ret = cholesky(J, v);
    MAT Z(J);
    cholesky_invert(Z, v, J);  // (X^T X)^-1
    J ^= X;  // (X^T X)^-1 * X^T
    return  ret;
}
// -------------------------


#undef  MAT


#endif  // !defined HAVE_CHOLESKY_H__
