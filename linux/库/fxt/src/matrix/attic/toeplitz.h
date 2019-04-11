#if !defined HAVE_TOEPLITZ_H__
#define      HAVE_TOEPLITZ_H__

#include "fxttypes.h"

#include "matrix/matrix.h"

#include "aux1/copy.h"


#define  MAT  matrix<Type>


template <typename Type>
void make_toeplitz(MAT &A, const Type *v)
// Set A to be the Toeplitz matrix
// with elements from v[] which needs to have 2*nc elements
// v[nc] is unused
{
    ulong nr = A.nrows();
    ulong nc = A.ncols();
    const Type *vm = v + nc + nc;
    for (ulong r=0; r<nr; ++r)
    {
        Type *rp = A[r];
        acopy(v, rp+r, nc-r);
        acopy(vm, rp, r);
        vm--;
    }
}
// -------------------------

template <typename Type>
void get_toeplitz_v(const MAT &A, Type *v)
// Extract vector v so that make_toeplitz(. , v) would create
// a Toeplitz matrix identical to A
// v[] needs to have 2*nc elements
{
    ulong nr = A.nrows();
    ulong nc = A.ncols();
    acopy(A[0], v, nc);
    for (ulong r=1,i=2*nc-1;  r<nr;  ++r,--i)  v[i] = A[r][0];
}
// -------------------------


template <typename Type>
void make_circulant(MAT &A, const Type *v)
// Set A to be the symmetric Toeplitz matrix
// with elements from v[] which needs to have nc elements
{
    ulong nr = A.nrows();
    ulong nc = A.ncols();
    for (ulong r=0; r<nr; ++r)
    {
        Type *rp = A[r];
        acopy(v, rp+r, nc-r);
        copy_reverse(v+1, rp, r);
    }
}
// -------------------------


template <typename Type>
void make_weighted_circulant(MAT &A, const Type *v, Type z)
// Set A to be the circulant matrix
// with row_k multiplied with z^k
// with elements from v[] which needs to have nc elements
{
    ulong nr = A.nrows();
    ulong nc = A.ncols();
    for (ulong r=0; r<nr; ++r)
    {
        Type *rp = A[r];
        acopy(v, rp+r, nc-r);
        copy_reverse(v+1, rp, r);
    }

    Type zk=z;
    for (ulong r=1; r<nr; ++r)
    {
        Type *rp = A[r];
        ::multiply_val(rp, nc, zk);
        zk *= z;
    }
}
// -------------------------


template <typename Type>
void get_circulant_v(const MAT &A, Type *v)
// Extract vector v so that make_circulant(. , v) would create
// a circulant matrix identical to A
// v[] needs to have nc elements
{
    ulong nc = A.ncols();
    acopy(A[0], v, nc);
}
// -------------------------


#undef  MAT


#endif // !defined HAVE_TOEPLITZ_H__
