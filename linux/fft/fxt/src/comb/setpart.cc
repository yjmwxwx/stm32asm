// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/setpart.h"

#include "aux0/sign.h"  // Abs()

#include "fxtio.h"
#include "fxttypes.h"



int
setpart::cp_append(const int *src, int *dst, int k, int a)
// Copy partition in src[0,...,k-2] to dst[0,...,k-1]
// append element k at subset a (a>=0)
// Return number of sets in created partition.
{
    int ct = 0;
    for (int j=0; j<k-1; ++j)
    {
        int e = src[j];
        if ( e > 0 )  dst[j] = e;
        else
        {
            if ( a==ct )
            {
                dst[j]=-e;
                ++dst;
                dst[j]=-k;
            }
            else  dst[j] = e;
            ++ct;
        }
    }
    if ( a>=ct )  { dst[k-1] = -k; ++ct; }

    return ct;
}
// -------------------------


int
setpart::next_rec(int k)
// Update partition in level k from partition in level k-1  (k<=n)
// Return number of sets in created partition
{
    if ( k<=1 )  return 0;  // current is last

    int d = d_[k];
    int as = as_[k] + d;
    bool ovq = ( (d>0) ? (as>ns_[k-1]) : (as<0) );
    if ( ovq )  // have to recurse
    {
        int ns1 = next_rec(k-1);
        if ( 0==ns1 )  return 0;

        d = ( xdr_ ? -d : dr0_ );
        d_[k] = d;

        as = ( (d>0) ? 0 : ns_[k-1] );
    }
    as_[k] = as;

    int ns = cp_append(pp_[k-1], pp_[k], k, as);
    ns_[k] = ns;
    return  ns;
}
// -------------------------


void
setpart::first(bool xdr, int dr0)
{
    dr0 = ( (dr0>=0) ? +1 : -1 );
    dr0_ = dr0;

    xdr_ = xdr;

    p_[0] = -1;

    int n = n_;
    if ( dr0_>0 )
    {
        for (int k=0; k<=n; ++k)  as_[k] = 0;
        for (int k=0; k<=n; ++k)  ns_[k] = 1;
    }
    else
    {
        for (int k=0; k<=n; ++k)  as_[k] = k - 1;
        for (int k=0; k<=n; ++k)  ns_[k] = k;
    }

    for (int k=0; k<=n; ++k)  d_[k] = dr0_;

    for (int k=2; k<=n; ++k)
    {
        cp_append(pp_[k-1], pp_[k], k, as_[k]);
    }
}
// -------------------------


void
setpart::print_internal()  const
{
//    const char sep[]=", ";
    const char sep[]=" ";

    int n = n_;
    const int *x = pp_[n];

    cout << "as[ ";
    for (int j=1; j<=n; ++j)  cout << as_[j] << sep;
    cout << "]    ";

    cout << "ns[ ";
    for (int j=1; j<=n; ++j)  cout << ns_[j] << sep;
    cout << "]    ";

    cout << "d[ ";
    for (int j=1; j<=n; ++j)  cout << (d_[j]>0 ? '+' : '-') << sep;
    cout << "]    ";

    cout << "x[ ";
    for (int j=0; j<n; ++j)
    {
        const long axj = (x[j]>0 ? x[j] : -x[j]);
        cout << (x[j]>0?'+':'-') << axj << sep;
    }
    cout << "]    ";
}
// -------------------------

int
setpart::print_p(int k)  const
{
    const int *x = pp_[k];
    int n = k;

    int nch = 1;  // number of chars printed
    cout << "{";
    for (int j=0; j<n; ++j)
    {
        int e = x[j];
        if ( e>0 ) { cout << e << ", ";  nch += 3; }
        else
        {
            e = -e;
            cout << e << "}";  nch += 2;
            if ( j+1<n )  { cout << ", {";  nch +=3; }
        }
    }

    if ( n>9 )
    {
        nch += (n-9);
        if ( n>99 )  nch += (n-99);
    }

    return nch;
}
// -------------------------
