#if !defined  HAVE_LEFT_RIGHT_ARRAY_H__
#define       HAVE_LEFT_RIGHT_ARRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


// whether to include some O(n) methods for testing purposes
//#define LR_WITH_DUMB_METHODS  // default off


class left_right_array
// Maintain index array [0,...,n-1], keep track which index is set or free.
// Allows, in time O(log(n)), to
// - find k-th free index (where 0<=k<=num_free())
// - find k-th set index (where 0<=k<=num_set())
// - determine how many indices are free/set to the left/right of
//   an absolute index i (where 0<=i<n).
{
public:
    ulong *fl_;  // Free indices Left (including current element) in bsearch interval
    bool *tg_;   // tags: tg[i]==true if and only if index i is free
    ulong n_;    // total number of indices
    ulong f_;    // number of free indices

private:  // have pointer data
    left_right_array(const left_right_array&);  // forbidden
    left_right_array & operator = (const left_right_array&);  // forbidden

public:
    explicit left_right_array(ulong n)
    {
        n_ = n;
        fl_ = new ulong[n_];
        tg_ = new bool[n_];
        free_all();
    }

    ~left_right_array()
    {
        delete [] fl_;
        delete [] tg_;
    }

    ulong num_free() const  { return f_; }
    ulong num_set() const  { return  n_ - f_; }
    bool is_free(ulong i) const  { return  tg_[i]; }
    bool is_set(ulong i) const  { return  ! tg_[i]; }

private:
    void init_rec(ulong i0, ulong i1)
    // Set elements of fl[0,...,n-2] according to all indices free.
    // The element fl[n-1] needs to be set to 1 afterwards.
    // Work is O(n).
    {
        if ( (i1-i0)!=0 )
        {
            ulong t = (i1+i0)/2;
            init_rec(i0, t);
            init_rec(t+1, i1);
        }
        fl_[i1] = i1-i0+1;
    }

public:
    void free_all()
    // Mark all indices as free.
    {
        f_ = n_;
        for (ulong j=0; j<n_; ++j)  tg_[j] = true;
        init_rec(0, n_-1);
        fl_[n_-1] = 1;
    }

    void set_all()
    // Mark all indices of as set.
    {
        f_ = 0;
        for (ulong j=0; j<n_; ++j)  tg_[j] = false;
        for (ulong j=0; j<n_; ++j)  fl_[j] = 0;
    }


    ulong get_free_idx(ulong k)  const
    // Return the k-th ( 0 <= k < num_free() ) free index.
    // Return ~0UL if k is out of bounds.
    // Work is O(log(n)).
    {
        if ( k >= num_free() )  return ~0UL;

        ulong i0 = 0,  i1 = n_-1;
        while ( 1 )
        {
            ulong t = (i1+i0)/2;
            if ( (fl_[t] == k+1) && (tg_[t]) )  return t;

            if ( fl_[t] > k )  // left:
            {
                i1 = t;
            }
            else   // right:
            {
                i0 = t+1;  k-=fl_[t];
            }
        }
    }


    ulong get_free_idx_chg(ulong k)
    // Return the k-th ( 0 <= k < num_free() ) free index.
    // Return ~0UL if k is out of bounds.
    // Change the arrays and fl[] and tg[] reflecting
    //   that index i will be set afterwards.
    // Work is O(log(n)).
    {
        if ( k >= num_free() )  return ~0UL;

        --f_;

        ulong i0 = 0,  i1 = n_-1;
        while ( 1 )
        {
            ulong t = (i1+i0)/2;

            if ( (fl_[t] == k+1) && (tg_[t]) )
            {
                --fl_[t];
                tg_[t] = false;
                return t;
            }

            if ( fl_[t] > k )  // left:
            {
                --fl_[t];
                i1 = t;
            }
            else    // right:
            {
                i0 = t+1;  k-=fl_[t];
            }
        }
    }


    ulong get_set_idx(ulong k)  const
    // Return the k-th ( 0 <= k < num_set() ) set index.
    // Return ~0UL if k is out of bounds.
    // Work is O(log(n)).
    {
        if ( k >= num_set() )  return ~0UL;

        ulong i0 = 0,  i1 = n_-1;
        while ( 1 )
        {
            ulong t = (i1+i0)/2;
            // how many elements to the left are set:
            ulong slt = t-i0+1 - fl_[t];

            if ( (slt == k+1) && (tg_[t]==false) )  return t;

            if ( slt > k )  // left:
            {
                i1 = t;
            }
            else   // right:
            {
                i0 = t+1;  k-=slt;
            }
        }
    }

    ulong get_set_idx_chg(ulong k)
    // Return the k-th ( 0 <= k < num_set() ) set index.
    // Return ~0UL if k is out of bounds.
    // Change the arrays and fl[] and tg[] reflecting
    //   that index i will be freed afterwards.
    // Work is O(log(n)).
    {
        if ( k >= num_set() )  return ~0UL;

        ++f_;

        ulong i0 = 0,  i1 = n_-1;
        while ( 1 )
        {
            ulong t = (i1+i0)/2;
            // how many elements to the left are set:
            ulong slt = t-i0+1 - fl_[t];

            if ( (slt == k+1) && (tg_[t]==false) )
            {
                ++fl_[t];
                tg_[t] = true;
                return t;
            }

            if ( slt > k )  // left:
            {
                ++fl_[t];
                i1 = t;
            }
            else   // right:
            {
                i0 = t+1;  k-=slt;
            }
        }
    }


    // The methods num_[FS][LR][IE](ulong i) return the number of
    // Free/Set indices Left/Right if (absolute) index i, Including/Excluding i.
    // Return ~0UL if i >= n.

    ulong num_FLE(ulong i)  const
    // Return number of Free indices Left of (absolute) index i (Excluding i).
    // Work is O(log(n)).
    {
        if ( i >= n_ )  { return ~0UL; }  // out of bounds

        ulong i0 = 0,  i1 = n_-1;
        ulong ns = i;  // number of set element left to i (including i)
        while ( 1 )
        {
            if ( i0==i1 )  break;

            ulong t = (i1+i0)/2;
            if ( i<=t )  // left:
            {
                i1 = t;
            }
            else   // right:
            {
                ns -= fl_[t];
                i0 = t+1;
            }
        }

        return  i-ns;
    }

    ulong num_FLI(ulong i)  const
    // Return number of Free indices Left of (absolute) index i (Including i).
    {
        if ( i >= n_ )  { return ~0UL; }
        return num_FLE(i) + tg_[i];
    }


    ulong num_FRE(ulong i)  const
    // Return number of Free indices Right of (absolute) index i (Excluding i).
    {
        if ( i >= n_ )  { return ~0UL; }
        return  num_free() - num_FLI(i);
    }

    ulong num_FRI(ulong i)  const
    // Return number of Free indices Right of (absolute) index i (Including i).
    {
        if ( i >= n_ )  { return ~0UL; }
        return  num_free() - num_FLE(i);
    }


    ulong num_SLE(ulong i)  const
    // Return number of Set indices Left of (absolute) index i (Excluding i).
    {
        if ( i >= n_ )  { return ~0UL; }
        return i - num_FLE(i);
    }

    ulong num_SLI(ulong i)  const
    // Return number of Set indices Left of (absolute) index i (Including i).
    {
        if ( i >= n_ )  { return ~0UL; }
        return i - num_FLE(i) + !tg_[i];
    }


    ulong num_SRE(ulong i)  const
    // Return number of Set indices Right of (absolute) index i (Excluding i).
    {
        if ( i >= n_ )  { return ~0UL; }
        return  num_set() - num_SLI(i);
    }

    ulong num_SRI(ulong i)  const
    // Return number of Set indices Right of (absolute) index i (Including i).
    {
        if ( i >= n_ )  { return ~0UL; }
        return  num_set() - i + num_FLE(i);
    }


#ifdef LR_WITH_DUMB_METHODS   // Work with all methods *_dumb() is O(n).
    ulong get_free_idx_dumb(ulong k)  const
    // Return the k-th ( 0 <= k < num_free() ) free index.
    // Return ~0UL if k is out of bounds.
    {
        if ( k >= num_free() )  return ~0UL;

        ulong idx = 0;
        for ( ; idx<n_; ++idx)
        {
            if ( tg_[idx]==true )
            {
                if ( k==0 )  break;
                --k;
            }
        }
        return idx;
    }

    ulong get_set_idx_dumb(ulong k)  const
    // Return the k-th ( 0 <= k < num_set() ) set index.
    // Return ~0UL if k is out of bounds.
    {
        if ( k >= num_set() )  return ~0UL;

        ulong idx = 0;
        for ( ; idx<n_; ++idx)
        {
            if ( tg_[idx]==false )
            {
                if ( k==0 )  break;
                --k;
            }
        }
        return idx;
    }


    ulong num_FLE_dumb(ulong i)  const
    // Return number of Free indices Left of (absolute) index i (Excluding i).
    {
        if ( i >= n_ )  { return ~0UL; }
        ulong nf = 0;
        for (ulong j=0; j<i; ++j)  nf += tg_[j];
        return nf;
    }

    ulong num_FLI_dumb(ulong i)  const
    // Return number of Free indices Left of (absolute) index i (Including i).
    {
        if ( i >= n_ )  { return ~0UL; }
        ulong nf = 0;
        for (ulong j=0; j<=i; ++j)  nf += tg_[j];
        return nf;
    }


    ulong num_FRE_dumb(ulong i)  const
    // Return number of Free indices Right of (absolute) index i (Excluding i).
    {
        if ( i >= n_ )  { return ~0UL; }
        ulong nf = 0;
        for (ulong j=i+1; j<n_; ++j)  nf += tg_[j];
        return nf;
    }

    ulong num_FRI_dumb(ulong i)  const
    // Return number of Free indices Right of (absolute) index i (Including i).
    {
        if ( i >= n_ )  { return ~0UL; }
        ulong nf = 0;
        for (ulong j=i; j<n_; ++j)  nf += tg_[j];
        return nf;
    }


    ulong num_SLE_dumb(ulong i)  const
    // Return number of Set indices Left of (absolute) index i (Excluding i).
    {
        if ( i >= n_ )  { return ~0UL; }
        ulong nf = 0;
        for (ulong j=0; j<i; ++j)  nf += !tg_[j];
        return nf;
    }

    ulong num_SLI_dumb(ulong i)  const
    // Return number of Set indices Left of (absolute) index i (Including i).
    {
        if ( i >= n_ )  { return ~0UL; }
        ulong nf = 0;
        for (ulong j=0; j<=i; ++j)  nf += !tg_[j];
        return nf;
    }


    ulong num_SRE_dumb(ulong i)  const
    // Return number of Set indices Right of (absolute) index i (Excluding i).
    {
        if ( i >= n_ )  { return ~0UL; }
        ulong nf = 0;
        for (ulong j=i+1; j<n_; ++j)  nf += !tg_[j];
        return nf;
    }

    ulong num_SRI_dumb(ulong i)  const
    // Return number of Set indices Right of (absolute) index i (Including i).
    {
        if ( i >= n_ )  { return ~0UL; }
        ulong nf = 0;
        for (ulong j=i; j<n_; ++j)  nf += !tg_[j];
        return nf;
    }

#endif  // LR_WITH_DUMB_METHODS
};
// -------------------------

//#undef LR_WITH_DUMB_METHODS  // leave defined


#endif  // !defined HAVE_LEFT_RIGHT_ARRAY_H__
