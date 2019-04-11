#if !defined HAVE_STACK_H__
#define      HAVE_STACK_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014, 2015, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "realloc.h"


template <typename Type>
class stack
{
public:
    Type  *x_;  // data
    ulong  s_;  // size
    ulong  p_;  // stack pointer (position of next write), top entry @ p-1
    ulong  gq_;  // grow by gq elements if necessary, 0 for "never grow"

public:
    explicit stack(ulong n, ulong growq=0)
    {
        s_ = n;
        x_ = new Type[s_];  // fixme: need default constructor for Type
        p_ = 0;  // stack is empty
        gq_ = growq;
    }

    ~stack()  { delete [] x_; }


private:
    stack(const stack&);  // forbidden
    stack& operator = (const stack&);  // forbidden


public:
    ulong num()  const  { return p_; }  // Return number of entries.

    ulong push(Type z)
    // Add element z on top of stack.
    // Return size of stack, zero on stack overflow.
    // If gq_ is nonzero the stack grows if needed.
    {
        if ( p_ >= s_ )
        {
            if ( 0 == gq_ )  return 0;  // overflow
            grow();
        }

        x_[p_] = z;
        ++p_;

        return  s_;
    }

    ulong pop(Type &z)
    // Retrieve top entry and remove it.
    // Return number of entries before removing element.
    // If empty return zero and leave z undefined.
    {
        ulong ret = p_;
        if ( 0 != p_ )  { --p_;  z = x_[p_]; }
        return  ret;
    }

    ulong pop()
    // Drop top entry.
    // Return number of entries before removing element.
    // If empty return zero.
    {
        ulong ret = p_;
        if ( 0 != p_ )  --p_;
        return  ret;
    }

    ulong poke(Type z)
    // Modify top entry.
    // Return number of entries.
    // If empty return zero and do nothing.
    {
        if ( 0 != p_ )  x_[p_-1] = z;
        return p_;
    }

    ulong peek(Type &z)  const
    // Read top entry, without removing it.
    // Return number of entries.
    // If empty return zero and leave z undefined.
    {
        if ( 0 != p_ )  z = x_[p_-1];
        return p_;
    }

    ulong peek_at(ulong j, Type &z)  const
    // Read entry x[j], without removing anything.
    // Return number of entries.
    // If j is out of range return zero and leave z undefined.
    {
        if ( j >= p_ )  return 0;
        z = x_[j];
        return p_;
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



#endif  // !defined HAVE_STACK_H__
