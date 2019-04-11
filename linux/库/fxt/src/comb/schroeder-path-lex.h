#if !defined  HAVE_SCHROEDER_PATH_LEX_H__
#define       HAVE_SCHROEDER_PATH_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"
#include "fxttypes.h"


//#include "jjassert.h"


class schroeder_path_lex
// Schroeder paths in lexicographic order, CAT algorithm.
// Steps are +1, 0, -1 (up, horizontal, down),
// the first and last elements are 0, all elements are non-negative, and
// horizontal steps appear consecutively an even number of times.
// Cf. OEIS sequence A006318: large Schroeder numbers.
{
public:
    ulong *a_;
    ulong n_;

private:  // have pointer data
    schroeder_path_lex(const schroeder_path_lex&);  // forbidden
    schroeder_path_lex & operator = (const schroeder_path_lex&);  // forbidden

public:
    explicit schroeder_path_lex(ulong n)
    // Must have n>=1.
    {
        n_ = 2 * n;  // note: length = 2 * n
        a_ = new ulong[n_+2];
        a_[0] = 0;  // lower sentinel
        ++a_;  // nota bene
        a_[n_] = 0;  // used in print() as final element

        first();
    }

    ~schroeder_path_lex()
    {
        --a_;
        delete [] a_;
    }

    void first()
    { for (ulong j=0; j<n_; ++j)  a_[j] = 0; }


    ulong next()
    {
#if 1  // "easy case" optimization:
        ulong j = n_ - 1;
        if ( a_[j] == 0 )  // easy case: trailing zero becomes one
        {
            a_[j] = 1;
            return j;
        }

        a_[j] = 0;
        --j;
        ulong m = 2;
#else
        ulong j = n_ - 1;
        ulong m = 1;
#endif

        // Find max rising-falling tail, i.e. of the form
        //  s, s+1, s+2, ..., t-3, t-2, t-1, t, t-1, ..., 3, 2, 1
        // or (maximal element t repeated)
        //  s, s+1, s+2, ..., t-3, t-2, t-1, t, t, t-1, ..., 3, 2, 1
        // where s is preceded by an element >= s

        // Scan falling part:
        while ( a_[j] == m )
        {
//            a_[j] = 0;
            m += 1;
            --j;
        }

        // Scan rising part:
        while ( a_[j] > a_[j-1] )  // can read lower sentinel
        {
//            a_[j] = 0;
            --j;
        }

        if ( j==0 )   return 0;  // current is last



        // now replace [s, ...] by [s+1, s, s-1, s-2, ..., 3, 2, 1]

//        const ulong e = 1 - (j & 1);  // whether j is even

        const ulong a0 = a_[j];
        const ulong a1 = a_[j-1];
        if ( a1 == 0 )  // leftmost change at j - 1
        {
//            jjassert( e );  // true as long as "easy case" is left active
            const ulong i = j - 1;
            a_[i] = 1;
            a_[j] = 0;
            while ( ++j < n_ )  { a_[j] = 0; }
            return  i;  // leftmost position changed
        }
        else
        {
//            jjassert( j>=2 );
//            jjassert( e != 0 );  // not true

            ulong v = a0 + 1;
            ulong i = j;
            a_[i] = v;

            if ( v == a1 )  // leftmost change at j
            {
                ++j;
//                jjassert( v != a_[j+1] );
            }
            else
            {
                if ( v == a_[j+1] )  // leftmost change at j - 1
                {
                    --i;
                    a_[i] = v;
                    v -= 1;
                }
//                else  // leftmost change at j
//                { ; }
            }
//            jjassert( v );

            while ( v )
            {
                a_[j] = v;
                v -= 1;
                ++j;
            }

            while ( j < n_ )  { a_[j] = 0;  ++j; }

            return i;  // leftmost position changed
        }
    }

    const ulong * data()  const  { return a_; }

    bool is_little_schroeder_path()  const
    // Return whether path has no peaks at height 1
    //   (is a "little Schroeder path).
    // See OEIS sequence A001003.
    {
        for (ulong i=1; i<n_; ++i)
            if ( (a_[i]==1) && (a_[i-1]==0) && (a_[i+1]==0 ) )
                return false;
        return true;
    }

    void print(const char *bla, bool dfz=false)
    { print_vec(bla, a_, n_+1, dfz); }
};
// -------------------------


#endif  // !defined HAVE_SCHROEDER_PATH_LEX_H__
