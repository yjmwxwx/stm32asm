#if !defined  HAVE_DEQUE_H__
#define       HAVE_DEQUE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "realloc.h"
#include "perm/rotate.h"  // rotate_left()


template <typename Type>
class deque
// deque := double-ended queue
// Can grow dynamically
{
public:
    Type *x_;   // data (ring buffer)
    ulong s_;   // allocated size (# of elements)
    ulong n_;   // current number of entries in buffer
    ulong fpos_;  // position of first element in buffer
    // insert_first() will write to (fpos-1)%n
    ulong lpos_;  // position of last element in buffer plus one
    // insert_last() will write to  lpos,  n==(lpos-fpos) (mod s)
    // entries are at [fpos, ..., lpos-1]  (range may be empty)

    ulong  gq_;  // grow gq elements if necessary, 0 for "never grow"

private:  // have pointer data
    deque(const deque&);  // forbidden
    deque & operator = (const deque&);  // forbidden

public:
    explicit deque(ulong n, ulong growq=0)
    {
        s_ = n;
        x_ = new Type[s_];
        n_ = 0;
        fpos_ = 0;
        lpos_ = 0;
        gq_ = growq;
    }

    ~deque()  { delete [] x_; }

    ulong num()  const  { return n_; }

    ulong insert_first(const Type &z)
    // Return number of entries after insertion.
    // Zero is returned on failure
    //   (i.e. space exhausted and 0==gq_)
    {
        if ( n_ >= s_ )
        {
            if ( 0==gq_ )  return 0;  // growing disabled
            grow();
        }

        --fpos_;
        if ( fpos_ == -1UL )  fpos_ = s_ - 1;
        x_[fpos_] = z;
        ++n_;
        return  n_;
    }


    ulong insert_last(const Type &z)
    // Return number of entries after insertion.
    // Zero is returned on failure
    //   (i.e. space exhausted and 0==gq_)
    {
        if ( n_ >= s_ )
        {
            if ( 0==gq_ )  return 0;  // growing disabled
            grow();
        }

        x_[lpos_] = z;
        ++lpos_;
        if ( lpos_>=s_ )  lpos_ = 0;
        ++n_;
        return  n_;
    }


    ulong extract_first(Type & z)
    // Return number of elements before extract.
    // Return 0 if extract on empty deque was attempted.
    {
        if ( 0==n_ )  return 0;
        z = x_[fpos_];
        ++fpos_;
        if ( fpos_ >= s_ )  fpos_ = 0;
        --n_;
        return  n_ + 1;
    }

    ulong extract_last(Type & z)
    // Return number of elements before extract.
    // Return 0 if extract on empty deque was attempted.
    {
        if ( 0==n_ )  return 0;
        --lpos_;
        if ( lpos_ == -1UL )  lpos_ = s_ - 1;
        z = x_[lpos_];
        --n_;
        return  n_ + 1;
    }


    ulong read_first(Type & z)  const
    // Read (but don't remove) first entry.
    // Return number of elements (i.e. on error return zero).
    {
        if ( 0==n_ )  return 0;
        z = x_[fpos_];
        return n_;
    }

    ulong read_last(Type & z)  const
    // Read (but don't remove) last entry.
    // Return number of elements (i.e. on error return zero).
    {
        return  read(n_-1, z);  // ok for n_==0
    }

    ulong read(ulong k, Type & z)  const
    // Read entry k (that is, [(fpos_ + k)%s_]).
    // Return 0 if k>=n_ else return k+1
    {
        if ( k>=n_ )  return 0;
        ulong j = fpos_ + k;
        if ( j>=s_ )  j -= s_;
        z = x_[j];
        return  k + 1;
    }

private:
    void grow()
    {
        ulong ns = s_ + gq_;  // new size
        // Move read-position to zero:
        rotate_left(x_, s_, fpos_);
        x_ = ReAlloc<Type>(x_, ns, s_);
        fpos_ = 0;
        lpos_ = n_;
        s_ = ns;
    }
};
// -------------------------



#endif  // !defined HAVE_DEQUE_H__
