#if !defined  HAVE_SETPART_P_RGS_LEX_H__
#define       HAVE_SETPART_P_RGS_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "sort/minmaxmed23.h"  // max2()
#include "comb/is-setpart-rgs.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class setpart_p_rgs_lex
// Set partitions of the n-set into p parts (where 2<=p<=n)
// as restricted growth strings (RGS).
// Lexicographic order.
// Cf. OEIS sequence A008277.
{
public:
    ulong n_;    // Number of elements of set (set = {1,2,3,...,n})
    ulong p_;    // Exactly p subsets
    ulong *m_;   // m[k+1] = max(s[0], s[1],..., s[k]) + 1
    ulong *s_;   // RGS

private:  // have pointer data
    setpart_p_rgs_lex(const setpart_p_rgs_lex&);  // forbidden
    setpart_p_rgs_lex & operator = (const setpart_p_rgs_lex&);  // forbidden

public:
    explicit setpart_p_rgs_lex(ulong n, ulong p)
    {
        n_ = n;
        m_ = new ulong[n_+1];
        m_[0] = ~0UL;    // sentinel: m[0] = infinity
        s_ = new ulong[n_];
        first(p);
    }

    ~setpart_p_rgs_lex()
    {
        delete [] m_;
        delete [] s_;
    }

    void first(ulong p)
    // Must have  1<=p<=n
    {
        for (ulong k=0; k<n_; ++k)  s_[k] = 0;
        for (ulong k=n_-p+1, j=1; k<n_; ++k, ++j)  s_[k] = j;

        for (ulong k=1; k<=n_; ++k)  m_[k] = s_[k-1] + 1;
        p_ = p;
    }

    bool next()
    {
        if ( p_ <= 1 )  return false;  // make things work for p==1

        ulong k = n_;
        bool q;
        do
        {
            --k;
            const ulong sk1 = s_[k] + 1;
            q = (sk1 > m_[k]);   // greater max
            q |= (sk1 >= p_);    // more than p parts
        }
        while ( q );

        if ( k == 0 )  return false;

        s_[k] += 1UL;
        ulong mm = m_[k];
        mm += ( s_[k] >= mm );
        m_[k+1] = mm;  // == max2(m_[k], s_[k]+1);

        while ( ++k < n_ )
        {
            s_[k] = 0;
            m_[k+1] = mm;
        }

        ulong p = p_;
        if ( mm < p )  // repair tail
        {
            do
            {
                m_[k] = p;
                --k;
                --p;
                s_[k] = p;
            }
            while ( m_[k] < p );
        }

        return true;
    }

    const ulong* data()  const  { return s_; }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_vec(bla, data(), n_, dfz); }

    void print_sets(const char *bla, ulong off=1)  const
    { print_setpart(bla, data(), n_, p_, off); }


    bool OK()  const
    {
        if ( n_ == 0 )  return true;

        if ( m_[n_] != p_ )  return false;

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


#endif  // !defined HAVE_SETPART_P_RGS_LEX_H__
