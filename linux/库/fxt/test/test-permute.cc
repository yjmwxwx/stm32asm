
#include <cmath>
#include <cstdlib>  // strtoul()

#include "perm-all.h"
#include "bits/revbin.h"
#include "perm/revbinpermute.h"
//#include "aux1/auxprint.h"
//#include "aux1/aux1double.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "fxtalloca.h"


#include "aux1/copy.h"
#include "aux0/swap.h"


#include "test.h"  // last to include


static void
test_revbin_perm(ulong *gr, ulong ldn)
{
    ulong n = 1UL << ldn;
    for (ulong z=0; z<n; ++z)
    {
        ulong rz=revbin(z,ldn);
        if( rz>z )  swap2(gr[z],gr[rz]);
    }
}
// -------------------------

int
main(int argc, char **argv)
{
  cout << "Running tests for permutations ... " << endl;
//  print_fxt_version();

  ulong minldn = 1, maxldn = 11;
  if ( argc>1 )  minldn = strtoul(argv[1], 0, 10);
  if ( argc>2 )  maxldn = strtoul(argv[2], 0, 10);

  ulong rep = 5;
  if ( argc>3 )  rep = strtoul(argv[3], 0, 10);


  ulong n = 1UL<<maxldn;
  ALLOCA(ulong, tar, n);
  ALLOCA(ulong, fr, n);
  ALLOCA(ulong, gr, n);
  const ulong *const ar = tar;

  for (ulong r=1; r<=rep; ++r)
  {
    cout << "+++++++++++++++++++++++++ PASS # " << r
         << " (of " << rep << ") +++++++++++++++++++++++++" << endl;

    for (ulong ldn=minldn; ldn<=maxldn; ++ldn)
    {
      n = 1UL<<ldn;
      cout << "====================  LDN = " << ldn
           << "   N = " << n << " :" << endl;

      null(tar, n);
//      for (ulong i=0; i<n; ++i)  tar[i] = ;
      random_permutation(tar, n);
      reverse(tar, n);
//      cerr << "S=";  for (ulong i=0; i<n; ++i)  cerr << " " << tar[i];  cerr << endl;
//      set_seq(tar, n, 0.0, 1.0);


      cout << "\n----- GRAY: -----" << endl;
      EQUIV_EXACT( gray_permute(ar, fr, n);/**/ acopy(ar, gr, n); gray_permute(gr, n); );
      if ( n==16 )
      {
          EQUIV_EXACT( gray_permute(ar, fr, n);/**/ acopy(ar, gr, n); gray_permute_16(gr); );
      }
      EQUIV_EXACT( acopy(ar, fr, n);/**/ acopy(ar, gr, n); gray_permute(ar, gr, n); inverse_gray_permute(gr, n); );

      EQUIV_EXACT( inverse_gray_permute(ar, fr, n);/**/ acopy(ar, gr, n); inverse_gray_permute(gr, n); );

      EQUIV_EXACT( gray_rev_permute(ar, fr, n);/**/ acopy(ar, gr, n); gray_rev_permute(gr, n); );
      EQUIV_EXACT( inverse_gray_rev_permute(ar, fr, n);/**/ acopy(ar, gr, n); inverse_gray_rev_permute(gr, n); );


      cout << "\n----- ZIP: -----" << endl;
      EQUIV_EXACT( acopy(ar, fr, n); zip(fr, n);/**/ acopy(ar, gr, n); zip(gr, n); );

      EQUIV_EXACT( acopy(ar, fr, n);/**/ acopy(ar, gr, n); zip(gr, n); unzip(gr, n); );
      EQUIV_EXACT( acopy(ar, fr, n);/**/ acopy(ar, gr, n); haar_permute(gr, n); inverse_haar_permute(gr, n); );

      EQUIV_EXACT( zip(ar, fr, n); unzip(fr,n); /**/ acopy(ar, gr, n); );
      EQUIV_EXACT( unzip(ar, fr, n); zip(fr,n); /**/ acopy(ar, gr, n); );

      EQUIV_EXACT( zip(ar, fr, n);  /**/ acopy(ar, gr, n); zip(gr, n); );
      EQUIV_EXACT( unzip(ar, fr, n);/**/ acopy(ar, gr, n); unzip(gr, n); );


      cout << "\n----- REVBIN: -----" << endl;
      EQUIV_EXACT( acopy(ar, fr, n); revbin_permute(fr, n);/**/
                   acopy(ar, gr, n); test_revbin_perm(gr, ldn); );
//      for (ulong z=0; z<n; ++z) { ulong rz=revbin(z,ldn); if(r>z) swap2(gr[z],gr[rz]); }  );


      cout << "\n----- EVENODDREV: -----" << endl;
      EQUIV_EXACT( acopy(ar, fr, n); zip_rev(fr, n);/**/ acopy(ar, gr, n); zip_rev(gr, n); );

      EQUIV_EXACT( acopy(ar, fr, n);/**/ acopy(ar, gr, n); zip_rev(gr, n); unzip_rev(gr, n); );

      EQUIV_EXACT( zip_rev(ar, fr, n);/**/ acopy(ar, gr, n); zip_rev(gr, n); );

      EQUIV_EXACT( unzip_rev(ar, fr, n);/**/ acopy(ar, gr, n); unzip_rev(gr, n); );


      cout << "\n----- PERMUTATION: -----" << endl;
//      acopy(ar, fr, n);/**/ acopy(ar, gr, n); make_inverse(gr, n);
//      cerr << "SS=";  for (ulong i=0; i<n; ++i)  cerr << " " << ar[i];  cerr << endl;
//      cerr << "II=";  for (ulong i=0; i<n; ++i)  cerr << " " << gr[i];  cerr << endl;
//      if ( 0==is_inverse(ar, gr, n) )  { exit(99); }

      EQUIV_EXACT( make_inverse(ar, fr, n);/**/ acopy(ar, gr, n); make_inverse(gr, n); );
      random_permutation(fr, n);
      EQUIV_EXACT( apply_permutation(ar, fr, gr, n); /**/ apply_permutation(ar, fr, n); );
      random_permutation(fr, n);
      EQUIV_EXACT( apply_inverse_permutation(ar, fr, gr, n); /**/ apply_inverse_permutation(ar, fr, n); );
      random_permutation(fr, n);
      EQUIV_EXACT( compose(ar, fr, gr, n); /**/ compose(ar, fr, n); );


// test makefile behavior with failure:
//      EQUIV_EXACT( unzip_rev(ar, fr, n);/**/ if (ldn<5) acopy(ar, gr, n); unzip_rev(gr, n); );
    }

    cout << "+++++++++++++++++++ PASS # " << r
         << " (of " << rep << ") ++++++ FINISHED +++++++++++++" << endl;
  }

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
