#if !defined HAVE_SETPART_CK_RGS_H__
#define      HAVE_SETPART_CK_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"
#include "fxttypes.h"


// optimization by keeping list of nonzero digits in use:
#define SETPART_CK_RGS_NZ  // default on (speedup)


class setpart_ck_rgs
// Restricted growth strings (RGS) for set partitions:
// each digit is either a fixed point or a digit from the prefix.
// Equivalently: rooted trees of height <= 2.
// Lexicographic order.
// See
//   Curtis Cooper, Robert E. Kennedy:
//   "Patterns, Automata, and Stirling Numbers of the Second Kind",
//    Mathematics and Computer Education Journal, vol.26, (1992),
// where these RGS are called "n-pattern sequences", a term
// we will not use because "pattern sequences" better describe
// the "usual" RGS for set partitions.  Instead we call them
// Cooper-Kennedy RGS, abbreviated here as CK-RGS.
{
public:
    ulong *a_;  // Cooper-Kennedy RGS
#ifdef SETPART_CK_RGS_NZ
    ulong *nz_; // ordered list of non-zero digits in a[0,1,...,m-1]
    ulong m_; // number of non-zero digits
#endif
    ulong n_;   // length of RGS

private:  // have pointer data
    setpart_ck_rgs(const setpart_ck_rgs&);  // forbidden
    setpart_ck_rgs & operator = (const setpart_ck_rgs&);  // forbidden

public:
    explicit setpart_ck_rgs(ulong n)
    {
        n_ = n;

        a_ = new ulong[n_+1];
        a_[0] = 0;  // sentinel: != -1
        ++a_;  // nota bene
#ifdef SETPART_CK_RGS_NZ
        nz_ = new ulong[n_];
#endif
        first();
    }

    ~setpart_ck_rgs()
    {
        --a_;
        delete [] a_;
#ifdef SETPART_CK_RGS_NZ
        delete [] nz_;
#endif
    }

    const ulong * data()  const  { return  a_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
#ifdef SETPART_CK_RGS_NZ
        for (ulong k=0; k<n_; ++k)  nz_[k] = 0;
        m_ = 0;
#endif
    }


    ulong next()
    {
        ulong j = n_ - 1;
        while ( a_[j] == j )  // can read sentinel
        {
            a_[j] = 0;
            --j;
#ifdef SETPART_CK_RGS_NZ
            --m_;
#endif
        }

        if ( j + 1 == 0 )  return 0;  // current is last

        ulong ma = a_[j] + 1;

#ifdef SETPART_CK_RGS_NZ
        nz_[m_] = j;  // make sure the scan stops
        ulong k = 0;
        while ( nz_[k] < ma )  ++k;
        ulong a1 = nz_[k];
        a_[j] = a1;
        if ( a1==j )  // new nonzero digit
        {
            nz_[m_] = j;
            ++m_;
        }

#else  // SETPART_CK_RGS_NZ
        a_[j] = j;  // make sure the scan stops
        ulong k = 1;
        while ( a_[k] < ma )  ++k;
        a_[j] = a_[k];

#endif  // SETPART_CK_RGS_NZ

        return  j;
    }

    void make_setpart_rgs(ulong *y)  const
    // Write "usual" setpart RGS to y[].
    {
#ifdef SETPART_CK_RGS_NZ
        for (ulong j=0; j<n_; ++j)  y[j] = 0;
        ulong mx = 0;
        for (ulong i=0; i<m_; ++i)
        {
            ulong nzi = nz_[i];
            ++mx;
            for (ulong j=mx; j<n_; ++j)
            {
                if ( a_[j] == nzi )
                    y[j] = mx;
            }
        }
#else
        for (ulong j=0; j<n_; ++j)  y[j] = a_[j];
        ulong mx = 0;
        for (ulong j=0; j<n_; ++j)
        {
            ulong v = y[j];
            if ( v > mx )
            {
                ++mx;
                for (ulong k=j; k<n_; ++k)
                    if ( y[k] == v )  y[k] = mx;
            }
        }
#endif
    }


    bool OK()  const
    {
        if ( n_ == 0 )  return true;
        if ( a_[0] != 0 )  return false;

//        ulong mx = 0;
        ulong m = 0;
        for (ulong j=1; j<n_; ++j)
        {
            ulong aj = a_[j];
            if ( aj==0 )  continue;

            if ( aj==j )
            {
#ifdef SETPART_CK_RGS_NZ
                if ( nz_[m] != aj )  return false;
#endif
                ++m;
            }
            else  // aj in prefix?
            {
#ifdef SETPART_CK_RGS_NZ
                ulong i = 0;
                while ( i < m )
                {
                    if ( nz_[i] == aj )  break;
                    ++i;
                }
                if ( i==m )  return false;
#else
                ulong i = 0;
                while ( i < j )
                {
                    if ( a_[i] == aj )  break;
                    ++i;
                }
                if ( i==j )  return false;
#endif
            }
        }

#ifdef SETPART_CK_RGS_NZ
        if ( m != m_ )  return false;
#endif

#ifdef SETPART_CK_RGS_NZ
        for (ulong k=0; k<m_; ++k)
        {
            ulong nzk = nz_[k];
            if ( a_[nzk] != nzk )  return false;
        }
#endif
        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_SETPART_CK_RGS_H__
