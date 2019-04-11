#if !defined HAVE_RARRAY_H__
#define      HAVE_RARRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "realloc.h"
#include "sort/sort.h"  // quick_sort()
#include "sort/unique.h"  // unique()



template <typename Type>
class rarray
// Array that grows in adjustable steps when necessary
// rarray := "Resizing array"
// All operations maintain the relative order between elements
{
public:
    Type  *x_;  // data
    ulong  s_;  // size
    ulong  n_;  // position of next write, top entry @ n-1
    ulong  gq_; // grow gq elements if necessary, 0 for "never grow"

public:
    explicit rarray(ulong n, ulong growq=0)
    {
        s_ = n;
        x_ = new Type[s_];
        n_ = 0;  // rarray is empty
        gq_ = growq;
    }

    ~rarray()  { delete [] x_; }

private:
    rarray & operator = (const rarray &);  // forbidden

public:
    Type * data()  { return x_; }

    ulong num()  const
    // Return number of entries.
    { return n_; }

    ulong size()  const
    // Return number of allocated entries.
    { return s_; }


    ulong append(const Type & z)
    // Return size of rarray, zero on rarray overflow
    {
        if ( n_ >= s_ )
        {
            if ( 0==gq_ )  return 0;  // overflow
            grow();
        }

        x_[n_] = z;
        ++n_;

        return  s_;
    }

    ulong remove_last()
    {
        ulong ret = n_;
        if ( n_!=0 )  --n_;
        return  ret;
    }

    ulong prepend(const Type & z)
    // Return size of rarray, zero on rarray overflow.
    {
        if ( n_ >= s_ )
        {
            if ( 0==gq_ )  return 0;  // overflow
            grow();
        }

        for (ulong k=n_; k!=0; --k)  x_[k] = x_[k-1];  // shift right
        x_[0] = z;
        ++n_;

        return  s_;
    }

    ulong remove_first()
    // Return how many elements were there before remove.
    // Zero indicates error.
    {
        ulong ret = n_;
        if ( n_!=0 )  --n_;
        for (ulong k=0; k<n_; ++k)  x_[k] = x_[k+1];  // shift left
        return  ret;
    }


    ulong search(const Type& x, ulong k=0)  const
    {
        for (  ; k<n_; ++k)  if ( x_[k]==x )  return k;
        return  s_;
    }


    void sort()  { ::quick_sort(x_, n_); }
    void unique()  { sort();  ::unique(x_, n_); }

    ulong insert_at(const Type & v, ulong j)
    // Return size of rarray.
    // Return zero on error: (rarray overflow or access beyond range)
    // (i.e. no action unless  0<=j<=n_)
    {
        if ( j >= n_ )  return 0;  // beyond bounds

        if ( n_ >= s_ )
        {
            if ( 0==gq_ )  return 0;  // overflow
            grow();
        }

        for (ulong k=n_; k!=j; --k)  x_[k] = x_[k-1];
        x_[j] = v;
        ++n_;

        return  s_;
    }

    ulong remove_at(ulong j)
    // Return how many elements were there before remove.
    // Zero indicates error.
    {
        ulong ret = n_;
        if ( j>=n_ )  return 0;
        --n_;
        for (ulong k=j; k<n_; ++k)  x_[k] = x_[k+1];
        return ret;
    }


private:
    void grow()
    {
        ulong ns = s_ + gq_;  // new size
        x_ = ReAlloc<Type>(x_, ns, s_);
        s_ = ns;
    }
};
// -------------------------



#endif // !defined HAVE_RARRAY_H__
