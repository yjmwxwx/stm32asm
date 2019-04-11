#if !defined  HAVE_ARRAY_LEN_H__
#define       HAVE_ARRAY_LEN_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#define  ARRAY_LEN(x)  (sizeof(x)/sizeof(typeof(x[0])))
#define  ARRAY_LEN(x)  (sizeof(x)/sizeof(x[0]))

#endif  // !defined HAVE_ARRAY_LEN_H__
