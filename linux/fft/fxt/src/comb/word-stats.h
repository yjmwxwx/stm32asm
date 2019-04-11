#if !defined  HAVE_WORD_STATS_H__
#define       HAVE_WORD_STATS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


class word_stats
// Various statistics for length-n arrays of type ulong.
{
private:
    const ulong *a;  // digits of the string
    ulong n;    // Number of digits

    ulong *h;  // aux for histogram
    ulong hn;  // hn+1 values in histogram: h[0..hn]

private:  // have pointer data
    word_stats(const word_stats&);  // forbidden
    word_stats & operator = (const word_stats&);  // forbidden

public:
    explicit word_stats(const ulong *ta, ulong tn, ulong thn=0)
    {
        n = tn;
        a = ta;

        // default n+1 values (0..n):
        hn = ( thn != 0 ? thn : n );
        h = new ulong[hn+1];  // [0..hn]
    }

    ~word_stats()  { delete [] h; }

    void set_len(ulong m)
    // Set length of array to be inspected.
    { n = m; }


    // Number of ascents/descents/flat-steps:

    ulong num_ascents()  const
    // Return number of ascents, i.e.,
    // number of pairs where a[k-1] < a[k].
    // Result s in range 0 <= s <= n-1.
    {
        ulong s = 0;
        for (ulong k=1; k<n; ++k)  s += ( a[k-1] < a[k] );
        return s;
    }

    ulong num_descents()  const
    // Return number of descents, i.e.,
    // number of pairs where a[k-1] > a[k].
    // Result s in range 0 <= s <= n-1;
    {
        ulong s = 0;
        for (ulong k=1; k<n; ++k)  s += ( a[k-1] > a[k] );
        return s;
    }

    ulong num_flat_steps()  const
    // Return number of flat steps, i.e.,
    // number of pairs where a[k-1]==a[k].
    // Result s in range 0 <= s <= n-1.
    {
        ulong s = 0;
        for (ulong k=1; k<n; ++k)  s += ( a[k-1] == a[k] );
        return s;
    }

    ulong num_nonflat_steps()  const
    // Return number of non-flat steps, i.e.,
    // number of pairs where a[k-1]!=a[k].
    // Result s in range 0 <= s <= n-1.
    {
        ulong s = 0;
        for (ulong k=1; k<n; ++k)  s += ( a[k-1] != a[k] );
        return s;
    }


    ulong num_peaks()  const
    // Return number of peaks, i.e.,
    // number of triples where a[k-1] < a[k] > a[k+1].
    // Result s in range 0 <= s <= n-2.
    {
        if ( n < 3 )  return 0;
        ulong s = 0;
        for (ulong k=1; k<n-1; ++k)
        {
            if ( a[k-1] < a[k] )
                s += ( a[k] > a[k+1] );
        }
        return s;
    }

    ulong num_valleys()  const
    // Return number of valleys, i.e.,
    // number of triples where a[k-1] > a[k] < a[k+1].
    // Result s in range 0 <= s <= n-2.
    {
        if ( n < 3 )  return 0;
        ulong s = 0;
        for (ulong k=1; k<n-1; ++k)
        {
            if ( a[k-1] > a[k] )
                s += ( a[k] < a[k+1] );
        }
        return s;
    }

    ulong max_flat_length()  const
    // Max number of successive identical digits.
    {
        if ( n==0 )  return 0;
        ulong r = 0,  c = 1;
        for (ulong k=1; k<n; ++k)
        {
            if ( a[k]==a[k-1] )  c += 1;
            else  c = 1;
            if ( c > r )  r = c;
        }
        return r;
    }


    ulong max_incr_length()  const
    // Max number of successive increasing digits.
    {
        if ( n==0 )  return 0;
        ulong r = 0,  c = 1;
        for (ulong k=1; k<n; ++k)
        {
            if ( a[k] > a[k-1] )  c += 1;
            else  c = 1;
            if ( c > r )  r = c;
        }
        return r;
    }


    ulong max_weakly_incr_length()  const
    // Max number of successive weakly increasing digits.
    {
        if ( n==0 )  return 0;
        ulong r = 0,  c = 1;
        for (ulong k=1; k<n; ++k)
        {
            if ( a[k] >= a[k-1] )  c += 1;
            else  c = 1;
            if ( c > r )  r = c;
        }
        return r;
    }


    ulong max_decr_length()  const
    // Max number of successive decreasing digits.
    {
        if ( n==0 )  return 0;
        ulong r = 0,  c = 1;
        for (ulong k=1; k<n; ++k)
        {
            if ( a[k] < a[k-1] )  c += 1;
            else  c = 1;
            if ( c > r )  r = c;
        }
        return r;
    }


    ulong max_weakly_decr_length()  const
    // Max number of successive weakly decreasing digits.
    {
        if ( n==0 )  return 0;
        ulong r = 0,  c = 1;
        for (ulong k=1; k<n; ++k)
        {
            if ( a[k] <= a[k-1] )  c += 1;
            else  c = 1;
            if ( c > r )  r = c;
        }
        return r;
    }



    // Position of first/last ascent/descent/flat-step:

    ulong first_ascent_idx()  const
    // Return index of (left member of) first ascent, i.e.,
    // return k for the first occurrence of a[k] < a[k+1].
    // Return n if all values are identical.  (note!)
    // Result s in range 0 <= s <= n.
    {
        if ( n<=1 )  return n;
        for (ulong k=0; k<n-1; ++k)
            if ( a[k] < a[k+1] )  return k;
        return n;
    }

    ulong last_ascent_idx()  const
    // Return index of (left member of) last asscent, i.e.,
    // return k for the last occurrence of a[k] < a[k+1].
    // Return n if all values are identical.  (note!)
    // Result s in range 0 <= s <= n.
    {
        if ( n<=1 )  return n;
        ulong k = n - 1;
        while ( k )
        {
            --k;
            if ( a[k] < a[k+1] )  return k;
        }
        return n;
    }

    ulong first_descent_idx()  const
    // Return index of (left member of) first descent, i.e.,
    // return k for the first occurrence of a[k] > a[k+1].
    // Return n if all values are identical.  (note!)
    // Result s in range 0 <= s <= n.
    {
        if ( n<=1 )  return n;
        for (ulong k=0; k<n-1; ++k)
            if ( a[k] > a[k+1] )  return k;
        return n;
    }
    ulong last_descent_idx()  const
    // Return index of (left member of) last descent, i.e.,
    // return k for the last occurrence of a[k] > a[k+1].
    // Return n if all values are identical.  (note!)
    // Result s in range 0 <= s <= n.
    {
        if ( n<=1 )  return n;
        ulong k = n - 1;
        while ( k )
        {
            --k;
            if ( a[k] > a[k+1] )  return k;
        }
        return n;
    }


    ulong first_flat_step_idx()  const
    // Return index of (left member of) first flat step, i.e.,
    // return k for the first occurrence of a[k] == a[k+1].
    // Return n if no two values are identical.  (note!)
    // Result s in range 0 <= s <= n.
    {
        if ( n<=1 )  return n;
        for (ulong k=0; k<n-1; ++k)
            if ( a[k] == a[k+1] )  return k;
        return n;
    }

    ulong last_flat_step_idx()  const
    // Return index of (left member of) last flat step, i.e.,
    // return k for the last occurrence of a[k] == a[k+1].
    // Return n if all values are equal (or n<=1).  (note!)
    // Result s in range 0 <= s <= n.
    {
        if ( n<=1 )  return n;
        ulong k = n - 1;
        while ( k )
        {
            --k;
            if ( a[k] == a[k+1] )  return k;
        }
        return n;
    }



    ulong num_val(ulong v)  const
    // Return number of digits == v.
    // Result s in range 0 <= s <= n.
    {
        ulong s = 0;
        for (ulong k=0; k<n; ++k)
            s += ( v == a[k] );
        return  s;
    }


    ulong num_leading_equal_val()  const
    // Return how many consecutive values at the starts
    // are equal to the first value.
    // Result s in range 0 <= s <= n.
    {
        if ( n<=1 )  return n;
        ulong s = 1,  v = a[0];
        for (ulong k=1; k<n; ++k)
        {
            if ( v == a[k] ) ++s;
            else  break;
        }
        return s;
    }

    ulong num_trailing_equal_val()  const
    // Return how many consecutive values at end
    // are equal to the last value.
    // Result s in range 0 <= s <= n.
    {
        if ( n<=1 )  return n;
        ulong s = 1,  v = a[n-1];
        ulong k = n - 2;
        do
        {
            if ( v == a[k] ) ++s;
            else  break;
        }
        while ( k-- != 0 );
        return s;
    }

    // Value of min/max, first/last value:

    ulong max_val()  const
    // Return value of maximal digit.
    // If the maximum is known, use num_val().
    // Return 0 for n==0.
    {
        ulong s = 0;
        for (ulong k=0; k<n; ++k)
            if ( a[k] > s )  s = a[k];
        return  s;
    }

    ulong min_val()  const
    // Return value of minimal digit.
    // Return 0 for n==0.
    // If the minimum is known, use num_val().
    // If the minium is known to be zero, use num_zeros().
    {
        if ( n==0 )  return 0;
        ulong s = ~0UL;  // max ulong
        for (ulong k=0; k<n; ++k)
            if ( a[k] < s )  s = a[k];
        return  s;
    }

    ulong min_max_diff()  const
    // return maxval - minval, return 0 for n=0.
    {
        if ( n==0 )  return 0;
        ulong mi = a[0], ma = a[0];
        for (ulong k=1; k<n; ++k)
        {
            const ulong d = a[k];
            if ( d < mi )  mi = d;
            if ( d > ma )  ma = d;
        }
        return ma - mi;
    }

    ulong min_max_num_diff()  const
    // return abs( (number of maxval) - (number of minval) )
    // return 0 for n=0.
    // Result s in range 0 <= s <= n-2
    {
        if ( n==0 )  return 0;

        ulong mi = a[0], ma = a[0];
        ulong cti = 1, cta = 1;
        for (ulong k=1; k<n; ++k)
        {
            const ulong d = a[k];
            if ( d == mi )  cti += 1;
            if ( d == ma )  cta += 1;
            if ( d < mi )  { mi = d;  cti = 1; }
            if ( d > ma )  { ma = d;  cta = 1; }
        }
        if ( cta > cti )  return cta - cti;
        else              return cti - cta;
    }

    ulong first_val()  const
    // Return value of first digit.
    // Return 0 for n==0.
    {
        if ( n==0 )  return 0;
        return a[0];
    }

    ulong last_val()  const
    // Return value of last digit.
    // Return 0 for n==0.
    {
        if ( n==0 )  return 0;
        return a[n-1];
    }


    // Number of occurrences of min/max/zero/even/odd/fixed-points:

    ulong num_zeros()  const
    // Return number of zeros.
    // Result s in range 0 <= s <= n.
    {
        ulong s = 0;
        for (ulong k=0; k<n; ++k)  s += ( 0==a[k] );
        return  s;
    }


    ulong num_fixed_points()  const
    // Return number of fixed points, i.e,
    // number of position k where a[k]==k.
    // Result s in range 0 <= s <= n.
    {
        ulong s = 0;
        for (ulong k=0; k<n; ++k)  s += ( k==a[k] );
        return  s;
    }


    ulong num_fixed_points_1()  const
    // Return number of fixed points with offset 1, i.e,
    // number of position k where a[k]==k+1.
    // Result s in range 0 <= s <= n.
    {
        ulong s = 0;
        for (ulong k=0; k<n; ++k)  s += ( k+1==a[k] );
        return  s;
    }


    ulong num_even_val()  const
    // Return number of even values.
    // Result s in range 0 <= s <= n.
    {
        ulong s = 0;
        for (ulong k=0; k<n; ++k)  s += ( 0 == (1UL & a[k]) );
        return  s;
    }

    ulong num_odd_val()  const
    // Return number of odd values.
    // Result s in range 0 <= s <= n.
    {
        ulong s = 0;
        for (ulong k=0; k<n; ++k)  s += ( 0 != (1UL & a[k]) );
        return  s;
    }


    ulong num_max_val()  const
    // Return number of occurrences of the maximal value.
    // Result s in range 1 <= s <= n.
    {
        if ( n<=1 )  return n;
        ulong mxct = 1,  mxv = a[0];  // need n!=0
        for (ulong k=1; k<n; ++k)
        {
            const ulong ak = a[k];
            if ( ak >= mxv )
            {
                mxct += 1;
                if ( ak > mxv )  mxct = 1;
                mxv = ak;
            }
        }
        return mxct;
    }

    ulong num_min_val()  const
    // Return number of occurrences of the minimal value.
    // If minimal value is know to be zero, use num_zeros().
    // Result s in range 1 <= s <= n.
    {
        if ( n<=1 )  return n;
        ulong mnct = 1,  mnv = a[0];  // need n!=0
        for (ulong k=1; k<n; ++k)
        {
            const ulong ak = a[k];
            if ( ak <= mnv )
            {
                mnct += 1;
                if ( ak < mnv )  mnct = 1;
                mnv = ak;
            }
        }
        return mnct;
    }



    // first/last occurrence of min/max/zero/value:

    ulong first_max_idx()  const
    // Return position of first element that is maximal.
    // Result s in range 0 <= s <= n-1.
    {
        if ( n==0 )  return 0;
        ulong mxp = 0,  mxv = a[0];  // need n!=0
        for (ulong k=1; k<n; ++k)
            if ( a[k] > mxv )  { mxv=a[k];  mxp=k; }
        return mxp;
    }

    ulong last_max_idx()  const
    // Return position of last element that is maximal.
    // Result s in range 0 <= s <= n-1.
    {
        if ( n==0 )  return 0;
        ulong mxp = 0,  mxv = a[0];  // need n!=0
        for (ulong k=1; k<n; ++k)
            if ( a[k] >= mxv )  { mxv=a[k];  mxp=k; }
        return mxp;
    }


    ulong first_min_idx()  const
    // Return position of first element that is minimal.
    // If the minimum is known to be zero, use first_zero_idx().
    // Result s in range 0 <= s <= n-1.
    {
        if ( n==0 )  return 0;
        ulong mnp = 0,  mnv = a[0];  // need n!=0
        for (ulong k=1; k<n; ++k)
            if ( a[k] < mnv )  { mnv=a[k];  mnp=k; }
        return mnp;
    }

    ulong last_min_idx()  const
    // Return position of last element that is minimal.
    // If the minimum is known to be zero, use last_zero_idx().
    // Result s in range 0 <= s <= n-1.
    {
        if ( n==0 )  return 0;
        ulong mnp = 0,  mnv = a[0];  // need n!=0
        for (ulong k=1; k<n; ++k)
            if ( a[k] <= mnv )  { mnv=a[k];  mnp=k; }
        return mnp;
    }


    ulong first_zero_idx()  const
    // Return position of first zero.
    // Result s in range 0 <= s <= n-1, or n if there is no zero.
    {
        for (ulong k=0; k<n; ++k)
            if ( a[k] == 0 )  return k;
        return  n;
    }

    ulong last_zero_idx()  const
    // Return position of last zero.
    // Result s in range 0 <= s <= n-1, or n if there is no zero.
    {
        if ( n==0 )  return n;
        ulong k = n;
        do
        {
            --k;
            if ( a[k]==0 )  return k;
        }
        while ( k );
        return  n;
    }

    ulong first_val_idx(ulong v)  const
    // Return position of first occurrence of v.
    // Result s in range 0 <= s <= n-1, or n if there is no value v.
    {
//        if ( n==0 )  return n;
        for (ulong k=0; k<n; ++k)
            if ( a[k] == v )  return k;
        return  n;
    }

    ulong last_val_idx(ulong v)  const
    // Return position of last occurrence of the value v.
    // Result s in range 0 <= s <= n-1, or n if there is no value v.
    {
        if ( n==0 )  return n;
        ulong k = n;
        do
        {
            --k;
            if ( a[k]==v )  return k;
        }
        while ( k );
        return  n;
    }

    ulong min_ascent()  const
    // Return minimal ascent.
    // Result s in range 0 <= s <= n-1.
    {
        if ( n<=1 )  return 0;  // note
        ulong k = ~0UL;
        for (ulong j=1; j<n; ++j)
        {
            const ulong d = a[j] - a[j-1];
            if ( a[j] >= a[j-1] )
                if ( d < k )  k = d;
        }
        return k;
    }

    ulong max_ascent()  const
    // Return maximal ascent.
    // Result s in range 0 <= s <= n-1.
    {
        ulong k = 0;
        for (ulong j=1; j<n; ++j)
        {
            const ulong d = a[j] - a[j-1];
            if ( a[j] > a[j-1] )
                if ( d > k )  k = d;
        }
        return k;
    }

    ulong min_descent()  const
    // Return minimal descent.
    // Result s in range 0 <= s <= n-1.
    {
        if ( n<=1 )  return 0;  // note
        ulong k = ~0UL;
        for (ulong j=1; j<n; ++j)
        {
            const ulong d = a[j-1] - a[j];
            if ( a[j-1] >= a[j] )
                if ( d < k )  k = d;
        }
        return k;
    }

    ulong max_descent()  const
    // Return maximal descent.
    // Result s in range 0 <= s <= n-1.
    {
        ulong k = 0;
        for (ulong j=1; j<n; ++j)
        {
            const ulong d = a[j-1] - a[j];
            if ( a[j-1] > a[j] )
                if ( d > k )  k = d;
        }
        return k;
    }


    ulong min_displacement()  const
    // Return min( abs( a[j] - j ) ).
    {
        long md = (long)n;
        for (ulong j=0; j<n; ++j)
        {
            long d = (long)( a[j] - j );
            if ( d < 0 )  d = -d;
            if ( d < md )  md = d;
        }

        return (ulong)md;
    }

    ulong max_displacement()  const
    // Return max( abs( a[j] - j ) ).
    {
        long md = 0;
        for (ulong j=0; j<n; ++j)
        {
            long d = (long)( a[j] - j );
            if ( d < 0 )  d = -d;
            if ( d > md )  md = d;
        }

        return (ulong)md;
    }

    ulong min_displacement_nfp()  const
    // Return min( abs( a[j] - j ) ) for all a[j] != j
    // Return zero if all element are fixed points.
    {
        bool q = true;
        for (ulong j=0; j<n; ++j)
            if ( a[j] != j )  { q=false; break; }
        if ( q )  return 0;

        long md = (long)n;
        for (ulong j=0; j<n; ++j)
        {
            long d = (long)( a[j] - j );
            if ( d == 0 )  continue;
            if ( d < 0 )  d = -d;
            if ( d < md )  md = d;
        }

        return (ulong)md;
    }

//    ulong max_displacement_nfp()  const  // same as max_displacement()
//    // Return max( abs( a[j] - j ) ) for all a[j] != j
//    // Return zero if all element are fixed points.
//    {
//        bool q = true;
//        for (ulong j=0; j<n; ++j)
//            if ( a[j] != j )  { q=false; break; }
//        if ( q )  return 0;
//
//        long md = 0;
//        for (ulong j=0; j<n; ++j)
//        {
//            long d = (long)( a[j] - j );
//            if ( d == 0 )  continue;
//            if ( d < 0 )  d = -d;
//            if ( d > md )  md = d;
//        }
//
//        return (ulong)md;
//    }



    // stats using histogram h[]:
protected:
    void histogram()  const
    // Write histogram into h[].
    {
        for (ulong j=0; j<=hn; ++j)  h[j] = 0;
        for (ulong j=0; j<n; ++j)  h[a[j]] += 1;
    }

public:
    ulong num_sorts()  const
    // Return number of nonzero buckets in histogram h[].
    {
        histogram();
        ulong r = 0;
        for (ulong j=0; j<=hn; ++j)  r += (h[j] != 0);
        return r;
    }

    ulong max_num_vals()  const
    // Return max frequency in histogram.
    {
        histogram();
        ulong r = 0;
        for (ulong j=0; j<=hn; ++j)
            if ( h[j] > r )  r = h[j];
        return r;
    }

    ulong min_num_vals()  const
    // Return min frequency in histogram.
    {
        if ( n == 0 )  return 0;
        histogram();
        ulong r = n;
        for (ulong j=0; j<=hn; ++j)
            if ( h[j] < r )  r = h[j];
        return r;
    }

    ulong min_num_vals_nz()  const
    // Return min frequency in histogram, ignore zero multiplicity.
    {
        if ( n == 0 )  return 0;
        histogram();
        ulong r = n;
        for (ulong j=0; j<=hn; ++j)
        {
            if ( h[j] ==0 )  continue;
            if ( h[j] < r )  r = h[j];
        }
        return r;
    }
};
// -------------------------


#endif  // !defined HAVE_WORD_STATS_H__
