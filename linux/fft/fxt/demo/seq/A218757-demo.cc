
#include "comb/ascent-nonflat-rgs.h"
#include "comb/word-stats.h"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% OEIS sequence A218757:
//% number of length-n ascent sequences without flat steps containing k zeros.

// Cf. comb/ascent-rgs-stats-demo.cc for statistics for ascent sequences
// Cf. comb/ascent-nonflat-rgs-demo.cc for ascent sequences without flat steps
// Cf. comb/ascent-rgs-demo.cc for all ascent sequences


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Length of strings");

    ascent_nonflat_rgs A(n);

    ulong ct = 0;


    word_stats S(A.data(), n);
    ulong st[64];
    for (ulong k=0; k<=n; ++k)  st[k] = 0;

    ulong j = n;
    do
    {
        ++ct;

        ulong t = S.num_zeros();  // default
//        ulong t = S.num_max_val();
//        ulong t = S.num_ascents();
//        ulong t = A.num_ascents();
//        ulong t = S.max_val();
        st[t] += 1;


#ifndef TIMING

        cout << setw(4) << ct << ":  ";

        // print RGS:
        print_vec("  ", A.data(), n, true );
//        print_vec("  ", A.m_, n, true );
//        cout << setw(4) << A.num_ascents();

//        cout << setw(4) << j;

        cout << "  " << t;

        cout << endl;

        jjassert( A.OK() );
#endif  // TIMING
    }
    while ( (j=A.next()) );


    for (ulong k=0; k<=n; ++k) cout << st[k] << ", ";
    cout << endl;

    cout << " ct=" << ct;  // OEIS sequence A138265
    cout << endl;

    return 0;
}
// -------------------------

/*

By number of zeros (A218757):

  0:  1,
  1:  0, 1,
  2:  0, 1, 0,
  3:  0, 1, 1, 0,
  4:  0, 2, 3, 0, 0,
  5:  0, 5, 9, 2, 0, 0,
  6:  0, 16, 32, 13, 0, 0, 0,
  7:  0, 61, 132, 72, 6, 0, 0, 0,
  8:  0, 271, 623, 409, 69, 0, 0, 0, 0,
  9:  0, 1372, 3314, 2480, 605, 24, 0, 0, 0, 0,
 10:  0, 7795, 19628, 16222, 5016, 432, 0, 0, 0, 0, 0,
 11:  0, 49093, 128126, 114594, 41955, 5498, 120, 0, 0, 0, 0, 0,
 12:  0, 339386, 914005, 872336, 363123, 62626, 3120, 0, 0, 0, 0, 0, 0,
 13:  0, 2554596, 7074517, 7132352, 3287492, 690935, 54370, 720, 0, 0, 0, 0, 0, 0,
 14:  0, 20794982, 59050739, 62408068, 31272370, 7644536, 814690, 25560, 0, 0, 0, 0, 0, 0, 0,
 15:  0, 182010945, 528741491, 582316795, 313016308, 86299772, 11464099, 584580, 5040, 0, 0, 0, 0, 0, 0, 0,


Row sums are A138265.

The sum of row n is the first element of the row n+1: the length-(n+1)
sequences with one zero (which must be at the initial position) are
formed by incrementing each digit of the length-n sequences and
prepending zero.

 */


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A218757-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A218757-demo.cc DEMOFLAGS=-DTIMING"
/// End:

