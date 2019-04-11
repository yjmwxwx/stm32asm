#if !defined  HAVE_MOTZKIN_RGS_LEX_H__
#define       HAVE_MOTZKIN_RGS_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "restrict.h"

#include "comb/is-motzkin-rgs.h"

#include "comb/comb-print.h"

//#define MOTZKIN_RGS_LEX_FIXARRAYS  // default off
// GCC 4.8.0: slowdown


class motzkin_rgs_lex
// Motzkin restricted growth strings (RGS):
// words a[0,1,...,n-1] where a[0] = 0, a_[k] <= a[k-1] + 1,
//  and there are no two consecutive up-steps.
// Lexicographic order.
// Cf. OEIS sequence A001006.
{
public:
#ifdef MOTZKIN_RGS_LEX_FIXARRAYS
    ulong * restrict a_;  // digits of the RGS: a_[k] <= a[k-1] + 1
    ulong * restrict s_;  // s[k]: how many consecutive increments up to position k
#else
    ulong a_[44];  // 4684478925507420069 RGS
    ulong s_[44];
#endif
    ulong n_;   // number of digits
    ulong i_;  // at most i rises in a row, at most i+1 consecutive ones in the Dyck word
    // i==1 ==> Motzkin RGS, A001006
    // i==n ==> Catalan RGS, A000108
#ifdef MOTZKIN_RGS_LEX_FIXARRAYS
    char * restrict str_;  // for bit string and paren string
#else
    char str_[90];
#endif

private:  // have pointer data
    motzkin_rgs_lex(const motzkin_rgs_lex&);  // forbidden
    motzkin_rgs_lex & operator = (const motzkin_rgs_lex&);  // forbidden

public:
    explicit motzkin_rgs_lex(ulong n, ulong i=1)
    {
        n_ = (n > 0 ? n : 1);  // shall work for n==0
        i_ = i;

#ifdef MOTZKIN_RGS_LEX_FIXARRAYS
        a_ = new ulong[n_];
        s_ = new ulong[n_];
        str_ = new char[2*n_+1];
#endif

        str_[2*n_] = 0;

        first();
    }

    ~motzkin_rgs_lex()
    {
#ifdef MOTZKIN_RGS_LEX_FIXARRAYS
        delete [] a_;
        delete [] s_;
        delete [] str_;
#endif
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  s_[k] = 0;
    }


    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong j = n_ - 1;
        ulong a0, a1;
        ulong s1;
        while ( j != 0 )
        {
            a1 = a_[j-1];
            a0 = a_[j];
            s1 = s_[j-1];

            if ( a0 < a1 )
            {
                a_[j] = a0 + 1;

                s_[j] = 0;
//                s_[j] = ( s1 ? s1 - 1 : 0 );  // still other strings for i!=1

                return j;
            }
            else
            {
                if ( a0 == a1 )
                {
#if 1  // default:
                    if ( s1 < i_ )
                    {
                        a_[j] = a0 + 1;
                        s_[j] = s1 + 1;
                        return j;
                    }
#else  // different from default for i!=1:
                    if ( 0==s_[j-1] )
                    {
                        a_[j] = a0 + 1;
                        s_[j] = i_;
                        return j;
                    }
#endif
                }
            }
            a_[j] = 0;
            s_[j] = 0;
            --j;
        }

        return 0;  // current is last
    }


    const ulong *data()  const  { return a_; }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz ); }

    const char* bit_string()
    {
        for (ulong k=0; k<2*n_; ++k)  str_[k] = '.';
        for (ulong k=0, j=0;  k<n_;  ++k, j+=2)  str_[ j - a_[k] ] = '1';
        return str_;
    }

    const char* paren_string()
    {
        for (ulong k=0; k<2*n_; ++k)  str_[k] = ')';
        for (ulong k=0, j=0;  k<n_;  ++k, j+=2)  str_[ j - a_[k] ] = '(';
        return str_;
    }

    bool OK()  const
    {
        // todo: check s[]
        return  is_motzkin_rgs(data(), n_, i_);
    }
};
// -------------------------


#endif  // !defined HAVE_MOTZKIN_RGS_LEX_H__
