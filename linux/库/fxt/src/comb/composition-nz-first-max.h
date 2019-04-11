#if !defined HAVE_COMPOSITION_NZ_FIRST_MAX_H__
#define      HAVE_COMPOSITION_NZ_FIRST_MAX_H__
// This file is part of the FXT library.
// Copyright (C) 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.



#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"

#include "fxtio.h"

#include "fxttypes.h"


// Cf. comb/balanced-tree-lev-seq.h


//#define COMPOSITION_NZ_FIRST_MAX_FIXARRAYS  // default off

class composition_nz_first_max
// Compositions of n into positive parts where no part is greater than the first.
// Lexicographic order.
// See OEIS sequences A079500 and A007059.
{
public:
#ifndef COMPOSITION_NZ_FIRST_MAX_FIXARRAYS
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[64];  // > 4 * 10^17 compositions
#endif
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts

private:  // have pointer data
    composition_nz_first_max(const composition_nz_first_max&);  // forbidden
    composition_nz_first_max & operator = (const composition_nz_first_max&);  // forbidden

public:
    explicit composition_nz_first_max(ulong n)
    {
        n_ = n;
#ifndef COMPOSITION_NZ_FIRST_MAX_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
#endif
        a_[0] = 0;  // returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0
        first();
    }

    ~composition_nz_first_max()
    {
#ifndef COMPOSITION_NZ_FIRST_MAX_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong first_part()  const  { return a_[1]; }  // also: max part
    ulong last_part()  const  { return a_[m_]; }

    ulong num_parts()  const  {  return m_; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
    }

//    void last()
//    {
//        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
//        a_[1] = n_;
//        m_ = 1;
//    }

    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        ulong f = a_[1];  // max
        ulong j = m_;
        ulong s = a_[j];
        while ( --j != 0 )
        {
            ulong v = a_[j];
            if ( v + 1 <= f )
            {
                a_[j] = v + 1;
                m_ = j + s - 1;
                do  { a_[++j] = 1; }  while ( j < m_ );
                return  m_;
            }
            s += v;
        }

        // need to increment max:
        f += 1;
        a_[1] = f;
        m_ = n_ - f + 1;
        for (ulong i=2; i<=m_; ++i)  a_[i] = 1;

        return  m_;
    }

//    ulong prev()
//    // Return number of parts of generated composition.
//    // Return zero if the current is the first composition.
//    {
//    }


    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;
        const ulong f = a_[1];
        for (ulong j=1; j<=m_; ++j)  // fist part max?
            if ( a_[j] > f )  return false;
        return true;
    }

    void print(const char *bla)  const
    { print_vec(bla, data(), num_parts(), false); }

    void print_aa()  const  // ASCII art
    { print_composition_aa(data(), num_parts()); }

    void print_tree_lev_seq(const char *bla)  const
    // Print level sequence of corresponding (rooted) balanced tree.
    {
        if ( bla )  cout << bla;
        cout << "[ ";
        cout << "0 ";
        const ulong f = a_[1];
        for (ulong j=1; j<=m_; ++j)
        {
            ulong i = f - a_[j] + 1;
            do  { cout << i << " "; }  while ( ++i <= f );
        }
        cout << "]";
    }

//    void print_tree_aa()  const;  // tree as ASCII art;  todo
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_FIRST_MAX_H__
