
#include "bpol/all-irredpoly.h"
// demo-include "bits/bit-necklace.h"
// demo-include "bpol/necklace2bitpol.h"
// demo-include "bpol/bitpol-normal.cc"

#include "bpol/normalbasis.h"

//#include "bits/bitcount.h"
//#include "bits/print-bin.h"
#include "bpol/bitpol-print.h"

#include "fxtio.h"
#include "fxttypes.h"  // ulong
#include "jjassert.h"  // ulong

#include "nextarg.h"  // NXARG()



//% Generate all irreducible binary polynomials of given degree (from Lyndon words).
//% Indicate which are primitive (P) and normal (N).

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 9;
    NXARG(n, "Degree of polynomials n<BITS_PER_LONG");
    jjassert( n<=BITS_PER_LONG );

    ulong st = 0;
    NXARG(st, "Stop after st polynomials where found,  zero==>list all polynomials");

#ifndef TIMING
    ulong fm = 2;
    NXARG(fm, "Print format:"
          "\n    0==>binary,"
          "\n    1==>hexadecimal,"
          "\n    2==>coefficients,"
          "\n    3==>polynomials");
#endif


    all_irredpoly ip(n);
    ulong p = ip.data();


    ulong ict = 0;  // count Lyndon words (irreducible polynomials)
#ifdef TIMING
    do
    {
        ++ict;
        if ( ict == st )  break;
        p = ip.next();
    }
    while ( p );

#else  // TIMING
    ulong pct = 0;  // count primitive polynomials
    ulong nct = 0;
    ulong npct = 0;  // count normal primitive polynomials
    do
    {
        ++ict;
        ulong pq = ip.is_primitive();
        pct += pq;

        bool nq = bitpol_normal_q(p, n, 1, 0);
        nct += nq;
        npct += (nq && pq);

        if ( nq )  cout << "  N";
        else       cout << "   ";
        if ( pq )  cout << "  P";  // primitive polynomial
        else       cout << "   ";

        cout << "    ";
        switch ( fm )
        {
        case 1:  cout << "0x" << hex << p << dec;  break;
        case 2:  bitpol_print_coeff("", p); break;
        case 3:  bitpol_print("", p); break;
        default: bitpol_print_bin("", p);
        }

        cout << endl;
        if ( ict == st )  break;
        p = ip.next();
    }
    while ( p );
#endif  // TIMING




    cout << endl;
    cout << " n = " << n << ":  ";
    cout << "  #irred. =" << ict;
#ifndef TIMING
    cout << "  #prim. =" << pct;
    cout << "  #normal =" << nct;
    cout << " = ( " << npct << " prim. + " << (nct-npct) << " non-prim.)";
#endif
    cout << endl;


    return 0;
}
// -------------------------


/*
Timing:

Format:
Output-lines
Timing
//Timing with slower routine for poly()

 time ./bin 24
 n = 24:    #irred. =698870
./bin 24  2.53s user 0.00s system 99% cpu 2.544 total
 ==> 698870/2.53 == 276.233 per second
//./bin 24  14.21s user 0.07s system 99% cpu 14.345 total
// ==> 698870/14.21 == 49,181 per second


 time ./bin 35 300000
 n = 35:    #irred. =300000
./bin 35 300000  2.42s user 0.00s system 99% cpu 2.418 total
 ==> 300000/2.42 == 123,966 per second
//./bin 35 300000  17.93s user 0.09s system 99% cpu 18.020 total
// ==> 300000/17.93 == 16,731 per second


 time ./bin 45 100000
 n = 45:    #irred. =100000
./bin 45 100000  1.37s user 0.00s system 99% cpu 1.378 total
 ==> 100000/1.37 == 72,992 per second
//./bin 45 100000  12.53s user 0.06s system 99% cpu 12.616 total
// ==> 100000/12.53 == 7,980 per second


 time ./bin 63 100000
 n = 63:    #irred. =100000
./bin 63 100000  2.59s user 0.00s system 99% cpu 2.598 total
 ==> 100000/2.59 == 38,610 per second
//./bin 63 100000  32.20s user 0.16s system 99% cpu 32.366 total
// ==> 100000/32.20 == 3,105 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)
(only fast versions:)

Using bitpolmod_minpoly() in necklace2bitpol.h:
 time ./bin 45 1000000
 n = 45:    #irred. =1000000
./bin 45 1000000  10.17s user 0.00s system 99% cpu 10.170 total
 ==> 1000000/10.17 == 98,328 per second

Using inlined code in necklace2bitpol.h:
 time ./bin 45 1000000
 n = 45:    #irred. =1000000
./bin 45 1000000  10.13s user 0.00s system 99% cpu 10.136 total
 ==> 1000000/10.13 == 98,716 per second

 time ./bin 24 1000000
 n = 24:    #irred. =698870
./bin 24 1000000  1.93s user 0.00s system 99% cpu 1.930 total
 ==> 1000000/1.93 == 518,134 per second

*/



/*
for ((n=2;n<=25;++n)); do ./bin $n; done | grep -F ' n = '
 n = 2:    #irred. =1  #prim. =1  #normal =1 = ( 1 prim. + 0 non-prim.)
 n = 3:    #irred. =2  #prim. =2  #normal =1 = ( 1 prim. + 0 non-prim.)
 n = 4:    #irred. =3  #prim. =2  #normal =2 = ( 1 prim. + 1 non-prim.)
 n = 5:    #irred. =6  #prim. =6  #normal =3 = ( 3 prim. + 0 non-prim.)
 n = 6:    #irred. =9  #prim. =6  #normal =4 = ( 3 prim. + 1 non-prim.)
 n = 7:    #irred. =18  #prim. =18  #normal =7 = ( 7 prim. + 0 non-prim.)
 n = 8:    #irred. =30  #prim. =16  #normal =16 = ( 7 prim. + 9 non-prim.)
 n = 9:    #irred. =56  #prim. =48  #normal =21 = ( 19 prim. + 2 non-prim.)
 n = 10:    #irred. =99  #prim. =60  #normal =48 = ( 29 prim. + 19 non-prim.)
 n = 11:    #irred. =186  #prim. =176  #normal =93 = ( 87 prim. + 6 non-prim.)
 n = 12:    #irred. =335  #prim. =144  #normal =128 = ( 52 prim. + 76 non-prim.)
 n = 13:    #irred. =630  #prim. =630  #normal =315 = ( 315 prim. + 0 non-prim.)
 n = 14:    #irred. =1161  #prim. =756  #normal =448 = ( 291 prim. + 157 non-prim.)
 n = 15:    #irred. =2182  #prim. =1800  #normal =675 = ( 562 prim. + 113 non-prim.)
 n = 16:    #irred. =4080  #prim. =2048  #normal =2048 = ( 1017 prim. + 1031 non-prim.)
 n = 17:    #irred. =7710  #prim. =7710  #normal =3825 = ( 3825 prim. + 0 non-prim.)
 n = 18:    #irred. =14532  #prim. =7776  #normal =5376 = ( 2870 prim. + 2506 non-prim.)
 n = 19:    #irred. =27594  #prim. =27594  #normal =13797 = ( 13797 prim. + 0 non-prim.)
 n = 20:    #irred. =52377  #prim. =24000  #normal =24576 = ( 11255 prim. + 13321 non-prim.)
 n = 21:    #irred. =99858  #prim. =84672  #normal =27783 = ( 23579 prim. + 4204 non-prim.)
 n = 22:    #irred. =190557  #prim. =120032  #normal =95232 = ( 59986 prim. + 35246 non-prim.)
 n = 23:    #irred. =364722  #prim. =356960  #normal =182183 = ( 178259 prim. + 3924 non-prim.)
 n = 24:    #irred. =698870  #prim. =276480  #normal =262144 = ( 103680 prim. + 158464 non-prim.)
 n = 25:    #irred. =1342176  #prim. =1296000  #normal =629145 = ( 607522 prim. + 21623 non-prim.)
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/all-irredpoly-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/all-irredpoly-demo.cc DEMOFLAGS=-DTIMING"
/// End:

