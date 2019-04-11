#if !defined HAVE_RESTRICT_H__
#define      HAVE_RESTRICT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "restrict.h"  // this file

// From http://gcc.gnu.org/onlinedocs/gcc/Restricted-Pointers.html
//  Because you cannot compile C++ by specifying the `-std=c99'
//  language flag, `restrict' is not a keyword in C++.
#define  restrict  __restrict


#endif // !defined HAVE_RESTRICT_H__
