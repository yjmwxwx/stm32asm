#if !defined HAVE_RSET_H__
#define      HAVE_RSET_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "sort/unique.h"  // unique()
#include "sort/sort.h"  // quick_sort()

#include "aux1/copy.h"


template <typename Type>
class rset
// set that grows in adjustable steps when necessary
// rset := "Resizing set"
{
public:
    Type  *x_;  // data
    ulong  s_;  // size
    ulong  n_;  // position of next write, top entry @ n-1
    ulong  gq_; // grow gq elements if necessary, 0 for "never grow"

public:
    explicit rset(ulong n, ulong growq=0)
    {
        s_ = n;
        x_ = new Type[s_];
        n_ = 0;  // rset is empty
        gq_ = growq;
    }

    ~rset()  { delete [] x_; }


private:
    rset & operator = (const rset &);  // forbidden


public:
    Type * data()  { return x_; }

    ulong num()  const
    // Return number of entries
    { return n_; }

    ulong size()  const
    // Return number of allocated entries
    { return s_; }


    ulong insert(const Type & z)
    // Insert element v (append v).
    // Return size of rset, zero on rset overflow
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

    ulong search(const Type & x, ulong k=0)  const
    {
        for (  ; k<n_; ++k)  if ( x_[k]==x )  return k;
        return  s_;
    }


    void sort()  { ::quick_sort(x_, n_); }
    void unique()  { sort();  ::unique(x_, n_); }


    ulong remove_at(ulong j)
    // Return how many elements were there before remove.
    // Zero indicates error.
    {
        ulong ret = n_;
        if ( j>=n_ )  return 0;
        --n_;
        x_[j] = x_[n_];
        return ret;
    }

    ulong remove(const Type & z)
    {
        ulong j = search(z);
        if ( j<n_ )  remove_at(j);
        return j;
    }

private:
    void grow()
    {
        ulong ns = s_ + gq_;  // new size
        Type *nx = new Type[ns];
        acopy(x_, nx, s_);
        delete [] x_;
        x_ = nx;
        s_ = ns;
    }
};
// -------------------------



#endif // !defined HAVE_RSET_H__
