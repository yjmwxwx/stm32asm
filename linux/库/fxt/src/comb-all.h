#if !defined HAVE_COMB_ALL_H__
#define      HAVE_COMB_ALL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014, 2015, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


//: Combinatorics

//: subsets:
#include "comb/subset-gray.h"
#include "comb/subset-gray-delta.h"
//#include "comb/subset-monotone.h"
#include "comb/subset-lex.h"
#include "comb/ksubset-lex.h"
#include "comb/subset-deltalex.h"
#include "comb/subset-debruijn.h"
#include "comb/ksubset-gray.h"
#include "comb/ksubset-twoclose.h"
#include "comb/ksubset-rec.h"
#include "comb/binary-sl-gray.h"
//
#include "comb/delta2gray.h"
#include "comb/monotonic-gray.h"
//
#include "comb/acgray.h"
// auxiliary routines:
#include "comb/test-gray.h"


//: combinations:
#include "comb/combination-lex.h"
#include "comb/combination-colex.h"
#include "comb/combination-revdoor.h"
#include "comb/combination-mod.h"
#include "comb/combination-emk.h"
#include "comb/combination-enup.h"
#include "comb/combination-endo.h"
#include "comb/combination-chase.h"
#include "comb/combination-rec.h"
#include "comb/combination-pref.h"


//: compositions:
#include "comb/composition-colex.h"
#include "comb/composition-colex2.h"
#include "comb/composition-ex-colex.h"
#include "comb/composition-ex-lex.h"
#include "comb/composition-nz-numparts.h"
//
#include "comb/composition-nz.h"
#include "comb/composition-nz-subset-lex.h"
#include "comb/composition-nz-rl.h"
#include "comb/composition-nz-gray.h"
#include "comb/composition-nz-gray2.h"
#include "comb/composition-nz-odd.h"
#include "comb/composition-nz-odd-subset-lex.h"
#include "comb/composition-nz-max.h"
#include "comb/composition-nz-min.h"
#include "comb/composition-nz-first-max.h"
#include "comb/composition-nz-binary.h"
#include "comb/composition-nz-smooth.h"
#include "comb/composition-nz-left-smooth.h"
#include "comb/composition-nz-left-2smooth.h"
#include "comb/composition-nz-i-smooth.h"
#include "comb/composition-nz-upstep.h"
#include "comb/composition-nz-weakly-unimodal.h"
#include "comb/composition-nz-carlitz.h"
#include "comb/composition-nz-minc.h"
#include "comb/composition-nz-superdiagonal.h"
#include "comb/composition-nz-restrpref.h"
//
#include "comb/composition-nz-sorts.h"
#include "comb/composition-nz-sorts2.h"
#include "comb/composition-nz-sorts2-pp.h"
//
#include "comb/composition-unimodal.h"
#include "comb/composition-dist-unimodal.h"
// auxiliary routines:
#include "comb/composition-rank.h"
#include "comb/comp2comb.h"
#include "comb/num-compositions.h"
#include "comb/print-composition-aa.h"
#include "comb/composition-nz-conj.h"
#include "comb/composition-nz-rank.h"
#include "comb/is-smooth.h"
#include "comb/is-composition-nz.h"
#include "comb/print-composition-by-sorts.h"
#include "comb/is-sorts-in-runs-sorted.h"
#include "comb/is-symmetric.h"
#include "comb/print-composition-unimodal.h"


//: ruler functions:
#include "comb/ruler-func.h"
#include "comb/ruler-func1.h"
#include "comb/ruler-func-s.h"

//: integer partitions:
#include "comb/partition-gen.h"
#include "comb/partition.h"
#include "comb/mpartition.h"
#include "comb/mpartition2.h"
#include "comb/partition-asc.h"
#include "comb/partition-desc.h"
#include "comb/partition-desc-bb.h"
#include "comb/partition-asc-subset-lex.h"
#include "comb/partition-asc-subset-lex-csh.h"
#include "comb/partition-odd-asc.h"
#include "comb/partition-odd-asc-subset-lex.h"
#include "comb/partition-odd-asc-subset-lex-csh.h"
#include "comb/partition-odd-desc.h"
#include "comb/partition-dist-asc.h"
#include "comb/partition-dist-asc-subset-lex.h"
#include "comb/partition-dist-asc-len.h"
#include "comb/partition-dist-d-asc.h"
#include "comb/partition-dist-desc.h"
#include "comb/partition-binary-asc.h"
#include "comb/partition-binary-desc.h"
#include "comb/partition-s-desc.h"
#include "comb/partition-2fall-desc.h"
#include "comb/partition-2fall-asc.h"
#include "comb/partition-2fall-asc-subset-lex.h"
#include "comb/partition-nonsquashing-desc.h"
#include "comb/partition-odd-nonsquashing-desc.h"
#include "comb/partition-strongly-decr-desc.h"
#include "comb/partition-asc-2rep.h"
#include "comb/partition-asc-2rep-subset-lex.h"
#include "comb/partition-asc-perim.h"
//
#include "comb/partition-rgs-lex.h"
//
#include "comb/binary-huffman.h"
//
#include "comb/partition-asc-sorts.h"
#include "comb/partition-asc-sorts2.h"
#include "comb/partition-asc-sorts2-pp.h"
//
// auxiliary routines:
#include "comb/partition-conj.h"
#include "comb/partition-hook-prod.h"
#include "comb/partition-boundary.h"
#include "comb/partition-odd-to-dist.h"
#include "comb/is-partition-asc.h"
#include "comb/is-partition-desc.h"
#include "comb/is-partition-rgs.h"
#include "comb/is-nonsquashing.h"
#include "comb/print-partition-conj.h"
#include "comb/print-partition-aa.h"


//: Catalan objects (like parenthesis strings, their RGS, and paths):
#include "comb/paren-lex.h"
#include "comb/paren.h"
#include "comb/paren-gray.h"
#include "comb/paren-pref.h"
#include "comb/catalan.h"
#include "comb/catalan-rgs.h"
#include "comb/catalan-rgs-gray.h"
#include "comb/catalan-rgs-gslex.h"
#include "comb/catalan-rgs-subset-lex.h"
#include "comb/catalan-path-lex.h"
#include "comb/catalan-step-rgs-lex.h"
#include "comb/catalan-step-rgs-colex.h"
#include "comb/catalan-step-rgs-subset-lexrev.h"
// auxiliary routines:
#include "comb/paren-string-to-rgs.h"
#include "comb/catalan-step-rgs-to-paren-string.h"
#include "comb/is-catalan-rgs.h"
#include "comb/is-catalan-path.h"
#include "comb/is-paren-string.h"
#include "comb/is-paren-position-word.h"
#include "comb/reverse-paren-string.h"
#include "comb/is-catalan-step-rgs.h"
#include "comb/print-catalan-step-rgs-aa.h"
#include "comb/print-catalan-path-aa.h"


//: Dyck words and their RGS:
#include "comb/dyck-rgs.h"
#include "comb/dyck-gray.h"
#include "comb/dyck-gray2.h"
#include "comb/dyck-pref.h"
#include "comb/dyck-pref2.h"
#include "comb/dyck-rgs-subset-lex.h"
// auxiliary routines:
#include "comb/is-dyck-rgs.h"


//: Motzkin and Schroeder paths:
#include "comb/motzkin-path-lex.h"
#include "comb/motzkin-rgs-lex.h"
#include "comb/motzkin-nonflat-rgs-lex.h"
#include "comb/motzkin-step-rgs-lex.h"
#include "comb/schroeder-path-lex.h"
#include "comb/schroeder-rgs-lex.h"
// auxiliary routines:
#include "comb/is-motzkin-path.h"
#include "comb/is-motzkin-rgs.h"
#include "comb/is-motzkin-step-rgs.h"
#include "comb/is-schroeder-path.h"
#include "comb/is-schroeder-rgs.h"


//: set partitions and their RGS:
#include "comb/setpart.h"
#include "comb/setpart-rgs-lex.h"
#include "comb/setpart-rgs-gray.h"
#include "comb/setpart-p-rgs-lex.h"
#include "comb/setpart-rgs-subset-lex.h"
#include "comb/setpart-ck-rgs.h"
#include "comb/setpart-zero-map-rgs.h"
#include "comb/setpart-s-zero-map-rgs.h"
#include "comb/setpart-ccf-rgs-lex.h"
// closely related RGS:
#include "comb/rgs-maxincr.h"
#include "comb/rgs-fincr.h"
#include "comb/rgs-kincr.h"
#include "comb/map23-rgs.h"
// auxiliary routines:
#include "comb/is-setpart-rgs.h"
#include "comb/is-noncrossing-setpart-rgs.h"
#include "comb/catalan-rgs-to-noncrossing-setpart-rgs.h"
#include "comb/is-setpart-ccf-perm.h"
#include "comb/is-zero-map-rgs.h"
#include "comb/print-zero-map-rgs.h"


//: ascent sequences, descent sequences, isoscent sequences:
#include "comb/ascent-rgs.h"
#include "comb/ascent-rgs-subset-lex.h"
#include "comb/ascent-nonflat-rgs.h"
#include "comb/ascent-alt-rgs.h"
#include "comb/descent-rgs.h"
#include "comb/isoscent-rgs.h"
// auxiliary routines:
#include "comb/is-ascent-rgs.h"
#include "comb/is-descent-rgs.h"
#include "comb/is-isoscent-rgs.h"


//: necklaces and deBruijn sequences:
#include "comb/necklace.h"
#include "comb/binary-necklace.h"
#include "comb/num-necklaces.h"
#include "comb/debruijn.h"
#include "comb/binary-debruijn.h"


//: mixed radix numbers:
#include "comb/mixedradix-lex.h"
#include "comb/mixedradix-colex.h"
#include "comb/mixedradix-subset-lex.h"
#include "comb/mixedradix-subset-lexrev.h"
#include "comb/mixedradix-sl-gray.h"
#include "comb/mixedradix-gslex.h"
#include "comb/mixedradix-gslex2.h"
#include "comb/mixedradix-gslex-alt.h"
#include "comb/mixedradix-gslex-alt2.h"
#include "comb/mixedradix-gray.h"
#include "comb/mixedradix-gray2.h"
#include "comb/mixedradix-modular-gray.h"
#include "comb/mixedradix-modular-gray2.h"
#include "comb/mixedradix-endo.h"
#include "comb/mixedradix-endo-gray.h"
#include "comb/mixedradix-rfact.h"
#include "comb/mixedradix-sod-lex.h"
#include "comb/mixedradix-naf.h"
#include "comb/mixedradix-naf-gray.h"
#include "comb/mixedradix-naf-subset-lex.h"
#include "comb/mixedradix-restrpref.h"
#include "comb/skew-binary.h"
// auxiliary routines:
#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/check-mixedradix.h"

//: permutations:
#include "comb/perm-lex.h"
#include "comb/perm-lex-inv.h"
#include "comb/perm-lex2.h"
#include "comb/perm-colex.h"
#include "comb/perm-rec.h"
#include "comb/perm-mv0.h"
#include "comb/perm-ives.h"
#include "comb/perm-trotter.h"
#include "comb/perm-trotter-lg.h"
#include "comb/perm-gray-ffact.h"
#include "comb/perm-gray-ffact2.h"
#include "comb/perm-gray-rfact.h"
#include "comb/perm-gray-rot1.h"
#include "comb/perm-gray-lipski.h"
#include "comb/perm-gray-wells.h"
#include "comb/perm-heap.h"
#include "comb/perm-heap2.h"
#include "comb/perm-heap2-swaps.h"
#include "comb/perm-rot.h"
#include "comb/perm-pref.h"
#include "comb/perm-star.h"
#include "comb/perm-star-swaps.h"
#include "comb/perm-restrpref.h"
#include "comb/perm-rev.h"
#include "comb/perm-rev2.h"
#include "comb/perm-st.h"
#include "comb/perm-st-pref.h"
#include "comb/perm-st-gray.h"
#include "comb/perm-derange.h"
#include "comb/perm-involution.h"
#include "comb/involution-zero-map-rgs.h"
// auxiliary routines:
#include "comb/is-stack-sortable.h"
#include "comb/check-permgen.h"

//: conversions between permutations and factorial numbers:
#include "comb/cyclic-perm.h"
#include "comb/fact2num2perm.h"
#include "comb/fact2perm.h"
#include "comb/big-fact2perm.h"
#include "comb/num2perm.h"
#include "comb/fact2num.h"


//: k-permutations:
#include "comb/kperm-lex.h"
#include "comb/kperm-gray.h"
// auxiliary routines:
#include "comb/check-kpermgen.h"


//: multiset permutations:
#include "comb/mset-perm-lex.h"
#include "comb/mset-perm-lex-rec.h"
#include "comb/mset-perm-pref.h"
#include "comb/mset-perm-gray.h"
// auxiliary routines:
//#include "comb/mset-perm-invtab.h"


//: Cayley permutations:
#include "comb/cayley-perm.h"
// auxiliary routines:
#include "comb/is-cayley-perm.h"


//: arrangements:
#include "comb/arrangement-lex.h"
#include "comb/arrangement-rgs.h"
#include "comb/change-rgs.h"
// auxiliary routines:
#include "comb/is-arrangement-rgs.h"
#include "comb/print-arrangement-rgs-perm.h"
#include "comb/is-change-rgs.h"

//: n-dimensional Hilbert curve:
#include "comb/wfl-hilbert.h"
#include "comb/hilbert-ndim.h"
#include "comb/hilbert-ndim-rec.h"


//: standard Young tableaux:
#include "comb/young-tab-rgs.h"
#include "comb/young-tab-rgs-subset-lex.h"
// auxiliary routines:
#include "comb/young-tab-rgs-descents.h"
#include "comb/is-young-tab-rgs.h"
#include "comb/is-shifted-young-tab-rgs.h"
#include "comb/print-young-tab-rgs-aa.h"


//: smooth factorial numbers (RGS):
#include "comb/smooth-rfact-rgs.h"


//: unimodal words (RGS):
#include "comb/weakly-unimodal-rgs-lex.h"
// auxiliary routines:
#include "comb/is-unimodal.h"


//: score sequences:
#include "comb/score-sequence.h"


//: rooted trees and maps:
#include "comb/tree-lev-seq.h"
#include "comb/id-tree-lev-seq.h"
#include "comb/balanced-ordered-tree-lev-seq.h"
#include "comb/ordered-tree-lev-seq.h"
#include "comb/ordered-tree-branching-seq.h"
#include "comb/ordered-tree-branches.h"
#include "comb/acyclic-map.h"
// auxiliary routines:
#include "comb/tree-lev-seq-aux.h"


//: string substitution (L-system):
#include "comb/stringsubst.h"


//: cycle leaders of the Gray-permutation:
#include "comb/gray-cycle-leaders.h"


// auxiliary routines:
#include "comb/lex-compare.h"
#include "comb/subset-lex-compare.h"
#include "comb/gray-compare.h"
#include "comb/sl-gray-compare.h"
#include "comb/word-stats.h"
#include "comb/comb-print.h"
#include "comb/endo-enup.h"

#include "comb/arith-3-progression.h"


#endif  // !defined HAVE_COMB_ALL_H__
