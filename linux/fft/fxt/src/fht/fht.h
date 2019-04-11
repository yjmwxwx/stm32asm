#if !defined  HAVE_FHT_H__
#define       HAVE_FHT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


//<<
// General format of arguments: (double *f, ulong ldn)
// f := pointer to data array,
// ldn := base 2 log of array length (length n=2**n)
//
// A routine some_func0(...) (note the '0')
// expects input data with upper half zeros ('zero padded' data).
//
// Data in the arrays without const modifier is generally modified.
//
// A comment 'aux' at the line end marks functions that are
// called by other routines and might not be of direct use
// for users of the library
//>>

#include "fxttypes.h"  // ulong
#include "complextype.h"  // type Complex

// fht/fhtdit.cc:
void fht_dit_core(double *f, ulong ldn);  // aux
void fht_dit(double *f, ulong ldn);

// fht/fhtdif.cc:
void fht_dif_core(double *f, ulong ldn);  // aux
void fht_dif(double *f, ulong ldn);

// fht/cfhtdit.cc:
void fht_dit_core(Complex *f, ulong ldn);  // aux
void fht_dit(Complex *f, ulong ldn);

// fht/cfhtdif.cc:
void fht_dif_core(Complex *f, ulong ldn);  // aux
void fht_dif(Complex *f, ulong ldn);

// fht/fht0.cc:
void fht0_dit(double *f, ulong ldn);

// fht/cfht0.cc:
void fht0_dit(Complex *f, ulong ldn);

// fht/fhtdit2.cc:
void fht_depth_first_dit2(double *f, ulong ldn);
void fht_dit2(double *f, ulong ldn);

// fht/fhtdif2.cc:
void fht_depth_first_dif2(double *f, ulong ldn);
void fht_dif2(double *f, ulong ldn);



//: -------- Spectrum:
// fht/fhtspect.cc:
void fht_spectrum(double *f, ulong ldn, int phasesq=0);



#endif  // !defined HAVE_FHT_H__
