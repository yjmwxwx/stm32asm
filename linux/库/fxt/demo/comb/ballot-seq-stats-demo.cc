
#include "comb/young-tab-rgs.h"
#include "comb/word-stats.h"
#include "comb/young-tab-rgs-descents.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Statistics for ballot sequences (and standard Young tableaux):
//% Cf. the following OEIS sequences:
//% A161126, A238121, A238123, A238125, A238128, and A238129.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of cells");
    ulong m = 0;
//    NXARG(m, "Number of allowed values for digits\n"
//          "         == max height of tableaux, 0 ==> all");
//    if ( m>n )  m = n;
//    if ( m==0 )  m = n;

    young_tab_rgs Y(n, m);
    word_stats W(Y.data(), n);
    const ulong nst = n + 1;
//    const ulong nst = n*(n-1)/2 + 1;  // for tableaux by major index
    ulong * st = new ulong[nst];  // stats
    for (ulong k=0; k<nst; ++k)  st[k] = 0;

    ulong sq = 0;
    NXARG(sq, "Select stats:\n"
          "     0 ==> by maximal descent\n"
          "     1 ==> by maximal ascent\n"
          "    10 ==> by number of ascents\n"
          "    11 ==> by number of descents\n"
          "    20 ==> by number of smallest parts\n"
          "    21 ==> by number of largest parts\n"
          "    30 ==> by position of last max val\n"
          "    31 ==> by position of last min val\n"
          "    40 ==> by number of flat steps\n"
          "    41 ==> by number of non-flat steps\n"
//          "     ==> by \n"
//          "    90 ==> by value of largest part\n"
          );

    bool tq = 0;
    NXARG(tq, "Whether do draw tableaux (as ASCII art)");

    ulong ct = 0;
    do
    {
#if 0   // only chess tableaux:  A238014
        if ( ! Y.is_chess_tableau() )  continue;
#endif

        ++ct;

        ulong s = 0;
        switch ( sq )
        {
        case 0:  // maximal descent: A238128
            // == SYT with a pair of cells (v,v+1) such that v lies k
            // rows above v+1, and no pair (u,u+1) with a larger such
            // separation exists.
            // First column: A000041
            s = W.max_descent();
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 3, 1, 0, 0,
            // 5, 4, 1, 0, 0,
            // 7, 13, 5, 1, 0, 0,
            // 11, 37, 21, 6, 1, 0, 0,
            // 15, 100, 78, 31, 7, 1, 0, 0,
            // 22, 265, 292, 133, 43, 8, 1, 0, 0,
            // 30, 694, 1028, 586, 215, 57, 9, 1, 0, 0,
            // 42, 1828, 3691, 2453, 1073, 325, 73, 10, 1, 0, 0,

        case 1:  // maximal ascent: A238129
            // == SYT with a pair of cells (v,v+1) such that v lies k
            // rows below v+1, and no pair (u,u+1) with a larger such
            // separation exists.
            s = W.max_ascent();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 3, 0, 0,
            // 1, 8, 1, 0, 0,
            // 1, 19, 5, 1, 0, 0,
            // 1, 47, 21, 6, 1, 0, 0,
            // 1, 114, 78, 31, 7, 1, 0, 0,
            // 1, 286, 292, 133, 43, 8, 1, 0, 0,
            // 1, 723, 1028, 586, 215, 57, 9, 1, 0, 0,
            // 1, 1869, 3691, 2453, 1073, 325, 73, 10, 1, 0, 0,


        case 10:  // number of ascents: A161126
            // == SYT such that there are k pairs of cells (v,v+1)
            // with v+1 lying in a row below v.
            // == involutions by descents
            s = W.num_ascents();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 2, 1, 0,
            // 1, 4, 4, 1, 0,
            // 1, 6, 12, 6, 1, 0,
            // 1, 9, 28, 28, 9, 1, 0,
            // 1, 12, 57, 92, 57, 12, 1, 0,
            // 1, 16, 105, 260, 260, 105, 16, 1, 0,
            // 1, 20, 179, 630, 960, 630, 179, 20, 1, 0,
            // 1, 25, 289, 1397, 3036, 3036, 1397, 289, 25, 1, 0,

        case 11:  // number of descents: A238121
            // == SYT such that there are k pairs of cells (v,v+1)
            // with v+1 lying in a row above v.
            s = W.num_descents();
            // first column: A000041
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 3, 1, 0, 0,
            // 5, 5, 0, 0, 0,
            // 7, 16, 3, 0, 0, 0,
            // 11, 43, 21, 1, 0, 0, 0,
            // 15, 99, 101, 17, 0, 0, 0, 0,
            // 22, 215, 373, 145, 9, 0, 0, 0, 0,
            // 30, 430, 1174, 836, 146, 4, 0, 0, 0, 0,
            // 42, 834, 3337, 3846, 1324, 112, 1, 0, 0, 0, 0,


        case 20:  // number of smallest parts (=number of cells in first row): A047884
            s = W.num_min_val();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 1, 2, 1,
            // 0, 1, 5, 3, 1,
            // 0, 1, 9, 11, 4, 1,
            // 0, 1, 19, 31, 19, 5, 1,
            // 0, 1, 34, 92, 69, 29, 6, 1,
            // 0, 1, 69, 253, 265, 127, 41, 7, 1,
            // 0, 1, 125, 709, 929, 583, 209, 55, 8, 1,
            // 0, 1, 251, 1936, 3356, 2446, 1106, 319, 71, 9, 1,

        case 21:  // number of largest parts (=number of cells in last row): A238123
            s = W.num_max_val();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 3, 0, 1,
            // 0, 7, 2, 0, 1,
            // 0, 20, 5, 0, 0, 1,
            // 0, 56, 14, 5, 0, 0, 1,
            // 0, 182, 35, 14, 0, 0, 0, 1,
            // 0, 589, 132, 28, 14, 0, 0, 0, 1,
            // 0, 2088, 399, 90, 42, 0, 0, 0, 0, 1,
            // 0, 7522, 1556, 285, 90, 42, 0, 0, 0, 0, 1,


        case 30:  // position of last max val (=last cell in bottom row): A238727
            // diagonal is A238728 (largest cell in the last row).
            s = W.last_max_idx();
            break;
            // 1,
            // 0, 2,
            // 0, 1, 3,
            // 0, 1, 2, 7,
            // 0, 1, 3, 8, 14,
            // 0, 1, 4, 11, 19, 41,
            // 0, 1, 7, 19, 34, 64, 107,
            // 0, 1, 11, 32, 62, 119, 202, 337,
            // 0, 1, 21, 64, 131, 248, 418, 671, 1066,
            // 0, 1, 36, 124, 277, 545, 943, 1518, 2361, 3691,

        case 31:  // position of last min val (=last cell in top row): A238794
            s = W.last_min_idx();
            break;
            // 1,
            // 1, 1,
            // 1, 1, 2,
            // 1, 2, 3, 4,
            // 1, 3, 5, 7, 10,
            // 1, 6, 10, 14, 19, 26,
            // 1, 10, 19, 29, 41, 56, 76,
            // 1, 20, 41, 66, 96, 132, 176, 232,
            // 1, 35, 86, 152, 232, 327, 441, 582, 764,
            // 1, 70, 197, 374, 596, 863, 1181, 1563, 2031, 2620,


        case 40:  // number of flat steps (=number of successions): A238125
            // == SYT with k successions (cf. A237770).
            // first column: A237770
            // second column: A238126
            // third column: A238127
            s = W.num_flat_steps();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 2, 1, 1, 0,
            // 4, 3, 2, 1, 0,
            // 9, 8, 6, 2, 1, 0,
            // 22, 24, 17, 9, 3, 1, 0,
            // 59, 70, 57, 29, 13, 3, 1, 0,
            // 170, 224, 191, 108, 49, 17, 4, 1, 0,
            // 516, 744, 663, 399, 201, 69, 23, 4, 1, 0,
            // 1658, 2588, 2415, 1573, 802, 322, 104, 28, 5, 1, 0,

        case 41:  // number of non-flat steps (=number of non-successions):
            // reversed triangle wrt. "number of flat steps"
            s = W.num_nonflat_steps();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 1, 2, 0,
            // 1, 2, 3, 4, 0,
            // 1, 2, 6, 8, 9, 0,
            // 1, 3, 9, 17, 24, 22, 0,
            // 1, 3, 13, 29, 57, 70, 59, 0,
            // 1, 4, 17, 49, 108, 191, 224, 170, 0,
            // 1, 4, 23, 69, 201, 399, 663, 744, 516, 0,
            // 1, 5, 28, 104, 322, 802, 1573, 2415, 2588, 1658, 0,


        case 50:  // number of fixed points (=cells v in row v): A238802
            // colum 1: A001475
            s = W.num_fixed_points();
            break;
            // 1,
            // 0, 1,
            // 0, 1, 1,
            // 0, 2, 1, 1,
            // 0, 5, 3, 1, 1,
            // 0, 13, 8, 3, 1, 1,
            // 0, 38, 24, 9, 3, 1, 1,
            // 0, 116, 74, 28, 9, 3, 1, 1,
            // 0, 382, 246, 93, 29, 9, 3, 1, 1,
            // 0, 1310, 848, 321, 98, 29, 9, 3, 1, 1,
            // 0, 4748, 3088, 1168, 350, 99, 29, 9, 3, 1, 1,

//        case 51:  // number of fixed points, offset 1 (trivial)
//            // colum 1:
//            s = W.num_fixed_points_1();
//            break;

        case 60:  // maxval - minval  (=tableaux with k rows): A047884
            s = W.min_max_diff();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 2, 1, 0,
            // 1, 5, 3, 1, 0,
            // 1, 9, 11, 4, 1, 0,
            // 1, 19, 31, 19, 5, 1, 0,
            // 1, 34, 92, 69, 29, 6, 1, 0,
            // 1, 69, 253, 265, 127, 41, 7, 1, 0,
            // 1, 125, 709, 929, 583, 209, 55, 8, 1, 0,
            // 1, 251, 1936, 3356, 2446, 1106, 319, 71, 9, 1, 0,


        case 61:  // abs(#minval - #maxval)  (=diff row lengths: first-last): A238707
            // column 0: A067228
            s = W.min_max_num_diff();
//            s = W.num_min_val() - W.num_max_val();  // same
            break;
            // 1,
            // 1, 0,
            // 2, 0, 0,
            // 2, 2, 0, 0,
            // 4, 3, 3, 0, 0,
            // 2, 14, 6, 4, 0, 0,
            // 12, 14, 35, 10, 5, 0, 0,
            // 2, 69, 71, 69, 15, 6, 0, 0,
            // 30, 97, 295, 195, 119, 21, 7, 0, 0,
            // 44, 251, 751, 929, 421, 188, 28, 8, 0, 0,
            // 86, 671, 2326, 3044, 2254, 791, 279, 36, 9, 0, 0,


//        case 70:  // tableaux by major index: A232439
//            // Warning: needs nst = n*(n-1)/2 + 1;
//            // cf. A003293, A228125
//            s = young_tab_rgs_major_index( Y.data(), n );
//            break;
//            // 1,
//            // 1,
//            // 1, 1,
//            // 1, 1, 1, 1,
//            // 1, 1, 2, 2, 2, 1, 1,
//            // 1, 1, 2, 3, 4, 4, 4, 3, 2, 1, 1,
//            // 1, 1, 2, 4, 5, 7, 9, 9, 9, 9, 7, 5, 4, 2, 1, 1,
//            // 1, 1, 2, 4, 6, 9, 13, 16, 19, 22, 23, 23, 22, 19, 16, 13, 9, 6, 4, 2, 1, 1,
//            // 1, 1, 2, 4, 7, 10, 16, 22, 30, 37, 46, 52, 60, 62, 64,
//            //    62, 60, 52, 46, 37, 30, 22, 16, 10, 7, 4, 2, 1, 1,


        case 80:  // tableaux by number of descents: A161126 (same as number of ascents)
            s = young_tab_rgs_descent_number( Y.data(), n );
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 2, 1, 0,
            // 1, 4, 4, 1, 0,
            // 1, 6, 12, 6, 1, 0,
            // 1, 9, 28, 28, 9, 1, 0,
            // 1, 12, 57, 92, 57, 12, 1, 0,
            // 1, 16, 105, 260, 260, 105, 16, 1, 0,
            // 1, 20, 179, 630, 960, 630, 179, 20, 1, 0,
            // 1, 25, 289, 1397, 3036, 3036, 1397, 289, 25, 1, 0,


        case 90:  // value of largest part (=number of rows): A047884
            s = W.max_val();
            break;
            // 1,
            // 1, 0,
            // 1, 1, 0,
            // 1, 2, 1, 0,
            // 1, 5, 3, 1, 0,
            // 1, 9, 11, 4, 1, 0,
            // 1, 19, 31, 19, 5, 1, 0,
            // 1, 34, 92, 69, 29, 6, 1, 0,
            // 1, 69, 253, 265, 127, 41, 7, 1, 0,
            // 1, 125, 709, 929, 583, 209, 55, 8, 1, 0,
            // 1, 251, 1936, 3356, 2446, 1106, 319, 71, 9, 1, 0,

        case 95:  // value of last part (=row containing max cell): A238750
            // Column 0: A000085
            // Column 1: A238124
            s = Y.data()[n-1];
//            s = W.num_val(Y.data()[n-1]);  // same stats
            break;
            // 0,
            // 1, 0,
            // 1, 1, 0,
            // 2, 1, 1, 0,
            // 4, 3, 2, 1, 0,
            // 10, 7, 5, 3, 1, 0,
            // 26, 20, 14, 11, 4, 1, 0,
            // 76, 56, 44, 31, 19, 5, 1, 0,
            // 232, 182, 139, 106, 69, 29, 6, 1, 0,
            // 764, 589, 475, 351, 265, 127, 41, 7, 1, 0,
            // 2620, 2088, 1658, 1303, 971, 583, 209, 55, 8, 1, 0,

        default:
            cerr << "Invalid choice (exiting)." << endl;
            return 1;
        }

        st[ s ] += 1;


#ifndef TIMING  // whether to print anything
        cout << setw(4) << ct << ":";

//        Y.print("  ");  // RGS, starting with cell 0
        Y.print1("  ");  // RGS, starting with cell 1
//        Y.print_stats("    ");  // partition of n
//        cout << setw(3) << Y.height();  // height
        cout << setw(4) << s;  // stats value

#if 0  // list positions of first occurrence of digits:
        ulong h = Y.height();
        cout << "   [ ";
        for (ulong d=0; d<h; ++d)
        {
            ulong p = 0;
            while ( Y.a_[p] != d )  ++p;
            cout << p << " ";
        }
        cout << "]";
#endif

        if ( tq )
        {
            cout << endl;
            Y.print_aa( 1 );  // arg is offset (0 or 1)
            cout << endl;
        }

        cout << endl;

//        jjassert( s <= nst );
#endif  // TIMING
    }
    while ( Y.next() );



    ulong sct = 0;
    for (ulong k=0; k<nst; ++k)
    {
        cout << st[k] << ", ";
        sct += st[k];
    }
    cout << endl;

    cout << " ct=" << ct;  // A000085
    cout << endl;

    delete [] st;

    return 0;
}
// -------------------------

/*

Print triangle for stats q:

OEIS example:
 q=0; for n in $(seq 0 10) ; do ./bin $n $q | grep ', $' ; done | nl -v0 -s':  ' -w2 -n rz

OEIS example, offset 1:
 q=30; for n in $(seq 1 10) ; do ./bin $n $q | grep ', $' ; done | nl -v1 -s':  ' -w2 -n rz | sed 's/ 0, $//g;'


C++ comment:
 q=0; for n in $(seq 0 10) ; do ./bin $n $q | grep ', $' ; done | sed 's/^/\/\/ /'

C++ comment, offset 1:
 q=30; for n in $(seq 1 10) ; do ./bin $n $q | grep ', $' ; done | sed 's/^/\/\/ /' | sed 's/ 0, $//g;'

Extract column c from stats q:
 q=0; c=0;  echo $(for n in $(seq 0 20) ; do ./bin $n $q | grep ', $' ; done | cut -d, -f$((c+1))) | sed 's/ /, /g;'

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ballot-seq-stats-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ballot-seq-stats-demo.cc DEMOFLAGS=-DTIMING"
/// End:
