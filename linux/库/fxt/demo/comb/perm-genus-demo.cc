
#include "perm/perm-genus.h"  // perm_genus()
#include "comb/perm-lex-inv.h"

//#include "comb/perm-trotter.h"
//#include "comb/perm-gray-rfact.h"


#include "perm/printcycles.h"
#include "comb/comb-print.h"

#include "comb/paren-string-to-rgs.h"

#include "ds/bitarray.h"


#include "comb/fact2perm.h"
#include "perm/perminvert.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

#include "jjassert.h"


//% Genus of all permutations of n elements.
//% Print parenthesis strings for permutations of genus zero.
//% Cf. OEIS sequence A177267.

// Cf. seq/A178514-demo.cc for genus of derangements, involutions, and up-down permutations.


// Whether to draw bit strings for permutations of genus zero:
#define DRAW_ZG_PARENS

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements.");

    ulong gct[32];  // stats: genus histogram
    for (ulong j=0; j<n; ++j)  gct[j] = 0;
    ulong cpi[32];  // aux for rotated inverse permutation
    bitarray B(n);  // aux for computation of genus

    perm_lex_inv P(n);
//    perm_trotter P(n);
//    perm_gray_rfact P(n);

    const ulong *p = P.data();

    ulong ct = 0;

#ifdef TIMING
    do
    {
        ++ct;
        const ulong gen = perm_genus(p, n, cpi, &B);
        gct[gen] += 1;
    }
    while ( P.next() );

#else  // TIMING

    bool dfz = true;  // whether to print dots for zeros

#ifdef DRAW_ZG_PARENS
    char *C = new char[2*n+1];  // binary paren strings
    C[2*n] = '\0';
    ulong *R = new ulong[n];  // Catalan RGS
#endif

    do
    {
        ++ct;
        const ulong gen = perm_genus(p, n, cpi, &B);
        gct[gen] += 1;

        cout << setw(4) << ct << ":";
        print_vec("    ", p, n, dfz);
        cout << "  " << gen;
        print_cycles("   ", p, n, &B);
//        print_cycles("   ", cpi, n, &B);


#ifdef DRAW_ZG_PARENS
        if ( gen == 0 )
        {
//            genus0_perm_to_paren(p, n, C, "()");  // paren string
            genus0_perm_to_paren(p, n, C, "1.");  // bit string
//            genus0_perm_to_paren(cpi, n, C, "1.");  // bit string form cpi[]
            cout << "   ";  // print bit string
            for (ulong j=0; j<2*n; ++j)   cout <<  C[j];

            // print Catalan RGS
            jjassert( paren_bit_string_to_rgs(C, R) );
            print_vec("   ", R, n, true);

//            ulong Z[32];
//            rfact2invperm(R+1, n, Z);
//            print_vec("   ", Z, n, true);
////            for (ulong j=0; j<n; ++j)  Z[j] = n-1-Z[j];
//            for (ulong j=0,i=n-1; j<i; ++j,--i)  swap2(Z[j], Z[i]);
//            ulong gz = perm_genus(Z, n, cpi, &B);
//            cout << "  " << gz;

//            perm2rfact(p, n, cpi);
////            for (ulong j=0; j<n-1; ++j)  cpi[j] = j+1-cpi[j];
//            print_vec("   ", cpi, n-1, true);
        }

#endif

        cout << endl;
    }
    while ( P.next() );

#ifdef DRAW_ZG_PARENS
    delete []  C;
    delete []  R;
#endif

#endif  // TIMING

    cout << " ct=" << ct << endl;

    for (ulong j=0; j<n; ++j)  { cout << gct[j] << ", "; ct-=gct[j]; }
    cout << endl;
    jjassert( ct==0 );


    return 0;
}
// -------------------------

/*

A177267:
 1: 1,
 2: 2, 0,
 3: 5, 1, 0,
 4: 14, 10, 0, 0,
 5: 42, 70, 8, 0, 0,
 6: 132, 420, 168, 0, 0, 0,
 7: 429, 2310, 2121, 180, 0, 0, 0,
 8: 1430, 12012, 20790, 6088, 0, 0, 0, 0,
 9: 4862, 60060, 174174, 115720, 8064, 0, 0, 0, 0,
10: 16796, 291720, 1309308, 1624480, 386496, 0, 0, 0, 0, 0,
11: 58786, 1385670, 9087078, 18748730, 10031736, 604800, 0, 0, 0, 0, 0,
12: 208012, 6466460, 59306676, 188208020, 186698512, 38113920, 0, 0, 0, 0, 0, 0,
13: 742900, 29745716, 368588220, 1700309468, 2788065280, 1271140416, 68428800, 0, 0, 0, 0, 0, 0,


Columns are
A000108 (2*n)!/(n!*(n+1)!)
A002802 (2*n+3)!/(6*n!*(n+1)!)

*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 11
./bin 11  7.49s user 0.00s system 99% cpu 7.491 total
 ==> 11!/7.49 == 5,329,345 per second

 time ./bin 12
./bin 12  95.58s user 0.00s system 99% cpu 1:35.60 total
 ==> 12!/95.58 == 5,011,525 per second

 time ./bin 13
./bin 13  1312.64s user 0.00s system 99% cpu 21:52.85 total
 ==> 13!/1312.64 == 4,743,890 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-genus-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-genus-demo.cc DEMOFLAGS=-DTIMING"
/// End:

