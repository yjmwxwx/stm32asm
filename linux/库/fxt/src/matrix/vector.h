#if !defined HAVE_VECTOR_H__
#define      HAVE_VECTOR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux1/arith1.h"  // add(), add_val()

#include "aux1/copy.h"  // acopy()

//#include "aux1/array.h"

//#include <cmath>  // sqrt()


// note: todo: insert compatibility checks with binary vector-operations


template <typename Type>
class vector
// Very simple vector class
{
public:
    ulong n_;  // #elems
    Type *f_;  // pointer to data

public:
    explicit vector(ulong n)
        : n_(n)
    {
        f_ = new Type[n_];
    }

    explicit vector(const vector<Type> &m)
    {
        f_ = new Type[n_];
        acopy(m.f_, f_, n_);
    }

    ~vector()
    {
        delete [] f_;
    }

    vector<Type> & operator =(const vector<Type> &m)
    {
        copy(m, *this);
        return *this;
    }

//    operator const Type *()  { return f_; }
//    operator Type *()  { return f_; }


//    Type norm_l2()  const
//    { return  sqrt( ::sum_of_squares(f_, n_) ); }

//    Type normalize(Type v=1)
//    {
//        Type a = norm_l2();
//        ::multiply_val(f_, n_,  v / a);
//        return  a;
//    }

//    void delta(ulong d)  { ::delta(f_, n_, d); }
//    void set_seq(Type start=0, Type step=1)  { ::set_seq(f_, n_, start, step); }

//    void negate()  { ::negate(f_, n_); }
//
//    void add_val(Type x)  { ::add_val(f_, n_, x); }
//    void subtract_val(Type x)  { ::subtract_val(f_, n_, x); }
//    void multiply_val(Type x)  { ::multiply_val(f_, n_, x); }

//    // element-wise (!) operations:
//    void add(const array<Type> &x)  { ::add(f_, n_, x.f_); }
//    void subtract(const array<Type> &x)  { ::subtract(f_, n_, x.f_); }
//    void multiply(const array<Type> &x)  { ::multiply(f_, n_, x.f_); }
//    void divide(const array<Type> &x)  { ::divide(f_, n_, x.f_); }
};
// -------------------------



template <typename Type>
inline vector<Type> & operator += (vector<Type> &t, const vector<Type> &h)
{ t.add(h);  return t; }

template <typename Type>
inline vector<Type> & operator -= (vector<Type> &t, const vector<Type> &h)
{ t.subtract(h);  return t; }

template <typename Type>
inline vector<Type> & operator *= (vector<Type> &t, const vector<Type> &h)
{ mmultby(t, h);  return t; }

template <typename Type>
inline vector<Type> & operator ^= (vector<Type> &t, const vector<Type> &h)
{ mmultbytr2(t, h);  return t; }


template <typename Type>
inline vector<Type> & operator += (vector<Type> &t, Type i)
{ t.add_val(i);  return t; }

template <typename Type>
inline vector<Type> & operator -= (vector<Type> &t, Type i)
{ t.subtract_val(i);  return t; }

template <typename Type>
inline vector<Type> & operator *= (vector<Type> &t, Type i)
{ t.multiply_val(i);  return t; }



#endif  // !defined HAVE_VECTOR_H__
