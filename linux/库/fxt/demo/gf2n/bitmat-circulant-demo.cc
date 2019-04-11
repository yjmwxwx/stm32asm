
#include "bmat/bitmat-funcs.h"
#include "bmat/bitmat-inline.h"
#include "bits/bit-necklace.h"
#include "bpol/bitpol-gcd.h"
#include "bpol/bitpolmod-arith.h"  // bitpolmod_inverse()

#include "bits/revbin.h"
#include "bits/bitcount.h"

#include "bits/bitrotate.h"  // bit_rotate_left()
#include "bits/print-bin.h"  // print_bin()
#include "aux1/copy.h"  // null()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"  // ulong

#include "jjassert.h"
#include "fxtio.h"
#include "fxtalloca.h"


//% Invertible circulant matrices over GF(2).
//% Cf. OEIS sequences A027362 and A003473.


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "  n x n - matrices");

    ulong wh = 2;
    NXARG(wh, "What to do: 0==>just count  1==>print words  2==>also print matrix");
    // 4==> also print nullspace

    ALLOCA(ulong, T, n);
    ALLOCA(ulong, M, n);
    null(M, n);
    null(T, n);

    ulong nct = 0;  // count invertible matrices
    ulong sct = 0;  // count singular matrices

    ulong cn = (1UL<<n)+1;
    bit_necklace bn(n);
    do
    {
        if ( 0==bn.is_lyndon_word() )  continue;  // periodic?

        ulong v0 = bn.data();
        if ( 0==(bit_count(v0) & 1) )  continue;  // even number of bits?
        v0 = revbin(v0, n);  // want minimum

        bitmat_circulant(v0, n, M);

        ulong nn = bitmat_nullspace(M, n, T);
        if ( 0==nn )  ++nct;
        else          ++sct;

        if ( wh<1 )  continue;  // just count

        print_bin_vec("L=", v0, n);
        if ( 0==nn )  cout << "    ";
        else          cout << " [S]";

        ulong vi = bitpolmod_inverse(v0, cn);
        if ( vi )  print_bin_vec("W=", vi, n);
        else       print_bin_vec("  N=", T[1], n);

        cout << endl;

        // check equivalence with gcd(v0, x^n-1):
        ulong gn = bitpol_gcd(v0, cn);  // gcd(L, x^n-1)
//        print_bin_vec("  gcd=", gn, n);  cout << " ";
        jjassert( ((nn)&&(gn!=1)) || ((0==nn)&&(gn==1)) );


        if ( wh<2 )  continue;  // only print word
        cout << endl;

        bitmat_print("  M =", M, n);
        cout << endl;

        if ( wh<3 )  continue;  // do not print nullspace
        for (ulong k=0; k<nn; ++k)
        {
            print_bin("   N: ", T[k], n);
            cout << endl;
        }
        cout << endl;

        if ( 0!=nn )  continue;
        bitmat_inverse(M, n, T);
        bitmat_print("  M^-1 =", T, n);
        cout << endl;
    }
    while ( bn.next() );

    cout << "n=" << n;
    cout << "   #invertible=" << nct;
    cout << "   #singular=" << sct;
//    cout << "   sum=" << (nct+sct);

    cout << endl;

    return 0;
}
// -------------------------

//OEIS:
//A027362 ,1,1,1,2,3,4,7,16,21,48,93,128,315,448,675,2048,
//A003473 ,1,2,3,8,15,24,49,128,189,480,1023,1536,4095,6272,


//  n = 1   #invertible = 1  #singular = 1  sum = 2
//  n = 2   #invertible = 1  #singular = 0  sum = 1
//  n = 3   #invertible = 1  #singular = 1  sum = 2
//  n = 4   #invertible = 2  #singular = 1  sum = 3
//  n = 5   #invertible = 3  #singular = 3  sum = 6
//  n = 6   #invertible = 4  #singular = 5  sum = 9
//  n = 7   #invertible = 7  #singular = 11  sum = 18
//  n = 8   #invertible = 16  #singular = 14  sum = 30
//  n = 9   #invertible = 21  #singular = 35  sum = 56
//  n = 10   #invertible = 48  #singular = 51  sum = 99
//  n = 11   #invertible = 93  #singular = 93  sum = 186
//  n = 12   #invertible = 128  #singular = 207  sum = 335
//  n = 13   #invertible = 315  #singular = 315  sum = 630
//  n = 14   #invertible = 448  #singular = 713  sum = 1161
//  n = 15   #invertible = 675  #singular = 1507  sum = 2182
//  n = 16   #invertible = 2048  #singular = 2032  sum = 4080
//  n = 17   #invertible = 3825  #singular = 3885  sum = 7710
//  n = 18   #invertible = 5376  #singular = 9156  sum = 14532
//  n = 19   #invertible = 13797  #singular = 13797  sum = 27594
//  n = 20   #invertible = 24576  #singular = 27801  sum = 52377
//  n = 21   #invertible = 27783  #singular = 72075  sum = 99858
//  n = 22   #invertible = 95232  #singular = 95325  sum = 190557
//  n = 23   #invertible = 182183  #singular = 182539  sum = 364722

//OEIS:
//A001037 ,1,2,1,2,3,6,9,18,30,56,99,186,335,630,1161,2182,4080,7710
//A059966   ,1,1,2,3,6,9,18,30,56,99,186,335,630,1161,2182,4080,7710
//A060477   ,3,1,2,3,6,9,18,30,56,99,186,335,630,1161,2182,4080,7710


// odd bitcount only:
//  n = 1   #invertible = 1  #singular = 0  sum = 1
//  n = 2   #invertible = 1  #singular = 0  sum = 1
//  n = 3   #invertible = 1  #singular = 0  sum = 1
//  n = 4   #invertible = 2  #singular = 0  sum = 2
//  n = 5   #invertible = 3  #singular = 0  sum = 3
//  n = 6   #invertible = 4  #singular = 1  sum = 5
//  n = 7   #invertible = 7  #singular = 2  sum = 9
//  n = 8   #invertible = 16  #singular = 0  sum = 16
//  n = 9   #invertible = 21  #singular = 7  sum = 28
//  n = 10   #invertible = 48  #singular = 3  sum = 51
//  n = 11   #invertible = 93  #singular = 0  sum = 93
//  n = 12   #invertible = 128  #singular = 42  sum = 170
//  n = 13   #invertible = 315  #singular = 0  sum = 315
//  n = 14   #invertible = 448  #singular = 137  sum = 585
//  n = 15   #invertible = 675  #singular = 416  sum = 1091
//  n = 16   #invertible = 2048  #singular = 0  sum = 2048
//  n = 17   #invertible = 3825  #singular = 30  sum = 3855
//  n = 18   #invertible = 5376  #singular = 1904  sum = 7280
//  n = 19   #invertible = 13797  #singular = 0  sum = 13797
//  n = 20   #invertible = 24576  #singular = 1638  sum = 26214
//  n = 21   #invertible = 27783  #singular = 22146  sum = 49929
//  n = 22   #invertible = 95232  #singular = 93  sum = 95325
//  n = 23   #invertible = 182183  #singular = 178  sum = 182361

// OEIS:
// A056303   ,0,1,1,2,3,5,9,16,28,51,93,170,315,585,1091,2048,3855,7280,13797,26214
// A000048 ,1,1,1,1,2,3,5,9,16,28,51,93,170,315,585,1091,2048,3855,7280,13797,26214

/*
 n=1   #invertible=1   #singular=0   #self-dual=1
 n=2   #invertible=1   #singular=0   #self-dual=1
 n=3   #invertible=1   #singular=0   #self-dual=1
 n=4   #invertible=2   #singular=0   #self-dual=2
 n=5   #invertible=3   #singular=0   #self-dual=1
 n=6   #invertible=4   #singular=1   #self-dual=2
 n=7   #invertible=7   #singular=2   #self-dual=1
 n=8   #invertible=16   #singular=0   #self-dual=4
 n=9   #invertible=21   #singular=7   #self-dual=3
 n=10   #invertible=48   #singular=3   #self-dual=4
 n=11   #invertible=93   #singular=0   #self-dual=3
 n=12   #invertible=128   #singular=42   #self-dual=16
 n=13   #invertible=315   #singular=0   #self-dual=5
 n=14   #invertible=448   #singular=137   #self-dual=8
 n=15   #invertible=675   #singular=416   #self-dual=15
 n=16   #invertible=2048   #singular=0   #self-dual=32
 n=17   #invertible=3825   #singular=30   #self-dual=17
 n=18   #invertible=5376   #singular=1904   #self-dual=48
 n=19   #invertible=13797   #singular=0   #self-dual=27
 n=20   #invertible=24576   #singular=1638   #self-dual=128
 n=21   #invertible=27783   #singular=22146   #self-dual=63
 n=22   #invertible=95232   #singular=93   #self-dual=96
 n=23   #invertible=182183   #singular=178   #self-dual=89
 n=24   #invertible=262144   #singular=87376   #self-dual=512
 n=25   #invertible=629145   #singular=41943   #self-dual=205

1,1,1,2,1,2,1,4,3,4,3,16,5,8,15,32,17,48,27,128,63,96,89,512,205
Nothing with super-seek

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/bitmat-circulant-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/bitmat-circulant-demo.cc DEMOFLAGS=-DTIMING"
/// End:

