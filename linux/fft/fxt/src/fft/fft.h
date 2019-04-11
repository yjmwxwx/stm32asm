#if !defined  HAVE_FFT_H__
#define       HAVE_FFT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"      // ulong
#include "complextype.h"   // Complex

//: FAST FOURIER TRANSFORM (FFT)

//<<
// typical format of arguments: (double *fr, double *fi, ulong ldn, int is)
// fr := pointer to data array (real part),
// fi := pointer to data array (imag part),
// ldn := base 2 log of array length
// is := sign of exponent in fourier kernel

// naming conventions:
// name_fft() := FFT implementation using algorithm "name"
// name_fft0() := same for zero padded data
//   (i.e. second half of the input data is expected to be zero)
//>>

// fft/fhtfft.cc:
void fht_fft(double *fr, double *fi, ulong ldn, int is);
void fht_fft0(double *fr, double *fi, ulong ldn, int is);
void fht_fft_conversion(double *fr, double *fi, ulong ldn, int is);  // aux

// fft/fhtcfft.cc:
void fht_fft(Complex *f, ulong ldn, int is);
void fht_fft0(Complex *f, ulong ldn, int is);
void fht_fft_conversion(Complex *f, ulong ldn, int is);  // aux


// fft/fftdif2.cc:
void fft_depth_first_dif2(Complex *f, ulong ldn, int is);
void fft_dif2(Complex *f, ulong ldn, int is);

// fft/fftdit2.cc:
void fft_depth_first_dit2(Complex *f, ulong ldn, int is);
void fft_dit2(Complex *f, ulong ldn, int is);

// fft/fftdif4l.cc:
void fft_dif4l(Complex *f, ulong ldn, int is);

// fft/fftdit4l.cc:
void fft_dit4l(Complex *f, ulong ldn, int is);

// fft/fftdif4.cc:
void fft_dif4_core_p1(double *fr, double *fi, ulong ldn);  // aux
void fft_dif4(double *fr, double *fi, ulong ldn, int is);

// fft/cfftdif4.cc:
void fft_dif4_core_p1(Complex *f, ulong ldn);  // aux
void fft_dif4_core_m1(Complex *f, ulong ldn);  // aux
void fft_dif4(Complex *f, ulong ldn, int is);

// fft/fftdit4.cc:
void fft_dit4_core_p1(double *fr, double *fi, ulong ldn);  // aux
void fft_dit4(double *fr, double *fi, ulong ldn, int is);

// fft/cfftdit4.cc:
void fft_dit4_core_m1(Complex *f, ulong ldn);  // aux
void fft_dit4_core_p1(Complex *f, ulong ldn);  // aux
void fft_dit4(Complex *f, ulong ldn, int is);


// fft/cfftsplitradix.cc:
void split_radix_dif_fft_core(Complex *f, ulong ldn);  // aux
void split_radix_dit_fft_core(Complex *f, ulong ldn);  // aux
void split_radix_fft(Complex *f, ulong ldn, int is);

// fft/fftsplitradix.cc:
void split_radix_fft_dif_core(double *fr, double *fi, ulong ldn);  // aux
void split_radix_fft(double *fr, double *fi, ulong ldn, int is);

// fft/cfftwrap.cc: (wrappers for type complex fourier)
void complex_to_real_imag(Complex *c, long ldn);  // aux
void real_imag_to_complex(double *fr/*, double *fi*/, long ldn);  // aux
void complex_fft(Complex *c, ulong ldn, int is);
void real_imag_fft(double *fr/*, double *fi*/, ulong ldn, int is);

// fft/fouriershift.cc:
void fourier_shift(Complex *a, ulong n, double v);  // aux
void fourier_shift(double *fr, double *fi, ulong n, double v);  // aux
void fourier_shift_imag0(double *fr, double *fi, ulong n, double v);  // aux
void fourier_shift(double *fr, double *fi, ulong n, double v, ulong k0, ulong kn);  // aux
void fourier_shift_imag0(double *fr, double *fi, ulong n, double v, ulong k0, ulong kn);  // aux

// fft/skipfft.cc:
void skip_fft(double *fr, double *fi, ulong n, ulong d, double *wr, double *wi, int is);  // aux
void skip_fft0(double *fr, double *fi, ulong n, ulong d, double *wr, double *wi, int is);  // aux

// fft/weightedfft.cc:
void weighted_fft(double *fr, double *fi, ulong ldn, int is, double w);
void weighted_inverse_fft(double *fr, double *fi, ulong ldn, int is, double w);


//: -------- 2-dim FFT:

// fft/twodimfft.cc:
void twodim_fft(double *fr, double *fi, ulong nr, ulong nc, int is);

//// fft/ndimfft.cc: (1...5 dim fft)
//void ndim_fft(double *fr, double *fi, ulong ndim, const ulong *ldn, int is);


////: -------- Gray-FFT:
//// fft/gfft.cc:
//void gfft_dif2_core(Complex *f, ulong ldn, int is);  // aux
//void gfft_dit2_core(Complex *f, ulong ldn, int is);  // aux
//void gfft(Complex *f, ulong ldn, int is);
//void gfft_auto_convolution(Complex *f, ulong ldn);
//void gfft_convolution(Complex *f, Complex *g, ulong ldn);

//: -------- Spectrum:
// fft/fftspect.cc:
void fft_spectrum(double *f, ulong ldn, int phasesq=0);



#endif  // !defined HAVE_FFT_H__
