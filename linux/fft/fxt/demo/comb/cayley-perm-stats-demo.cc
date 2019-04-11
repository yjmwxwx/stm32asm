
#include "comb/cayley-perm.h"
#include "comb/word-stats.h"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Statistics for Cayley permutations.
//% Cf. the following OEIS sequences:
//% A090665: Cayley permutations by first element.
//% A131689: Cayley permutations by max element.
//% A154921: Cayley permutations by number of zeros (size of first block).

// Cf. comb/cayley-perm-demo.cc

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Length of strings, n>=1");

    ulong sq = 0;
    NXARG(sq, "Select stats:\n"
          "    0 ==> first element\n"
          "    1 ==> max element\n"
          "    2 ==> number of zeros\n"
          "    3 ==> position of first occurrence of the maximal value\n"
          );

    cayley_perm A(n);
    word_stats W(A.data(), n);

    ulong ct = 0;
    ulong * st = new ulong[n+1];  // stats
    for (ulong k=0; k<n+1; ++k)  st[k] = 0;

#ifndef TIMING
    const ulong *x = A.data();
#endif

    ulong j = 0;
    do
    {
        ++ct;
        ulong s = 0;
        switch ( sq )
        {
        case 0:  // by first element: A090665, cf. A054255
            s = W.first_val();
            // first column is A000629
            break;
            // 1,
            // 1, 0,
            // 2, 1, 0,
            // 6, 5, 2, 0,
            // 26, 25, 18, 6, 0,
            // 150, 149, 134, 84, 24, 0,
            // 1082, 1081, 1050, 870, 480, 120, 0,
            // 9366, 9365, 9302, 8700, 6600, 3240, 720, 0,
            // 94586, 94585, 94458, 92526, 82320, 57120, 25200, 5040, 0,

        case 1:  // by max element: A131689, A019538 (k!*Stirling2(n,k))
            s = W.max_val();
            // second col is A000918: 2^n - 2
            // third col is A001117: 3^n - 3*2^n + 3
            // fourth col is A000919: 4^n - C(4,3)*3^n + C(4,2)*2^n - C(4,1)
            break;
            // 1,
            // 1, 0,
            // 1, 2, 0,
            // 1, 6, 6, 0,
            // 1, 14, 36, 24, 0,
            // 1, 30, 150, 240, 120, 0,
            // 1, 62, 540, 1560, 1800, 720, 0,
            // 1, 126, 1806, 8400, 16800, 15120, 5040, 0,
            // 1, 254, 5796, 40824, 126000, 191520, 141120, 40320, 0,

        case 2:  // by number of zeros: A154921
            s = W.num_zeros();
            // second col is A052882
            // third col is A154931
            break;
            // 1,
            // 0, 1,
            // 0, 2, 1,
            // 0, 9, 3, 1,
            // 0, 52, 18, 4, 1,
            // 0, 375, 130, 30, 5, 1,
            // 0, 3246, 1125, 260, 45, 6, 1,
            // 0, 32781, 11361, 2625, 455, 63, 7, 1,
            // 0, 378344, 131124, 30296, 5250, 728, 84, 8, 1,

        case 3:  // position of first occurrence of max value: A000000
            s = W.first_max_idx();
            // first col is A000629
            // second col is A162509
            break;
            // 1,
            // 1, 0,
            // 2, 1, 0,
            // 6, 4, 3, 0,
            // 26, 20, 16, 13, 0,
            // 150, 124, 104, 88, 75, 0,
            // 1082, 932, 808, 704, 616, 541, 0,
            // 9366, 8284, 7352, 6544, 5840, 5224, 4683, 0,
            // 94586, 85220, 76936, 69584, 63040, 57200, 51976, 47293, 0,

        case 4:  // A000000
            s = W.max_flat_length();
            break;
            // 1,
            // 1, 0,
            // 0, 2, 1,
            // 0, 8, 4, 1,
            // 0, 44, 26, 4, 1,
            // 0, 308, 200, 28, 4, 1,
            // 0, 2612, 1812, 226, 28, 4, 1,
            // 0, 25988, 18928, 2116, 228, 28, 4, 1,
            // 0, 296564, 224220, 22648, 2142, 228, 28, 4, 1,

        case 5:  // A000000
            s = W.max_incr_length();
            break;
            // 1,
            // 1, 0,
            // 0, 2, 1,
            // 0, 4, 8, 1,
            // 0, 8, 54, 12, 1,
            // 0, 16, 372, 136, 16, 1,
            // 0, 32, 2846, 1554, 230, 20, 1,
            // 0, 64, 24572, 18940, 3344, 348, 24, 1,
            // 0, 128, 239610, 248814, 50780, 5984, 490, 28, 1,

        case 6:  // A000000
            s = W.max_weakly_incr_length();
            break;
            // 1,
            // 1, 0,
            // 0, 1, 2,
            // 0, 1, 8, 4,
            // 0, 1, 42, 24, 8,
            // 0, 1, 240, 220, 64, 16,
            // 0, 1, 1702, 2100, 688, 160, 32,
            // 0, 1, 13868, 22720, 8288, 1968, 384, 64,
            // 0, 1, 130962, 273456, 108520, 26560, 5312, 896, 128,

        default:
            cerr << "Invalid choice (exiting)." << endl;
            return 1;
        }


        st[ s ] += 1;


#ifndef TIMING
        cout << setw(4) << ct << ":";

        // print Cayley-permutations:
        print_vec("  ", x, n, true );

        cout << setw(4) << s;

        cout << endl;

//        jjassert( A.OK() );
#endif  // TIMING
    }
    while ( (j=A.next()) );


    ulong sct = 0;
    for (ulong k=0; k<=n; ++k)
    {
        cout << st[k] << ", ";
        sct += st[k];
    }
    cout << endl;

    cout << " ct=" << ct;  // total: OEIS sequence A000670
    cout << endl;

    jjassert( sct == ct );

    delete [] st;

    return 0;
}
// -------------------------

/*

Print triangle for stats q:


OEIS example:
q=0; for n in $(seq 0 8) ; do ./bin $n $q | grep ', $' ; done | nl -v0 -s':  ' -w2 -n rz

C++ comment:
q=0;  for n in $(seq 0 8) ; do ./bin $n $q | grep ', $' ; done | sed 's/^/\/\/ /; s/ $//;'

Extract column c from stats q:
q=0;  c=0;  echo $(for n in $(seq 0 13) ; do ./bin $n $q | grep ', $' ; done | cut -d, -f$((c+1))) | sed 's/ /, /g;'

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/cayley-perm-stats-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/cayley-perm-stats-demo.cc DEMOFLAGS=-DTIMING"
/// End:
