#if !defined HAVE_MIXEDRADIX_NAF_SUBSET_LEX_H__
#define      HAVE_MIXEDRADIX_NAF_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"

#define MIXEDRADIX_NAF_SUBSET_LEX_FIXARRAYS  // default on

class mixedradix_naf_subset_lex
// Mixed radix non-adjacent forms (NAF), subset-lex order.
// Loopless generation.
{
public:
#ifndef MIXEDRADIX_NAF_SUBSET_LEX_FIXARRAYS
    ulong *iset_;  // Set of positions of nonzero digits
    // Internally the empty set is represented with one element pointing to a zero,
    // the method iset_size() hides this (by default) from the user, see there.
    ulong *a_;    // Digits
    ulong *m1_;   // Nines (radix minus one) for each digit
#else
    ulong iset_[96];
    ulong a_[96];  // > 10^19 words with Fibonacci words
    ulong m1_[96];
#endif
    ulong ni_;    // Number of elements in iset[]
    ulong n_;     // Number of digits
//    ulong j_;     // Position of last change


private:  // have pointer data
    mixedradix_naf_subset_lex(const mixedradix_naf_subset_lex&);  // forbidden
    mixedradix_naf_subset_lex & operator = (const mixedradix_naf_subset_lex&);  // forbidden

public:
    explicit mixedradix_naf_subset_lex(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;

#ifndef MIXEDRADIX_NAF_SUBSET_LEX_FIXARRAYS
        const ulong ne = (n >0 ? n : 1);  // make things work for size zero
        iset_ = new ulong[(ne+1)/2];
        a_ = new ulong[ne];
        m1_ = new ulong[ne];
#endif

        mixedradix_init(n_, mm, m, m1_);
        first();
    }

    ~mixedradix_naf_subset_lex()
    {
#ifndef MIXEDRADIX_NAF_SUBSET_LEX_FIXARRAYS
        delete [] iset_;
        delete [] m1_;
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return a_; }
    const ulong * iset()  const  { return iset_; }
    ulong iset_size()  const
    {
#if 1  // Report size zero for empty set:
        return ni_ - (0==a_[iset_[0]]);

#else  // Empty set as size-1 set containing a zero multiplicity:
        // Activate if your application can live with that.
        return ni_;
#endif
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;

        // iset[] initially with one element zero:
        iset_[0] = 0;
        ni_ = 1;

        if ( n_==0 )  // make things work for n == 0
        {
            m1_[0] = 0;
            a_[0] = 0;
        }
//        j_ = n_;
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;

        if ( n_==0 )  // make things work for n == 0
        {
            m1_[0] = 0;
            a_[0] = 0;
        }
        else
        {
            a_[n_-1] = m1_[n_-1];
            iset_[0] = n_ - 1;
            ni_ = 1;
        }
//        j_ = n_;
    }


    bool next()
    // Loopless algorithm.
    {
        ulong j = iset_[ni_-1];
        const ulong aj = a_[j] + 1;
        if ( aj <= m1_[j] )  // can increment last digit
        {
            a_[j] = aj;
            return true;
        }

        if ( j + 2 < n_ )  // can append new digit
        {
            iset_[ni_] = j + 2;
            a_[j+2] = 1;  // assume all m1[] are nonzero
            ++ni_;
            return true;
        }

        a_[j] = 0;  // set last nonzero digit to zero

        if ( j + 1 < n_ )  // can move last digit to the right
        {
            a_[j+1] = 1;
            iset_[ni_-1] = j + 1;
            return true;
        }

        if ( ni_ == 1 )  return false;  // current is last


        // Now we look to the left:
        const ulong k = iset_[ni_-2];  // nearest nonzero digit to the left
        const ulong ak = a_[k] - 1;    // decrement digit to the left
        a_[k] = ak;
        if ( ak == 0 )  // move digit one to the right
        {
            a_[k+1] = 1;
            iset_[ni_-2] = k + 1;
            --ni_;
            return true;
        }
        else  // append digit two positions to the right
        {
            a_[k+2] = 1;
            iset_[ni_-1] = k + 2;
            return true;
        }
    }


    bool prev()
    // Loopless algorithm.
    {
        ulong j = iset_[ni_-1];
        const ulong aj = a_[j] - 1;
        if ( aj != 0 )  // can decrement last digit
        {
            if ( aj == -1UL )  return false;  // current is first

            a_[j] = aj;
            return true;
        }

        a_[j] = 0;  // set last to zero

        if ( j==0 )  // next is first
        {
            // Now we have the empty set (but leave ni==1)
            return true;
        }


        if ( ni_ == 1 )  // just one digit
        {
            if ( j == n_ - 1 )  // on last track, move left and put nine
            {
                a_[j-1] = m1_[j-1];
                iset_[0] = j - 1;
                return true;
            }

            // put 1 left and append nine at end
            a_[j-1] = 1;  // assume all m1[] are nonzero
            iset_[0] = j - 1;
            a_[n_-1] = m1_[n_-1];
            iset_[1] = n_ - 1;
            ni_ = 2;
            return true;
        }

        // here ni >= 2, so we can look left
        const ulong k = iset_[ni_-2];  // left neighbor

        if ( k == j - 2 )  // Left neighbor is two-adjacent
        {
            if ( a_[k] == m1_[k] )  // Left is nine: simply detach last digit
            {
                --ni_;
                return true;
            }

            // increment left and put nine at end
            ++a_[k];
            a_[n_-1] = m1_[n_-1];
            iset_[ni_-1] = n_ - 1;
            return true;
        }

        // here left neighbor is at least 3 positions away
        if ( j == n_ -  1 )  // put nine left
        {
            a_[j-1] = m1_[j-1];
            iset_[ni_-1] = j - 1;
            return true;
        }

        // start left neighbor and attach nine at end
        a_[j-1] = 1;
        iset_[ni_-1] = j - 1;

        a_[n_-1] = m1_[n_-1];
        iset_[ni_] = n_ - 1;
        ++ni_;

        return true;
    }

//    ulong pos()  const  { return j_; }  // position of last change

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_mixedradix(bla, a_, n_, dfz); }

    void print_nines(const char *bla)  const
    { print_mixedradix(bla, m1_, n_, false); }

    ulong to_num()  const
    // Return (integer) value of mixed radix number.
    { return mixedradix2num(a_, m1_, n_); }


    bool OK()  const
    {
        if ( ! is_mixedradix_num(a_, n_, m1_) )  return false;

        for (ulong j=1; j<n_; ++j)  // NAF ?
            if ( (a_[j-1]!=0) && (a_[j]!=0) )  return false;

        // iset[] correct ?
//        ulong ns = iset_size();
        ulong ns = ni_ - (0==a_[iset_[0]]);  // strict iset_size()
        ulong s = 0;
        for (ulong j=0; j<n_; ++j)  s += ( a_[j] != 0 );
        if ( s != ns )  return false;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_MIXEDRADIX_NAF_SUBSET_LEX_H__
