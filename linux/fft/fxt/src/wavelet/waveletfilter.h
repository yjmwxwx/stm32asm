#if !defined HAVE_WAVELETFILTER_H__
#define      HAVE_WAVELETFILTER_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong
#include <cmath>  // fabs(), pow()

// Daubechies bases are given in daubechies.h

class wavelet_filter
{
private:  // forbidden
    const wavelet_filter & operator =(const wavelet_filter &);
    wavelet_filter(const wavelet_filter &);

public:
    double *h_;  // low-pass filter
    double *g_;  // high-pass filter
    ulong n_;    // number of taps

    void ctor_core()
    {
        h_ = new double[n_];
        g_ = new double[n_];
    }

    explicit wavelet_filter(const double *w, ulong n=0)
    {
        if ( 0!=n )  n_ = n;
        else  // zero terminated array w[]
        {
            n_ = 0;
            while ( w[n_] != 0.0 )  ++n_;
        }

        ctor_core();

        for (ulong i=0, j=n_-1;  i<n_;  ++i, --j)
        {
            h_[i] = w[i];

            if ( !(i&1) )  g_[j] = -h_[i];  // even indices
            else           g_[j] = +h_[i];  // odd indices
        }
    }

    explicit wavelet_filter(const double *h, const double *g, ulong n)
    {
        n_ = n;
        ctor_core();
        for (ulong i=0;  i<n_;  ++i)  h_[i] =h[i];
        for (ulong i=0;  i<n_;  ++i)  g_[i] =g[i];
    }

    ~wavelet_filter()
    {
        delete [] h_;
        delete [] g_;
    }


public:
//    double sum_even()  const  { return sum_even(h_, n_); }
//    double sum_odd()  const  { return sum_odd(h_, n_); }
    double norm_sqr(ulong s=0)  const  { return norm_sqr(h_, n_, s); }
    double moment(ulong x=0)  const  { return moment(h_, n_, x); }

    bool check(double eps=1e-6) const
    {
        if ( fabs(norm_sqr(0)-1.0) > eps )  return false;

        for (ulong i=1;  i<n_/2;  ++i)
        {
            if ( fabs(norm_sqr(i)) > eps )  return false;
        }

        return true;
    }

public:  // static methods
//    static double sum_even(const double *h, ulong n)
//    {
//        double v = 0;
//        for (ulong k=0; k<n; k+=2)  v += h[k];
//        return  v;
//    }
//
//    static double sum_odd(const double *h, ulong n)
//    {
//        double v = 0;
//        for (ulong k=1; k<n; k+=2)  v += h[k];
//        return  v;
//    }

    static double norm_sqr(const double *h, ulong n, ulong s=0)
    {
        s *= 2;  // Note!
        if ( s>=n )  return 0.0;

        double v = 0;
        for (ulong k=0, j=s;  j<n;  ++k, ++j)  v += (h[k]*h[j]);
        return  v;
    }

    static double moment(const double *h, ulong n, ulong x=0)
    {
//        if ( 0==x )  return  sum_even(h, n) - sum_odd(h, n);
        if ( 0==x )
        {
            double v = 0.0;
            for (ulong k=0; k<n; k+=2)  v += h[k];
            for (ulong k=1; k<n; k+=2)  v -= h[k];
            return v;
        }

        double dk;
        const double dx = (double)x;

        double ve = 0;
        dk = 2.0;
        for (ulong k=2;  k<n;  k+=2, dk+=2.0)  ve += (pow(dk, dx) * h[k]);

        double vo = 0;
        dk = 1.0;
        for (ulong k=1;  k<n;  k+=2, dk+=2.0)  vo += (pow(dk, dx) * h[k]);
        return  ve - vo;
    }
};
// -------------------------


#endif  // !defined HAVE_WAVELETFILTER_H__
