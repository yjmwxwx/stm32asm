#if !defined  HAVE_MK_SPECIAL_DIGRAPHS_H__
#define       HAVE_MK_SPECIAL_DIGRAPHS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "graph/digraph-paths.h"
#include "graph/digraph.h"
#include "fxttypes.h"

//: Auxiliary routines for special graphs

// graph/mk-complete-digraph.cc:
digraph * make_complete_digraph(ulong n);


// graph/mk-debruijn-digraph.cc:
digraph * make_debruijn_digraph(ulong n);
digraph * make_complement_shift_digraph(ulong n);
digraph * make_debruijn_digraph(ulong n, ulong m);

// graph/mk-gray-digraph.cc:
digraph * make_gray_digraph(ulong n, bool rq=0);
ulong start_monotonic_gray_path(digraph_paths &dp, ulong n);


// graph/mk-paren-gray-digraph.cc:
digraph * make_parengray_digraph(ulong nb, ulong pcd);

// graph/mk-fibrep-gray-digraph.cc:
digraph * make_fibrepgray_digraph(ulong n);


// graph/mk-mtl-digraph.cc:
digraph * make_mtl_digraph(ulong k, bool rq=0);

// graph/mk-perm-gray-digraph.cc:
digraph * make_perm_gray_digraph(ulong n, bool stq);

// graph/mk-perm-pref-rev-digraph.cc:
digraph * make_perm_pref_rev_digraph(ulong n);

// graph/mk-perm-pref-rot-digraph.cc:
digraph * make_perm_pref_rot_digraph(ulong n, bool rq=0);


// graph/mk-lyndon-gray-digraph.cc:

class lyngray_dat
// Data needed for Gray paths through Lyndon words.
{
public:
    ulong *ww;  // Lyndon words (==sv[] in digraph)
    uchar *rr;  // rotations of Lyndon word in Gray path
    uchar *dd;  // delta sequence of Gray path
    ulong nbits;  // number of bits of Lyndon words

private:  // have pointer data
    lyngray_dat(const lyngray_dat&);  // forbidden
    lyngray_dat & operator = (const lyngray_dat&);  // forbidden

public:
    explicit lyngray_dat(ulong ng, ulong nb, ulong *tww);
    ~lyngray_dat();

    ulong get(ulong *&w, uchar *&r, uchar *&d)
    { w = ww; r = rr; d = dd; return  nbits; }
};
// -------------------------

void print_lyndon_gray_digraph(digraph &dg, lyngray_dat *ldat);
bool lyndon_gray_rot_delta(const ulong *rv, ulong ng, lyngray_dat *ldat);
void print_lyndon_gray_path(const digraph_paths &dp, lyngray_dat *ldat);
digraph * make_lyndon_gray_digraph(ulong n, lyngray_dat *&ldat, ulong rot0q=0);

// graph/lyndon-cmp.cc:
int lyndon_cmp0(const ulong &a, const ulong &b);
int lyndon_cmp1(const ulong &a, const ulong &b);
int lyndon_cmp2(const ulong &a, const ulong &b);
int lyndon_cmp3(const ulong &a, const ulong &b);
int lyndon_cmp4(const ulong &a, const ulong &b);
int lyndon_cmp5(const ulong &a, const ulong &b);
int lyndon_cmp6(const ulong &a, const ulong &b);
int lyndon_cmp7(const ulong &a, const ulong &b);



#endif  // !defined HAVE_MK_SPECIAL_DIGRAPHS_H__
