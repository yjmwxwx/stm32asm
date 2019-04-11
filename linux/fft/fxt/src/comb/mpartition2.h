#if !defined HAVE_MPARTITION2_H__
#define      HAVE_MPARTITION2_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

//#define MPARTITION2_FIXARRAYS
// slight speedup

class mpartition2
// Partitions into m parts.
// Representation as list of parts in weakly ascending order.
// Cf. OEIS sequence A008284.
// Same functionality as class mpartition, this
//   implementation avoids the auxiliary array s[].
{
public:
#ifndef MPARTITION2_FIXARRAYS
    ulong *x_;  // partition: x[1] + x[2] + ... + x[m] = n
#else
    ulong x_[128];
#endif
    ulong n_;   // integer partitions of n  (must have n>0)
    ulong m_;   // ... into m parts  (must have 0<m<=n)

private:  // have pointer data
    mpartition2(const mpartition2&);  // forbidden
    mpartition2 & operator = (const mpartition2&);  // forbidden

public:
    explicit mpartition2(ulong n, ulong m)
    // Must have n >= 1 and 1 <= m <= n.
    {
        n_ = n;
        m_ = m;
#ifndef MPARTITION2_FIXARRAYS
        x_ = new ulong[m_+1];
#endif
        first();
    }

    ~mpartition2()
    {
#ifndef MPARTITION2_FIXARRAYS
        delete [] x_;
#endif
    }

    const ulong * data()  const  { return x_+1; }

    void first()
    {
        x_[0] = 0;  // sentinel
        for (ulong k=1; k<m_; ++k)  x_[k] = 1;
        x_[m_] = n_ - m_ + 1;
    }

    bool next()
    {
        ulong u = x_[m_];  // last element
        ulong k = m_;
        ulong s = u;
        while ( --k )
        {
            s += x_[k];
            if ( x_[k] + 2 <= u )  break;
        }

        if ( k==0 )  return false;  // current is last

        ulong f = x_[k] + 1;
        while ( k < m_ )
        {
            x_[k] = f;
            s -= f;
            ++k;
        }
        x_[m_] = s;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_MPARTITION2_H__
