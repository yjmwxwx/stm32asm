#if !defined  HAVE_REALFFT_H__
#define       HAVE_REALFFT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong

//<<
// General format of arguments: (double *f, ulong ldn)
// f := pointer to data array,
// ldn := base 2 log of array length (length n=2**n)
//
// A function some_func0(...) (note the '0')
// expects input data with upper half zeros ('zero padded' data).
//
// Data in the arrays without const modifier is generally modified.
//
// A comment 'aux' at the line end marks functions that are
// called by other routines and might not be of direct use
// for users of the library
//>>


// info about the ordering of the data can be found in each source file

// realfft/realfftbyfht.cc:
void fht_real_complex_fft(double *f, ulong ldn, int is=+1);
void fht_real_complex_fft0(double *f, ulong ldn, int is=+1);
void fht_complex_real_fft(double *f, ulong ldn, int is=+1);
void realisator(double *gr, const double *gi, ulong n, int is);  // aux
void imaginator(const double *gr, double *gi, ulong n, int is);  // aux
void separator(double *gr, double *gi, ulong n, int is);  // aux

// realfft/realfftwrap.cc:
void wrap_real_complex_fft(double *f, ulong ldn/*, int is=+1*/);
void wrap_complex_real_fft(double *f, ulong ldn/*, int is=+1*/);

// realfft/realffteasyord.cc:
void easy_ordering_real_complex_fft(double *f, ulong ldn, int is=+1);
void easy_ordering_real_complex_fft0(double *f, ulong ldn, int is=+1);
void easy_ordering_complex_real_fft(double *f, ulong ldn, int is=+1);

// realfft/realfftsplitradix.cc:
void split_radix_real_complex_fft(double *x, ulong ldn, int is=-1);
void split_radix_real_complex_fft0(double *x, ulong ldn, int is=-1);
void split_radix_complex_real_fft(double *x, ulong ldn, int is=-1);
void split_radix_real_complex_fft_dit_core(double *x, ulong ldn);  // aux
void split_radix_complex_real_fft_dif_core(double *x, ulong ldn);  // aux

// realfft/skiprealfft.cc:
void skip_real_complex_fft(double *f, ulong n, ulong d, double *w);  // aux
void skip_real_complex_fft0(double *f, ulong n, ulong d, double *w);  // aux
void skip_complex_real_fft(double *f, ulong n, ulong d, double *w);  // aux


//: inlines give default implementations
inline void real_complex_fft(double *f, ulong ldn, int is)
{ fht_real_complex_fft(f, ldn, is); }

inline void complex_real_fft(double *f, ulong ldn, int is)
{ fht_complex_real_fft(f, ldn, is); }


#endif  // !defined HAVE_REALFFT_H__
