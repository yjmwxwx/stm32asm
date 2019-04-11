
// demo-is-self-contained

#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

//% Generate pre-necklaces as described by Cattell, Ruskey, Sawada, Miers, Serra.
//% Recursive CAT algorithm.

ulong *f;  // data in f[1..N],  f[0] = 0
ulong N;  // word length
ulong K;  // K-ary

ulong pct;  // count pre-necklaces

//#define TIMING  // uncomment to disable printing

#ifdef TIMING
void
visit(ulong)
{
    ++pct;
}
#else  // TIMING
void
visit(ulong j)
{
    ++pct;
    cout << setw(4) << pct << ":";
    print_vec("  ", f+1, N, true);
    cout << "   j=" << j;
    if ( N%j==0 )  cout << "  N";
    if ( N==j )  cout << "  L";
    cout << endl;
}
// -------------------------
#endif  // TIMING

void crsms_gen(ulong n, ulong j)
{
    if ( n > N )  visit(j);  // pre-necklace in f[1,...,N]
    else
    {
        f[n] = f[n-j];
        crsms_gen(n+1, j);

        for (ulong i=f[n-j]+1; i<K; ++i)
        {
            f[n] = i;
            crsms_gen(n+1, n);
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    N = 6;
    NXARG(N, "Length of necklaces (n>=1)");
    K = 2;
    NXARG(K, "Number of different beads (k>=2)");

    f = new ulong[N+1];
    for (ulong i=0; i<=N; ++i)  f[i] = 0;
    pct = 0;
    crsms_gen(1, 1);
    cout << "  # pre-necklaces=" << pct << endl;

    delete [] f;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 32 2
arg 1: 32 == N  [Length of necklaces (n>=1)]  default=6
arg 2: 2 == K  [Number of different beads (k>=2)]  default=2
  # pre-necklaces=277737797
./bin 32 2  3.89s user 0.02s system 99% cpu 3.909 total
 ==> 277737797/3.89 == 71,397,891 pre-necklaces per second

 time ./bin 21 3
  # pre-necklaces=766918996
./bin 21 3  7.66s user 0.04s system 99% cpu 7.707 total
 ==> 766918996/7.66 == 100,119,973 pre-necklaces per second

 time ./bin 15 5
bin 15 5  22.83s user 0.11s system 99% cpu 22.948 total
  # pre-necklaces=2590404239
 ==> 2590404239/22.83 == 113,464,925 pre-necklaces per second
*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32 2
  # pre-necklaces=277737797
./bin 32 2  2.63s user 0.00s system 99% cpu 2.629 total
 ==> 277737797/2.63 == 105,603,725 pre-necklaces per second

 time ./bin 21 3
  # pre-necklaces=766918996
./bin 21 3  5.15s user 0.00s system 99% cpu 5.150 total
 ==> 766918996/5.15 == 148,916,309 pre-necklaces per second

 time ./bin 15 5
  # pre-necklaces=2590404239
./bin 15 5  12.82s user 0.00s system 99% cpu 12.824 total
 ==> 2590404239/12.82 == 202,059,613 pre-necklaces per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/necklace-cat-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/necklace-cat-demo.cc DEMOFLAGS=-DTIMING"
/// End:

