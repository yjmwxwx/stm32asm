// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "graph/mk-special-digraphs.h"
#include "graph/digraph.h"

#include "sort/sort.h"
#include "sort/bsearch.h"
#include "sort/unique.h"

#include "sort/sortfunc.h"

#include "comb/num-necklaces.h"

#include "mod/primes.h"

#include "bits/bit-necklace.h"
#include "bits/bit2pow.h"
#include "bits/bitcyclic-minmax.h"
#include "bits/bitcyclic-period.h"
#include "bits/bitcyclic-match.h"
#include "bits/print-bin.h"
#include "bits/bitlow.h"
//#include "bits/bit2pow.h"
#include "bits/bitrotate.h"
#include "bits/bitsperlong.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "fxtalloca.h"

#include "jjassert.h"  //  jjnote: asserts used in code: Lyndon word graphs


lyngray_dat::lyngray_dat(ulong ng, ulong nb, ulong *tww)
{
    ww = tww;
    rr = new uchar[ng];
    dd = new uchar[ng];
    nbits = nb;
}
// -------------------------

lyngray_dat::~lyngray_dat()
{
    delete [] rr;
    delete [] dd;
}
// -------------------------



void
print_lyndon_gray_digraph(const digraph &dg, lyngray_dat *ldat)
// Print Lyndon-Gray digraph.
{
    cout << "Node: Edge0 Edge1 ..." << endl;
    ulong ng = dg.ng_;
    const ulong *e = dg.e_;
    const ulong *ep = dg.ep_;
    const ulong *ww = ldat->ww;
    const ulong nbits = ldat->nbits;
    for (ulong k=0; k<ng; ++k)
    {
        cout << setw(3) << k;
        print_bin(" ", ww[k], nbits);
        cout << ":  ";
        for (ulong j=ep[k]; j<ep[k+1]; ++j)
        {
//            cout << setw(3) << e[j];
            print_bin(" ", ww[e[j]], nbits);
            cout << " ";
        }
        cout << endl;
    }
    cout << "  #nodes=" << dg.num_nodes();
    cout << "  #edges=" << dg.num_edges();
    cout << endl;
    cout << endl;
}
// -------------------------


static inline ulong cyc_match(ulong v1, ulong v0, ulong nbits)
// try to find a cyclic match such that lowest bit equals one.
{
    ulong r0 = bit_cyclic_dist1_match(v1, v0, nbits);
    ulong w = bit_rotate_left(v1, r0, nbits);
    if ( w & 1UL )  return r0;

    for (ulong k=r0+1; k<nbits; ++k)
    {
        w = bit_rotate_left(v1, 1, nbits);
        ulong c = v1 ^ v0;
        if ( one_bit_q(c) && (w&1UL) )  return  k;
    }

    return  r0;
}
// -------------------------


bool
lyndon_gray_rot_delta(const ulong *rv, ulong ng, lyngray_dat *ldat)
// Setup arrays with rotations (rr[]) and the delta sequence (dd[]).
// Return whether all rotations are zero.
{
    uchar *rr, *dd;
    ulong *ww;
    ulong nbits = ldat->get(ww, rr, dd);

    ulong v0 = 0;
    ulong zq = 0;
    ulong eq = 1;
    for (ulong k=0; k<ng; ++k)
    {
        ulong n = rv[k];  // node
        ulong v1 = ww[n];
//        ulong r = bit_cyclic_dist1_match(v1, v0, nbits);
        ulong r = cyc_match(v1, v0, nbits);
        rr[k] = (uchar)r;
        zq |= r;
        v1 = bit_rotate_left(v1, r, nbits);
        eq &= v1;
        ulong c = v0 ^ v1;
        c = lowest_one_idx(c);
        dd[k] = (uchar)c;

        v0 = v1;
        jjassert( r<=BITS_PER_LONG );
    }

//    return ( 0==zq );  // whether all rotations are zero
    return ( eq );  // whether lowest track is always one
}
// -------------------------


void
print_lyndon_gray_path(const digraph_paths &dp, lyngray_dat *ldat)
// Detailed print of path through Lyndon-Gray digraph.
{
    uchar *rr, *dd;
    ulong *ww;
    const ulong nbits = ldat->get(ww, rr, dd);
    const int inb = (int)nbits;  // for setw()

    const ulong *rv = dp.rv_;
    ulong ng = dp.ng_;

    cout << "    k :  [ node]  lyn_dec ";
    cout << setw(inb) << "lyn_bin";
    cout << " #rot ";
    cout << setw(inb) << "rot(lyn)" << "  ";
    cout << setw(inb) << "diff" << "  delta";
    cout << endl;
    for (ulong k=0; k<ng; ++k)
    {
        ulong n = rv[k];  // node
        ulong v1 = ww[n];

        cout << setw(5) << k << " :  ";
        cout << "[" << setw(5) << n << "]  ";
        cout << "  " << setw(5) << v1 << "  ";
        print_bin("", v1, nbits );

        ulong r = (ulong)rr[k];
        cout << " " << setw(2) << r;
        v1 = bit_rotate_left(v1, r, nbits);
//        v1 = zz[k];
        print_bin("   ", v1, nbits );

        ulong c = (ulong)dd[k];
        print_bin("   ", 1UL<<c, nbits );
        cout << " " << setw(2) << c;

        cout << endl;

        jjassert( r<BITS_PER_LONG );
    }
    cout << endl;
}
// -------------------------



//#include "bits/revbin.h"
//#include "bits/print-bin.h"

#define MINFUNC(p, n)  bit_cyclic_min(p, n)
//#define MINFUNC(p, n)  bit_cyclic_max(p, n)


static void make_lyndon(ulong n, ulong *ww, ulong ng)
// Fill all n-bit Lyndon words into ww[0,..,ng-1]
{
    bit_necklace bn(n);
    ulong k = 0;
    while ( bn.next() )
    {
        if ( 0==bn.is_lyndon_word() )  continue;
        ulong p = bn.data();
        p = MINFUNC(p, n);
        ww[k++] = p;
    }
    quick_sort(ww, ng);  // will be searched with bsearch()
}
// -------------------------


digraph *
make_lyndon_gray_digraph(ulong n, lyngray_dat *&ldat, ulong rot0q/*=0*/)
// Initialization for Lyndon-Gray digraph:
// n must be a prime <=BITS_PER_LONG.
{
//    jjassert( is_small_prime(n) );

    ulong ng = num_lyndon_tab[n];  // number of n-bit Lyndon words.

    ulong ne = ng * n;  // > number of edges
    ulong *ep, *e;
//    digraph dg(ng, ne, ep, e, true);
    digraph * dgp = new digraph(ng, ne, ep, e, true);
    digraph &dg = *dgp;

    ulong *ww = dg.vn_;
    ldat = new lyngray_dat(ng, n, ww);

    make_lyndon(n, ww, ng);

    ulong j = 0;
//    ulong m = (1UL<<n) - 1;
    ALLOCA(ulong, uu, n);
    for (ulong k=0; k<ng; ++k)  // for all nodes
    {
        ep[k] = j;
        ulong w = ww[k];
        ulong mct = 0;
        for (ulong c=0, b=1;  c<n;  ++c, b<<=1)  // for all neighbors
        {
            ulong vc = w ^ b;  // change one bit

            if ( n!=bit_cyclic_period(vc, n) )  continue;
//            if ( 0==vc )  continue;
//            if ( m==vc )  continue;

            ulong vm = MINFUNC(vc, n);
            if ( rot0q && (vm!=vc) )  continue;

            uu[mct++] = vm;
        }
        selection_sort(uu, mct);
        ulong u = unique(uu, mct);

        for (ulong i=0; i<u; ++i)
        {
            ulong vc = uu[i];
            ulong x = bsearch(ww, ng, vc);
            jjassert( x != ng );
            e[j++] = x;
        }
    }
    ep[ng] = j;
    jjassert( j<=ne );

//    return  dg;
    return  dgp;
}
// -------------------------
