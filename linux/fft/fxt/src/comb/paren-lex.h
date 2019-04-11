#if !defined  HAVE_PAREN_LEX_H__
#define       HAVE_PAREN_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-paren-position-word.h"
#include "fxttypes.h"


//#define PAREN_LEX_FIXARRAY  // default off

class paren_lex
// Parentheses strings, lexicographic order.
// Representation as list of positions of opening parenthesis.
{
public:
#ifndef PAREN_LEX_FIXARRAY
    ulong *x_;   // Positions of opening parenthesis (RGS)
#else
    ulong x_[64];
#endif
    ulong k_;    // Number of paren pairs
    ulong n_;    // ==2*k

    char *str_;  // String representation,  e.g. "((())())()"
    // str[] is generated on demand

private:  // have pointer data
    paren_lex(const paren_lex&);  // forbidden
    paren_lex & operator = (const paren_lex&);  // forbidden

public:
    explicit paren_lex(ulong k)
    {
        // make things work with k==0:
        if ( k==0 )  k = 1;

        k_ = k;
        n_ = 2 * k_;
#ifndef PAREN_LEX_FIXARRAY
        x_ = new ulong[k_ + 1];
#endif
        x_[0] = 1;  // sentinel (value repeated in method OK())
        str_ = new char[n_ + 1];
        str_[n_] = 0;

        first();
    }

    ~paren_lex()
    {
#ifndef PAREN_LEX_FIXARRAY
        delete [] x_;
#endif
        delete [] str_;
    }

    const ulong * data()  const  { return x_ + 1; }

    void first()  { for (ulong i=1; i<=k_; ++i)  x_[i] = i - 1; }

    void last()  { for (ulong i=1; i<=k_; ++i)  x_[i] = 2*i-2; }

    ulong next()
    // Return position of leftmost change,
    // return zero if current is last.
    {
        ulong j = k_;
        const ulong z = x_[j];
        ulong m = n_ - 2;
        if ( z < m )  // easy case: can increment last part
        {
            x_[j] = z + 1;
            return j - 1;
        }

        do // scan over tail
        {
            --j;
            m -= 2;
        }
        while ( x_[j]==m );  // can read sentinel

        if ( j==0 )  return 0;  // current is last

        ulong t = x_[j];
        ulong i = j;
        do  // write lex first tail:  x[j]+1, x[j]+2, x[j]+3, ...
        {
            ++t;
            x_[i] = t;
        }
        while ( i++ != k_ );

        return  j - 1;
    }

    ulong prev()
    // Return position of leftmost change,
    // return zero if current is first.
    {
        ulong m = n_;
        ulong j = k_;

        ulong z = x_[j];
        ulong y = x_[j-1];  // can read sentinel
        ulong d = z - y;
        while ( true )
        {
            if ( d != 1 )  // can decrement
            {
                if ( j==0 )  return 0;  // current is first

                x_[j] = z - 1;
                return j - 1;
            }

            m -= 2;
            x_[j] = m;

            z = y;
            --j;
            y = x_[j-1];  // can read sentinel
            d = z - y;
        }
    }


    bool OK()  const
    {
        if ( x_[0] != 1 )  return false;  // sentinel OK?

        return  is_paren_position_word(data(), k_);
    }

    const char * string()  // generate on demand
    {
        for (ulong j=0; j<n_; ++j)  str_[j] = ')';
        for (ulong j=1; j<=k_; ++j)  str_[x_[j]] = '(';
        return str_;
    }
};
// -------------------------



#endif  // !defined HAVE_PAREN_LEX_H__
