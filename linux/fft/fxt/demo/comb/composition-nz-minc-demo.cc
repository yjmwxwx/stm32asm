
#include "comb/composition-nz-minc.h"

#include "comb/comb-print.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts with first part c and
//%   each part <= f times its predecessor.
//% For c=1 the same as: f-ary Huffman codes (canonical trees) with
//%   (f-1)*n+1 terminal nodes, a[k] is the number of internal nodes of depth k.
//% Such compositions (for f=2) are treated in
//%   Henryk Minc: "A Problem in Partitions: Enumeration of Elements of a
//%     given Degree in the free commutative entropic cyclic Groupoid",
//%   Proceedings of the Edinburgh Mathematical Society (2),
//%   vol.11, no.4, pp.223-224, (November-1959).
//% The compositions for f=2 are also called "Cayley compositions", see
//%   George E. Andrews, Peter Paule, Axel Riese, Volker Strehl:
//%   "MacMahon's Partition Analysis V: Bijections, Recursions, and Magic Squares",
//%   in: Algebraic Combinatorics and Applications, proceedings of Euroconference Alcoma 99,
//%   September 12-19, 1999, Goessweinstein, Germany,
//%   A. Betten, A. Kohnert, R. Laue, A. Wassermann eds., Springer-Verlag, pp.1-39, (2001).
//% See also:
//%   Christian Elsholtz, Clemens Heuberger, Helmut Prodinger:
//%   "The number of Huffman codes, compact trees, and sums of unit fractions",
//%   arXiv:1108.5964 [math.CO], (30-August-2011).
//%
//% Cf. OEIS sequences:
//% f=2:  A002572 (c=1), A002573 (c=2), A002574 (c=3),
//%       A049284 (c=4), A049285 (c=5).
//% c=1:  A002572 (f=2), A176485 (f=3), A176503 (f=4),
//%       A194628 (f=5), A194629 (f=6), A194630 (f=7),
//%       A194631 (f=8), A194632 (f=9), A194633 (f=10).



// Cf. comb/binary-huffman-demo.cc for partitions of 1 into n powers of 1/2
// Cf. comb/composition-nz-demo.cc for all compositions

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 9;
    NXARG(n, "compositions of n");
    ulong c = 1;
    NXARG(c, "first part");
    ulong f = 2;
    NXARG(f, "max. ratio of consecutive parts");

    composition_nz_minc P(n, c, f);

    ulong ct = 0;

#ifdef TIMING
    P.first();
    do  { ++ct; }  while ( P.next() );

#else  // TIMING

    ulong m = P.num_parts();
    do
    {
//        cout << "[" << setw(2) << ct << "]";

        cout << setw(4) << ct << ":";
        ++ct;


//        cout << "  [" << setw(2) << m << "]";

        P.print_unit_partition("    ", true);

        P.print("  ");

        cout << endl;

        jjassert( P.OK() );
    }
    while ( (m=P.next()) );
#endif  // TIMING

    ct -= ( c > n );
    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)


 time ./bin 38 1 2
arg 1: 38 == n  [compositions of n]  default=9
arg 2: 1 == c  [first part]  default=1
arg 3: 2 == f  [max. ratio of consecutive parts]  default=2
 ct=1127987211
./bin 38 1 2  4.56s user 0.00s system 99% cpu 4.564 total
 ==> 1127987211/4.56 == 247,365,616 per second


// Timing with f==2 hard-coded:
 time ./bin 40 1
arg 1: 40 == n  [compositions of n]  default=7
arg 2: 1 == c  [first part]  default=1
 ct=3630948907
./bin 40 1  14.11s user 0.00s system 99% cpu 14.119 total
 ==> 3630948907/14.11 == 257,331,602 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-minc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-minc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

