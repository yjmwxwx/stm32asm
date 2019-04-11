#if !defined HAVE_MPARTITION_H__
#define      HAVE_MPARTITION_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

class mpartition
// Partitions into m parts.
// Representation as list of parts in weakly ascending order.
// Cf. OEIS sequence A008284.
// Same functionality as class mpartition2, which
//   avoids the auxiliary array s[].
{
public:
    ulong *x_;  // partition: x[1] + x[2] + ... + x[m] = n
    ulong *s_;  // aux: cumulative sums of x[]  (s[0]=0)
    ulong n_;   // integer partitions of n  (must have n>0)
    ulong m_;   // ... into m parts  (must have 0<m<=n)

private:  // have pointer data
    mpartition(const mpartition&);  // forbidden
    mpartition & operator = (const mpartition&);  // forbidden

public:
    explicit mpartition(ulong n, ulong m)
    // Must have n >= 1 and 1 <= m <= n.
    {
        n_ = n;
        m_ = m;
        x_ = new ulong[m_+1];
        s_ = new ulong[m_+1];
        first();
    }

    ~mpartition()
    {
        delete [] x_;
        delete [] s_;
    }

    const ulong * data()  const  { return x_+1; }

    void first()
    {
        x_[0] = 0;  // sentinel
        for (ulong k=1; k<m_; ++k)  x_[k] = 1;
        x_[m_] = n_ - m_ + 1;
        ulong s = 0;
        for (ulong k=0; k<=m_; ++k)  { s+=x_[k]; s_[k]=s; }
    }

    bool next()
    {
        ulong u = x_[m_];  // last element
        ulong k = m_;
        while ( --k )  { if ( x_[k] + 2 <= u )  break; }

        if ( k==0 )  return false;  // current is last

        ulong f = x_[k] + 1;
        ulong s = s_[k-1];
        while ( k < m_ )
        {
            x_[k] = f;
            s += f;
            s_[k] = s;
            ++k;
        }
        x_[m_] = n_ - s_[m_-1];
        // s_[m_] = n_;  // unchanged

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_MPARTITION_H__
