
#include "fft-all.h"
#include "fht-all.h"
#include "dctdst-all.h"
#include "walsh-all.h"
#include "haar-all.h"
#include "perm-all.h"
#include "fxtio.h"

//#include "aux1/aux1double.h"
//#include "aux1/auxprint.h"
#include "aux1/arith1.h"
#include "aux0/randf.h"

#include <cmath>
#include <cstdlib>  // strtoul()

#include "fxttypes.h"
#include "fxtalloca.h"


#include "test.h"  // last to include

#include "aux1/copy.h"


template <typename Type>
inline void walsh_wal_dif2(Type *f, ulong ldn)
{
    revbin_permute(f, (1UL<<ldn));
    walsh_wal_dif2_core(f, ldn);
}
// -------------------------

template <typename Type>
inline void walsh_wal_dit2(Type *f, ulong ldn)
{
    walsh_wal_dit2_core(f, ldn);
    revbin_permute(f, (1UL<<ldn));
}
// -------------------------

int
main(int argc, char **argv)
{
  cout << "Running tests for other transforms ... " << endl;

  ulong minldn = 0, maxldn = 15;
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

      double *fi=fr+n,  *gi=gr+n; //,  *ai=ar+n;
      null(ac, n);
      //   ar[1] = ai[1] = 1;
      for (ulong i=0; i<n; ++i)  ac[i] = Complex(white_noise(), white_noise());
      //   for (ulong i=0; i<n; ++i)  ac[i] = Complex(white_noise(), 0.0 );
      //   set_seq(ar, 2*n, 1.0/(double)n, 1.0/(double)n);
//      fill(ar, 2*n, 1.0);  // makes things more traceable

      cout << "\n----- FHT: -----" << endl;
      ECHO( fht_dit(fr, ldn); );
      CHECK_REAL( fht_dif(gr, ldn); );
      if ( ldn<=SMALL_LDN )
      {
        CHECK_REAL( recursive_fht_dif2(gr, ldn); );
        CHECK_REAL( recursive_fht_dit2(gr, ldn); );
        CHECK_REAL( fht_depth_first_dit2(gr, ldn); );
        CHECK_REAL( fht_depth_first_dif2(gr, ldn); );
      }


      cout << "\n----- IDENTITY (WALSH/invWALSH): -----" << endl;
      ECHO( acopy(ac, fc, n); );
      CHECK_REAL( walsh_wal(gr, ldn); walsh_wal(gr, ldn); multiply_val(gr, n, 1.0/(double)n); );
      CHECK_REAL( walsh_wak(gr, ldn); walsh_wak(gr, ldn); multiply_val(gr, n, 1.0/(double)n); );
      CHECK_REAL( walsh_pal(gr, ldn); walsh_pal(gr, ldn); multiply_val(gr, n, 1.0/(double)n); );
      CHECK_REAL( walsh_seq1(gr, ldn); inverse_walsh_seq1(gr, ldn); multiply_val(gr, n, 1.0/(double)n); );
      CHECK_REAL( walsh_seq2(gr, ldn); inverse_walsh_seq2(gr, ldn); multiply_val(gr, n, 1.0/(double)n); );
      CHECK_REAL( walsh_gray(gr, ldn); inverse_walsh_gray(gr, ldn); multiply_val(gr, n, 1.0/(double)n); );
      CHECK_REAL( walsh_wal_rev(gr, ldn); walsh_wal_rev(gr, ldn); multiply_val(gr, n, 1.0/(double)n); );
//      CHECK_REAL( walsh_z1(gr, ldn); walsh_z1(gr, ldn); multiply_val(gr, n, 1.0/(double)n); );
//      CHECK_REAL( walsh_seq1(gr, ldn); inverse_walsh_seq1(gr, ldn); multiply_val(gr, n, 1.0/(double)n); );

//      cout << "\n----- IDENTITY (ARITH-trans, PARITY-trans): -----" << endl;
      ECHO( acopy(ac, fc, n); );
      CHECK_REAL( arith_transform_plus(gr, ldn); arith_transform_minus(gr, ldn); );
      CHECK_REAL( rev_arith_transform_plus(gr, ldn); rev_arith_transform_minus(gr, ldn); );
      CHECK_REAL( reverse(gr,n); rev_arith_transform_plus(gr, ldn); reverse(gr,n); arith_transform_minus(gr, ldn); );
      CHECK_REAL( reverse(gr,n); rev_arith_transform_minus(gr, ldn); reverse(gr,n); arith_transform_plus(gr, ldn); );
      CHECK_REAL( rev_arith_transform_plus(gr, ldn); rev_arith_transform_minus(gr, ldn); );
      CHECK_REAL( prefix_transform(gr, ldn); inverse_prefix_transform(gr, ldn); );

      const double w = -1.0;
      CHECK_REAL( arith_transform_plus(gr, ldn, w); arith_transform_minus(gr, ldn, w); );
      CHECK_REAL( bit_count_weight(gr, ldn, w); bit_count_weight(gr, ldn, 1/w); );
      CHECK_REAL( rev_bit_count_weight(gr, ldn, w); rev_bit_count_weight(gr, ldn, 1/w); );

      CHECK_REAL( rev_arith_transform_plus(gr, ldn, w); rev_arith_transform_minus(gr, ldn, w); );

//      CHECK_REAL( parity_transform(gr, ldn, w); inverse_parity_transform(gr, ldn, w); );
//      CHECK_REAL( rev_parity_transform(gr, ldn); inverse_rev_parity_transform(gr, ldn); multiply_val(gr, n, 1.0); );


      cout << "\n----- IDENTITY (DCT/DST): -----" << endl;
      ECHO( acopy(ac, fc, n); );
      CHECK_REAL( dsth(gr, ldn); idsth(gr, ldn); multiply_val(gr, n, 1.0/(double)n); );
      CHECK_REAL( dcth(gr, ldn); idcth(gr, ldn); multiply_val(gr, n, 1.0/(double)n); );
      CHECK_REAL( dst(gr, ldn);  dst(gr, ldn);   multiply_val(gr, n, 2.0/(double)n); );
      EQUIV( acopy(ar, fr, n); dcth(fr, ldn);/**/ acopy(ar, gr, n); dcth_zapata(gr, ldn); );


      cout << "\n----- EQUIV (WALSH): -----" << endl;
      EQUIV( acopy(ar, fr, n); walsh_wak_dif2(fr, ldn);/**/ acopy(ar, gr, n); walsh_wak_dit2(gr, ldn); );
      EQUIV( acopy(ar, fr, n); walsh_wal_dif2(fr, ldn);/**/ acopy(ar, gr, n); walsh_wal_dit2(gr, ldn); );

      cout << "\n----- EQUIV (HAAR): -----" << endl;
      EQUIV( acopy(ar, fr, n); haar(fr, ldn);/**/ acopy(ar, gr, n); haar_inplace(gr, ldn); haar_permute(gr, n); );
      EQUIV( acopy(ar, fr, n); inverse_haar(fr, ldn);/**/ acopy(ar, gr, n); inverse_haar_permute(gr, n); inverse_haar_inplace(gr, ldn); );



    }  // === ldn ===

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
