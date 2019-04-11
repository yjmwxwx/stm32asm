
#include "comb/partition-dist-asc.h"
#include "comb/word-stats.h"


#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"

//% Statistics for partitions into distinct parts (as ascending lists of parts).
//% Cf. the following OEIS sequences:
//% A026836, A026821, A060016, A116679, and A116675

// Cf. comb/partition-dist-asc-demo.cc

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 15;
    NXARG(n, "Partitions of n");

    ulong sq = 0;
    NXARG(sq, "Select stats:\n"
          "     0 ==> by largest part\n"
          "     1 ==> by smallest part\n"
//          "     3 ==> by number of largest parts\n"
//          "     4 ==> by number of smallest parts\n"
          "     5 ==> by number of ones\n"
          "    10 ==> by number of ascents\n"
//          "    11 ==> by number of descents\n"
//          "    30 ==> position of last one\n"
//          "    31 ==> position of first one\n"
//          "    40 ==> position of first occurrence of largest part\n"
//          "    41 ==> position of last occurrence of largest part\n"
//          "    42 ==> position of first occurrence of smallest part\n"
          "    43 ==> position of last occurrence of smallest part\n"
          "    50 ==> number of even values\n"
          "    51 ==> number of odd values\n"
//          "    60 ==> by number of fixed points (offset 0)\n"
          "    61 ==> by number of fixed points (offset 1)\n"
//          "    70 ==> number of flat steps\n"
//          "    71 ==> number of non-flat steps\n"
          "    80 ==> max ascent\n"
          "    81 ==> min ascent\n"
//          "    82 ==> max descent\n"
          );

    partition_dist_asc P(n);
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
        case 0:  // value of largest part: A026836
            s = W.max_val();
            break;
            // 1,
            // 0, 1,
            // 0, 0, 1,
            // 0, 0, 1, 1,
            // 0, 0, 0, 1, 1,
            // 0, 0, 0, 1, 1, 1,
            // 0, 0, 0, 1, 1, 1, 1,
            // 0, 0, 0, 0, 2, 1, 1, 1,
            // 0, 0, 0, 0, 1, 2, 1, 1, 1,
            // 0, 0, 0, 0, 1, 2, 2, 1, 1, 1,
            // 0, 0, 0, 0, 1, 2, 2, 2, 1, 1, 1,
            // 0, 0, 0, 0, 0, 2, 3, 2, 2, 1, 1, 1,
            // 0, 0, 0, 0, 0, 2, 3, 3, 2, 2, 1, 1, 1,
            // 0, 0, 0, 0, 0, 1, 3, 4, 3, 2, 2, 1, 1, 1,
            // 0, 0, 0, 0, 0, 1, 3, 4, 4, 3, 2, 2, 1, 1, 1,
            // 0, 0, 0, 0, 0, 1, 3, 4, 5, 4, 3, 2, 2, 1, 1, 1,

        case 1:  // value of smallest part: A026821
            s = W.min_val();
            break;
            // 1,
            // 0, 1,
            // 0, 0, 1,
            // 0, 1, 0, 1,
            // 0, 1, 0, 0, 1,
            // 0, 1, 1, 0, 0, 1,
            // 0, 2, 1, 0, 0, 0, 1,
            // 0, 2, 1, 1, 0, 0, 0, 1,
            // 0, 3, 1, 1, 0, 0, 0, 0, 1,
            // 0, 3, 2, 1, 1, 0, 0, 0, 0, 1,
            // 0, 5, 2, 1, 1, 0, 0, 0, 0, 0, 1,
            // 0, 5, 3, 1, 1, 1, 0, 0, 0, 0, 0, 1,
            // 0, 7, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 1,
            // 0, 8, 4, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
            // 0, 10, 5, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
            // 0, 12, 6, 3, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,


//        case 3:  // number of largest parts:
//            s = W.num_max_val();
//            break;
//
//        case 4:  // number of smallest parts:
//            s = W.num_min_val();
//            break;

        case 5:  // number of ones:
            s = W.num_val(1);
            break;
            // 1,
            // 0, 1,
            // 1, 0, 0,
            // 1, 1, 0, 0,
            // 1, 1, 0, 0, 0,
            // 2, 1, 0, 0, 0, 0,
            // 2, 2, 0, 0, 0, 0, 0,
            // 3, 2, 0, 0, 0, 0, 0, 0,
            // 3, 3, 0, 0, 0, 0, 0, 0, 0,
            // 5, 3, 0, 0, 0, 0, 0, 0, 0, 0,
            // 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 10, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 12, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

        case 10:  // number of ascents (==num parts): A060016, A008289 (tabf)
            s = W.num_ascents();
            break;
            // 1,
            // 1, 0,
            // 1, 0, 0,
            // 1, 1, 0, 0,
            // 1, 1, 0, 0, 0,
            // 1, 2, 0, 0, 0, 0,
            // 1, 2, 1, 0, 0, 0, 0,
            // 1, 3, 1, 0, 0, 0, 0, 0,
            // 1, 3, 2, 0, 0, 0, 0, 0, 0,
            // 1, 4, 3, 0, 0, 0, 0, 0, 0, 0,
            // 1, 4, 4, 1, 0, 0, 0, 0, 0, 0, 0,
            // 1, 5, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0,
            // 1, 5, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 1, 6, 8, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 1, 6, 10, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 1, 7, 12, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

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

//        case 40:  // position of first occurrence of largest part: same as num ascents
//            s = W.first_max_idx();
//            break;

//        case 41:  // position of last occurrence of largest part:
//            s = W.last_max_idx();
//            break;

//        case 42:  // position of first occurrence of smallest part:
//            s = W.first_min_idx();
//            break;

//        case 43:  // position of last occurrence of smallest part:
//            s = W.last_min_idx();
//            break;

        case 50:  // number of even values: A116679
            // cf. A116680
            s = W.num_even_val();
            break;
            // 1,
            // 1, 0,
            // 0, 1, 0,
            // 1, 1, 0, 0,
            // 1, 1, 0, 0, 0,
            // 1, 2, 0, 0, 0, 0,
            // 1, 2, 1, 0, 0, 0, 0,
            // 1, 3, 1, 0, 0, 0, 0, 0,
            // 2, 3, 1, 0, 0, 0, 0, 0, 0,
            // 2, 4, 2, 0, 0, 0, 0, 0, 0, 0,
            // 2, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0,
            // 2, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 3, 7, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 3, 8, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 3, 10, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 4, 11, 10, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

        case 51:  // number of odd values: A116675
            // cf. A116676
            s = W.num_odd_val();
            break;
            // 1,
            // 0, 1,
            // 1, 0, 0,
            // 0, 2, 0, 0,
            // 1, 0, 1, 0, 0,
            // 0, 3, 0, 0, 0, 0,
            // 2, 0, 2, 0, 0, 0, 0,
            // 0, 5, 0, 0, 0, 0, 0, 0,
            // 2, 0, 4, 0, 0, 0, 0, 0, 0,
            // 0, 7, 0, 1, 0, 0, 0, 0, 0, 0,
            // 3, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 10, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
            // 4, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 14, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 5, 0, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 19, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,


//        case 60:  // by number of fixed points (offset 0):
//            s = W.num_fixed_points();
//            break;

        case 61:  // by number of fixed points (offset 1): A000000
            s = W.num_fixed_points_1();
            // column k=0: A025147 partitions into distinct parts >= 2.
            break;
            // 1,
            // 0, 1,
            // 1, 0, 0,
            // 1, 0, 1, 0,
            // 1, 1, 0, 0, 0,
            // 2, 1, 0, 0, 0, 0,
            // 2, 1, 0, 1, 0, 0, 0,
            // 3, 1, 1, 0, 0, 0, 0, 0,
            // 3, 2, 1, 0, 0, 0, 0, 0, 0,
            // 5, 2, 1, 0, 0, 0, 0, 0, 0, 0,
            // 5, 3, 1, 0, 1, 0, 0, 0, 0, 0, 0,
            // 7, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
            // 8, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 10, 5, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 12, 6, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 15, 7, 3, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

//        case 70:  // number of flat steps:
//            s = W.num_flat_steps();
//            break;
//
//        case 71:  // number of non-flat steps:
//            s = W.num_nonflat_steps();
//            break;

        case 80:  // max ascent: A000000
            s = W.max_ascent();
            // reversed rows --> A087897  partitions into odd parts >= 1.
            break;
            // 1,
            // 1, 0,
            // 1, 0, 0,
            // 1, 1, 0, 0,
            // 1, 0, 1, 0, 0,
            // 1, 1, 0, 1, 0, 0,
            // 1, 1, 1, 0, 1, 0, 0,
            // 1, 1, 1, 1, 0, 1, 0, 0,
            // 1, 0, 2, 1, 1, 0, 1, 0, 0,
            // 1, 2, 1, 1, 1, 1, 0, 1, 0, 0,
            // 1, 1, 2, 2, 1, 1, 1, 0, 1, 0, 0,
            // 1, 1, 2, 3, 1, 1, 1, 1, 0, 1, 0, 0,
            // 1, 1, 3, 2, 3, 1, 1, 1, 1, 0, 1, 0, 0,
            // 1, 1, 3, 3, 3, 2, 1, 1, 1, 1, 0, 1, 0, 0,
            // 1, 1, 3, 4, 3, 3, 2, 1, 1, 1, 1, 0, 1, 0, 0,
            // 1, 3, 3, 4, 4, 3, 2, 2, 1, 1, 1, 1, 0, 1, 0, 0,

        case 81:  // min ascent: A000000
            s = W.min_ascent();
            break;
            // 1,
            // 1, 0,
            // 1, 0, 0,
            // 1, 1, 0, 0,
            // 1, 0, 1, 0, 0,
            // 1, 1, 0, 1, 0, 0,
            // 1, 1, 1, 0, 1, 0, 0,
            // 1, 2, 0, 1, 0, 1, 0, 0,
            // 1, 2, 1, 0, 1, 0, 1, 0, 0,
            // 1, 3, 1, 1, 0, 1, 0, 1, 0, 0,
            // 1, 4, 2, 0, 1, 0, 1, 0, 1, 0, 0,
            // 1, 5, 2, 1, 0, 1, 0, 1, 0, 1, 0, 0,
            // 1, 6, 3, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0,
            // 1, 8, 3, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0,
            // 1, 10, 4, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0,
            // 1, 13, 4, 3, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0,

//        case 82:  // max descent:
//            s = W.max_descent();
//            break;


        case 90: // test
            s = m;  // number of parts: A060016, A008289 (tabf)
            // cf. A091492
            break;
            // 1,
            // 0, 1,
            // 0, 1, 0,
            // 0, 1, 1, 0,
            // 0, 1, 1, 0, 0,
            // 0, 1, 2, 0, 0, 0,
            // 0, 1, 2, 1, 0, 0, 0,
            // 0, 1, 3, 1, 0, 0, 0, 0,
            // 0, 1, 3, 2, 0, 0, 0, 0, 0,
            // 0, 1, 4, 3, 0, 0, 0, 0, 0, 0,
            // 0, 1, 4, 4, 1, 0, 0, 0, 0, 0, 0,
            // 0, 1, 5, 5, 1, 0, 0, 0, 0, 0, 0, 0,
            // 0, 1, 5, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 1, 6, 8, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 1, 6, 10, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            // 0, 1, 7, 12, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

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

    cout << " ct=" << ct;  // total: OEIS sequence A000009
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
/// make-target: "1demo DSRC=demo/comb/partition-dist-asc-stats-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-dist-asc-stats-demo.cc DEMOFLAGS=-DTIMING"
/// End:
