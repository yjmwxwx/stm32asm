
#include "comb/ksubset-gray.h"

#include "comb/comb-print.h"  // print_deltaset_as_bitset()
#include "bits/bitset2set.h"  // set2bitset()
#include "bits/print-bin.h"

#include "fxtio.h"
#include "fxttypes.h"

#include "nextarg.h"  // NXARG()

#include "jjassert.h"

//% k-subsets (kmin<=k<=kmax) in minimal-change order

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    cout << "k-subsets of n,  kmin<=k<=kmax  in minimal-change order." << endl;
    ulong n = 5;
    NXARG(n, "size of set");
    ulong kmin = 2;
    NXARG(kmin, "Minimum of k,  kmin>=1");
    ulong kmax = 4;
    NXARG(kmax, "Maximum of k  (zero ==> kmax:=n)");
    if ( 0==kmax )  kmax = n;
    bool rq = 0;
    NXARG(rq, "Whether to generate subsets in reversed order");

    jjassert( kmin<=kmax );

    ksubset_gray S(n, kmin, kmax);

#ifndef TIMING

    const ulong *x = S.data();
    ulong num, idx = 0, q;
    if ( rq )  S.last();  else  S.first();
    ulong bo = 0;  // bitset
    do
    {
        num = S.num();
        ++idx;
        cout << setw(4) << idx << ":";
//        cout << "   #=" << num;
        S.print_deltaset("    ");
//        cout << "   j=" << S.j_;

        ulong b = set2bitset(x, num, 1);   // bitset
//        print_bin_vec("  ", b, n);
        if ( idx==1 )  bo = b;
        print_bin_vec_diff("    ", bo, b, n, "..PM");
        bo = b;

        S.print_set("    ");
        cout << endl;
        q = ( rq ? S.prev() : S.next() );
    }
    while ( q );
    cout << endl;
#else

    ulong ct = 0;
    if ( !rq )
    {
        cout << "forward:" << endl;
        S.last();   do { ++ct; }  while ( S.prev() );
    }
    else
    {
        cout << "backward:" << endl;
        S.first();  do { ++ct; }  while ( S.next() );
    }
    cout << " ct=" << ct << endl;

#endif  // TIMING

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 30 3 18 0
k-subsets of n,  kmin<=k<=kmax  in minimal-change order.
arg 1: 30 == n  [size of set]  default=5
arg 2: 3 == kmin  [Minimum of k,  kmin>=1]  default=2
arg 3: 18 == kmax  [Maximum of k  (zero ==> kmax:=n)]  default=4
arg 4: 0 == rq  [Whether to generate subsets in reversed order]  default=0
forward:
  ct = 966104956
./bin 30 3 18 0  6.41s user 0.04s system 100% cpu 6.448 total
 ==> 966104956/6.41 == 150,718,401 per second

 time ./bin 30 3 18 1
k-subsets of n,  kmin<=k<=kmax  in minimal-change order.
arg 1: 30 == n  [size of set]  default=5
arg 2: 3 == kmin  [Minimum of k,  kmin>=1]  default=2
arg 3: 18 == kmax  [Maximum of k  (zero ==> kmax:=n)]  default=4
arg 4: 1 == rq  [Whether to generate subsets in reversed order]  default=0
backward:
  ct = 966104956
./bin 30 3 18 1  7.38s user 0.04s system 99% cpu 7.425 total
 ==> 966104956/7.38 == 130,908,530 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 3 18 0
k-subsets of n,  kmin<=k<=kmax  in minimal-change order.
arg 1: 30 == n  [size of set]  default=5
arg 2: 3 == kmin  [Minimum of k,  kmin>=1]  default=2
arg 3: 18 == kmax  [Maximum of k  (zero ==> kmax:=n)]  default=4
arg 4: 0 == rq  [Whether to generate subsets in reversed order]  default=0
forward:
  ct = 966104956
./bin 30 3 18 0  4.04s user 0.00s system 99% cpu 4.040 total
 ==> 966104956/4.04 == 239,134,890 per second

 time ./bin 30 3 18 1
k-subsets of n,  kmin<=k<=kmax  in minimal-change order.
arg 1: 30 == n  [size of set]  default=5
arg 2: 3 == kmin  [Minimum of k,  kmin>=1]  default=2
arg 3: 18 == kmax  [Maximum of k  (zero ==> kmax:=n)]  default=4
arg 4: 1 == rq  [Whether to generate subsets in reversed order]  default=0
backward:
  ct = 966104956
./bin 30 3 18 1  4.83s user 0.00s system 99% cpu 4.835 total
 ==> 966104956/4.83 == 200,021,730 per second

 */

 /*
BENCHARGS=30 3 18 0
BENCHARGS=30 3 18 1

*/



/* *********************
// Original taken from T.A.Jenkyns: "Loopless Gray Code Algorithms":

//  Algorithm A4  //  to generate all k-subsets of {1..n}
//               //  where min    <    k    <    max  in a Gray code
BEGIN S[1]:=1;  k:=min;
    IF min=1 THEN j:=1
    ELSE FOR i:=2 TO min DO S[i]:=n-min+i END; j:=2
    END;

    Process( S[1],...,S[k] );

    WHILE S[1] < n-min+1 DO
        IF ((j MOD 2) > 0 THEN           // j is odd
            IF S[j] = n THEN j:=j-1
            ELSE IF j < max THEN  S[j+1]:=n;  j:=j+1
                ELSE S[j]:=S[j]+1;
                    IF S[min]=n THEN j:=j-1 END
                END
            END
        ELSE  // j is even
            IF S[j-1] = S[j]-1 THEN S[j-1]:= S[j];
                IF j > min THEN
                    IF S[min] = n THEN j:=j-2 ELSE j:=j-1 END
                ELSE S[j]:=n-min+j;
                    IF S[j-1]=S[j]-1 THEN j:=j-2 END
                END
            ELSE S[j]:=S[j]-1;
                IF j < max THEN S[j+1]:=S[j]+1;
                    IF j >= min-1 THEN j:=j+1 ELSE j:=j+2 END
                END
            END
        END;
        IF j<min THEN k:=min ELSE k:=j END;
        Process( S[1],...,S[k] )
    END
END  // Algorithm A4.

//This algorithm can be somewhat simplified when 1<min and/or min<max.

********************* */


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ksubset-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ksubset-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

