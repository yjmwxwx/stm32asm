#if !defined HAVE_MMULT_H__
#define      HAVE_MMULT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#if !defined FXT_NO_WARN_HDR  // defined by make target 'invdep'
#if !defined HAVE_MATRIX_H__
#error 'Do not include directly, this file is included by matrix/matrix.h'
#endif
#endif  // !defined FXT_NO_WARN_HDR


//#define PARANOIA  // define to enable for this file
#ifdef PARANOIA
#warning  'PARANOIA tests enabled in mmult.h'
#include "jjassert.h"
#endif  // PARANOIA

#include "fxttypes.h"


#define  MAT  matrix<Type>

// note: optimize the matrix mult funcs (using tmp_)
// note: replace accesses via f_ by accesses via rowp_


template <typename Type>
void mmult(const MAT &a1, const MAT &a2, MAT &z)
// z = a1 * a2
// Result undefined if z is identical to either a1 or a2
{
#ifdef PARANOIA
    jjassert( a1.f_ != z.f_ );
    jjassert( a2.f_ != z.f_ );
#endif  // PARANOIA
    ulong nr = a1.num_rows();
    ulong nc = a1.num_cols();
    for (ulong r=0; r<nr; ++r)
    {
        Type *pz = z.row(r);
        for (ulong c=0; c<nc; ++c)
        {
            Type s = 0;
            for (ulong k=0; k<nc; ++k)
            {
//                s += a1.f_[k + r * nc1] * a2.f_[c + k * nc2];
                s += a1.f_[k + r * nc] * a2.f_[c + k * nr];
            }
            pz[c] = s;
        }
    }
}
// -------------------------

//template <typename Type>
//void mmulttr2(const MAT &a1, const MAT &a2, MAT &z)
//// z = a1 * a2^T
//// Result undefined if z is identical to either a1 or a2
//{
//#ifdef PARANOIA
//    jjassert( a1.f_ != z.f_ );
//    jjassert( a2.f_ != z.f_ );
//#endif  // PARANOIA
//    ulong nr = a1.num_rows();
//    ulong nc = a1.num_cols();
//    for (ulong r=0; r<nr; ++r)
//    {
//        Type *pz = z.row(r);
//        for (ulong c=0; c<nc; ++c)
//        {
//            Type s = 0.0;
//            for (ulong k=0; k<nc; ++k)
//            {
////                s += a1.f_[ k + r * nc1] * a2.f_[k + c * nr2];
//                s += a1.f_[ k + r * nc] * a2.f_[k + c * nr];
//            }
//            pz[c] = s;
//        }
//    }
//}
//// -------------------------
//
//template <typename Type>
//void mmulttr1(const MAT &a1, const MAT &a2, MAT &z)
//// z = a1^T * a2
//// Result undefined if z is identical to either a1 or a2
//{
//#ifdef PARANOIA
//    jjassert( a1.f_ != z.f_ );
//    jjassert( a2.f_ != z.f_ );
//#endif  // PARANOIA
//    ulong nr = a1.num_rows();
//    ulong nc = a1.num_cols();
//    for (ulong r=0; r<nr; ++r)
//    {
//        Type *pz = z.row(r);
//        for (ulong c=0; c<nc; ++c)
//        {
//            Type s = 0.0;
//            for (ulong k=0; k<nc; ++k)
//            {
////                s += a1.f_[ r + k * nr1] * a2.f_[c + k * nr2];
//                s += a1.f_[ r + k * nc] * a2.f_[c + k * nr];
//            }
//            pz[c] = s;
//        }
//    }
//}
//// -------------------------


template <typename Type>
void mmultby(MAT &a, const MAT &b)
// a *= b
{
    ulong  nr = b.num_rows();  // , nc = a.num_cols();
    MAT tt(nr);
    mmult(a, b, tt);
    copy(tt, a);
}
// -------------------------


template <typename Type>
void mmultbytr2(MAT &a, const MAT &b)
// a = a * b^T
{
    ulong  nr = b.num_cols();  // , nc = a.ncols();
    MAT tt(nr);
    mmulttr2(a, b, tt);
    copy(tt, a);
}
// -------------------------

//template <typename Type>
//void mmultbytr1(MAT &a, const MAT &b)
//// a = a^T * b
//{
//    ulong  nr = b.num_rows();  // , nc = a.num_rows();
//    MAT tt(nr);
//    mmulttr1(a, b, tt);
//    copy(tt, a);
//}
//// -------------------------


template <typename Type>
void msqr(MAT &a)
//  a *= a
{
    mmultby(a, a);
}
// -------------------------

template <typename Type>
void msqr(const MAT &a, MAT &b)
//  b = a * a
{
    copy(a, b);
    mmultby(b, a);
}
// -------------------------

template <typename Type>
void mvmult(const MAT &A, const Type *x, Type *b)
// b = A * x
{
    ulong nr = A.num_rows();
    ulong nc = A.num_cols();
    for (ulong r=0; r<nr; ++r)
    {
        b[r] = scalar_product(A[r], x, nc);
    }
}
// -------------------------

template <typename Type>
void mvmulttr(const MAT &A, const Type *x, Type *b)
// b = A^T * x
{
    ulong nr = A.num_rows();
    ulong nc = A.num_cols();
    for (ulong c=0; c<nc; ++c)
    {
        b[c] = scalar_product( A.get_col(c), x, nr);
    }
}
// -------------------------


#undef  MAT


#endif  // !defined HAVE_MMULT_H__
