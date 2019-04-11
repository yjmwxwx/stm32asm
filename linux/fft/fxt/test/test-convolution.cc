
#include "fft-all.h"
#include "fht-all.h"
#include "convolution-all.h"
#include "correlation-all.h"
#include "walsh-all.h"
#include "haar-all.h"
#include "restrict.h"

#include "bits/grsnegative.h"

#include "aux1/copy.h"
//#include "aux1/aux1double.h"
#include "aux0/randf.h"
//#include "aux1/auxprint.h"
//#include "aux1/arith1.h"
#include "perm/reverse.h"
#include "convolution/slowcnvl.h"
#include "correlation/slowcorr.h"

#include "fxtio.h"

#include <cmath>
#include <cstdlib>  // strtoul()

#include "fxttypes.h"
#include "fxtalloca.h"

#include "test.h"  // last to include



template <typename Type>
void g_dyadic_auto_convolution(Type *f, ulong ldn)
{
    ulong n = (1UL<<ldn);
    walsh_gray(f, ldn);
    for (ulong k=0; k<n; ++k)  f[k] *= f[k];
    for (ulong k=0; k<n; ++k)  if ( grs_negative_q(k) )  f[k] = -f[k];
    inverse_walsh_gray(f, ldn);
}
// -------------------------

template <typename Type>
void w_dyadic_auto_convolution(Type *f, ulong ldn)
{
    ulong n = (1UL<<ldn);
    walsh_wak(f, ldn);
    for (ulong k=0; k<n; ++k)  f[k] *= f[k];
    walsh_wak(f, ldn);
}
// -------------------------

template <typename Type>
void g_dyadic_convolution(Type * restrict f, Type * restrict g, ulong ldn)
{
    ulong n = (1UL<<ldn);
    walsh_gray(f, ldn);
    walsh_gray(g, ldn);
    for (ulong k=0; k<n; ++k)
    {
        Type t = g[k] * f[k];
        if ( grs_negative_q(k) )  t = -t;
        g[k] = t;
    }
    inverse_walsh_gray(g, ldn);
}
// -------------------------

template <typename Type>
void w_dyadic_convolution(Type * restrict f, Type * restrict g, ulong ldn)
{
    ulong n = (1UL<<ldn);
    walsh_wak(f, ldn);
    walsh_wak(g, ldn);
    for (ulong k=0; k<n; ++k)  g[k] *= f[k];
    walsh_wak(g, ldn);
}
// -------------------------

int
main(int argc, char **argv)
{
  cout << "Running tests for convolution/correlation/spectrum ... " << endl;

  ulong minldn = 0, maxldn = 11;
  if ( argc>1 )  minldn = strtoul(argv[1], 0, 10);
  if ( argc>2 )  maxldn = strtoul(argv[2], 0, 10);

  ulong rep = 1;
  if ( argc>3 )  rep = strtoul(argv[3], 0, 10);


  ulong n = 1UL<<maxldn;
  ALLOCA(Complex, ac, n);
  ALLOCA(Complex, fc, n);
  ALLOCA(Complex, gc, n);
  double *ar=(double *)ac, *fr=(double *)fc, *gr=(double *)gc;
  for (ulong r=1; r<=rep; ++r)
  {
    cout << "+++++++++++++++++++++++++ PASS # " << r
         << " (of " << rep << ") +++++++++++++++++++++++++" << endl;

    for (ulong ldn=minldn; ldn<=maxldn; ++ldn)
    {
      n = 1UL<<ldn;
      cout << "====================  LDN = " << ldn
           << "   N = " << n << " :" << endl;

//      ulong nh = n/2;
      const ulong ldnh = (ldn ? ldn-1 : 1),  nh = 1UL<<ldnh;
      double *fi=fr+n,  *gi=gr+n,  *ai=ar+n;
      null(ac, n);
//      ar[1] = ai[1] = 1;
      for (ulong i=0; i<n; ++i)  ac[i] = Complex(white_noise(), white_noise());
//      for (ulong i=0; i<n; ++i)  ac[i] = Complex(white_noise(), 0.0 );
//      set_seq(ar, 2*n, 1.0/n, 1.0/n);
      fill(ar, 2*n, 1.0);  // makes things more traceable

      ECHO( matrix_fft_auto_convolution(fc, ldn); );
      CHECK( fht_auto_convolution(gc, ldn); );
      CHECK( fft_complex_auto_convolution(gc, ldn); );
//      CHECK( gfft_auto_convolution(gc, ldn); );
      if ( ldn<=SMALL_LDN )
      {
        CHECK( slow_auto_convolution(gc, n); );
      }

      cout << "\n----- EQUIV (SPECTRUM): -----" << endl;
      EQUIV( acopy(ar, fr, n); fht_spectrum(fr, ldn, 1);
      acopy(ar, gr, n); fft_spectrum(gr, ldn, 1); );


      cout << "\n----- real SELF- CONVOLUTION/CORRELATION: -----" << endl;
      ECHO( fht_auto_convolution(fr, ldn); );
      CHECK_REAL( fht_fft_auto_convolution(gr, ldn); );
      CHECK_REAL( split_radix_fft_auto_convolution(gr, ldn); );
      CHECK_REAL( matrix_fft_auto_convolution(gr, ldn); );
      if ( ldn<=SMALL_LDN )
      {
        CHECK_REAL( slow_convolution(gr, gr, n); );
        CHECK_REAL( slow_auto_convolution(gr, n); );
      }

      cout << "\n----- DYADIC SELF- CONVOLUTION: -----" << endl;
      ECHO( dyadic_auto_convolution(fr, ldn); );
      CHECK_REAL( w_dyadic_auto_convolution(gr, ldn); );
      CHECK_REAL( g_dyadic_auto_convolution(gr, ldn); );

//      if ( n>=4 )
      {
      cout << "\n----- DYADIC CONVOLUTION: -----" << endl;
      ECHO( dyadic_convolution(fi, fr, ldn); );
      CHECK_REAL( w_dyadic_convolution(gi, gr, ldn); );
      CHECK_REAL( g_dyadic_convolution(gi, gr, ldn); );

      cout << "\n----- OR CONVOLUTION: -----" << endl;
      ECHO( slow_or_convolution(fi, fr, ldn); );
      CHECK_REAL( or_convolution(gi, gr, ldn); );
      }

      {
      cout << "\n----- weighted OR CONVOLUTION: -----" << endl;
      ECHO( or_convolution(fi, fr, ldn); );
      CHECK_REAL( weighted_or_convolution(gi, gr, ldn, 1.0); );
      const double w = -1.0;
      ECHO( slow_weighted_or_convolution(fi, fr, ldn, w); );
      CHECK_REAL( weighted_or_convolution(gi, gr, ldn, w); );
      }

      {
      cout << "\n----- SUBSET CONVOLUTION: -----" << endl;
      ECHO( subset_convolution(fi, fr, ldn); );
      CHECK_REAL( slow_subset_convolution(gi, gr, ldn); );
      ECHO( subset_auto_convolution(fr, ldn); );
      CHECK_REAL( slow_subset_auto_convolution(gi, gr, ldn); );
      }

      {
      cout << "\n----- PREFIX CONVOLUTION: -----" << endl;
      ECHO( prefix_convolution(fi, fr, ldn); );
      CHECK_REAL( slow_prefix_convolution(gi, gr, ldn); );
      }

      if ( n>=2 )
      {
        cout << "\n----- real CONVOLUTION/CORRELATION: -----" << endl;
//        ECHO( slow_convolution(fi, fr, n); );
        ECHO( split_radix_fft_convolution(fi, fr, ldn); );
        CHECK_REAL( split_radix_fft_convolution(gi, gr, ldn); );
        CHECK_REAL( fht_fft_convolution(gi, gr, ldn); );
        CHECK_REAL( fht_convolution(gi, gr, ldn); );
      }

      if ( n>=4 )
      {
        cout << "\n----- complex CONVOLUTION: -----" << endl;
        ECHO( fft_complex_convolution(fc, fc+nh, ldnh); null(fc, nh); );
//        CHECK( gfft_convolution(gc, gc+nh, ldnh); null(gc, nh); );
        CHECK( fht_convolution(gc, gc+nh, ldnh); null(gc, nh); );
      }

      if ( n>=2 )  // ==== begin ZERO PADDED: ====
      {
        null(ar+nh, nh);
        null(ai+nh, nh);

        cout << "\n----- LINEAR CONVOLUTION/CORRELATION: -----" << endl;
        ECHO( fht_fft_convolution0(fr, fi, ldn); );
        CHECK_IMAG( fht_convolution0(gr, gi, ldn); );
        if ( ldn<=SMALL_LDN )
        {
          CHECK_IMAG( slow_convolution0(gr, gi, n); );
        }

        ECHO( fft_correlation0(fr, fi, ldn); );
        CHECK_IMAG( fht_correlation0(gr, gi, ldn); );
        if ( ldn<=SMALL_LDN )
        {
          CHECK_IMAG( slow_correlation0(gr, gi, n); );
        }

        ECHO( fht_auto_convolution0(fr, ldn); );
        CHECK_REAL( matrix_fft_auto_convolution0(gr, ldn); );
        CHECK_REAL( fht_fft_auto_convolution0(gr, ldn); );
        CHECK_REAL( split_radix_fft_auto_convolution0(gr, ldn); );
        if ( ldn<=SMALL_LDN )
        {
          CHECK_REAL( slow_convolution0(gr, gr, n); );
          CHECK_REAL( slow_auto_convolution0(gr, n); );
        }

        ECHO( fft_auto_correlation0(fr, ldn); );
        CHECK_REAL( fht_auto_correlation0(gr, ldn); );
        if ( ldn<=SMALL_LDN )
        {
          CHECK_REAL( slow_auto_correlation(gr, n); );
          CHECK_REAL( slow_correlation(gr, gr, n); );
          CHECK_REAL( slow_correlation0(gr, gr, n); );
          CHECK_REAL( slow_auto_correlation0(gr, n); );
          CHECK_REAL( slow_correlation(ar, gr, n); );
          CHECK_REAL( reverse(gr, n); slow_convolution(ar, gr, n); reverse(gr, n); );
        }


//        ECHO( fft_complex_convolution0(fr, fi, ldn); );
//        CHECK( fht_complex_convolution0(gr, gi, ldn); );


      } // ==== end ZERO PADDED: ====

    cout << "+++++++++++++++++++ PASS # " << r
         << " (of " << rep << ") ++++++ FINISHED +++++++++++++" << endl;

    } // === ldn ===

  } // === r ===

  cout << "\nOK, all passed." << endl;
  return 0;
}
// -------------------------
/*
Local variables:
mode: C++
c-basic-offset: 2
End:
*/
