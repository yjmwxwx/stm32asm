#if !defined  HAVE_EVENODD_H__
#define       HAVE_EVENODD_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


static inline bool is_even(ulong x)  { return (0==(x&1UL)); }
static inline bool is_odd(ulong x)  { return (0!=(x&1UL)); }

// next or previous even or odd value:
static inline ulong next_even(ulong x)  { return (x|1UL)+1UL; }
static inline ulong prev_even(ulong x)  { return (x-1UL)&~1UL; }
static inline ulong next_odd(ulong x)  { return (x+1UL)|1UL; }
static inline ulong prev_odd(ulong x)  { return (x&~1UL)-1UL; }
//static inline ulong next_even(ulong x)  { return x+2-(x&1UL); }
//static inline ulong prev_even(ulong x)  { return x-2+(x&1UL); }
//static inline ulong next_odd(ulong x)  { return x+1UL+(x&1UL); }
//static inline ulong prev_odd(ulong x)  { return x-1UL-(x&1UL); }


// same or next, and same or previous even or odd value:
static inline ulong next0_even(ulong x)  { return (x+1UL)&~1UL; }
static inline ulong prev0_even(ulong x)  { return x&~1UL; }
static inline ulong next0_odd(ulong x)  { return x|1UL; }
static inline ulong prev0_odd(ulong x)  { return (x-1UL)|1UL; }
//static inline ulong next0_even(ulong x)  { return x+(x&1UL); }
//static inline ulong prev0_even(ulong x)  { return x-(x&1UL); }
//static inline ulong next0_odd(ulong x)  { return x+1UL-(x&1UL); }
//static inline ulong prev0_odd(ulong x)  { return x-1UL+(x&1UL); }


#endif  // !defined HAVE_EVENODD_H__
