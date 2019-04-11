#if !defined HAVE_ORDEREDRARRAY_H__
#define      HAVE_ORDEREDRARRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "ds/rarray.h"
#include "sort/bsearch.h"  // bsearch_geq()

//#include "aux1/copy.h"


template <typename Type>
class ordered_rarray : private rarray<Type>
// Resizable array that maintains ascending order of elements.
// Private inheritance to hide those functions that
// in general destroy the order.
{
public:
    explicit ordered_rarray(ulong n, ulong growq=0)
        : rarray<Type>(n, growq)
    { ; }

//    explicit ordered_rarray(const rarray<Type> &v)
//        : rarray<Type>(v.n(), v.gq_)
//    {
//        acopy(v.data(), n_, x_);
//        ::quick_sort(x_, n_);
//    }

    ~ordered_rarray()  { ; }

private:
    ordered_rarray & operator = (const ordered_rarray &);  // forbidden


public:
    using rarray<Type>::x_;
    using rarray<Type>::n_;
    using rarray<Type>::num;
    using rarray<Type>::data;
    using rarray<Type>::size;
    using rarray<Type>::remove_last;
    using rarray<Type>::remove_first;
    using rarray<Type>::remove_at;
    using rarray<Type>::insert_at;
    using rarray<Type>::append;

    ulong search(const Type & v)  const
    // Return index of first element in that is == v
    // Return n_ if there is no such element
    { return ::bsearch(x_, n_, v); }

    ulong search_geq(const Type & v)  const
    // Return index of first element in that is >= v
    // Return n_ if there is no such element
    { return ::bsearch_geq<Type>(x_, n_, v); }

    ulong insert(const Type & v)
    // Insert v so that ascending order is kept.
    // Return size, zero on rarray overflow.
    {
        if ( 0==n_ )  { return append(v); }

        ulong j = search_geq(v);
        if ( j>=n_ )  return  append(v);
        else          return  insert_at(v, j);
    }

    ulong insert_uniq(const Type & v)
    // Insert v so that ascending order is kept.
    // Don't insert if element already in array.
    // Return size, zero on rarray overflow.
    {
        if ( 0==n_ )  { return append(v); }

        ulong j = search_geq(v);
        if ( j>=n_ )  return  append(v);
        else
        {
            if ( (x_[j] = v) )  return 0;
            return  rarray<Type>::insert_at(v, j);
        }
    }
};
// -------------------------


#endif // !defined HAVE_ORDEREDRARRAY_H__
