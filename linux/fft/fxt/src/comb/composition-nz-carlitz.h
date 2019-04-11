#if !defined HAVE_COMPOSITION_NZ_CARLITZ_H__
#define      HAVE_COMPOSITION_NZ_CARLITZ_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"
#include "fxttypes.h"


class composition_nz_carlitz
// Compositions of n into positive parts, such that
// adjacent parts are different.  Lexicographic order.
// Cf. OEIS sequence A003242.
{
public:
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts

private:  // have pointer data
    composition_nz_carlitz(const composition_nz_carlitz&);  // forbidden
    composition_nz_carlitz & operator = (const composition_nz_carlitz&);  // forbidden

public:
    explicit composition_nz_carlitz(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+1];
        first();
    }

    ~composition_nz_carlitz()
    {
        delete [] a_;
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  {  return m_; }


    void first()
    {
        a_[0] = 0;  // sentinel for comparision to left in next()

        if ( n_ <= 2 )
        {
            m_ = ( n_ != 0 );
            if ( n_ != 0 )  a_[1] = n_;
            return;
        }

        m_ = write_tail(n_, 1);
    }


private:
    ulong write_tail(ulong z, ulong k)
    {
        while ( z>=3 )  // put 1, 2, 1, 2, 1, 2, ...
        {
            a_[k] = 1;
            a_[k+1] = 2;
            z -= 3;
            k += 2;
        }

        if ( z )
        {
            a_[k] = 1;
            z -= 1;
            a_[k-1] += z;
        }
        else  k -= 1;

        return  k;
    }


public:
    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    // the position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        ulong x = a_[m_-2];  // may read sentinel a[0]==0
        ulong y = a_[m_-1] + 1;
        ulong z = a_[m_] - 1;

        if ( z==0 )  // last part was ==1
        {
            if ( y != x )  // can increase second last
            {
                m_ -= 1;
                a_[m_] = y;
            }
            else  // need to increase third last
            {
                x += 1;
                y -= 1;

                const ulong w = a_[m_-3];
                if ( x == w )
                {
                    x += 1;
                    y -= 1;
                }

                a_[m_-2] = x;

                if ( y >= 3 )
                {
                    m_ = write_tail(y, m_-1);
                }
                else
                {
                    m_ -= 1;
                    a_[m_] = y;
                }
            }

            return  m_;
        }


        if ( z == y )
        {
            if ( z == 2 )
            {
                y += 1;
                z -= 1;
            }
        }

        if ( y == x )
        {
            y += 1;
            z -= 1;

            if ( z == 0 )
            {
                m_ -= 1;
                a_[m_] = y;
                return  m_;
            }
        }

        a_[m_-1] = y;


        if ( z == 2 )
        {
            a_[m_] = z;
        }
        else
        {
            m_ = write_tail(z, m_);
        }

        return  m_;
    }


    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<m_; ++j)  // check that adjacent part differ
            if ( a_[j] == a_[j+1] )  return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_CARLITZ_H__
