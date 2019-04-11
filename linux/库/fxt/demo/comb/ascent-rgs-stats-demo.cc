
#include "comb/ascent-rgs.h"
#include "comb/word-stats.h"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Statistics for ascent sequences.
//% Cf. the following OEIS sequences:
//% A218577:
//%   triangle, length-n ascent sequences with maximal element k-1.
//%   An ascent sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0, d(k)>=0,
//%   and d(k) <= 1 + asc([d(1), d(2), ..., d(k-1)]) and asc(.) counts the number
//%   of ascents of its argument.
//% A137251: ascent sequences with k ascents.
//% A175579: ascent sequences with k zeros.
//% A218579: ascent sequences with position of last zero at index k-1.
//% A218580: ascent sequences with position of first occurrence of maximal value at index k-1.
//% A218581: ascent sequences with position of last occurrence of maximal value at index k-1.


// Cf. comb/descent-rgs-stats-demo.cc for stats for descent sequences
// Cf. comb/ascent-rgs-demo.cc

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Length of strings, n>=1");

    ulong sq = 0;
    NXARG(sq, "Select stats:\n"
          "    0 ==> max element\n"
          "    1 ==> number of ascents\n"
          "    2 ==> number of descents\n"
          "    3 ==> number of zeros\n"  // same stats as 5
          "    4 ==> number of fixed points\n"  // same stats as 3
          "    5 ==> number of maximal digits\n"
          "    6 ==> position of last occurrence of zero\n"
          "    7 ==> position of first occurrence of the maximal value\n"
          "    8 ==> position of last occurrence of the maximal value\n"
          "    9 ==> number of flat steps\n"
          "   10 ==> number of even values\n"
//          "   11 ==> number of \n"
          );

    ascent_rgs A(n);
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
        case 0:  // by max element: A218577
            s = W.max_val();
            break;
            // 1,
            // 1, 1,
            // 1, 3, 1,
            // 1, 7, 6, 1,
            // 1, 15, 25, 11, 1,
            // 1, 31, 90, 74, 20, 1,
            // 1, 63, 301, 402, 209, 37, 1,
            // 1, 127, 966, 1951, 1629, 590, 70, 1,
            // 1, 255, 3025, 8869, 10839, 6430, 1685, 135, 1,
            // 1, 511, 9330, 38720, 65720, 56878, 25313, 4870, 264, 1,


        case 1:  // by number of ascents: A137251
            s = A.num_ascents();
//            jjassert( s == W.num_ascents() );
            break;
            // 1,
            // 1, 1,
            // 1, 3, 1,
            // 1, 6, 7, 1,
            // 1, 10, 26, 15, 1,
            // 1, 15, 71, 98, 31, 1,
            // 1, 21, 161, 425, 342, 63, 1,
            // 1, 28, 322, 1433, 2285, 1138, 127, 1,
            // 1, 36, 588, 4066, 11210, 11413, 3670, 255, 1,
            // 1, 45, 1002, 10165, 44443, 79781, 54073, 11586, 511, 1,

        case 2:  // by number of descents: A238858
            // column (k=0) is A011782
            s = W.num_descents();
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 4, 1, 0, 0,
            // 8, 7, 0, 0, 0,
            // 16, 33, 4, 0, 0, 0,
            // 32, 131, 53, 1, 0, 0, 0,
            // 64, 473, 429, 48, 0, 0, 0, 0,
            // 128, 1611, 2748, 822, 26, 0, 0, 0, 0,
            // 256, 5281, 15342, 9305, 1048, 8, 0, 0, 0, 0,
            // 512, 16867, 78339, 83590, 21362, 937, 1, 0, 0, 0, 0,
            // 1024, 52905, 376159, 647891, 307660, 35841, 594, 0, 0, 0, 0, 0,
            // 2048, 163835, 1728458, 4537169, 3574869, 834115, 45747, 262, 0, 0, 0, 0, 0,
            // 4096, 502769, 7689744, 29532566, 35900857, 14475124, 1752513, 45355, 76, 0, 0, 0, 0, 0,


        case 3:  // by number of zeros: A175579
            // Also the number of length-n ascent sequences with k fixed points.
            s = W.num_zeros();
//            jjassert( s == W.num_min_val() );
            break;
            // 1,
            // 1, 1,
            // 2, 2, 1,
            // 5, 6, 3, 1,
            // 15, 21, 12, 4, 1,
            // 53, 84, 54, 20, 5, 1,
            // 217, 380, 270, 110, 30, 6, 1,
            // 1014, 1926, 1490, 660, 195, 42, 7, 1,
            // 5335, 10840, 9020, 4300, 1365, 315, 56, 8, 1,
            // 31240, 67195, 59550, 30290, 10255, 2520, 476, 72, 9, 1,


        case 4:  // by number of fixed points: (same as number of zeros)
            s = W.num_fixed_points();
            break;

        case 5:  // by number of max digits: A000000
            s = W.num_max_val();
            break;
            // 1,
            // 1, 1,
            // 3, 1, 1,
            // 9, 4, 1, 1,
            // 32, 14, 5, 1, 1,
            // 134, 55, 20, 6, 1, 1,
            // 643, 249, 86, 27, 7, 1, 1,
            // 3471, 1274, 419, 126, 35, 8, 1, 1,
            // 20809, 7262, 2281, 657, 176, 44, 9, 1, 1,
            // 137147, 45683, 13704, 3794, 977, 237, 54, 10, 1, 1,
            // 985536, 314563, 90251, 23977, 5965, 1394, 310, 65, 11, 1, 1,
            // 7669233, 2353714, 647597, 165008, 39571, 8969, 1924, 396, 77, 12, 1, 1,


        case 6:  // position of last zero: A218579
            s = W.last_zero_idx();
//            jjassert( s == W.last_min_idx() );
            break;
            // 1,
            // 1, 1,
            // 2, 1, 2,
            // 5, 2, 3, 5,
            // 15, 5, 8, 10, 15,
            // 53, 15, 26, 32, 38, 53,
            // 217, 53, 99, 122, 142, 164, 217,
            // 1014, 217, 433, 537, 619, 704, 797, 1014,
            // 5335, 1014, 2143, 2683, 3069, 3464, 3876, 4321, 5335,
            // 31240, 5335, 11854, 15015, 17063, 19140, 21294, 23522, 25905, 31240,

        case 7:  // position of first occurrence of max: A218580
            s = W.first_max_idx();
            break;
            // 1,
            // 1, 1,
            // 1, 2, 2,
            // 1, 4, 5, 5,
            // 1, 8, 13, 15, 16,
            // 1, 16, 35, 47, 56, 62,
            // 1, 32, 97, 153, 204, 248, 279,
            // 1, 64, 275, 515, 770, 1030, 1257, 1423,
            // 1, 128, 793, 1785, 3000, 4424, 5869, 7140, 8100,
            // 1, 256, 2315, 6347, 12026, 19582, 28293, 37058, 44843, 50887,

        case 8:  // position of last occurrence of max: A218581
            s = W.last_max_idx();
            break;
            // 1,
            // 0, 2,
            // 0, 1, 4,
            // 0, 1, 4, 10,
            // 0, 1, 6, 15, 31,
            // 0, 1, 10, 29, 62, 115,
            // 0, 1, 18, 63, 148, 288, 496,
            // 0, 1, 34, 149, 392, 826, 1496, 2437,
            // 0, 1, 66, 375, 1120, 2592, 5036, 8615, 13435,
            // 0, 1, 130, 989, 3392, 8698, 18332, 33391, 54548, 82127,


        case 9:  // number of flat steps: A242153
            s = W.num_flat_steps();
            break;
            // Leftmost colum: A138265 (upper triangular zero-one matrices
            //   with n ones and no zero rows or columns)
            // 1,
            // 1, 1,
            // 2, 2, 1,
            // 5, 6, 3, 1,
            // 16, 20, 12, 4, 1,
            // 61, 80, 50, 20, 5, 1,
            // 271, 366, 240, 100, 30, 6, 1,
            // 1372, 1897, 1281, 560, 175, 42, 7, 1,
            // 7795, 10976, 7588, 3416, 1120, 280, 56, 8, 1,
            // 49093, 70155, 49392, 22764, 7686, 2016, 420, 72, 9, 1,
            // 339386, 490930, 350775, 164640, 56910, 15372, 3360, 600, 90, 10, 1,

        case 10:  // number of even values: A000000
            s = W.num_even_val();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 1, 3, 1,
            // 0, 1, 6, 7, 1,
            // 0, 1, 12, 24, 15, 1,
            // 0, 1, 24, 75, 84, 32, 1,
            // 0, 1, 49, 225, 384, 282, 72, 1,
            // 0, 1, 106, 680, 1617, 1808, 946, 176, 1,
            // 0, 1, 250, 2120, 6641, 10239, 8258, 3260, 470, 1,
            // 0, 1, 648, 6904, 27337, 54788, 61035, 37752, 11772, 1370, 1,

        case 11:  // number of odd values: row reversal of "even values"
            s = W.num_odd_val();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 3, 1, 0,
            // 1, 7, 6, 1, 0,
            // 1, 15, 24, 12, 1, 0,
            // 1, 32, 84, 75, 24, 1, 0,
            // 1, 72, 282, 384, 225, 49, 1, 0,
            // 1, 176, 946, 1808, 1617, 680, 106, 1, 0,
            // 1, 470, 3260, 8258, 10239, 6641, 2120, 250, 1, 0,
            // 1, 1370, 11772, 37752, 61035, 54788, 27337, 6904, 648, 1, 0,
            // 1, 4357, 44934, 175754, 355046, 414118, 287276, 114995, 23750, 1842, 1, 0,

        case 61:  // abs(#minval - #maxval): A000000
            s = W.min_max_num_diff();
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 2, 3, 0, 0,
            // 7, 4, 4, 0, 0,
            // 14, 27, 7, 5, 0, 0,
            // 64, 82, 54, 11, 6, 0, 0,
            // 244, 429, 221, 97, 16, 7, 0, 0,
            // 1250, 2068, 1323, 504, 160, 22, 8, 0, 0,
            // 6696, 11960, 7815, 3475, 1009, 247, 29, 9, 0, 0,
            // 40691, 74125, 52330, 24286, 7936, 1831, 362, 37, 10, 0, 0,
            // 268807, 506657, 376229, 186591, 63913, 16229, 3082, 509, 46, 11, 0, 0,


        default:
            cerr << "Invalid choice (exiting)." << endl;
            return 1;
        }


        st[ s ] += 1;


#ifndef TIMING
        cout << setw(4) << ct << ":";

        // print RGS:
        print_vec("  ", x, n, true );
//        print_vec("    ", A.m_, n, true );

        cout << setw(4) << s;

//        cout << setw(3) << A.num_zeros() << setw(3) << A.num_fixed_points();

//        cout << setw(4) << j;

        cout << endl;

        jjassert( A.OK() );
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

    cout << " ct=" << ct;  // total: OEIS sequence A022493
    cout << endl;

    jjassert( sct == ct );

    delete [] st;

    return 0;
}
// -------------------------

/*

Print triangle for stats q:


OEIS example:
q=0; for n in $(seq 0 13) ; do ./bin $n $q | grep ', $' ; done | nl -v0 -s':  ' -w2 -n rz

C++ comment:
q=0;  for n in $(seq 0 13) ; do ./bin $n $q | grep ', $' ; done | sed 's/^/\/\/ /; s/ $//;'

Extract column c from stats q:
q=0;  c=0;  echo $(for n in $(seq 0 13) ; do ./bin $n $q | grep ', $' ; done | cut -d, -f$((c+1))) | sed 's/ /, /g;'

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ascent-rgs-stats-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ascent-rgs-stats-demo.cc DEMOFLAGS=-DTIMING"
/// End:
