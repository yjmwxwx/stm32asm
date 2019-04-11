
#include "comb/composition-nz.h"
#include "comb/word-stats.h"

#include "comb/comb-print.h"

#include "comb/composition-nz-odd.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Statistics for compositions into non-zero parts.
//% Cf. the following OEIS sequences:
//% A048004: Compositions by value of largest part.
//% A105147: compositions by value of smallest part.
//% A119473: compositions by number of even values.
//% A100749: compositions by number of odd values.
//% A105422: compositions by number of ones
//% A106356: compositions by number of flat steps
//% A238130: compositions by number of non-flat steps
//% A225084: compositions by max ascent

// Cf. comb/composition-nz-demo.cc

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Compositions of n");

    ulong sq = 0;
    NXARG(sq, "Select stats:\n"
          "     0 ==> by largest part\n"
          "     1 ==> by smallest part\n"
          "     3 ==> by number of largest parts\n"
          "     4 ==> by number of smallest parts\n"
          "     5 ==> by number of ones\n"
          "    10 ==> by number of descents\n"
          "    11 ==> by number of ascents (same as number of descents)\n"
          "    30 ==> number of smallest parts\n"
          "    31 ==> number of largest parts\n"
          "    40 ==> position of first occurrence of largest part\n"
          "    41 ==> position of last occurrence of largest part\n"
          "    42 ==> position of first occurrence of smallest part\n"
          "    43 ==> position of last occurrence of smallest part\n"
          "    50 ==> number of even values\n"
          "    51 ==> number of odd values\n"
          "    60 ==> by number of fixed points (offset 0)\n"
          "    61 ==> by number of fixed points (offset 1)\n"
          "    70 ==> number of flat steps\n"
          "    71 ==> number of non-flat steps\n"
          "    80 ==> max ascent\n"
          "    81 ==> max descent (same as max ascent)\n"
          );

    composition_nz C(n);
//    composition_nz_odd C(n);
    word_stats W(C.data(), n);

    ulong ct = 0;
    ulong * st = new ulong[n+1];  // stats
    for (ulong k=0; k<=n; ++k)  st[k] = 0;

    ulong m = C.num_parts();
    do
    {
        W.set_len(m);
        ++ct;
        ulong s = 0;
        switch ( sq )
        {
        case 0:  // value of largest part: A048004
            s = W.max_val();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 1, 2, 1,
            // 0, 1, 4, 2, 1,
            // 0, 1, 7, 5, 2, 1,
            // 0, 1, 12, 11, 5, 2, 1,
            // 0, 1, 20, 23, 12, 5, 2, 1,
            // 0, 1, 33, 47, 27, 12, 5, 2, 1,
            // 0, 1, 54, 94, 59, 28, 12, 5, 2, 1,
            // 0, 1, 88, 185, 127, 63, 28, 12, 5, 2, 1,

            // column 2 is A000071
            // column 3 is A000100

        case 1:  // value of smallest part: A105147
            s = W.min_val();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 3, 0, 1,
            // 0, 6, 1, 0, 1,
            // 0, 13, 2, 0, 0, 1,
            // 0, 27, 3, 1, 0, 0, 1,
            // 0, 56, 5, 2, 0, 0, 0, 1,
            // 0, 115, 9, 2, 1, 0, 0, 0, 1,
            // 0, 235, 15, 3, 2, 0, 0, 0, 0, 1,
            // 0, 478, 25, 5, 2, 1, 0, 0, 0, 0, 1,

            // column 1 is A099036
            // column 2 is A200047


        case 3:  // number of largest parts: A238341
            s = W.num_max_val();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 3, 0, 1,
            // 0, 6, 1, 0, 1,
            // 0, 12, 3, 0, 0, 1,
            // 0, 23, 7, 1, 0, 0, 1,
            // 0, 46, 13, 4, 0, 0, 0, 1,
            // 0, 91, 25, 10, 1, 0, 0, 0, 1,
            // 0, 183, 46, 21, 5, 0, 0, 0, 0, 1,
            // 0, 367, 89, 39, 15, 1, 0, 0, 0, 0, 1,

            // column 1 is A097979

        case 4:  // number of smallest parts: A238342
            s = W.num_min_val();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 3, 0, 1,
            // 0, 3, 4, 0, 1,
            // 0, 8, 3, 4, 0, 1,
            // 0, 11, 10, 5, 5, 0, 1,
            // 0, 20, 18, 14, 5, 6, 0, 1,
            // 0, 34, 35, 24, 21, 6, 7, 0, 1,
            // 0, 59, 60, 59, 35, 27, 7, 8, 0, 1,
            // 0, 96, 121, 108, 85, 49, 35, 8, 9, 0, 1,

            // column 1 is A105039

        case 5:  // number of ones: A105422, cf. A139821
            s = W.num_val(1);
            break;
            // 1,
            // 0, 1,
            // 1, 0, 1,
            // 1, 2, 0, 1,
            // 2, 2, 3, 0, 1,
            // 3, 5, 3, 4, 0, 1,
            // 5, 8, 9, 4, 5, 0, 1,
            // 8, 15, 15, 14, 5, 6, 0, 1,
            // 13, 26, 31, 24, 20, 6, 7, 0, 1,
            // 21, 46, 57, 54, 35, 27, 7, 8, 0, 1,
            // 34, 80, 108, 104, 85, 48, 35, 8, 9, 0, 1,
            // 55, 139, 199, 209, 170, 125, 63, 44, 9, 10, 0, 1,
            // 89, 240, 366, 404, 360, 258, 175, 80, 54, 10, 11, 0, 1,
            // 144, 413, 666, 780, 725, 573, 371, 236, 99, 65, 11, 12, 0, 1,


        case 10:  // number of descents: A238343, A238344 (tabf)
            s = W.num_descents();
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 3, 1, 0, 0,
            // 5, 3, 0, 0, 0,
            // 7, 9, 0, 0, 0, 0,
            // 11, 19, 2, 0, 0, 0, 0,
            // 15, 41, 8, 0, 0, 0, 0, 0,
            // 22, 77, 29, 0, 0, 0, 0, 0, 0,
            // 30, 142, 81, 3, 0, 0, 0, 0, 0, 0,
            // 42, 247, 205, 18, 0, 0, 0, 0, 0, 0, 0,

            // column 0 is A000041

        case 11:  // number of ascents (same as number of descents)
            s = W.num_ascents();
            break;


        case 30:  // number of smallest parts: A238342
            s = W.num_min_val();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 3, 0, 1,
            // 0, 3, 4, 0, 1,
            // 0, 8, 3, 4, 0, 1,
            // 0, 11, 10, 5, 5, 0, 1,
            // 0, 20, 18, 14, 5, 6, 0, 1,
            // 0, 34, 35, 24, 21, 6, 7, 0, 1,
            // 0, 59, 60, 59, 35, 27, 7, 8, 0, 1,
            // 0, 96, 121, 108, 85, 49, 35, 8, 9, 0, 1,

        case 31:  // number of largest parts: A238341
            s = W.num_max_val();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 3, 0, 1,
            // 0, 6, 1, 0, 1,
            // 0, 12, 3, 0, 0, 1,
            // 0, 23, 7, 1, 0, 0, 1,
            // 0, 46, 13, 4, 0, 0, 0, 1,
            // 0, 91, 25, 10, 1, 0, 0, 0, 1,
            // 0, 183, 46, 21, 5, 0, 0, 0, 0, 1,
            // 0, 367, 89, 39, 15, 1, 0, 0, 0, 0, 1,
            // 0, 737, 175, 70, 35, 6, 0, 0, 0, 0, 0, 1,


        case 40:  // position of first occurrence of largest part: A238345
            s = W.first_max_idx();
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 3, 1, 0, 0,
            // 5, 2, 1, 0, 0,
            // 8, 5, 2, 1, 0, 0,
            // 14, 9, 6, 2, 1, 0, 0,
            // 24, 18, 12, 7, 2, 1, 0, 0,
            // 43, 33, 25, 16, 8, 2, 1, 0, 0,
            // 77, 62, 49, 35, 21, 9, 2, 1, 0, 0,
            // 140, 115, 95, 73, 49, 27, 10, 2, 1, 0, 0,

            // Column k=1: T(n,1) = A079500(n)= A007059(n+1).

        case 41:  // position of last occurrence of largest part: A238346
            s = W.last_max_idx();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 2, 1, 1, 0,
            // 3, 3, 1, 1, 0,
            // 5, 5, 4, 1, 1, 0,
            // 8, 9, 8, 5, 1, 1, 0,
            // 14, 15, 15, 12, 6, 1, 1, 0,
            // 24, 27, 27, 24, 17, 7, 1, 1, 0,
            // 43, 47, 50, 46, 37, 23, 8, 1, 1, 0,
            // 77, 85, 90, 89, 75, 55, 30, 9, 1, 1, 0,

            // column 0 is A007059
            // Column k=1: T(n,1) = A079500(n-1) = A007059(n).

        case 42:  // position of first occurrence of smallest part: A238347
            s = W.first_min_idx();
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 3, 1, 0, 0,
            // 6, 2, 0, 0, 0,
            // 10, 5, 1, 0, 0, 0,
            // 20, 9, 3, 0, 0, 0, 0,
            // 37, 19, 7, 1, 0, 0, 0, 0,
            // 72, 36, 16, 4, 0, 0, 0, 0, 0,
            // 140, 71, 33, 11, 1, 0, 0, 0, 0, 0,
            // 275, 139, 67, 26, 5, 0, 0, 0, 0, 0, 0,

            // column 0 is A171682

        case 43:  // position of last occurrence of smallest part: A238348
            s = W.last_min_idx();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 2, 1, 1, 0,
            // 2, 3, 2, 1, 0,
            // 4, 4, 4, 3, 1, 0,
            // 5, 7, 8, 7, 4, 1, 0,
            // 8, 11, 14, 14, 11, 5, 1, 0,
            // 12, 18, 23, 27, 25, 16, 6, 1, 0,
            // 19, 27, 39, 49, 51, 41, 22, 7, 1, 0,
            // 28, 44, 64, 85, 98, 92, 63, 29, 8, 1, 0,

            // column 0 is A079501


        case 50:  // number of even values: A119473 (zeros dropped)
            s = W.num_even_val();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 2, 2, 0, 0,
            // 3, 4, 1, 0, 0,
            // 5, 8, 3, 0, 0, 0,
            // 8, 15, 8, 1, 0, 0, 0,
            // 13, 28, 19, 4, 0, 0, 0, 0,
            // 21, 51, 42, 13, 1, 0, 0, 0, 0,
            // 34, 92, 89, 36, 5, 0, 0, 0, 0, 0,
            // 55, 164, 182, 91, 19, 1, 0, 0, 0, 0, 0,

            // column 0 is A000045
            // column 1 is A029907

        case 51:  // number of odd values: A100749
            s = W.num_odd_val();
            break;
            // 1,
            // 0, 1,
            // 1, 0, 1,
            // 0, 3, 0, 1,
            // 2, 0, 5, 0, 1,
            // 0, 8, 0, 7, 0, 1,
            // 4, 0, 18, 0, 9, 0, 1,
            // 0, 20, 0, 32, 0, 11, 0, 1,
            // 8, 0, 56, 0, 50, 0, 13, 0, 1,
            // 0, 48, 0, 120, 0, 72, 0, 15, 0, 1,
            // 16, 0, 160, 0, 220, 0, 98, 0, 17, 0, 1,

        case 60:  // by number of fixed points (offset 0):
            s = W.num_fixed_points();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 2, 2, 0, 0,
            // 4, 3, 1, 0, 0,
            // 7, 7, 2, 0, 0, 0,
            // 13, 14, 5, 0, 0, 0, 0,
            // 24, 30, 9, 1, 0, 0, 0, 0,
            // 46, 59, 21, 2, 0, 0, 0, 0, 0,
            // 88, 119, 44, 5, 0, 0, 0, 0, 0, 0,
            // 170, 239, 91, 12, 0, 0, 0, 0, 0, 0, 0,


        case 61:  // by number of fixed points (offset 1): A238349, A238350 (tabf)
            s = W.num_fixed_points_1();
            break;
            // 1,
            // 0, 1,
            // 1, 1, 0,
            // 2, 1, 1, 0,
            // 3, 4, 1, 0, 0,
            // 6, 7, 3, 0, 0, 0,
            // 11, 16, 4, 1, 0, 0, 0,
            // 22, 29, 12, 1, 0, 0, 0, 0,
            // 42, 60, 23, 3, 0, 0, 0, 0, 0,
            // 82, 120, 47, 7, 0, 0, 0, 0, 0, 0,
            // 161, 238, 100, 12, 1, 0, 0, 0, 0, 0, 0,
            // 316, 479, 198, 30, 1, 0, 0, 0, 0, 0, 0, 0,
            // 624, 956, 404, 61, 3, 0, 0, 0, 0, 0, 0, 0, 0,
            // 1235, 1910, 818, 126, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0,

            // column 0 is A238351

        case 70:  // number of flat steps: A106356
            s = W.num_flat_steps();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 3, 0, 1, 0,
            // 4, 3, 0, 1, 0,
            // 7, 6, 2, 0, 1, 0,
            // 14, 7, 8, 2, 0, 1, 0,
            // 23, 20, 10, 8, 2, 0, 1, 0,
            // 39, 42, 22, 13, 9, 2, 0, 1, 0,
            // 71, 72, 58, 28, 14, 10, 2, 0, 1, 0,
            // 124, 141, 112, 72, 33, 16, 11, 2, 0, 1, 0,

            // column 0 is A003242 (Carlitz compositions)
            // column 1 is A106357
            // column 2 is A106358
            // column 3 is A106359
            // column 4 is A106360

        case 71:  // number of non-flat steps: A238130 (or A238279)
            s = W.num_nonflat_steps();
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 2, 2, 0, 0,
            // 3, 4, 1, 0, 0,
            // 2, 10, 4, 0, 0, 0,
            // 4, 12, 14, 2, 0, 0, 0,
            // 2, 22, 29, 10, 1, 0, 0, 0,
            // 4, 26, 56, 36, 6, 0, 0, 0, 0,
            // 3, 34, 100, 86, 31, 2, 0, 0, 0, 0,
            // 4, 44, 148, 200, 99, 16, 1, 0, 0, 0, 0,

            // column 0 is A000005
            // column 1 is 2 * A002133

        case 80:  // max ascent: A225084, cf. A225085
            s = W.max_ascent();
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 3, 1, 0, 0,
            // 5, 2, 1, 0, 0,
            // 7, 6, 2, 1, 0, 0,
            // 11, 12, 6, 2, 1, 0, 0,
            // 15, 26, 14, 6, 2, 1, 0, 0,
            // 22, 50, 33, 14, 6, 2, 1, 0, 0,
            // 30, 97, 72, 34, 14, 6, 2, 1, 0, 0,
            // 42, 180, 156, 77, 34, 14, 6, 2, 1, 0, 0,
            // 56, 332, 328, 173, 78, 34, 14, 6, 2, 1, 0, 0,
            // 77, 600, 681, 378, 177, 78, 34, 14, 6, 2, 1, 0, 0,

            // column 0 is A000041

        case 81:  // max descent: same as max ascent
            s = W.max_descent();
            break;

        case 85:  // number of (distinct) parts: A235998
            s = W.num_sorts();
            break;
            // 1,
            // 0, 1,
            // 0, 2, 0,
            // 0, 2, 2, 0,
            // 0, 3, 5, 0, 0,
            // 0, 2, 14, 0, 0, 0,
            // 0, 4, 22, 6, 0, 0, 0,
            // 0, 2, 44, 18, 0, 0, 0, 0,
            // 0, 4, 68, 56, 0, 0, 0, 0, 0,
            // 0, 3, 107, 146, 0, 0, 0, 0, 0, 0,
            // 0, 4, 172, 312, 24, 0, 0, 0, 0, 0, 0,
            // 0, 2, 261, 677, 84, 0, 0, 0, 0, 0, 0, 0,
            // 0, 6, 396, 1358, 288, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 2, 606, 2666, 822, 0, 0, 0, 0, 0, 0, 0, 0, 0,

        case 86:  // max multiplicity of any part: A242447
            s = W.max_num_vals();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 3, 0, 1,
            // 0, 3, 4, 0, 1,
            // 0, 5, 6, 4, 0, 1,
            // 0, 11, 10, 5, 5, 0, 1,
            // 0, 13, 21, 18, 5, 6, 0, 1,
            // 0, 19, 40, 34, 21, 6, 7, 0, 1,
            // 0, 27, 87, 59, 40, 27, 7, 8, 0, 1,
            // 0, 57, 121, 132, 100, 49, 35, 8, 9, 0, 1,
            // 0, 65, 219, 272, 210, 131, 63, 44, 9, 10, 0, 1,
            // 0, 101, 421, 519, 396, 279, 176, 80, 54, 10, 11, 0, 1,
            // 0, 133, 690, 966, 870, 635, 378, 236, 99, 65, 11, 12, 0, 1,

        case 87:  // min multiplicity of any part: A242451
            s = W.min_num_vals_nz();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 3, 0, 1,
            // 0, 6, 1, 0, 1,
            // 0, 15, 0, 0, 0, 1,
            // 0, 23, 7, 1, 0, 0, 1,
            // 0, 53, 10, 0, 0, 0, 0, 1,
            // 0, 94, 32, 0, 1, 0, 0, 0, 1,
            // 0, 203, 31, 21, 0, 0, 0, 0, 0, 1,
            // 0, 404, 71, 35, 0, 1, 0, 0, 0, 0, 1,
            // 0, 855, 77, 91, 0, 0, 0, 0, 0, 0, 0, 1,
            // 0, 1648, 222, 105, 71, 0, 1, 0, 0, 0, 0, 0, 1,
            // 0, 3416, 342, 211, 126, 0, 0, 0, 0, 0, 0, 0, 0, 1,

        case 90: // test
            s = m;  // number of parts: A097805 (A007318)
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 1, 2, 1,
            // 0, 1, 3, 3, 1,
            // 0, 1, 4, 6, 4, 1,
            // 0, 1, 5, 10, 10, 5, 1,
            // 0, 1, 6, 15, 20, 15, 6, 1,
            // 0, 1, 7, 21, 35, 35, 21, 7, 1,
            // 0, 1, 8, 28, 56, 70, 56, 28, 8, 1,

        case 95: // test
            s = W.first_val();  // first part: A155038
            // odd parts: A242086
            break;

        default:
            cerr << "Invalid choice (exiting)." << endl;
            return 1;
        }

        st[ s ] += 1;


#ifndef TIMING
        cout << setw(4) << ct << ":";
        C.print("  ");
        cout << setw(4) << s;
        cout << endl;

        jjassert( C.OK() );
#endif  // TIMING
    }
    while ( 0 != (m=C.next()) );


    ulong sct = 0;
    for (ulong k=0; k<=n; ++k)
    {
        sct += st[k];
        cout << st[k] << ", ";
//        cout << sct << ", ";  // cumulative values
    }
    cout << endl;

    cout << " ct=" << ct;  // total: OEIS sequence A011782
    cout << endl;

    jjassert( sct == ct );

    delete [] st;

    return 0;
}
// -------------------------

/*

Print triangle for stats q:

q=0

OEIS example:
 for n in $(seq 0 15) ; do ./bin $n $q | grep ', $' ; done | nl -v0 -s':  ' -w2 -n rz

OEIS example, offset 1:
 q=30; for n in $(seq 1 10) ; do ./bin $n $q | grep ', $' ; done | nl -v1 -s':  ' -w2 -n rz | sed 's/ 0, $//g;'



C++ comment:
 for n in $(seq 0 15) ; do ./bin $n $q | grep ', $' ; done | sed 's/^/\/\/ /'

C++ comment, offset 1:
 q=30; for n in $(seq 1 10) ; do ./bin $n $q | grep ', $' ; done | sed 's/^/\/\/ /' | sed 's/ 0, $//g;'

Extract column c from stats q:
 c=0;  echo $(for n in $(seq 0 20) ; do ./bin $n $q | grep ', $' ; done | cut -d, -f$((c+1))) | sed 's/ /, /g;'

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-stats-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-stats-demo.cc DEMOFLAGS=-DTIMING"
/// End:
