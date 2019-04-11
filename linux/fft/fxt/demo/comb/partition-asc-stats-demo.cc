
#include "comb/partition-asc.h"
#include "comb/word-stats.h"

//#include "comb/partition-desc.h"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Statistics for partitions (as weakly ascending lists of parts).
//% Cf. the following OEIS sequences:
//% A008284: partitions by value of largest part.
//% A026794: partitions by value of smallest part.
//% A116482: partitions by number of even values.
//% A103919: partitions by number of odd values.
//% A116598: partitions by number of ones
//% A133121: partitions by number of flat steps
//% A116608: partitions by number of non-flat steps (ascents)

// Cf. comb/partition-asc-demo.cc

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 10;
    NXARG(n, "Partitions of n");

    ulong sq = 0;
    NXARG(sq, "Select stats:\n"
          "     0 ==> by largest part\n"
          "     1 ==> by smallest part\n"
          "     3 ==> by number of largest parts\n"
          "     4 ==> by number of smallest parts\n"
          "     5 ==> by number of ones\n"
          "    10 ==> by number of ascents\n"
//          "    11 ==> by number of descents\n"
//          "    30 ==> position of last one\n"
//          "    31 ==> position of first one\n"
          "    40 ==> position of first occurrence of largest part\n"
          "    41 ==> position of last occurrence of largest part\n"
//          "    42 ==> position of first occurrence of smallest part\n"
          "    43 ==> position of last occurrence of smallest part\n"
          "    50 ==> number of even values\n"
          "    51 ==> number of odd values\n"
          "    60 ==> by number of fixed points (offset 0)\n"
          "    61 ==> by number of fixed points (offset 1)\n"
          "    70 ==> number of flat steps\n"
          "    71 ==> number of non-flat steps\n"
          "    80 ==> max ascent\n"
          "    81 ==> min ascent\n"
//          "    82 ==> max descent\n"
          );

    partition_asc P(n);
    word_stats W(P.data(), n);

    ulong ct = 0;
    ulong * st = new ulong[n+1];  // stats
    for (ulong k=0; k<=n; ++k)  st[k] = 0;

    ulong m = P.num_parts();
    do
    {
        W.set_len(m);
        ++ct;
        ulong s = 0;
        switch ( sq )
        {
        case 0:  // value of largest part: A008284, cf. A072233
            s = W.max_val();
            break;
            //  0:  1,
            //  1:  0, 1,
            //  2:  0, 1, 1,
            //  3:  0, 1, 1, 1,
            //  4:  0, 1, 2, 1, 1,
            //  5:  0, 1, 2, 2, 1, 1,
            //  6:  0, 1, 3, 3, 2, 1, 1,
            //  7:  0, 1, 3, 4, 3, 2, 1, 1,
            //  8:  0, 1, 4, 5, 5, 3, 2, 1, 1,
            //  9:  0, 1, 4, 7, 6, 5, 3, 2, 1, 1,
            // 10:  0, 1, 5, 8, 9, 7, 5, 3, 2, 1, 1,
            // 11:  0, 1, 5, 10, 11, 10, 7, 5, 3, 2, 1, 1,
            // 12:  0, 1, 6, 12, 15, 13, 11, 7, 5, 3, 2, 1, 1,

        case 1:  // value of smallest part: A026794
            s = W.min_val();
            break;
            //  0:  1,
            //  1:  0, 1,
            //  2:  0, 1, 1,
            //  3:  0, 2, 0, 1,
            //  4:  0, 3, 1, 0, 1,
            //  5:  0, 5, 1, 0, 0, 1,
            //  6:  0, 7, 2, 1, 0, 0, 1,
            //  7:  0, 11, 2, 1, 0, 0, 0, 1,
            //  8:  0, 15, 4, 1, 1, 0, 0, 0, 1,
            //  9:  0, 22, 4, 2, 1, 0, 0, 0, 0, 1,
            // 10:  0, 30, 7, 2, 1, 1, 0, 0, 0, 0, 1,
            // 11:  0, 42, 8, 3, 1, 1, 0, 0, 0, 0, 0, 1,
            // 12:  0, 56, 12, 4, 2, 1, 1, 0, 0, 0, 0, 0, 1,


        case 3:  // number of largest parts: A026794 (same as value of smallest part)
            s = W.num_max_val();
            break;
            //  0:  1,
            //  1:  0, 1,
            //  2:  0, 1, 1,
            //  3:  0, 2, 0, 1,
            //  4:  0, 3, 1, 0, 1,
            //  5:  0, 5, 1, 0, 0, 1,
            //  6:  0, 7, 2, 1, 0, 0, 1,
            //  7:  0, 11, 2, 1, 0, 0, 0, 1,
            //  8:  0, 15, 4, 1, 1, 0, 0, 0, 1,
            //  9:  0, 22, 4, 2, 1, 0, 0, 0, 0, 1,
            // 10:  0, 30, 7, 2, 1, 1, 0, 0, 0, 0, 1,
            // 11:  0, 42, 8, 3, 1, 1, 0, 0, 0, 0, 0, 1,
            // 12:  0, 56, 12, 4, 2, 1, 1, 0, 0, 0, 0, 0, 1,

        case 4:  // number of smallest parts: A096144
            s = W.num_min_val();
            // reversed rows --> A002865
            break;
            //  0:  1,
            //  1:  0, 1,
            //  2:  0, 1, 1,
            //  3:  0, 2, 0, 1,
            //  4:  0, 2, 2, 0, 1,
            //  5:  0, 4, 1, 1, 0, 1,
            //  6:  0, 4, 3, 2, 1, 0, 1,
            //  7:  0, 7, 3, 2, 1, 1, 0, 1,
            //  8:  0, 8, 6, 2, 3, 1, 1, 0, 1,
            //  9:  0, 12, 5, 6, 2, 2, 1, 1, 0, 1,
            // 10:  0, 14, 11, 5, 4, 3, 2, 1, 1, 0, 1,
            // 11:  0, 21, 11, 8, 5, 4, 2, 2, 1, 1, 0, 1,
            // 12:  0, 24, 17, 11, 9, 4, 5, 2, 2, 1, 1, 0, 1,

        case 5:  // number of ones: A116598
            // column k=0: A002865
            // reversed rows give A002865
            s = W.num_val(1);
            break;
            //  0:  1,
            //  1:  0, 1,
            //  2:  1, 0, 1,
            //  3:  1, 1, 0, 1,
            //  4:  2, 1, 1, 0, 1,
            //  5:  2, 2, 1, 1, 0, 1,
            //  6:  4, 2, 2, 1, 1, 0, 1,
            //  7:  4, 4, 2, 2, 1, 1, 0, 1,
            //  8:  7, 4, 4, 2, 2, 1, 1, 0, 1,
            //  9:  8, 7, 4, 4, 2, 2, 1, 1, 0, 1,
            // 10:  12, 8, 7, 4, 4, 2, 2, 1, 1, 0, 1,
            // 11:  14, 12, 8, 7, 4, 4, 2, 2, 1, 1, 0, 1,
            // 12:  21, 14, 12, 8, 7, 4, 4, 2, 2, 1, 1, 0, 1,


        case 10:  // number of ascents: A116608
            s = W.num_ascents();
            break;
            //  0:  1,
            //  1:  1, 0,
            //  2:  2, 0, 0,
            //  3:  2, 1, 0, 0,
            //  4:  3, 2, 0, 0, 0,
            //  5:  2, 5, 0, 0, 0, 0,
            //  6:  4, 6, 1, 0, 0, 0, 0,
            //  7:  2, 11, 2, 0, 0, 0, 0, 0,
            //  8:  4, 13, 5, 0, 0, 0, 0, 0, 0,
            //  9:  3, 17, 10, 0, 0, 0, 0, 0, 0, 0,
            // 10:  4, 22, 15, 1, 0, 0, 0, 0, 0, 0, 0,
            // 11:  2, 27, 25, 2, 0, 0, 0, 0, 0, 0, 0, 0,
            // 12:  6, 29, 37, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//        case 11:  // number of descents:
//            s = W.num_descents();
//            break;

//        case 30:  // position of last one:
//            s = W.last_val_idx(1);  // may not exist!
//            break;
//
//        case 31:  // position of first one:
//            s = W.first_val_idx(1);  // may not exist!
//            break;

        case 40:  // position of first occurrence of largest part: A097364, A116685(tabf)
            s = W.first_max_idx();
            break;
            //  0:  1,
            //  1:  1, 0,
            //  2:  2, 0, 0,
            //  3:  2, 1, 0, 0,
            //  4:  3, 1, 1, 0, 0,
            //  5:  2, 3, 1, 1, 0, 0,
            //  6:  4, 2, 3, 1, 1, 0, 0,
            //  7:  2, 5, 3, 3, 1, 1, 0, 0,
            //  8:  4, 4, 6, 3, 3, 1, 1, 0, 0,
            //  9:  3, 6, 6, 7, 3, 3, 1, 1, 0, 0,
            // 10:  4, 6, 10, 7, 7, 3, 3, 1, 1, 0, 0,
            // 11:  2, 9, 10, 12, 8, 7, 3, 3, 1, 1, 0, 0,
            // 12:  6, 6, 15, 14, 13, 8, 7, 3, 3, 1, 1, 0, 0,

        case 41:  // position of last occurrence of largest part: A008284
            s = W.last_max_idx();
            break;
            //  0:  1,
            //  1:  1, 0,
            //  2:  1, 1, 0,
            //  3:  1, 1, 1, 0,
            //  4:  1, 2, 1, 1, 0,
            //  5:  1, 2, 2, 1, 1, 0,
            //  6:  1, 3, 3, 2, 1, 1, 0,
            //  7:  1, 3, 4, 3, 2, 1, 1, 0,
            //  8:  1, 4, 5, 5, 3, 2, 1, 1, 0,
            //  9:  1, 4, 7, 6, 5, 3, 2, 1, 1, 0,
            // 10:  1, 5, 8, 9, 7, 5, 3, 2, 1, 1, 0,
            // 11:  1, 5, 10, 11, 10, 7, 5, 3, 2, 1, 1, 0,
            // 12:  1, 6, 12, 15, 13, 11, 7, 5, 3, 2, 1, 1, 0,

//        case 42:  // position of first occurrence of smallest part:
//            s = W.first_min_idx();
//            break;

        case 43:  // position of last occurrence of smallest part: A096144 (same as number of smallest values)
            // not: A091602
            // column k=0: A002865;  k=1: A096373
            s = W.last_min_idx();
            break;
            //  0:  1,
            //  1:  1, 0,
            //  2:  1, 1, 0,
            //  3:  2, 0, 1, 0,
            //  4:  2, 2, 0, 1, 0,
            //  5:  4, 1, 1, 0, 1, 0,
            //  6:  4, 3, 2, 1, 0, 1, 0,
            //  7:  7, 3, 2, 1, 1, 0, 1, 0,
            //  8:  8, 6, 2, 3, 1, 1, 0, 1, 0,
            //  9:  12, 5, 6, 2, 2, 1, 1, 0, 1, 0,
            // 10:  14, 11, 5, 4, 3, 2, 1, 1, 0, 1, 0,
            // 11:  21, 11, 8, 5, 4, 2, 2, 1, 1, 0, 1, 0,
            // 12:  24, 17, 11, 9, 4, 5, 2, 2, 1, 1, 0, 1, 0,


        case 50:  // number of even values: A116482
            s = W.num_even_val();
            break;
            //  0:  1,
            //  1:  1, 0,
            //  2:  1, 1, 0,
            //  3:  2, 1, 0, 0,
            //  4:  2, 2, 1, 0, 0,
            //  5:  3, 3, 1, 0, 0, 0,
            //  6:  4, 4, 2, 1, 0, 0, 0,
            //  7:  5, 6, 3, 1, 0, 0, 0, 0,
            //  8:  6, 8, 5, 2, 1, 0, 0, 0, 0,
            //  9:  8, 11, 7, 3, 1, 0, 0, 0, 0, 0,
            // 10:  10, 14, 10, 5, 2, 1, 0, 0, 0, 0, 0,
            // 11:  12, 19, 14, 7, 3, 1, 0, 0, 0, 0, 0, 0,
            // 12:  15, 24, 19, 11, 5, 2, 1, 0, 0, 0, 0, 0, 0,

        case 51:  // number of odd values: A103919
            s = W.num_odd_val();
            break;
            //  0:  1,
            //  1:  0, 1,
            //  2:  1, 0, 1,
            //  3:  0, 2, 0, 1,
            //  4:  2, 0, 2, 0, 1,
            //  5:  0, 4, 0, 2, 0, 1,
            //  6:  3, 0, 5, 0, 2, 0, 1,
            //  7:  0, 7, 0, 5, 0, 2, 0, 1,
            //  8:  5, 0, 9, 0, 5, 0, 2, 0, 1,
            //  9:  0, 12, 0, 10, 0, 5, 0, 2, 0, 1,
            // 10:  7, 0, 17, 0, 10, 0, 5, 0, 2, 0, 1,
            // 11:  0, 19, 0, 19, 0, 10, 0, 5, 0, 2, 0, 1,
            // 12:  11, 0, 28, 0, 20, 0, 10, 0, 5, 0, 2, 0, 1,


        case 60:  // by number of fixed points (offset 0):
            s = W.num_fixed_points();
            break;
            //  0:  1,
            //  1:  1, 0,
            //  2:  1, 1, 0,
            //  3:  2, 1, 0, 0,
            //  4:  3, 1, 1, 0, 0,
            //  5:  3, 4, 0, 0, 0, 0,
            //  6:  5, 4, 2, 0, 0, 0, 0,
            //  7:  7, 7, 0, 1, 0, 0, 0, 0,
            //  8:  9, 8, 5, 0, 0, 0, 0, 0, 0,
            //  9:  11, 14, 5, 0, 0, 0, 0, 0, 0, 0,
            // 10:  14, 22, 3, 3, 0, 0, 0, 0, 0, 0, 0,
            // 11:  19, 27, 9, 0, 1, 0, 0, 0, 0, 0, 0, 0,
            // 12:  25, 35, 13, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,

        case 61:  // by number of fixed points (offset 1): A238352
            // column k=0: A238394;  k=1: A000000
            s = W.num_fixed_points_1();
            break;
            //  0:  1,
            //  1:  0, 1,
            //  2:  1, 1, 0,
            //  3:  1, 1, 1, 0,
            //  4:  1, 4, 0, 0, 0,
            //  5:  2, 3, 2, 0, 0, 0,
            //  6:  3, 7, 0, 1, 0, 0, 0,
            //  7:  3, 7, 5, 0, 0, 0, 0, 0,
            //  8:  4, 14, 4, 0, 0, 0, 0, 0, 0,
            //  9:  5, 19, 3, 3, 0, 0, 0, 0, 0, 0,
            // 10:  8, 24, 9, 0, 1, 0, 0, 0, 0, 0, 0,
            // 11:  9, 32, 11, 4, 0, 0, 0, 0, 0, 0, 0, 0,
            // 12:  12, 46, 15, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,

        case 70:  // number of flat steps: A133121
            s = W.num_flat_steps();
            break;
            //  0:  1,
            //  1:  1, 0,
            //  2:  1, 1, 0,
            //  3:  2, 0, 1, 0,
            //  4:  2, 2, 0, 1, 0,
            //  5:  3, 2, 1, 0, 1, 0,
            //  6:  4, 2, 3, 1, 0, 1, 0,
            //  7:  5, 4, 2, 2, 1, 0, 1, 0,
            //  8:  6, 6, 3, 3, 2, 1, 0, 1, 0,
            //  9:  8, 7, 5, 4, 2, 2, 1, 0, 1, 0,
            // 10:  10, 8, 10, 3, 5, 2, 2, 1, 0, 1, 0,
            // 11:  12, 13, 8, 9, 4, 4, 2, 2, 1, 0, 1, 0,
            // 12:  15, 15, 14, 10, 8, 5, 4, 2, 2, 1, 0, 1, 0,

        case 71:  // number of non-flat steps: A116608 (same as "number of distinct parts")
            // column k=0: A000005;  k=1: A002133;  k=2: A002134;  k=3: A000000
            s = W.num_nonflat_steps();
            break;
            //  0:  1,
            //  1:  1, 0,
            //  2:  2, 0, 0,
            //  3:  2, 1, 0, 0,
            //  4:  3, 2, 0, 0, 0,
            //  5:  2, 5, 0, 0, 0, 0,
            //  6:  4, 6, 1, 0, 0, 0, 0,
            //  7:  2, 11, 2, 0, 0, 0, 0, 0,
            //  8:  4, 13, 5, 0, 0, 0, 0, 0, 0,
            //  9:  3, 17, 10, 0, 0, 0, 0, 0, 0, 0,
            // 10:  4, 22, 15, 1, 0, 0, 0, 0, 0, 0, 0,
            // 11:  2, 27, 25, 2, 0, 0, 0, 0, 0, 0, 0, 0,
            // 12:  6, 29, 37, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0,

        case 80:  // max ascent: A238353
            // column k=0: A000005;  k=1: A237665;  k=2: A000000
            s = W.max_ascent();
            break;
            //  0:  1,
            //  1:  1, 0,
            //  2:  2, 0, 0,
            //  3:  2, 1, 0, 0,
            //  4:  3, 1, 1, 0, 0,
            //  5:  2, 3, 1, 1, 0, 0,
            //  6:  4, 3, 2, 1, 1, 0, 0,
            //  7:  2, 6, 3, 2, 1, 1, 0, 0,
            //  8:  4, 6, 6, 2, 2, 1, 1, 0, 0,
            //  9:  3, 10, 6, 5, 2, 2, 1, 1, 0, 0,
            // 10:  4, 11, 11, 6, 4, 2, 2, 1, 1, 0, 0,
            // 11:  2, 16, 13, 10, 5, 4, 2, 2, 1, 1, 0, 0,
            // 12:  6, 17, 19, 12, 9, 4, 4, 2, 2, 1, 1, 0, 0,

        case 81:  // min ascent: A238354
            // column k=0: 1 + A047967;  k=1: A238708;  k=2: A000000
            s = W.min_ascent();
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 2, 1, 0, 0,
            // 4, 0, 1, 0, 0,
            // 5, 1, 0, 1, 0, 0,
            // 8, 1, 1, 0, 1, 0, 0,
            // 11, 2, 0, 1, 0, 1, 0, 0,
            // 17, 2, 1, 0, 1, 0, 1, 0, 0,
            // 23, 3, 1, 1, 0, 1, 0, 1, 0, 0,
            // 33, 4, 2, 0, 1, 0, 1, 0, 1, 0, 0,

//        case 82:  // max descent:
//            s = W.max_descent();
//            break;


        case 85:  // number of distinct parts: A116608, cf. A060177
            // column k=1: A000005;  k=2: A002133;  k=3: A002134;
            //  k=4: A000000;  k=5: A000000
            s = W.num_sorts();
            break;
            // 1,
            // 0, 1,
            // 0, 2, 0,
            // 0, 2, 1, 0,
            // 0, 3, 2, 0, 0,
            // 0, 2, 5, 0, 0, 0,
            // 0, 4, 6, 1, 0, 0, 0,
            // 0, 2, 11, 2, 0, 0, 0, 0,
            // 0, 4, 13, 5, 0, 0, 0, 0, 0,
            // 0, 3, 17, 10, 0, 0, 0, 0, 0, 0,
            // 0, 4, 22, 15, 1, 0, 0, 0, 0, 0, 0,
            // 0, 2, 27, 25, 2, 0, 0, 0, 0, 0, 0, 0,
            // 0, 6, 29, 37, 5, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 2, 37, 52, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0,

        case 86:  // max multiplicity of any part: A091602
            // column k=1: A000009;  k=2: A091605; k=3: A091606;
            //  k=4: A091607;  k=5: A091608;  k=6: A091609
            s = W.max_num_vals();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 2, 0, 1,
            // 0, 2, 2, 0, 1,
            // 0, 3, 2, 1, 0, 1,
            // 0, 4, 3, 2, 1, 0, 1,
            // 0, 5, 4, 3, 1, 1, 0, 1,
            // 0, 6, 7, 3, 3, 1, 1, 0, 1,
            // 0, 8, 8, 6, 3, 2, 1, 1, 0, 1,
            // 0, 10, 12, 7, 5, 3, 2, 1, 1, 0, 1,
            // 0, 12, 15, 11, 6, 5, 2, 2, 1, 1, 0, 1,
            // 0, 15, 21, 14, 10, 5, 5, 2, 2, 1, 1, 0, 1,
            // 0, 18, 26, 20, 12, 9, 5, 4, 2, 2, 1, 1, 0, 1,

        case 87:  // min multiplicity of any part: A243978;   cf. A183568
            // column k=1: A183558;  k=2: A244515;  k=3: A244516;
            //  k=4: A244517;  k=5: A244518
            s = W.min_num_vals_nz();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 2, 0, 1,
            // 0, 3, 1, 0, 1,
            // 0, 6, 0, 0, 0, 1,
            // 0, 7, 2, 1, 0, 0, 1,
            // 0, 13, 1, 0, 0, 0, 0, 1,
            // 0, 16, 4, 0, 1, 0, 0, 0, 1,
            // 0, 25, 2, 2, 0, 0, 0, 0, 0, 1,
            // 0, 33, 6, 1, 0, 1, 0, 0, 0, 0, 1,
            // 0, 49, 4, 2, 0, 0, 0, 0, 0, 0, 0, 1,
            // 0, 61, 9, 3, 2, 0, 1, 0, 0, 0, 0, 0, 1,
            // 0, 90, 6, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,


        case 90: // test
            s = m;  // number of parts: A008284 (same as "largest part")
            break;
            //  0:  1,
            //  1:  0, 1,
            //  2:  0, 1, 1,
            //  3:  0, 1, 1, 1,
            //  4:  0, 1, 2, 1, 1,
            //  5:  0, 1, 2, 2, 1, 1,
            //  6:  0, 1, 3, 3, 2, 1, 1,
            //  7:  0, 1, 3, 4, 3, 2, 1, 1,
            //  8:  0, 1, 4, 5, 5, 3, 2, 1, 1,
            //  9:  0, 1, 4, 7, 6, 5, 3, 2, 1, 1,
            // 10:  0, 1, 5, 8, 9, 7, 5, 3, 2, 1, 1,
            // 11:  0, 1, 5, 10, 11, 10, 7, 5, 3, 2, 1, 1,
            // 12:  0, 1, 6, 12, 15, 13, 11, 7, 5, 3, 2, 1, 1,

        default:
            cerr << "Invalid choice (exiting)." << endl;
            return 1;
        }


        st[ s ] += 1;


#ifndef TIMING
        cout << setw(4) << ct << ":";
        P.print("  ");
        cout << setw(4) << s;
        cout << endl;

        jjassert( P.OK() );
#endif  // TIMING
    }
    while ( 0 != (m=P.next()) );


    ulong sct = 0;
    for (ulong k=0; k<=n; ++k)
    {
        sct += st[k];
        cout << st[k] << ", ";
//        cout << sct << ", ";  // cumulative values
    }
    cout << endl;

    cout << " ct=" << ct;  // total: OEIS sequence A000041
    cout << endl;

    jjassert( sct == ct );

    delete [] st;

    return 0;
}
// -------------------------

/*

Print triangle for stats q:

OEIS example:
 q=0; for n in $(seq 0 15) ; do ./bin $n $q | grep ', $' ; done | nl -v0 -s':  ' -w2 -n rz

C++ comment:
 q=0; for n in $(seq 0 15) ; do ./bin $n $q | grep ', $' ; done | sed 's/^/\/\/ /'

Extract column c from stats q:
 q=0; c=0;  echo $(for n in $(seq 0 20) ; do ./bin $n $q | grep ', $' ; done | cut -d, -f$((c+1))) | sed 's/ /, /g;'

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-stats-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-stats-demo.cc DEMOFLAGS=-DTIMING"
/// End:
