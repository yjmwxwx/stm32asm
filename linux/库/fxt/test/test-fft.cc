
#include "fft-all.h"
#include "realfft-all.h"
#include "fht-all.h"
#include "chirpzt-all.h"
#include "perm-all.h"

#include "aux1/copy.h"
//#include "aux1/aux1double.h"
//#include "aux1/auxprint.h"
#include "aux1/arith1.h"
#include "aux0/randf.h"
#include "fxtio.h"

#include <cmath>
#include <cstdlib>  // strtoul()

// note: todo: generated (short) versions
// note: todo: ntt


#include "fxttypes.h"
#include "fxtalloca.h"

#include "test.h"  // last to include


int
main(int argc, char **argv)
{
  cout << "Running tests for FFTs ... " << endl;

  ulong minldn = 0, maxldn = 11;
  if ( argc>1 )  minldn = strtoul(argv[1], 0, 10);
  if ( argc>2 )  maxldn = strtoul(argv[2], 0, 10);

  ulong rep = 1;
  if ( argc>3 )  rep = strtoul(argv[3], 0, 10);


  ulong n = 1UL<<maxldn;
  ALLOCA(Complex, ac, n);
  ALLOCA(Complex, fc, n);
  ALLOCA(Complex, gc, n);
//  double *ar=(double *)ac;
  double *fr=(double *)fc, *gr=(double *)gc;


  for (ulong r=1; r<=rep; ++r)
  {
    cout << "+++++++++++++++++++++++++ PASS # " << r
         << " (of " << rep << ") +++++++++++++++++++++++++" << endl;

    {
        n = 8;
        for (ulong i=0; i<n; ++i)  ac[i] = Complex(white_noise(), white_noise());
        for (ulong i=0; i<n; ++i)  fc[i] = ac[i];
        double *fi=fr+n,  *gi=gr+n; // ,  *ai=ar+n;
        CHECK( fft8_dif_core_p1(gc); fft8_dit_core_m1(gc); multiply_val(gc, n, (Complex)(1.0/(double)n)); );
        CHECK( fft8_dit_core_m1(gc); fft8_dif_core_p1(gc); multiply_val(gc, n, (Complex)(1.0/(double)n)); );
        CHECK( fft8_dit_core_p1(gc); fft8_dif_core_m1(gc); multiply_val(gc, n, (Complex)(1.0/(double)n)); );
        CHECK( fft8_dif_core_m1(gc); fft8_dit_core_p1(gc); multiply_val(gc, n, (Complex)(1.0/(double)n)); );

        CHECK( fft8_dif_core_p1(gr,gi); fft8_dit_core_m1(gr,gi); multiply_val(gr, 2*n, 1.0/(double)n); );
        CHECK( fft8_dit_core_m1(gr,gi); fft8_dif_core_p1(gr,gi); multiply_val(gr, 2*n, 1.0/(double)n); );
        CHECK( fft8_dit_core_p1(gr,gi); fft8_dif_core_m1(gr,gi); multiply_val(gr, 2*n, 1.0/(double)n); );
        CHECK( fft8_dif_core_m1(gr,gi); fft8_dit_core_p1(gr,gi); multiply_val(gr, 2*n, 1.0/(double)n); );

        n = 9;
        fi=fr+n,  gi=gr+n; // ,  *ai=ar+n;
        for (ulong i=0; i<9; ++i)  ac[i] = Complex(white_noise(), white_noise());
        for (ulong i=0; i<n; ++i)  fc[i] = ac[i];
        CHECK( fft9_p1(gr,gi); fft9_m1(gr,gi); multiply_val(gc, n, (Complex)(1.0/(double)n)); );
        CHECK( fft9_p1(gc); fft9_m1(gc); multiply_val(gc, n, (Complex)(1.0/(double)n)); );
    }



    for (ulong ldn=minldn; ldn<=maxldn; ++ldn)
    {
      n = 1UL<<ldn;
      cout << "====================  LDN = " << ldn
           << "   N = " << n << " :" << endl;

      ulong nh = n/2;
      double *fi=fr+n,  *gi=gr+n; // ,  *ai=ar+n;
      null(ac, n);
      //   ar[1] = ai[1] = 1;
      for (ulong i=0; i<n; ++i)  ac[i] = Complex(white_noise(), white_noise());
//      for (ulong i=0; i<n; ++i)  ac[i] = Complex(white_noise(), 0.0 );
//      set_seq((double *)ac, 2*n, 1.0/(double)n, 1.0/(double)n);
//   fill((double *)ac, 2*n, 1.0);


      for (int is=+1; is>=-1; is-=2)
      {
        cout << "========= ISIGN = " << is << endl;

        cout << "\n----- COMPLEX FFT: -----" << endl;
        ECHO( fht_fft(fc, ldn, is); );

        CHECK( split_radix_fft(gc, ldn, is); );
        CHECK( matrix_fft(gc, ldn, is); );
        CHECK( fht_fft(gc, ldn, is); );
        CHECK( split_radix_fft(gc, ldn, is); );
        CHECK( matrix_fft(gc, ldn, is); );
        CHECK( fft_dif4(gc, ldn, is); );
        CHECK( fft_dit4(gc, ldn, is); );
        CHECK( fft_dif4l(gc, ldn, is); );
        CHECK( fft_dit4l(gc, ldn, is); );
        CHECK( fft_dif2(gc, ldn, is); );
        CHECK( fft_dit2(gc, ldn, is); );
//        CHECK( gfft(gc, ldn, is); );

        if ( ldn<=SMALL_LDN )
        {
          CHECK( slow_ft(gc, n, is); );
          CHECK( slow_fract_ft(gc, n, is); );
          double phi = 2.0 * M_PI * (double)is / (double)n;
          CHECK( slow_zt(gc, n, Complex(cos(phi),sin(phi))); );

          CHECK( recursive_fft_dif2(gc, ldn, is); );
          CHECK( recursive_fft_dit2(gc, ldn, is); );
          CHECK( fft_depth_first_dit2(gc, ldn, is); );
          CHECK( fft_depth_first_dif2(gc, ldn, is); );
        }


        cout << "----- COMPLEX (RE/IM) FFT: -----" << endl;
        ECHO( fht_fft(fr, fi, ldn, is); );
        CHECK( fft_dif4(gr, gi, ldn, is); );

        if ( ldn<=SMALL_LDN )
        {
          CHECK( slow_ft(gr, gi, n, is); );
          CHECK( slow_fract_ft(gr, gi, n, is); );
        }

        acopy(ac, fc, n);
        CHECK( fht_fft(gr, gi, ldn, is);/**/ separator(gr, gi, n, is); multiply_val(gr, 2*n, 1.0/(double)n); fht_complex_real_fft(gr, ldn); fht_complex_real_fft(gi, ldn); );

        cout << "----- COMPLEX FHT: -----" << endl;
        acopy(ac, fc, n);  acopy(ac, gc, n);
        EQUIV( unzip(fr, 2*n); fht_dif(fr, ldn); fht_dif(fi, ldn); /**/ fht_dif(gc, ldn); unzip(gr, 2*n););

        cout << "\n----- REAL FFT: -----" << endl;
        ECHO( fht_real_complex_fft(fr, ldn, is); );

        if ( is>0 )  CHECK( wrap_real_complex_fft(gr, ldn); unzip(gr, n); );

        CHECK( easy_ordering_real_complex_fft(gr, ldn, is); if (n>=4) reverse(gr+nh+1, nh-1); );

        CHECK( split_radix_real_complex_fft(gr, ldn, is); );


        cout << "\n----- IDENTITY (FFT/invFFT): -----" << endl;
        ECHO( acopy(ac, fc, n); );

        CHECK( fht_real_complex_fft(gr, ldn, is);/**/ fht_complex_real_fft(gr, ldn, is); multiply_val(gr, n, 1.0/(double)n); );

        CHECK( split_radix_real_complex_fft(gr, ldn, is);/**/ split_radix_complex_real_fft(gr, ldn, is); multiply_val(gr, n, 1.0/(double)n); );

        if ( is>0 )  CHECK( wrap_real_complex_fft(gr, ldn);/**/ wrap_complex_real_fft(gr, ldn); multiply_val(gr, n, 1.0/(double)n); );

        CHECK( fft_dif4_core_p1(gc, ldn); fft_dit4_core_m1(gc, ldn); multiply_val(gr, 2*n, 1.0/(double)n); );
        CHECK( fft_dit4_core_p1(gc, ldn); fft_dif4_core_m1(gc, ldn); multiply_val(gr, 2*n, 1.0/(double)n); );

        CHECK( split_radix_dif_fft_core(gc, ldn); /* is = +1 */ split_radix_dit_fft_core(gc, ldn); /* is = -1 */ multiply_val(gr, 2*n, 1.0/(double)n); );

      } // ---------- end isign loop

    } // === ldn ===

    cout << "+++++++++++++++++++ PASS # " << r
         << " (of " << rep << ") ++++++ FINISHED +++++++++++++" << endl;

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
