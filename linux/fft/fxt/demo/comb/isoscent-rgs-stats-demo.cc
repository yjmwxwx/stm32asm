
#include "comb/isoscent-rgs.h"
#include "comb/word-stats.h"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Statistics for isoscent sequences.
//% An isoscent sequence is a sequence [d(1), d(2), ..., d(n)] where
//%  d(1)=0, d(k)>=0, and d(k) <= 1 + eq([d(1), d(2), ..., d(k-1)])
//%  where eq(.) counts the number of flat steps of its argument.

// See the following OEIS sequences:
// A242351: triangle, length-n isoscent sequences with k ascents.
// A242352: triangle, length-n isoscent sequences with k descents.

// Cf. comb/ascent-rgs-stats-demo.cc for stats for ascent sequences
// Cf. comb/isoscent-rgs-demo.cc

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Length of strings, n>=1");

    ulong sq = 1;
    NXARG(sq, "Select stats:\n"
          "    0 ==> max element\n"
          "    1 ==> number of descents\n"
          "    2 ==> number of ascents\n"
          "    3 ==> number of zeros - 1\n"
          "    4 ==> number of maximal digits - 1\n"
          "    6 ==> position of last occurrence of zero\n"
          "    7 ==> position of first occurrence of the maximal value\n"
          "    8 ==> position of last occurrence of the maximal value\n"
          "   10 ==> number of odd values\n"
          "   40 ==> number of flat steps\n"
//          "   80 ==> number of fixed points - 1\n"
          );

    isoscent_rgs A(n);
    word_stats W(A.data(), n);

    ulong ct = 0;
    ulong * st = new ulong[n+1];  // stats
    for (ulong k=0; k<=n; ++k)  st[k] = 0;

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
        case 0:  // by max element: A000000
            s = W.max_val();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 3, 1, 0,
            // 1, 7, 6, 1, 0,
            // 1, 15, 25, 10, 1, 0,
            // 1, 31, 90, 65, 15, 1, 0,
            // 1, 63, 301, 350, 140, 21, 1, 0,
            // 1, 127, 966, 1701, 1050, 266, 28, 1, 0,
            // 1, 255, 3025, 7770, 6951, 2646, 462, 36, 1, 0,
            // 1, 511, 9330, 34105, 42525, 22827, 5880, 750, 45, 1, 0,


        case 1:  // by number of descents: A242352
            s = W.num_descents();
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 4, 1, 0, 0,
            // 9, 6, 0, 0, 0,
            // 21, 29, 2, 0, 0, 0,
            // 51, 124, 28, 0, 0, 0, 0,
            // 127, 499, 241, 10, 0, 0, 0, 0,
            // 323, 1933, 1667, 216, 1, 0, 0, 0, 0,
            // 835, 7307, 10142, 2765, 98, 0, 0, 0, 0, 0,
            // 2188, 27166, 56748, 27214, 2637, 22, 0, 0, 0, 0, 0,

        case 2:  // by number of ascents: A242351
            s = W.num_ascents();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 4, 0, 0,
            // 1, 11, 3, 0, 0,
            // 1, 26, 25, 0, 0, 0,
            // 1, 57, 128, 17, 0, 0, 0,
            // 1, 120, 525, 229, 2, 0, 0, 0,
            // 1, 247, 1901, 1819, 172, 0, 0, 0, 0,
            // 1, 502, 6371, 11172, 3048, 53, 0, 0, 0, 0,
            // 1, 1013, 20291, 58847, 33065, 2751, 7, 0, 0, 0, 0,


        case 3:  // by number of zeros (=min values): A000000
            s = W.num_zeros();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 1, 3, 1,
            // 0, 2, 6, 6, 1,
            // 0, 5, 15, 21, 10, 1,
            // 0, 15, 46, 71, 55, 15, 1,
            // 0, 52, 162, 266, 255, 120, 21, 1,
            // 0, 203, 642, 1100, 1185, 750, 231, 28, 1,
            // 0, 877, 2813, 4975, 5787, 4355, 1897, 406, 36, 1,
            // 0, 4140, 13454, 24404, 29990, 25285, 13720, 4270, 666, 45, 1,

        case 4:  // by number of max digits: A000000
            s = W.num_max_val();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 3, 1, 1,
            // 0, 9, 4, 1, 1,
            // 0, 31, 14, 5, 1, 1,
            // 0, 121, 54, 20, 6, 1, 1,
            // 0, 523, 233, 85, 27, 7, 1, 1,
            // 0, 2469, 1101, 400, 125, 35, 8, 1, 1,
            // 0, 12611, 5625, 2046, 635, 175, 44, 9, 1, 1,
            // 0, 69161, 30846, 11226, 3488, 952, 236, 54, 10, 1, 1,

        case 6:  // position of last zero (last occurrence of min): A000000
            s = W.last_zero_idx();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 2, 2, 0,
            // 2, 4, 4, 5, 0,
            // 5, 10, 10, 12, 15, 0,
            // 15, 30, 32, 32, 42, 52, 0,
            // 52, 104, 116, 108, 128, 166, 203, 0,
            // 203, 406, 468, 428, 462, 570, 726, 877, 0,
            // 877, 1754, 2074, 1904, 1910, 2252, 2770, 3466, 4140, 0,
            // 4140, 8280, 9992, 9284, 8852, 9958, 11916, 14522, 17884, 21147, 0,


        case 7:  // position of first occurrence of max: A000000
            s = W.first_max_idx();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 2, 2, 0,
            // 1, 4, 5, 5, 0,
            // 1, 8, 13, 15, 15, 0,
            // 1, 16, 35, 47, 52, 52, 0,
            // 1, 32, 97, 153, 188, 203, 203, 0,
            // 1, 64, 275, 515, 706, 825, 877, 877, 0,
            // 1, 128, 793, 1785, 2744, 3479, 3937, 4140, 4140, 0,
            // 1, 256, 2315, 6347, 11002, 15177, 18313, 20270, 21147, 21147, 0,

        case 8:  // position of last occurrence of max: A000000
            s = W.last_max_idx();
            break;
            // 1,
            // 1, 0,
            // 0, 2, 0,
            // 0, 1, 4, 0,
            // 0, 1, 4, 10, 0,
            // 0, 1, 6, 15, 30, 0,
            // 0, 1, 10, 29, 59, 104, 0,
            // 0, 1, 18, 63, 139, 250, 406, 0,
            // 0, 1, 34, 149, 365, 692, 1145, 1754, 0,
            // 0, 1, 66, 375, 1039, 2110, 3627, 5649, 8280, 0,
            // 0, 1, 130, 989, 3149, 6932, 12521, 20085, 29874, 42294, 0,

        case 10:  // number of odd values: (reversal of "even values")
            s = W.num_odd_val();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 2, 2, 1, 0,
            // 4, 6, 4, 1, 0,
            // 9, 19, 15, 7, 2, 0,
            // 23, 58, 63, 39, 16, 4, 0,
            // 65, 192, 255, 203, 109, 44, 9, 0,
            // 199, 685, 1053, 1021, 689, 347, 123, 23, 0,
            // 654, 2579, 4577, 5111, 4108, 2506, 1169, 378, 65, 0,
            // 2296, 10187, 20647, 26200, 24116, 17191, 9692, 4179, 1268, 199, 0,

        case 11:  // number of even values: A000000
            s = W.num_even_val();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 1, 2, 2,
            // 0, 1, 4, 6, 4,
            // 0, 2, 7, 15, 19, 9,
            // 0, 4, 16, 39, 63, 58, 23,
            // 0, 9, 44, 109, 203, 255, 192, 65,
            // 0, 23, 123, 347, 689, 1021, 1053, 685, 199,
            // 0, 65, 378, 1169, 2506, 4108, 5111, 4577, 2579, 654,
            // 0, 199, 1268, 4179, 9692, 17191, 24116, 26200, 20647, 10187, 2296,

        case 40:  // number of flat steps: A000000
//            s = W.num_flat_steps();
            s = A.num_flat_steps();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 3, 1, 0,
            // 1, 7, 6, 1, 0,
            // 1, 15, 25, 10, 1, 0,
            // 1, 31, 90, 65, 15, 1, 0,
            // 1, 63, 301, 350, 140, 21, 1, 0,
            // 1, 127, 966, 1701, 1050, 266, 28, 1, 0,
            // 1, 255, 3025, 7770, 6951, 2646, 462, 36, 1, 0,
            // 1, 511, 9330, 34105, 42525, 22827, 5880, 750, 45, 1, 0,


        case 41:  // number of non-flat steps: A000000
            s = W.num_nonflat_steps();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 3, 1, 0,
            // 1, 6, 7, 1, 0,
            // 1, 10, 25, 15, 1, 0,
            // 1, 15, 65, 90, 31, 1, 0,
            // 1, 21, 140, 350, 301, 63, 1, 0,
            // 1, 28, 266, 1050, 1701, 966, 127, 1, 0,
            // 1, 36, 462, 2646, 6951, 7770, 3025, 255, 1, 0,
            // 1, 45, 750, 5880, 22827, 42525, 34105, 9330, 511, 1, 0,


//        case 60:  // maxval - minval == maxval
//            s = W.min_max_diff();
//            break;

        case 61:  // abs(#minval - #maxval): A000000
            s = W.min_max_num_diff();
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 1, 4, 0, 0,
            // 6, 2, 7, 0, 0,
            // 7, 23, 11, 11, 0, 0,
            // 36, 52, 64, 35, 16, 0, 0,
            // 103, 251, 222, 194, 85, 22, 0, 0,
            // 473, 946, 1088, 873, 556, 175, 29, 0, 0,
            // 2000, 4534, 5031, 4686, 3106, 1431, 322, 37, 0, 0,
            // 9928, 21936, 26223, 25332, 18779, 9876, 3309, 546, 46, 0, 0,


        case 80:  // by number of fixed points:
            s = W.num_fixed_points();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 2, 3, 0,
            // 0, 6, 9, 0, 0,
            // 0, 22, 30, 0, 0, 0,
            // 0, 91, 112, 0, 0, 0, 0,
            // 0, 413, 464, 0, 0, 0, 0, 0,
            // 0, 2031, 2109, 0, 0, 0, 0, 0, 0,
            // 0, 10736, 10411, 0, 0, 0, 0, 0, 0, 0,
            // 0, 60624, 55351, 0, 0, 0, 0, 0, 0, 0, 0,


        case 95:  // value of last part: A000000
            s = A.data()[n-1];
            break;
            // 1, 0,
            // 1, 1, 0,
            // 2, 2, 1, 0,
            // 5, 5, 4, 1, 0,
            // 15, 15, 14, 7, 1, 0,
            // 52, 52, 51, 36, 11, 1, 0,
            // 203, 203, 202, 171, 81, 16, 1, 0,
            // 877, 877, 876, 813, 512, 162, 22, 1, 0,
            // 4140, 4140, 4139, 4012, 3046, 1345, 295, 29, 1, 0,
            // 21147, 21147, 21146, 20891, 17866, 10096, 3145, 499, 37, 1, 0,

        default:
            cerr << "Invalid choice (exiting)." << endl;
            return 1;
        }


        st[ s ] += 1;


#ifndef TIMING
        cout << setw(4) << ct << ":  ";

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

    cout << " ct=" << ct;  // total: OEIS sequence A000110
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
/// make-target: "1demo DSRC=demo/comb/isoscent-rgs-stats-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/isoscent-rgs-stats-demo.cc DEMOFLAGS=-DTIMING"
/// End:
