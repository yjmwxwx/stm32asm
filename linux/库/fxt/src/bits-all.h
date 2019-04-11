#if !defined HAVE_BITS_ALL_H__
#define      HAVE_BITS_ALL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//: bit wizardry

// Define BITS_PER_LONG:
#include "bits/bitsperlong.h"

// Inline assembler (for i386 and AMD64):

#include "bits/bitasm.h"
// For automatic testing:
#if 0
#include "bits/bitasm-i386.h"
#include "bits/bitasm-amd64.h"
#include "bits/bitasm-sse.h"
#endif // 0



// Combinatorial routines:

#include "bits/bitsubsetq.h"
#include "bits/bitsubset.h"
#include "bits/bitsubset-gray.h"

#include "bits/bitcombcolex.h"
//#include "bits/bitcomblex.h"
#include "bits/bitcombminchange.h"
#include "bits/bitcombshifts.h"
//#include "bits/bit2composition.h"
#include "bits/bitlex.h"
#include "bits/bit-sl-gray.h"
#include "bits/bin-to-sl-gray.h"
#include "bits/parenwords.h"

#include "bits/thue-morse.h"
#include "bits/grsnegative.h"


// Arithmetic and representation in non-standard bases:

#include "bits/average.h"
#include "bits/evenodd.h"

#include "bits/negbin.h"
#include "bits/radix-m4.h"
#include "bits/radix-m1pi.h"
#include "bits/radix-2i.h"
#include "bits/bin2naf.h"
#include "bits/fibrep.h"
#include "bits/fibrep-subset-lexrev.h"
#include "bits/bitfibgray.h"
#include "bits/bit-rll2.h"
#include "bits/bitsequency.h"

#include "bits/bit2adic.h"


// Space-filling curves:

#include "bits/hilbert.h"
#include "bits/zorder.h"
#include "bits/bit-paper-fold.h"
#include "bits/bit-dragon3.h"
#include "bits/bit-dragon-r4.h"
#include "bits/bit-dragon-r5.h"
#include "bits/bit-dragon-r7.h"
#include "bits/bit-dragon-r9.h"
#include "bits/bit-dragon-r13.h"


// Functions about cyclic rotations, necklaces, and Lyndon words:

#include "bits/bitrotate.h"
//#include "bits/bitmrotate.h"

#include "bits/bit-necklace.h"

#include "bits/bitperiodic.h"
#include "bits/bitcyclic-minmax.h"
#include "bits/bitcyclic-dist.h"
#include "bits/bitcyclic-match.h"
#include "bits/bitcyclic-period.h"
#include "bits/bitcyclic-xor.h"


// Gray code, parity, and invertible transformations:

#include "bits/graycode.h"
#include "bits/parity.h"
#include "bits/nextgray.h"

#include "bits/revgraycode.h"
#include "bits/graypower.h"
#include "bits/bittransforms.h"
#include "bits/blue-fixed-points.h"
#include "bits/bitxtransforms.h"


// Cyclic Redundancy Check (CRC):

#include "bits/crc32.h"
#include "bits/crc64.h"
#include "bits/tcrc64.h"
#include "bits/pcrc64.h"


// Mixing colors (8-bit RGB channels):

#include "bits/colormix.h"
#include "bits/colormixp.h"
#include "bits/colormix-fl.h"


// Permutations of bits:

#include "bits/bitzip.h"
#include "bits/bitzip-pairs.h"
#include "bits/bitbutterfly.h"
#include "bits/bitgraypermute.h"
#include "bits/bitgather.h"
#include "bits/bitseparate.h"

#include "bits/revbin.h"
#include "bits/revbin-upd.h"


// Kolakoski sequence:
#include "bits/kolakoski-seq.h"


// All the rest (low level functions):

#include "bits/bitcount.h"
#include "bits/bitswap.h"
#include "bits/bitlow.h"
#include "bits/bitlow-edge.h"
#include "bits/bithigh.h"
#include "bits/bithigh-edge.h"
#include "bits/bit2pow.h"
#include "bits/bitldeq.h"
#include "bits/tinyfactors.h"
#include "bits/ith-one-idx.h"

#include "bits/zerobyte.h"

#include "bits/cswap.h"
#include "bits/branchless.h"

#include "bits/bittest.h"
#include "bits/bitcopy.h"
#include "bits/bitblock.h"
#include "bits/bit-isolate.h"


#include "bits/bitset2set.h"

#include "bits/print-bin.h"




#endif // !defined HAVE_BITS_ALL_H__
