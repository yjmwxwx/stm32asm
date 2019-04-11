
#include "comb/id-tree-lev-seq.h"
#include "comb/word-stats.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Statistics for (level sequences of) unordered rooted identity trees.
//% Cf. the following OEIS sequences:
//% A004111: all identity trees.
//% A227819: identity trees by height.
//% A055327: identity trees by number of descents.
//% A227774: identity trees by number of ones.
//% A244523: identity trees by maximal branching number (out-degree).


// Cf. comb/ordered-tree-lev-seq-stats-demo.cc for stats for ordered trees

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Number of non-root nodes");
//    jjassert( n>=1 );

    ulong sq = 0;
    NXARG(sq, "Select stats:\n"
          "    0 ==> by height\n"
          "    1 ==> number of ascents\n"
          "    2 ==> number of descents\n"
          "    3 ==> number of ones\n"
//          "    4 ==> number of fixed points\n"  // same stats as 0
          "    5 ==> number of maximal levels\n"
          "    6 ==> position of last occurrence of one\n"
//          "    7 ==> position of first occurrence of the maximal value\n"  // same stats as 0
          "    8 ==> position of last occurrence of the maximal value\n"
//          "    9 ==> number of flat steps\n"
          "   10 ==> number of even values\n"
          "   11 ==> number of odd values\n"
//          "   20 ==> number of flat steps\n"
//          "   21 ==> number of non-flat steps\n"
          "   25 ==> number of peaks\n"
//          "   11 ==> number of \n"
          );

    bool aa = false;  // whether to print as ASCII art
    NXARG(aa,"Whether to render trees as ASCII art");

    id_tree_lev_seq T(n);
    const ulong N = T.size(); // + (n==0);
//    cout << " :: N = " << N << endl;
    word_stats W(T.data(), N);

    ulong ct = 0;
    ulong * st = new ulong[N];  // stats
    for (ulong k=0; k<N; ++k)  st[k] = 0;


    ulong j = 0;
    do
    {
        ++ct;
        ulong s = 0;
        switch ( sq )
        {
        case 0:  // by height: A227819
            s = W.max_val();
            // Columns k=4-10: A038088, A038089, A038090, A038091, A038092, A229403, A229404.
            // Column sums: A038081.
            break;
            // 1, 0,
            // 0, 1, 0,
            // 0, 0, 1, 0,
            // 0, 0, 1, 1, 0,
            // 0, 0, 0, 2, 1, 0,
            // 0, 0, 0, 2, 3, 1, 0,
            // 0, 0, 0, 2, 5, 4, 1, 0,
            // 0, 0, 0, 2, 8, 9, 5, 1, 0,
            // 0, 0, 0, 1, 12, 18, 14, 6, 1, 0,
            // 0, 0, 0, 1, 17, 34, 33, 20, 7, 1, 0,
            // 0, 0, 0, 1, 23, 61, 72, 54, 27, 8, 1, 0,
            // 0, 0, 0, 0, 32, 108, 149, 132, 82, 35, 9, 1, 0,
            // 0, 0, 0, 0, 41, 187, 301, 303, 221, 118, 44, 10, 1, 0,

        case 1:  // by number of ascents: A000000
            s = W.num_ascents();
            break;
            // 1, 0,
            // 0, 1, 0,
            // 0, 0, 1, 0,
            // 0, 0, 1, 1, 0,
            // 0, 0, 0, 2, 1, 0,
            // 0, 0, 0, 1, 4, 1, 0,
            // 0, 0, 0, 0, 5, 6, 1, 0,
            // 0, 0, 0, 0, 2, 13, 9, 1, 0,
            // 0, 0, 0, 0, 0, 11, 28, 12, 1, 0,
            // 0, 0, 0, 0, 0, 3, 40, 53, 16, 1, 0,
            // 0, 0, 0, 0, 0, 0, 26, 109, 91, 20, 1, 0,
            // 0, 0, 0, 0, 0, 0, 6, 116, 254, 146, 25, 1, 0,
            // 0, 0, 0, 0, 0, 0, 0, 61, 387, 524, 223, 30, 1, 0,


        case 2:  // by number of descents: A055327
            s = W.num_descents();
            // column 1: A002620
            // column 2..: A055328, A055329, A055330, A055331, A055332, A055333
            break;
            // 1, 0,
            // 1, 0, 0,
            // 1, 0, 0, 0,
            // 1, 1, 0, 0, 0,
            // 1, 2, 0, 0, 0, 0,
            // 1, 4, 1, 0, 0, 0, 0,
            // 1, 6, 5, 0, 0, 0, 0, 0,
            // 1, 9, 13, 2, 0, 0, 0, 0, 0,
            // 1, 12, 28, 11, 0, 0, 0, 0, 0, 0,
            // 1, 16, 53, 40, 3, 0, 0, 0, 0, 0, 0,
            // 1, 20, 91, 109, 26, 0, 0, 0, 0, 0, 0, 0,
            // 1, 25, 146, 254, 116, 6, 0, 0, 0, 0, 0, 0, 0,
            // 1, 30, 223, 524, 387, 61, 0, 0, 0, 0, 0, 0, 0, 0,


        case 3:  // by number of ones: A227774
            s = W.num_val(1);
//            s = T.branching_number(0);  // same
            // Columns k=1-10: A004111, A227806, A227807, A227808,
            // A227809, A227810, A227811, A227812, A227813, A227814.
            break;
            // 1, 0,
            // 0, 1, 0,
            // 0, 1, 0, 0,
            // 0, 1, 1, 0, 0,
            // 0, 2, 1, 0, 0, 0,
            // 0, 3, 3, 0, 0, 0, 0,
            // 0, 6, 5, 1, 0, 0, 0, 0,
            // 0, 12, 11, 2, 0, 0, 0, 0, 0,
            // 0, 25, 22, 5, 0, 0, 0, 0, 0, 0,
            // 0, 52, 49, 12, 0, 0, 0, 0, 0, 0, 0,
            // 0, 113, 104, 28, 2, 0, 0, 0, 0, 0, 0, 0,
            // 0, 247, 232, 65, 4, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 548, 513, 152, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//        case 4:  // by number of fixed points: (same as "by height")
//            s = W.num_fixed_points();
//            break;

        case 5:  // by number of max levels: A000000
            // column 1: A000000
            s = W.num_max_val();
            break;
            // 0, 1,
            // 0, 1, 0,
            // 0, 1, 0, 0,
            // 0, 2, 0, 0, 0,
            // 0, 3, 0, 0, 0, 0,
            // 0, 6, 0, 0, 0, 0, 0,
            // 0, 12, 0, 0, 0, 0, 0, 0,
            // 0, 24, 1, 0, 0, 0, 0, 0, 0,
            // 0, 50, 2, 0, 0, 0, 0, 0, 0, 0,
            // 0, 107, 6, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 232, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 509, 39, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 1129, 96, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,


        case 6:  // position of last one: A000000
            s = W.last_val_idx(1);
            // column 1: A004111
            break;
            // 0, 1,
            // 0, 1, 0,
            // 0, 1, 0, 0,
            // 0, 1, 0, 1, 0,
            // 0, 2, 0, 0, 1, 0,
            // 0, 3, 0, 0, 1, 2, 0,
            // 0, 6, 0, 0, 0, 2, 4, 0,
            // 0, 12, 0, 0, 0, 2, 3, 8, 0,
            // 0, 25, 0, 0, 0, 1, 3, 6, 17, 0,
            // 0, 52, 0, 0, 0, 0, 6, 6, 14, 35, 0,
            // 0, 113, 0, 0, 0, 0, 3, 12, 12, 29, 78, 0,
            // 0, 247, 0, 0, 0, 0, 3, 15, 24, 26, 64, 169, 0,
            // 0, 548, 0, 0, 0, 0, 3, 15, 33, 50, 58, 140, 379, 0,

//        case 7:  // position of first occurrence of max: (same as "by height")
//            s = W.first_max_idx();
//            break;

        case 8:  // position of last occurrence of max: A000000
            s = W.last_max_idx();
            break;
            // 1, 0,
            // 0, 1, 0,
            // 0, 0, 1, 0,
            // 0, 0, 1, 1, 0,
            // 0, 0, 0, 2, 1, 0,
            // 0, 0, 0, 2, 3, 1, 0,
            // 0, 0, 0, 2, 5, 4, 1, 0,
            // 0, 0, 0, 1, 8, 9, 5, 2, 0,
            // 0, 0, 0, 0, 11, 18, 14, 7, 2, 0,
            // 0, 0, 0, 0, 13, 33, 33, 21, 9, 4, 0,
            // 0, 0, 0, 0, 15, 56, 71, 55, 30, 14, 6, 0,
            // 0, 0, 0, 0, 16, 92, 143, 131, 87, 45, 23, 11, 0,
            // 0, 0, 0, 0, 15, 146, 279, 296, 226, 137, 69, 40, 18, 0,

//        case 9:  // number of flat steps: (trivial, no flat steps)
//            s = W.num_flat_steps();
//            break;

        case 10:  // number of even values: A000000
            s = W.num_even_val();
            break;
            // 0, 1,
            // 0, 1, 0,
            // 0, 0, 1, 0,
            // 0, 0, 2, 0, 0,
            // 0, 0, 1, 2, 0, 0,
            // 0, 0, 0, 5, 1, 0, 0,
            // 0, 0, 0, 4, 8, 0, 0, 0,
            // 0, 0, 0, 1, 19, 5, 0, 0, 0,
            // 0, 0, 0, 0, 20, 31, 1, 0, 0, 0,
            // 0, 0, 0, 0, 10, 76, 27, 0, 0, 0, 0,
            // 0, 0, 0, 0, 2, 95, 139, 11, 0, 0, 0, 0,
            // 0, 0, 0, 0, 0, 65, 339, 142, 2, 0, 0, 0, 0,
            // 0, 0, 0, 0, 0, 23, 472, 648, 83, 0, 0, 0, 0, 0,

        case 11:  // number of odd values: A000000
            s = W.num_odd_val();
            break;
            // 1, 0,
            // 0, 1, 0,
            // 0, 1, 0, 0,
            // 0, 0, 2, 0, 0,
            // 0, 0, 2, 1, 0, 0,
            // 0, 0, 1, 5, 0, 0, 0,
            // 0, 0, 0, 8, 4, 0, 0, 0,
            // 0, 0, 0, 5, 19, 1, 0, 0, 0,
            // 0, 0, 0, 1, 31, 20, 0, 0, 0, 0,
            // 0, 0, 0, 0, 27, 76, 10, 0, 0, 0, 0,
            // 0, 0, 0, 0, 11, 139, 95, 2, 0, 0, 0, 0,
            // 0, 0, 0, 0, 2, 142, 339, 65, 0, 0, 0, 0, 0,
            // 0, 0, 0, 0, 0, 83, 648, 472, 23, 0, 0, 0, 0, 0,


        case 25: // number of peaks: A000000
            s = W.num_peaks();
            // column 1: A000000
            break;
            // 1, 0,
            // 1, 0, 0,
            // 1, 0, 0, 0,
            // 1, 1, 0, 0, 0,
            // 1, 2, 0, 0, 0, 0,
            // 1, 5, 0, 0, 0, 0, 0,
            // 1, 10, 1, 0, 0, 0, 0, 0,
            // 1, 20, 4, 0, 0, 0, 0, 0, 0,
            // 1, 36, 15, 0, 0, 0, 0, 0, 0, 0,
            // 1, 65, 46, 1, 0, 0, 0, 0, 0, 0, 0,
            // 1, 112, 124, 10, 0, 0, 0, 0, 0, 0, 0, 0,
            // 1, 192, 307, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 1, 323, 711, 189, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//        case 30: // max flat length: (trivial)
//            s = W.max_flat_length();
//            break;


        case 40: // max frequency in histogram (of level seq.): A000000
            s = W.max_num_vals();
            // column 2: A077865
            // column 3: A000000
            break;
            // 0, 1,
            // 0, 1, 0,
            // 0, 1, 0, 0,
            // 0, 1, 1, 0, 0,
            // 0, 1, 2, 0, 0, 0,
            // 0, 1, 5, 0, 0, 0, 0,
            // 0, 1, 9, 2, 0, 0, 0, 0,
            // 0, 1, 18, 6, 0, 0, 0, 0, 0,
            // 0, 1, 32, 19, 0, 0, 0, 0, 0, 0,
            // 0, 1, 60, 49, 3, 0, 0, 0, 0, 0, 0,
            // 0, 1, 107, 123, 16, 0, 0, 0, 0, 0, 0, 0,
            // 0, 1, 196, 289, 60, 2, 0, 0, 0, 0, 0, 0, 0,
            // 0, 1, 351, 670, 191, 13, 0, 0, 0, 0, 0, 0, 0, 0,


        case 50:  // max branching number (out-degree): A244523
            s = T.max_branching_number();
            // columns 2..10: A245747, A245748, A245749, A245750,
            //     A245751, A245752, A245753, A245754, A245755.
            break;
            // 1, 0,
            // 0, 1, 0,
            // 0, 1, 0, 0,
            // 0, 1, 1, 0, 0,
            // 0, 1, 2, 0, 0, 0,
            // 0, 1, 5, 0, 0, 0, 0,
            // 0, 1, 10, 1, 0, 0, 0, 0,
            // 0, 1, 21, 3, 0, 0, 0, 0, 0,
            // 0, 1, 42, 9, 0, 0, 0, 0, 0, 0,
            // 0, 1, 87, 25, 0, 0, 0, 0, 0, 0, 0,
            // 0, 1, 178, 66, 2, 0, 0, 0, 0, 0, 0, 0,
            // 0, 1, 371, 170, 6, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 1, 773, 431, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//        case 51:  // min branching number (out-degree) of internal nodes: (trivial, always==1)
//            s = T.min_branching_number();
//            break;

        case 60:  // number of leaves: A055327
            s = T.num_leaves();
            // columns: A002620, A055328, ..., A055333
            break;
            // 0, 1,
            // 0, 1, 0,
            // 0, 1, 0, 0,
            // 0, 1, 1, 0, 0,
            // 0, 1, 2, 0, 0, 0,
            // 0, 1, 4, 1, 0, 0, 0,
            // 0, 1, 6, 5, 0, 0, 0, 0,
            // 0, 1, 9, 13, 2, 0, 0, 0, 0,
            // 0, 1, 12, 28, 11, 0, 0, 0, 0, 0,
            // 0, 1, 16, 53, 40, 3, 0, 0, 0, 0, 0,
            // 0, 1, 20, 91, 109, 26, 0, 0, 0, 0, 0, 0,
            // 0, 1, 25, 146, 254, 116, 6, 0, 0, 0, 0, 0, 0,
            // 0, 1, 30, 223, 524, 387, 61, 0, 0, 0, 0, 0, 0, 0,


        default:
            cerr << "Invalid choice (exiting)." << endl;
            return 1;
        }

//        cout << " :: s = " << s << endl;

        jjassert( s < N );  // equality possible for n=0 and num_max_val()
        st[ s ] += 1;



#ifndef TIMING
        cout << setw(4) << ct << ":";

        // print RGS:
        T.print("  ");

//        T.print_branching_numbers("    ");


        cout << setw(4) << s;

        if ( aa )
        {
            cout << endl;
            T.print_aa("");
            cout << endl;
        }

        cout << endl;

//        jjassert( T.OK() );
#endif  // TIMING
    }
    while ( (j=T.next()) );


    ulong sct = 0;
    for (ulong k=0; k<N; ++k)
    {
        cout << st[k] << ", ";
        sct += st[k];
    }
    cout << endl;

    cout << " ct=" << ct;  // total: OEIS sequence A004111
    cout << endl;

    jjassert( sct == ct );

    delete [] st;

    return 0;
}
// -------------------------

/*

Print triangle for stats q:


OEIS example:
q=0; for n in $(seq 0 12) ; do ./bin $n $q | grep ', $' ; done | nl -v1 -s':  ' -w2 -n rz

C++ comment:
q=0;  for n in $(seq 0 12) ; do ./bin $n $q | grep ', $' ; done | sed 's/^/\/\/ /; s/ $//;'

Extract column c from stats q:
q=0;  c=0;  echo $(for n in $(seq 0 12) ; do ./bin $n $q | grep ', $' ; done | cut -d, -f$((c+1))) | sed 's/ /, /g;'

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/id-tree-lev-seq-stats-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/id-tree-lev-seq-stats-demo.cc DEMOFLAGS=-DTIMING"
/// End:
