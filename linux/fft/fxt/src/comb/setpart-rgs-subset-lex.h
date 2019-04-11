#if !defined  HAVE_SETPART_RGS_SUBSET_LEX_H__
#define       HAVE_SETPART_RGS_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-setpart-rgs.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


// Cf. comb/dyck-rgs-subset-lex.h for RGS of Dyck words in subset-lex order.
// Cf. comb/catalan-subset-lex.h for Catalan RGS in subset-lex order.


#define SETPART_RGS_SUBSET_LEX_SC  // whether to allow n<=1
// this gives a small slowdown

class setpart_rgs_subset_lex
// Set partitions of the n-set as restricted growth strings (RGS):
// strings a[0, 1, ..., n-1] such that a[k] <= max(a[0], a[1], ..., a[k-1]) + 1.
// Subset-lex order.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
    ulong *a_;  // digits of the RGS
    ulong *m_;  // maximum + 1 in prefix (only maitained for m[0, 1, ..., tr])
    ulong tr_;  // current track
    ulong n_;   // Number of digits in RGS

private:  // have pointer data
    setpart_rgs_subset_lex(const setpart_rgs_subset_lex&);  // forbidden
    setpart_rgs_subset_lex & operator = (const setpart_rgs_subset_lex&);  // forbidden

public:
    explicit setpart_rgs_subset_lex(ulong n)
    {
        n_ = n;

        a_ = new ulong[n_+ 1 + (n_==0)];  // incl. sentinel
        a_[0] = +1;  // sentinel !=0  to catch scan to the left
        ++a_;  // nota bene
        if ( n_==0 )  a_[0] = 0;

        m_ = new ulong[n_ + 1 + (n_==0)];  // incl. write-only at right
        m_[n_] = 0;  // arbitrary
        if ( n_==0 )  m_[0] = 1;

        first();
    }

    ~setpart_rgs_subset_lex()
    {
        --a_;
        delete [] a_;
        delete [] m_;
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  m_[k] = 1;
        tr_ = 1;

        // make things work for n <= 1:
        if ( n_ <= 1 )  tr_ = 0;
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        tr_ = n_ - 1;
        // make things work for n <= 1:
        if ( n_==0 )
        {
            tr_ = 0;
            a_[0] = 1;
        }
        if ( n_>=2 )  a_[tr_] = 1;
    }


    bool next()
    {
        ulong j = tr_;
        if ( a_[j] < m_[j] )   // easy case 1: can increment track
        {
#ifdef SETPART_RGS_SUBSET_LEX_SC
            if ( n_ <= 1 )  return false;
#endif
            a_[j] += 1;
            return true;
        }

        const ulong j1 = j + 1;
        if ( j1 < n_ )  // easy case 2: can attach
        {
            m_[j1] = m_[j] + 1;
            a_[j1] = +1;
            tr_ = j1;
            return true;
        }

        a_[j] = 0;
        m_[j] = m_[j-1];

        // Find nonzero track to the left:
        do  { --j; }  while ( a_[j] == 0 );  // can read sentinel

        if ( (long)j < 0 )  return false;  // current is last

        if ( a_[j] == m_[j] )  m_[j+1] = m_[j];
        a_[j] -= 1;

        ++j;
        a_[j] = 1;
        tr_ = j;
        return true;
    }

    bool prev()
    {
#ifdef SETPART_RGS_SUBSET_LEX_SC
        if ( n_<=1 )  return false;
#endif

        ulong j = tr_;
        if ( a_[j] > 1 )   // easy case 1: can decrement track
        {
            a_[j] -= 1;
            return true;
        }

        const ulong aj = a_[j];  // zero or one
        a_[j] = 0;
        --j;
        if ( a_[j] == m_[j] )  // move track to the left
        {
            --tr_;
            return true;
        }

        if ( j==0 )  // current or next is last
        {
            if ( aj == 0 )  return false;
            return true;
        }

        a_[j] += 1;
        if ( a_[j] == m_[j] )  m_[j+1] = m_[j] + 1;

        const ulong m1 = m_[j+1];
        for (ulong i=j+2; i<n_; ++i)  m_[i] = m1;

        tr_ = n_ - 1;
        m_[tr_] = m1;
        a_[tr_] = m_[tr_];
        return true;
    }

    const ulong *data()  const  { return a_; }


    ulong num_sets()  const
    {
        if ( n_==0 )  return 0;
#if 1
        ulong ns = m_[tr_];
        if ( a_[tr_] >= ns )  ns = a_[tr_] + 1;
        return  ns;
#else
        ulong ns = 0;
        for (ulong j=0; j<n_; ++j)
            if ( a_[j] > ns )  ns = a_[j];
        return  ns + 1;
#endif
    }


    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_vec(bla, data(), n_, dfz); }

    void print_sets(const char *bla, ulong off=1)  const
    { print_setpart(bla, data(), n_, num_sets(), off); }


    bool OK()  const
    {
        if ( ! is_setpart_rgs( data(), n_) )  return false;

        if ( tr_ != 0 )  // prefix maxima m[0,1,2,...,tr_] OK?
        {
            ulong mx = 0;
            for (ulong j=0; j<=tr_; ++j)
            {
                if ( m_[j] != mx+1 )  return false;
                mx += ( a_[j] > mx );
            }
        }

        return true;
    }

};
// -------------------------

#endif  // !defined HAVE_SETPART_RGS_SUBSET_LEX_H__
