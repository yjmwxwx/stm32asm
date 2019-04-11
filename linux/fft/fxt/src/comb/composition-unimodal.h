#if !defined HAVE_COMPOSITION_UNIMODAL_H__
#define      HAVE_COMPOSITION_UNIMODAL_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


//#include "comb/comb-print.h"
#include "comb/print-composition-by-sorts.h"
#include "comb/print-composition-unimodal.h"

#include "fxttypes.h"


class composition_unimodal
// Strongly unimodal compositions.
// Representation as list of parts in weakly ascending order,
//   with each part except for the last of 2 sorts and
//   no repeated parts of the same sort.
// Cf. OEIS sequence A059618.
{
public:
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
    ulong *s_;  // sorts of parts
    ulong n_;   // integer compositions of n
    ulong m_;   // current composition has m parts

private:  // have pointer data
    composition_unimodal(const composition_unimodal&);  // forbidden
    composition_unimodal & operator = (const composition_unimodal&);  // forbidden

public:
    explicit composition_unimodal(ulong n)
    {
        n_ = n;

        a_ = new ulong[n_+1];  // fixme: somewhat wasteful
        s_ = new ulong[n_+1];

        first();
    }

    ~composition_unimodal()
    {
        delete [] a_;
        delete [] s_;
    }

    const ulong * data()  const  { return  a_ + 1; }
    const ulong * sdata()  const  { return  s_ + 1; }

    ulong num_parts()  const  {  return m_; }

    void first()
    {
        a_[0] = 0;  // unused
        s_[0] = 0;  // unused
        if ( n_ == 0 )  { m_=0;  return; }

        ulong p = 0;
        ulong s = n_;
        ulong k = 1;
        ulong rq = 1;
        while ( s >= (p += rq) )
        {
            a_[k] = p;
            s -= p;
            rq = 1 - rq;
            s_[k] = rq;
            k += 1;
        }

        k -= 1;


        const ulong t = (a_[k] += s);
        if ( a_[k] == a_[k-1] )
        {
            k -= 1;
            a_[k] += t;
        }
        s_[k] = 0;

        m_ = k;

    }


    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        const ulong s1 = s_[m_-1];
        s_[m_-1] = 1 - s1;
        s_[m_] = 0;

        ulong p = a_[m_-1] + 1;
        ulong s;
        if ( s1 == 1 )
        {
            s = a_[m_] + a_[m_-1];
            m_ -= 1;
        }
        else
        {
            s = a_[m_];
        }

        ulong x = a_[m_-1];
        ulong rq = 0;

        while ( s >= (p += rq) )
        {
            a_[m_] = p;
            s -= p;

//            rq = (p==a_[m_-1]);
            rq = (p==x);
            x = p;
            s_[m_] = rq;

            m_ += 1;
        }

        m_ -= 1;
        s_[m_] = 0;

        const ulong t = (a_[m_] += s);
        if ( a_[m_] == a_[m_-1] )
        {
            m_ -= 1;
            a_[m_] += t;
        }

        return  m_;
    }


    bool OK()  const
    {
        if ( m_==0 )  return true;

        if ( s_[m_] != 0 )  return false;
        if ( a_[m_] == a_[m_-1] )  return false;

        for (ulong j=2; j<=m_; ++j)  // weakly ascending?
            if ( a_[j] < a_[j-1] )  return false;

        ulong s = 0;  // sum of parts == n  ?
        for (ulong j=1; j<=m_; ++j)  s += a_[j];
        if ( s != n_ )  return false;

        for (ulong j=2; j<=m_; ++j)
            if ( a_[j] == a_[j-1] )
                if ( a_[j] == a_[j-2] )
                    return false;

        return true;
    }

    void print_with_sorts(const char *bla)  const
    { print_composition_with_sorts(bla, data(), sdata(), num_parts() ); }

    void print(const char *bla)  const
    { print_composition_unimodal(bla, data(), sdata(), num_parts() ); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_UNIMODAL_H__
