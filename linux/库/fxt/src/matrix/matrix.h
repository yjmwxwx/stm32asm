#if !defined HAVE_MATRIX_H__
#define      HAVE_MATRIX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/array2d.h"


//#include "aux2/arith2d.h"  // add(), add_val()
#include "aux1/arith1.h"  // add(), add_val()

#include "fxttypes.h"

#include "aux1/copy.h"

#include "aux0/sign.h"  // abs()
#include "aux0/swap.h"

#include "aux2/transpose.h"

// included after class definition:
//#include "matrix/mmult.h"  // matrix multiplication


#include <cmath>  // sqrt()



template <typename Type>
class matrix : public array2d<Type>
// Square matrix
{
public:
    Type *tmp_;  // scratch space with max(nr_, nc_) elements

public:
    using array2d<Type>::nr_;
    using array2d<Type>::nc_;
    using array2d<Type>::rowp_;
    using array2d<Type>::row;
    using array2d<Type>::null;

    matrix(ulong n, Type *f=0)
        : array2d<Type>(n, n, f)
    { tmp_ = new Type[n]; }

    matrix(ulong n, Type **rowp)
        : array2d<Type>(n, n, rowp)
    { tmp_ = new Type[n]; }

    matrix(const matrix<Type> &m)
        : array2d<Type>(m.nr_, m.nc_)
    {
        tmp_ = new Type[nr_];
        copy(m.rowp_, rowp_, nr_, nc_);
    }

    ~matrix()  { delete [] tmp_; }

    matrix<Type> & operator =(const matrix<Type> &m)
    {
        copy(m, *this);
        return *this;
    }

//    operator const Type *const*()  { return rowp_; }
//    operator Type **()  { return rowp_; }

    void transpose();

//    Type norm_l2()  const
//    { return  sqrt( ::sum_of_squares(rowp_, nr_, nc_) ); }

//    Type normalize(Type v=1)
//    {
//        Type a = norm_l2();
//        ::multiply_val(rowp_, nr_, nc_,  v / a);
//        return  a;
//    }


    void get_row(ulong r, Type *v)  const
    { acopy(rowp_[r], v, nc_); }

    void set_row(ulong r, const Type *v)
    { acopy(v, rowp_[r], nc_); }

//    void set_row(ulong r, Type v)
//    { ::fill(rowp_[r], nc_, v); }


    void get_col(ulong c, Type *v)  const
    { for (ulong r=0; r<nr_; ++r)  v[r] = rowp_[r][c]; }

    void set_col(ulong c, Type *v)
    { for (ulong r=0; r<nr_; ++r)  rowp_[r][c] = v[r]; }

//    void set_col(ulong c, Type v)
//    { for (ulong r=0; r<nr_; ++r)  rowp_[r][c] = v; }

    bool is_diag(Type *v)  const
    {
        for (ulong k=0; k<nr_; ++k)
            if (v[k] != rowp_[k][k])  return false;

        for (ulong r=0; r<nr_; ++r)
            for (ulong c=0; c<nc_; ++c)
                if ( (c!=r) && (rowp_[r][c]!=0) )  return false;

        return true;
    }

    bool is_diag(Type v)  const
    // Whether diagonal with diagonal entries ==v
    {
        for (ulong k=0; k<nr_; ++k)  tmp_[k] = v;
        return is_diag(tmp_);
    }

//    bool is_diag(const Type *v, Type eps)  const
//    {
//        for (ulong k=0; k<nr_; ++k)
//            if ( abs(v[k] - rowp_[k][k])>eps )  return false;
//        for (ulong r=0; r<nr_; ++r)
//            for (ulong c=0; c<nc_; ++c)
//                if ( (c!=r) && (abs(rowp_[r][c])>eps) )  return false;
//        return true;
//    }
//
//    bool is_diag(Type v, Type eps)  const
//    {
//        for (ulong k=0; k<nr_; ++k)  tmp_[k] = v;
//        return is_diag(tmp_, eps);
//    }
//
//
//    void get_diag(Type *v)  const
//    { for (ulong k=0; k<nr_; ++k)  v[k] = rowp_[k][k]; }
//
//    Type *get_diag()  const
//    { get_diag(tmp_); return tmp_; }

    void set_diag(Type v)
    { for (ulong k=0; k<nr_; ++k)  rowp_[k][k] = v; }

    void set_diag(const Type *v)
    { for (ulong k=0; k<nr_; ++k)  rowp_[k][k] = v[k]; }

//    void set_diag_seq(Type start=0, Type step=1)
//    {
//        for (ulong k=0; k<nr_; ++k)  { rowp_[k][k] = start; start += step; }
//    }

    void unit(Type v=1)  { null();  set_diag( v ); }

    bool is_unitary(Type v)  const
    {
        if ( nr_ != nc_ )  return false;
        matrix<Type> T(*this);  T.transpose();
        T *= *this;
        return  T.is_diag(v);
    }

    bool kronecker(const matrix<Type> A, const matrix<Type> B)
    {
        ulong nra = A.nr_,  nca = A.nc_;
        ulong nrb = B.nr_,  ncb = B.nc_;
        if ( nra * nrb != nr_ )  return false;
        if ( nca * ncb != nc_ )  return false;
        for (ulong ra=0; ra<nra; ++ra)
        {
            ulong ro = ra * nrb;
            for (ulong ca=0; ca<nca; ++ca)
            {
                ulong co = ca * ncb;
                Type ea = A.get(ra, ca);
                for (ulong rb=0; rb<nrb; ++rb)
                {
                    ulong r = ro + rb;
                    for (ulong cb=0; cb<ncb; ++cb)
                    {
                        Type eb = B.get(rb, cb);
                        ulong c = co + cb;
                        Type p = ea * eb;
                        array2d<Type>::set(r, c, p);
                    }
                }
            }
        }
        return true;
    }

//    Type unit_sqr_diff(Type v=1)
//    {
//        Type s = 0;
//        for (ulong r=0; r<nr_; ++r)
//        {
//            s += delta_sqr_diff(rowp_[r], nc_, r, v);
//        }
//        return  s;
//    }

    void diag_add_val(Type v)
    { for (ulong k=0; k<nr_; ++k)  rowp_[k][k] += v; }

    void diag_subtract_val(Type v)
    { for (ulong k=0; k<nr_; ++k)  rowp_[k][k] -= v; }

//    void diag2col()
//    {  for (ulong r=1; r<nr_; ++r)  ::rotate_left(row(r), nc_, r); }
//    void col2diag()
//    {  for (ulong r=1; r<nr_; ++r)  ::rotate_right(row(r), nc_, r); }
//    void diag2row()  { diag2col();  transpose(); }
//    void row2diag()  { transpose(); col2diag(); }
//
    void negate()  { ::negate(rowp_, nr_, nc_); }

//    void add_val(Type x)  { ::add_val(rowp_, nr_, nc_, x); }
//    void subtract_val(Type x)  { ::subtract_val(rowp_, nr_, nc_, x); }
    void multiply_val(Type x)  { ::multiply_val(rowp_, nr_, nc_, x); }
//
//    // element-wise (!) operations:
//    void add(const array2d<Type> &x)  { ::add(rowp_, nr_, nc_, x.rowp_); }
//    void subtract(const array2d<Type> &x)  { ::subtract(rowp_, nr_, nc_, x.rowp_); }
//    void multiply(const array2d<Type> &x)  { ::multiply(rowp_, nr_, nc_, x.rowp_); }
//    void divide(const array2d<Type> &x)  { ::divide(rowp_, nr_, nc_, x.rowp_); }
};
// -------------------------



template <typename Type>
void transpose(const matrix<Type> &src, matrix<Type> &dst)
{
    // note: todo: check compatibility
    ::transpose((const Type *)src.f_, dst.f_, src.nr_, src.nc_);
}
// -------------------------

template <typename Type>
void matrix<Type>::transpose()
{
    ::transpose_square(rowp_, nr_);
}
// -------------------------



#include "matrix/mmult.h"  // matrix multiplication


template <typename Type>
inline matrix<Type> & operator += (matrix<Type> &t, const matrix<Type> &h)
{ t.add(h);  return t; }

template <typename Type>
inline matrix<Type> & operator -= (matrix<Type> &t, const matrix<Type> &h)
{ t.subtract(h);  return t; }

template <typename Type>
inline matrix<Type> & operator *= (matrix<Type> &t, const matrix<Type> &h)
{ mmultby(t, h);  return t; }

//template <typename Type>
//inline matrix<Type> & operator ^= (matrix<Type> &t, const matrix<Type> &h)
//{ mmultbytr2(t, h);  return t; }



//template <typename Type>
//inline matrix<Type> & operator += (matrix<Type> &t, Type i)
//{ t.add_val(i);  return t; }
//
//template <typename Type>
//inline matrix<Type> & operator -= (matrix<Type> &t, Type i)
//{ t.subtract_val(i);  return t; }
//
//template <typename Type>
//inline matrix<Type> & operator *= (matrix<Type> &t, Type i)
//{ t.multiply_val(i);  return t; }



#endif  // !defined HAVE_MATRIX_H__
