#if !defined  HAVE_PRIORITYQUEUE1_H__
#define       HAVE_PRIORITYQUEUE1_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "realloc.h"

#include "aux0/swap.h"


//<<
#if  1
// next() is the one with the smallest key
// i.e.  extract_next()  is  extract_min()
#define _CMP1_ <
#define _CMPEQ1_ <=
#else
// next() is the one with the biggest key
// i.e.  extract_next()  is  extract_max()
#define _CMP1_ >
#define _CMPEQ1_ >=
#endif
//>>

template <typename Type1>
class priority_queue1
// Priority queue with just the time as data (no extra "event data").
// Can grow dynamically.
{
public:
    Type1 *t1_;  // time:   t1[1..s]  one-based array!
    ulong s_;    // allocated size (# of elements)
    ulong n_;    // current number of events
    ulong gq_;   // grow gq elements if necessary, 0 for "never grow"

public:
    priority_queue1(ulong n, ulong growq=0)
    {
        s_ = n;
        t1_ = new Type1[s_] - 1;

        n_ = 0;
        gq_ = growq;
    }

    ~priority_queue1()
    {
        delete [] (t1_+1);
    }

    ulong num()  const  { return n_; }

    bool get_next(Type1 &t)  const
    {
        if ( n_ == 0 )  return false;
        t = t1_[1];
        return true;
    }

    bool extract_next(Type1 &t)
    // Extract next event.
    {
        if ( n_ == 0 )  return false;

        t = t1_[1];
        t1_[1] = t1_[n_];
        --n_;
        heapify(1);

        return true;
    }

    bool insert(const Type1 &t)
    // Insert time t.
    // Return true if successful,
    //   else false (space exhausted and growth disabled).
    {
        if ( n_ >= s_ )
        {
            if ( 0==gq_ )  return false;  // growing disabled
            grow();
        }

        ++n_;
        ulong j = n_;
        while ( j > 1 )
        {
            ulong k = (j>>1);  // k==parent(j)
            if ( t1_[k] _CMPEQ1_ t )  break;
            t1_[j] = t1_[k];
            j = k;
        }
        t1_[j] = t;

        return true;
    }

    void reschedule_next(Type1 t)
    {
        t1_[1] = t;
        heapify(1);
    }


private:
    void heapify(ulong k)
    {
        ulong m = k;

    hstart:
        ulong l = (k<<1); // left(k);
        ulong r = l + 1;  // right(k);
        if ( (l <= n_) && (t1_[l] _CMP1_ t1_[k]) )  m = l;
        if ( (r <= n_) && (t1_[r] _CMP1_ t1_[m]) )  m = r;

        if ( m != k )
        {
            swap2(t1_[k], t1_[m]);
//            heapify(m);
            k = m;
            goto hstart;  // tail recursion
        }
    }

    void grow()
    {
        ulong ns = s_ + gq_;  // new size
        t1_ = ReAlloc<Type1>(t1_+1, ns, s_) - 1;
        s_ = ns;
    }
};
// -------------------------

#undef _CMP1_
#undef _CMPEQ1_


#endif  // !defined HAVE_PRIORITYQUEUE1_H__
