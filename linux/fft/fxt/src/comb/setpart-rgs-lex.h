#if !defined  HAVE_SETPART_RGS_LEX_H__
#define       HAVE_SETPART_RGS_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "sort/minmaxmed23.h"  // max2()
#include "comb/is-setpart-rgs.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class setpart_rgs_lex
// Set partitions of the n-set as restricted growth strings (RGS):
// strings s[0, 1, ..., n-1] such that s[k] <= max(s[0], s[1], ..., s[k-1]) + 1.
// Lexicographic order.
{
public:
    ulong n_;    // Number of elements of set (set = {1,2,3,...,n})
    ulong *m_;   // m[k+1] = max(s[0], s[1], ..., s[k]) + 1
    ulong *s_;   // RGS

private:  // have pointer data
    setpart_rgs_lex(const setpart_rgs_lex&);  // forbidden
    setpart_rgs_lex & operator = (const setpart_rgs_lex&);  // forbidden

public:
    explicit setpart_rgs_lex(ulong n)
    {
        n_ = n;
        m_ = new ulong[n_+1];
//        m_[0] = ~0UL;    // sentinel:  m[0] = infinity
        m_[0] = 1;    // sentinel:  m[0] = 1
        s_ = new ulong[n_];
        first();
    }

    ~setpart_rgs_lex()
    {
        delete [] m_;
        delete [] s_;
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  s_[k] = 0;
        for (ulong k=1; k<=n_; ++k)  m_[k] = 1;
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  s_[k] = k;
        for (ulong k=1; k<=n_; ++k)  m_[k] = k;
    }



    bool next()
    {
        if ( m_[n_] >= n_ )  return false;

        ulong k = n_;
        do  { --k; }  while ( (s_[k] + 1) > m_[k] );

//        if ( k == 0 )  return false;

        s_[k] += 1UL;
#if 0
        const ulong mm = m_[k+1] = max2(m_[k], s_[k]+1);
#else  // faster:
        ulong mm = m_[k];
        mm += (s_[k]>=mm);
        m_[k+1] = mm;  // == max2(m_[k], s_[k]+1)
#endif

        while ( ++k<n_ )
        {
            s_[k] = 0;
            m_[k+1] = mm;
        }

        return true;
    }

    bool prev()
    {
        if ( m_[n_] == 1 )  return false;

        ulong k = n_;
        do  { --k; }  while ( s_[k]==0 );

        s_[k] -= 1;
        ulong mm = m_[k+1] = max2(m_[k], s_[k]+1);

        while ( ++k<n_ )
        {
            s_[k] = mm;  // == m[k]
            ++mm;
            m_[k+1] = mm;
        }

        return true;
    }

    const ulong* data()  const  { return s_; }
    ulong num_sets()  const  { return ( n_ ? m_[n_] : 0 ); }


    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_vec(bla, data(), n_, dfz); }

    void print_sets(const char *bla, ulong off=1)  const
    { print_setpart(bla, data(), n_, num_sets(), off); }


    bool OK()  const
    {
        if ( ! is_setpart_rgs( data(), n_) )  return false;

        if ( n_ != 0 )  // prefix maxima in m[0,1,2,...,n_-1] OK?
        {
            ulong mx1 = 0;
            for (ulong j=0; j<n_; ++j)
            {
                mx1 += ( s_[j] >= mx1 );
                const ulong mj = m_[j+1];
                if ( mj != mx1 )  return false;
            }
        }

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_SETPART_RGS_LEX_H__
