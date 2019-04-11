#if !defined HAVE_ARRAY_H__
#define      HAVE_ARRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "perm/rotate.h"
#include "perm/reverse.h"
#include "sort/minmax.h"

#include "aux1/scale.h"
#include "aux1/applyfunc.h"
#include "aux1/shift.h"
#include "aux1/copy.h"

#include "fxttypes.h"


template <typename Type>
class array
{
public:
    ulong n_;  // #elems
    Type *f_;  // pointer to data

protected:
    bool myfq_;  // whether f_ was allocated by constructor


public:
    array(ulong n, Type *f=0)
    : n_(n)
    {
        if ( 0!=f )  { f_ = f; myfq_ = false; }
        else         { f_ = new Type[n_]; myfq_ = true; }
    }

    ~array()  { if ( myfq_ )  delete [] f_; }

    Type *operator [] (ulong x) const  { return f_[x]; }

    ulong nelem()  const  { return n_; }

    Type get(ulong k)  const  { return f_[k]; }
    void set(ulong k, Type v)  { f_[k]=v; }

    void null()  { ::null(f_, n_); }
    void copy(array<Type> a)  { acopy(a.f_, a.n_, f_, n_); }

    void min_max(Type *mi, Type *ma)  const  { ::min_max(f_, n_, mi, ma); }

    void linear_scale(Type mi, Type ma, Type nmi, Type nma)
    { ::linear_scale(f_, n_, mi, ma, nmi, nma); }
    void linear_scale(Type nmi, Type nma)
    { ::linear_scale(f_, n_, nmi, nma); }
    void log_scale(double xi, double xa, Type nma)
    { ::log_scale(f_, n_, xi, xa, nma); }

    void apply_func(Type (*func)(Type)) { ::apply_func(f_, n_, func); }

    void shift_left(ulong r)  { ::shift_left(f_, n_, r); }
    void shift_right(ulong r)  { ::shift_right(f_, n_, r); }
    void shift(long s)  { ::shift_sgn(f_, n_, s); }

    void reverse()  { ::reverse(f_, n_); }
    void reverse_0()  { ::reverse_0(f_, n_); }

    void rotate_left(ulong r)  { ::rotate_left(f_, n_, r); }
    void rotate_right(ulong r)  { ::rotate_right(f_, n_, r); }
    void rotate(long r)  { ::rotate_sgn(f_, n_, r); }

//    void zero2center()  { ::zero2center(f_, n_); }
};
// -------------------------


template <typename Type>
void copy(const array<Type> &src, array<Type> &dst)
{
    copy(src.f_, src.n_, dst.f_, dst.n_);
}
// -------------------------


//template <typename Type>
//void copy(const array<Type> &src, array<Type> &dst, ulong off)
//{
//    dst.null();
//    ::offset_copy(src.f_, src.n_, dst.f_, dst.n_, off);
//}
//// -------------------------


template <typename Type>
void copy(const array<Type> &src, Type *dst)
// assuming dst[] has compatible length
{
    ulong n = src.n_;
    copy(src.f_, n, dst, n);
}
// -------------------------

template <typename Type>
void copy(const Type *src, array<Type> &dst)
// assuming dst[] has compatible length
{
    ulong n = dst.n_;
    copy(src, n, dst.f_, n);
}
// -------------------------



#endif  // !defined HAVE_ARRAY_H__
