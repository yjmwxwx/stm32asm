
#include "fht-all.h"
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
  cout << "Running tests for FHTs ... " << endl;

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

    for (ulong ldn=minldn; ldn<=maxldn; ++ldn)
    {
      n = 1UL<<ldn;
      cout << "====================  LDN = " << ldn
           << "   N = " << n << " :" << endl;

//      ulong nh = n/2;
      double *fi=fr+n,  *gi=gr+n; // ,  *ai=ar+n;
      null(ac, n);
      //   ar[1] = ai[1] = 1;
      for (ulong i=0; i<n; ++i)  ac[i] = Complex(white_noise(), white_noise());
      //   for (ulong i=0; i<n; ++i)  ac[i] = Complex(white_noise(), 0.0 );
      //   set_seq(ar, 2*n, 1.0/(double)n, 1.0/(double)n);
      //   fill(ar, 2*n, 1.0);


      cout << "\n----- FHT: -----" << endl;
      ECHO( fht_dit(fr, ldn); );

      CHECK_REAL( fht_dif(gr, ldn); );
      CHECK( fht_dit2(gr, ldn); );
      CHECK( fht_dif2(gr, ldn); );
      CHECK( fht_loc_dif2_core(gr, ldn); revbin_permute(gr, n); );
      CHECK( revbin_permute(gr, n); fht_loc_dit2_core(gr, ldn); );

      if ( ldn<=SMALL_LDN )
      {
        CHECK_REAL( slow_ht(gr, n); );

        CHECK_REAL( recursive_fht_dit2(gr, ldn); );
        CHECK_REAL( recursive_fht_dif2(gr, ldn); );
        CHECK( fht_depth_first_dit2(gr, ldn); );
        CHECK( fht_depth_first_dif2(gr, ldn); );
      }

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
