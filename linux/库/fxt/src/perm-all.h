#if !defined HAVE_PERM_ALL_H__
#define      HAVE_PERM_ALL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


//: properties of permutations:
#include "perm/permq.h"
#include "perm/perm-genus.h"

//: special permutations:
#include "perm/reverse.h"
#include "perm/rotate.h"
#include "perm/swapblocks.h"
//#include "perm/mrotate.h"
#include "perm/zip.h"
#include "perm/ziprev.h"
#include "perm/even2lower.h"
#include "perm/graypermute.h"
#include "perm/grayrevpermute.h"
#include "perm/xorpermute.h"
#include "perm/haarpermute.h"
#include "perm/radixpermute.h"

#include "perm/revbinpermute.h"
#include "perm/revbinpermute0.h"
#include "perm/shortgraypermute.h"
#include "perm/shortrevbinpermute.h"
#include "perm/shortrevbinpermute0.h"

//: general permutations:
#include "perm/perm2ccf.h"
#include "perm/permapply.h"
#include "perm/permapplyfunc.h"
#include "perm/perminvert.h"
#include "perm/permcomplement.h"
#include "perm/permcompose.h"
#include "perm/printcycles.h"

//: action of permutations via swap bijection:
#include "perm/fact2perm-swp-apply.h"

//: random permutations of certain types:
#include "perm/permrand.h"
#include "perm/permrand-pref.h"
#include "perm/permrand-parity.h"
#include "perm/permrand-ord.h"
#include "perm/permrand-cyclic.h"
#include "perm/permrand-2cycles.h"
#include "perm/permrand-ncm2.h"
#include "perm/permrand-cycle-type.h"
#include "perm/permrand-self-inverse.h"
#include "perm/permrand-derange.h"
#include "perm/permrand-derange3.h"
#include "perm/permrand-connected.h"
#include "perm/permrand-sdc.h"
#include "perm/permrand-inv-mod-m.h"


#endif  // !defined HAVE_PERM_ALL_H__
