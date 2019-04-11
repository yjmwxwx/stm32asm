#if !defined  HAVE_COMPOSITION_NZ_I_SMOOTH_H__
#define       HAVE_COMPOSITION_NZ_I_SMOOTH_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-composition-nz.h"
#include "comb/is-smooth.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"

#include "fxttypes.h"


// define to track amount of work:
//#define COMPOSITION_NZ_I_SMOOTH_WRK  // default off


class composition_nz_i_smooth
// Internally smooth compositions:
// consecutive parts differ by at most 1.
// Lexicographic order.
// See OEIS sequence A034297.
{
public:
    ulong *a_;  // parts of the composition: a[1] + a[2] + ... + a[m] == n
    ulong n_;   // compositions of n
    ulong m_;   // number of parts in current composition

#ifdef COMPOSITION_NZ_I_SMOOTH_WRK    // track amount of work: (recursive calls)
    ulong wrk_;   // work with last call of next()
    ulong mwrk_;  // max work with last call of next() so far
    ulong twrk_;  // total work
    // it appears that  twrk / count approaches 1.66407...
#endif

private:  // have pointer data
    composition_nz_i_smooth(const composition_nz_i_smooth&);  // forbidden
    composition_nz_i_smooth & operator = (const composition_nz_i_smooth&);  // forbidden

public:
    explicit composition_nz_i_smooth(ulong n)
    {
        n_ = n;  // works for n==0

        a_ = new ulong[n_+2];
        a_[0] = n_ + 5;  // sentinel (big value)

        first();
    }

    ~composition_nz_i_smooth()
    { delete [] a_; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
#ifdef COMPOSITION_NZ_I_SMOOTH_WRK
        wrk_ = 0;  mwrk_=0;  twrk_ = 0;
#endif
    }


private:
    ulong easy3(ulong y, ulong z)
    // Handle cases [*, Y, Z] where  Y+Z <= 3
    {
        ulong s = y + z;

        if ( s==2 )
        {  // [*, 1, 1] --> [*, 2]
            a_[m_-1] = y + 1;
            m_ -= 1;
            return m_;
        }
        // here s==3

        ulong x = a_[m_-2];
        if ( z==1 ) // y==2
        {
            if ( x == 1 )
            {  // [*, X, 2, 1] --> [*, X, 1, 1]  (where X==1)
                a_[m_-2] = 2;
                a_[m_-1] = 1;
                return m_;
            }
            else
            {  // [*, X, 2, 1] --> [*, X, 3]  (where X==2 or X==3)
//                a_[m_-1] = y + 1;
                a_[m_-1] = 3;
                m_ -= 1;
                return m_;
            }
        }
        else  // z==2, y==1
        {  // [*, 1, 2] --> [*, 2, 1]
            a_[m_] = 1;  // == z-1
//            a_[m_-1] = y + 1;
            a_[m_-1] = 2;
            return m_;
        }
    }

private:
    ulong two_parts(ulong y, ulong z)
    // Handle two parts: called only once
    {
        if ( z == y + 1 )  // can move one unit left
        {  // [Y, Y+1] --> [Y+1, Y]
            z -= 1;
            a_[m_] = z;
            a_[m_-1] = y + 1;
            m_ -= (z==0);
            return m_;
        }
        else  // next has one part
        {  // [Y, Z] --> [Y+Z]
            a_[m_-1] = y + z;
            m_ = 1;
            return m_;
        }
    }

private:
    ulong try_write_tail(ulong j, ulong s, ulong p)
    // Try writing lex-min tail, starting from position j,
    // s is the sums to be distributed, p the part to be put.
    // Return last position written to or zero if there is no smooth tail.
    {
#ifdef COMPOSITION_NZ_I_SMOOTH_WRK
        wrk_ += 1;
        twrk_ += 1;
#endif

        a_[j] = p;
        if ( s==p )  return j;  // straight fit

        if ( p==0 )  return 0;

        if ( s > p )
        {
            s -= p;  // note modified
            ulong t;
            ulong w = p - 1;
            if ( w != 0 )
            {
                t = try_write_tail(j+1, s, w);  if ( t!=0 )  return t;
            }
            w = p+0;  t = try_write_tail(j+1, s, w);  if ( t!=0 )  return t;
            w = p+1;  t = try_write_tail(j+1, s, w);  if ( t!=0 )  return t;
        }
        return 0;
    }
public:

    ulong next()
    // Return number of parts.
    // Return 0 if current composition is last.
    {
        if ( m_ <= 1 )  return  0;  // current is last

#ifdef COMPOSITION_NZ_I_SMOOTH_WRK
        wrk_ = 0;
#endif
        ulong y = a_[m_-1];  // can read sentinel
        ulong z = a_[m_];
        ulong s = y + z;

        if ( m_ >= 3 )
        {
            if ( s <= 3 )  return  easy3(y, z);  // easy case(s)

            ulong j = m_ - 1;
            ulong x = a_[j-1];

            while ( true )  // left with break statements
            {
                while ( x < y )  // try find y we can increment
                {
                    s += x;
                    y = x;
                    j -= 1;
                    x = a_[j-1];
                }

                // here x >= y
                ulong t;
                t = try_write_tail(j, s - 0, y + 1);
                if ( t != 0 )
                {
                    m_ = t;
//                    return m_;
                    break;
                }

                a_[j] = y + 1;
                t = try_write_tail(j + 1, s - y-1, y + 1);
                if ( t != 0 )
                {
                    m_ = t;
//                    return m_;
                    break;
                }

                if ( x > y )
                {
                    t = try_write_tail(j, s - 0, y + 2);
                    if ( t != 0 )
                    {
                        m_ = t;
//                        return m_;
                        break;
                    }
                }

                if ( j==1 )  // we'll get 2 parts
                {
                    s = n_;
                    t = s / 2;
                    s -= t;
                    a_[1] = t;
                    a_[2] = s;
                    m_ = 2;
//                    return m_;
                    break;
                }

                // move left:
                s += x;
                y = x;
                j -= 1;
                x = a_[j-1];
            }

#ifdef COMPOSITION_NZ_I_SMOOTH_WRK
            if ( wrk_ > mwrk_ )  mwrk_ = wrk_;
#endif
            return m_;
        }

        // 1 or 2 parts, happens at most twice
        return  two_parts(y, z);
    }


    const ulong *data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;

        if ( ! is_smooth(data(), num_parts(), 1) )  return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }

    void print_aa()  const  // ASCII art
    { print_composition_aa(a_+1, m_); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_I_SMOOTH_H__
