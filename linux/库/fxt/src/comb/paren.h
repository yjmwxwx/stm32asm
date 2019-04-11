#if !defined  HAVE_PAREN_H__
#define       HAVE_PAREN_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-paren-position-word.h"
#include "fxttypes.h"


class paren
// Parentheses strings, co-lexicographic order.
// Representation as list of positions of opening parenthesis.
{
public:
    ulong k_;    // Number of paren pairs
    ulong n_;    // ==2*k
    ulong *x_;   // Positions of opening parenthesis
    char *str_;  // String representation,  e.g. "((())())()"
    // str[] is generated on demand

private:  // have pointer data
    paren(const paren&);  // forbidden
    paren & operator = (const paren&);  // forbidden

public:
    explicit paren(ulong k)
    {
        k_ = (k>1 ? k : 2);  // not zero (empty) or one (trivial: "()")
        n_ = 2 * k_;
        x_ = new ulong[k_ + 1];
        x_[k_] = ~0UL;  // sentinel (value repeated in method OK())
        str_ = new char[n_ + 1];
        str_[n_] = 0;
        first();
    }

    ~paren()
    {
        delete [] x_;
        delete [] str_;
    }

    const ulong * data()  const  { return x_; }

    void first()  { for (ulong i=0; i<k_; ++i)  x_[i] = i; }

    void last()  { for (ulong i=0; i<k_; ++i)  x_[i] = 2*i; }

    ulong next()  // return zero if current paren is the last
    {
        // if ( k_<=1 )  return 0;  // uncomment to make algorithm work for k_<=1

        ulong j = 0;
        if ( x_[1] == 2 )
        {
            // scan for low end == 010101:
            j = 2;
//            while ( (j<=k_) && (x_[j]==2*j) )  ++j;
            while ( x_[j]==2*j )  ++j;  // can read sentinel
            if ( j==k_ )  {  first();  return 0; }
        }

        // scan block:
        while ( 1 == (x_[j+1] - x_[j]) )  { ++j; }

        ++x_[j];  // move edge element up
        for (ulong i=0; i<j; ++i)  x_[i] = i;  // attach block at low end

        return 1;
    }

    ulong prev()  // return zero if current paren is the first
    {
        // if ( k_==1 )  return 0;  // uncomment to make algorithm work for k_==1

        ulong j = 0;
        // scan for first gap:
        while ( x_[j]==j )  ++j;
        if ( j==k_ )  { last();  return 0; }

        if ( x_[j]-x_[j-1] == 2 )  --x_[j];  // gap of length one
        else
        {
            ulong i = --x_[j];
            --j;
            --i;
            // j items to go, distribute as 1.1.1.11111
            for (  ;  2*i>j;  --i, --j)  x_[j] = i;
            for (  ; i; --i)  x_[i] = 2*i;
            x_[0] = 0;
        }

        return 1;
    }


    bool OK()  const
    {
        if ( x_[k_] != ~0UL )  return false;  // sentinel OK?

        return  is_paren_position_word(data(), k_);
    }

    const char * string()  // generate on demand
    {
        for (ulong j=0; j<n_; ++j)  str_[j] = ')';
        for (ulong j=0; j<k_; ++j)  str_[x_[j]] = '(';
        return str_;
    }
};
// -------------------------



#endif  // !defined HAVE_PAREN_H__
