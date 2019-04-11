#if !defined  HAVE_SETPART_RGS_GRAY_H__
#define       HAVE_SETPART_RGS_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-setpart-rgs.h"
#include "comb/comb-print.h"

#include "sort/minmaxmed23.h"  // max2()

#include "fxttypes.h"


class setpart_rgs_gray
// Set partitions of the n-set as restricted growth strings (RGS):
// strings s[0, 1, ..., n-1] such that s[k] <= max(s[0], s[1], ..., s[k-1]) + 1.
// Minimal-change order for set partitions,
//  note that the RGS can change in more than one position.
{
public:
    ulong n_;    // Number of elements of set (set = {1,2,3,...,n})
    ulong *m_;   // m[k+1] = max(s[0], s[1],..., s[k]) + 1
    ulong *s_;   // RGS
    ulong *d_;   // direction with recursion (+1 or -1)

private:  // have pointer data
    setpart_rgs_gray(const setpart_rgs_gray&);  // forbidden
    setpart_rgs_gray & operator = (const setpart_rgs_gray&);  // forbidden

public:
    explicit setpart_rgs_gray(ulong n, int dr0=+1)
    // dr0=+1  ==> start with partition  {{1,2,3,...,n}}
    // dr0=-1  ==> start with partition  {{1},{2},{3},...,{n}}}
    {
        n_ = n;
        m_ = new ulong[n_+1];
        m_[0] = ~0UL;    // sentinel m[0] = infinity
        s_ = new ulong[n_];
        d_ = new ulong[n_];
        first(dr0);
    }

    ~setpart_rgs_gray()
    {
        delete [] m_;
        delete [] s_;
        delete [] d_;
    }

    void first(int dr0)
    {
        const ulong n = n_;
        const ulong dd = (dr0 >= 0 ? +1UL : -1UL);
        if ( dd==1 )
        {
            for (ulong k=0; k<n; ++k)  s_[k] = 0;
            for (ulong k=1; k<=n; ++k)  m_[k] = 1;
        }
        else
        {
            for (ulong k=0; k<n; ++k)  s_[k] = k;
            for (ulong k=1; k<=n; ++k)  m_[k] = k;
        }

        for (ulong k=0; k<n; ++k)  d_[k] = dd;
    }


    bool next()
    {
        ulong k = n_;
        do  { --k; }  while ( (s_[k] + d_[k]) > m_[k] );  // <0 or >max

        if ( k == 0 )  return false;

        s_[k] += d_[k];
        m_[k+1] = max2(m_[k], s_[k]+1);

        while ( ++k<n_ )
        {
            const ulong d = d_[k] = -d_[k];
            const ulong mk = m_[k];
#if 1
            s_[k] = ( (d==1UL) ? 0 : mk );
//            m_[k+1] = max2(mk, s_[k]+1);
            m_[k+1] = mk + (d!=1UL);  // == max2(mk, s_[k]+1)

#else  // slower:

            if ( d==1UL )
            {
                s_[k] = 0;
                m_[k+1] = mk;
            }
            else
            {
                s_[k] = mk;
                m_[k+1] = mk + 1;
            }
#endif
        }

        return true;
    }

    const ulong* data()  const  { return s_; }
    ulong num_sets()  const  { return ( n_ ? m_[n_] : 0 ); }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }

    void print()  const;  // used in fxtbook

    void print_set(const char *bla, ulong off=1)  const
    { print_setpart(bla, data(), n_, num_sets(), off); }


    bool OK()  const
    { return is_setpart_rgs(data(), n_); }
};
// -------------------------


#endif  // !defined HAVE_SETPART_RGS_GRAY_H__
