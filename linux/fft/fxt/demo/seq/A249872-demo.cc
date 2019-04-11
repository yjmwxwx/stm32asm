
#include "ds/array2d.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A249872:
//% Number of iterations to reach a final state for an n X n lattice of sand piles on a torus.


//#define TIMING  // uncomment to disable printing


template <typename Type>
void print(const array2d<Type> &A)
{
    const ulong nr = A.num_rows();
    const ulong nc = A.num_cols();
    for (ulong r=0; r<nr; ++r)
    {
        for (ulong c=0; c<nc; ++c)
        {
            cout << " " << A[r][c];
        }
        cout << endl;
    }
    cout << endl;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong nr = 3;
    NXARG(nr, "Number of rows (nr>=1)");
    jjassert( nr >= 1 );

    ulong nc = nr;
    NXARG(nr, "Number of columns (nc>=1)");
    jjassert( nc >= 1 );

    array2d<ulong> A(nr, nc);
    A.fill( 4 );

    ulong nscan = 0;  // count full scans until no cell has entry >= 4
    ulong ct = 0;  // count steps until no cell has entry >= 4
    while ( true )
    {
        A[0][0] = 0;  // empty the sink

#ifndef TIMING
//        cout << nscan << ":" << endl;
//        print( A );  // output only every scan
#endif  // TIMING

        bool ge4 = false;  // any cell >= 4 ?
        for (ulong r=0; r<nr; ++r)
        {
            for (ulong c=0; c<nc; ++c)
            {
                ulong z = A[r][c];
                if ( z >= 4 )
                {
                    ++ct;
                    ge4 = true;
                    A[r][c] = z - 4;
                    A[ (r==0 ? nr-1 : r-1) ][ c ] += 1;
                    A[ (r+1==nr ? 0 : r+1) ][ c ] += 1;
                    A[ r ][ (c==0 ? nc-1 : c-1) ] += 1;
                    A[ r ][ (c+1==nc ? 0 : c+1) ] += 1;
#ifndef TIMING
                    cout << ct << ":" << endl;
                    print( A );
#endif  // TIMING
                }
            }
        }

        if ( ! ge4 )  break;
        nscan += 1;
    }

    cout << " nscan=" << nscan << endl;
    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

// echo $(for n in $(seq 1 20); do ./bin $n; done | grep ct= ) | sed 's/ ct=/, /g;'
// for n in $(seq 1 50); do ./bin $n | grep -F 'nscan=' ;  done
// time ( for n in $(seq 1 1000); do ./binxx $n | grep -F 'ct=' ; done > tt-A249872.txt; )

/*
Timing:  (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)
GCC 4.9.2:

 time ./bin 100
arg 1: 100 == nr  [Number of rows (nr>=1)]  default=3
arg 2: 100 == nr  [Number of columns (nc>=1)]  default=100
 ct=136104469
./bin 100  0.78s user 0.00s system 99% cpu 0.780 total

 time ./bin 120
arg 1: 120 == nr  [Number of rows (nr>=1)]  default=3
arg 2: 120 == nr  [Number of columns (nc>=1)]  default=120
 ct=290080235
./bin 120  1.61s user 0.00s system 99% cpu 1.617 total

 time ./bin 150
arg 1: 150 == nr  [Number of rows (nr>=1)]  default=3
arg 2: 150 == nr  [Number of columns (nc>=1)]  default=150
 ct=735211013
./bin 150  4.06s user 0.00s system 99% cpu 4.069 total

 time ./bin 200
arg 1: 200 == nr  [Number of rows (nr>=1)]  default=3
arg 2: 200 == nr  [Number of columns (nc>=1)]  default=200
 ct=2423042301
./bin 200  12.86s user 0.01s system 99% cpu 12.880 total

All n <= 607:
144144.16s user 39.99s system 99% cpu 40:07:12.62 total

 time ./bin 256
arg 1: 256 == nr  [Number of rows (nr>=1)]  default=3
arg 2: 256 == nr  [Number of columns (nc>=1)]  default=256
 nscan=154735
 ct=6773804435
./bin 256  35.15s user 0.00s system 99% cpu 35.188 total


 time ./bin 1024
arg 1: 1024 == nr  [Number of rows (nr>=1)]  default=3
arg 2: 1024 == nr  [Number of columns (nc>=1)]  default=1024
 nscan=2645270
 ct=2091045956715
./bin 1024  11307.75s user 4.62s system 99% cpu 3:08:44.25 total

 */

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A249872-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A249872-demo.cc DEMOFLAGS=-DTIMING"
/// End:

