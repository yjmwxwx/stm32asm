#if !defined  HAVE_FXTALLOCA_H__
#define       HAVE_FXTALLOCA_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


// define to force use of alloca.h:
#define FORCE_ALLOCA_H

#ifdef CLANG  // llvm/clang needs alloca.h:
#define FORCE_ALLOCA_H
#endif

#if defined  __GNUC__  // GNU compiler
#define ALLOCA(Type, v, n)  Type v[n]
#else // __GNUC__
#include <alloca.h>
#define ALLOCA(Type, v, n)  Type *v = (Type *)alloca((n)*sizeof(Type))
#endif // __GNUC__

#ifdef FORCE_ALLOCA_H
#undef ALLOCA
#include <alloca.h>
//#include <stdlib.h>  // for BSD
#define ALLOCA(Type, v, n)  Type *v = (Type *)alloca((n)*sizeof(Type))
#endif

#endif  // !defined HAVE_FXTALLOCA_H__

