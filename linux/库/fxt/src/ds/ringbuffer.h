#if !defined  HAVE_RINGBUFFER_H__
#define       HAVE_RINGBUFFER_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
class ringbuffer
// Implementation of a ring buffer
{
public:
    Type *x_;   // data (ring buffer)
    ulong s_;   // allocated size (# of elements)
    ulong n_;   // current number of entries in buffer
    ulong wpos_;  // next position to write in buffer
    ulong fpos_;  // first position to read in buffer

private:  // have pointer data
    ringbuffer(const ringbuffer&);  // forbidden
    ringbuffer & operator = (const ringbuffer&);  // forbidden

public:
    explicit ringbuffer(ulong n)
    {
        s_ = n;
        x_ = new Type[s_];
        n_ = 0;
        wpos_ = 0;
        fpos_ = 0;
    }

    ~ringbuffer()  { delete [] x_; }

    ulong num()  const  { return n_; }

    void insert(const Type &z)
    {
        x_[wpos_] = z;
        if ( ++wpos_>=s_ )  wpos_ = 0;
        if ( n_ < s_ )  ++n_;
        else  fpos_ =  wpos_;
    }

    ulong read(ulong k, Type &z)  const
    // Read entry k (that is, [(fpos_ + k)%s_]).
    // Return 0 if k>=n, else return k+1.
    {
        if ( k>=n_ )  return 0;
        ulong j = fpos_ + k;
        if ( j>=s_ )  j -= s_;
        z = x_[j];
        return  k + 1;
    }
};
// -------------------------


#endif  // !defined HAVE_RINGBUFFER_H__
