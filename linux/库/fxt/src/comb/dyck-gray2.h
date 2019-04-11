#if !defined  HAVE_DYCK_GRAY2_H__
#define       HAVE_DYCK_GRAY2_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


//#include "jjassert.h"
#include "fxttypes.h"



class dyck_gray2
// Loopless generation of k-ary Dyck words (same as: k-ary trees)
// (two-close Gray code with homogeneous moves).
// Adapted from:
//   Vincent Vajnovszki, Timothy R. Walsh:
//   "A loop-free two-close Gray-code algorithm for listing k-ary Dyck words",
//   Journal of Discrete Algorithms, vol.4, no.4, pp.633-648, (December-2006)
{
public:
    ulong m, k;  // m ones (and m*(k-1) zeros)
    bool ptt;    // Parity of Total number of Tories (variable 'Odd' in paper)
    ulong *c_;   // positions of ones (1-based)
    ulong *e_;   // Ehrlich array (focus pointers)
    bool *p_;    // parity (1-based)
    ulong *s_;     // directions: whether last/first (==0) or
    // rising (>0) or falling (<0);  (1-based)

private:  // have pointer data
    dyck_gray2(const dyck_gray2&);  // forbidden
    dyck_gray2 & operator = (const dyck_gray2&);  // forbidden

public:
    explicit dyck_gray2(ulong tk, ulong tm)
    // must have tk>=2, tm>=1
    {
        k = tk;
        m = tm;
        ptt = false;

        c_ = new ulong[m+2];
        // sentinels c_[0] (with computing MN) and c_[m+1] (with condition in next())

        e_ = new ulong[m+1];
        p_ = new bool[m+1];   // p_[0] unused
        s_ = new ulong[m+1];    // s_[0] unused
        first();
    }

    ~dyck_gray2()
    {
        delete [] c_;
        delete [] e_;
        delete [] p_;
        delete [] s_;
    }

    void first()
    {
        for (ulong j=0; j<=m; ++j)  e_[j] = j;      //  {e_[j] = j for 0 <= j <= m}
        for (ulong j=0; j<=m; ++j)  s_[j] = 0;      //  {s_[j] = 0 for 1 <= j <= m}  // (all at first value)
        for (ulong j=0; j<=m; ++j)  p_[j] = false;  //  {p_[j] = 0 for 1 <= j <= m}  // actually no need to initialize
        for (ulong j=0; j<=m; ++j)  c_[j] = j;      // first word == [1, 2, 3, ..., m]
        c_[m+1] = 0;  // sentinel, c_[0] is also sentinel
    }

    ulong next()
    // Return zero if current==last, else
    // position (!=0) in (zero-based) array c_[]
    // (the first element never changes).
    // Comments in curly braces {like this} are from the paper.
    {
        ulong i = e_[m];  // The pivot
//        jjassert( i<=m );
        if ( i==1 )  return 0;  // current is last
//        jjassert( i>1 );
        const ulong MN = c_[i-1] + 1;  // {MN is the minimum value of c_[i]}  // can read sentinel c_[0]
        const ulong MX = (i - 1)*k + 1;  // { MX is the maximum value of c_[i]}

        if ( s_[i] == 0 )  // { c_[i] is at its first value }
        {
            p_[i] = ptt;  // { parity of total number of tories }
            s_[i] = +1;  // {c_[i] starts rising unless it starts at max(i)}

            if ( c_[i] == MX )  // {one of these tories is not to c_[i]'s left}
            {
                p_[i] = 1 - p_[i];
                s_[i] = -s_[i];
            }

//            if ( (k==2) && (i<m) && (c_[i+1]==MX+2) )  // {see above comment}
//            if ( (k==2) && (c_[i+1]==MX+2) )  // can read sentinel c_[m+1]
            if ( c_[i+1] == MX+k )  // can read sentinel c_[m+1]==0  // jj-NOTE: is this correct?
            {
                p_[i] = 1 - p_[i];
            }
        }

//        jjassert( s_[i] != 0 );

        if ( (long)s_[i] > 0 )  // { c_[i] is rising }
        {
            if ( c_[i] == MN )  // {MN is taken and c_[i] can't end there}
            {
                s_[i] = 2;
            }
            else
            {
                if ( (c_[i] == MN+1) && (s_[i] == 2) )  // {MN+1 is also taken}
                {
                    s_[i] = 3;
                }
            }

//            if ( ((c_[i] % 2) == p_[i]) && (c_[i] < MX-1) )
//            {
//                c_[i] = c_[i] + 2;
//            }
//            else
//            {
//                c_[i] = c_[i] + 1;
//            }
            c_[i] += ( 1 + ( ((c_[i] % 2) == p_[i]) && (c_[i] < MX-1) ) );

            if ( c_[i] == MX )  // {one more tory}
            {
                ptt = 1 - ptt;
                s_[i] = -s_[i];
            }
        }
        else  // { c_[i] is falling }
        {
            if ( c_[i] == MX ) {  ptt = 1 - ptt; }  // {one fewer tory}

//            if ( ((c_[i] % 2) != p_[i] ) && (c_[i] > MN+1) )
//            {
//                c_[i] = c_[i] - 2;
//            }
//            else
//            {
//                c_[i] = c_[i] - 1;
//            }
            c_[i] -= ( 1 + ( ((c_[i] % 2) != p_[i] ) && (c_[i] > MN+1) ) );
        }
//        jjassert( c_[i] > c_[i-1] );

        e_[m] = m;  // {beginning to update Ehrlich array}
        if ( c_[i] + s_[i] == MN - 1 )  // {c_[i] is at its last value}
        {
            s_[i] = 0;  // {c_[i] will be at its first value the next time i is the pivot}
            e_[i] = e_[i-1];
            e_[i-1] = i - 1;
        }

        return  i - 1;  // position in zero-based array c_[]
    }

    const ulong *data()  const  { return c_+1; }  // zero-based array

//    bool OK()  const  // need another test
//    { return is_dyck_rgs( sq_, n_, k_ ); }
};
// -------------------------



#endif  // !defined HAVE_DYCK_GRAY2_H__
