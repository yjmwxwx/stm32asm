
#include "perm/perminvert.h"  // make_inverse_notag()

#include "perm/permrand.h"
//#include "perm/permq.h"

#include "comb/comb-print.h"  // print_perm()

#include "ds/bitarray.h"
#include "bits/bitsperlong.h"

#include "fxttypes.h"
#include "jjassert.h"
#include "nextarg.h"


//% Inversion of a permutation without extra tag bits.


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Array size = 2**n");
    ulong N = 1UL<<n;
//    NXARG(N, "Array size");

    ulong *f = new ulong[N];

#ifdef TIMING
    ulong r = 10;
    NXARG(r, "Number of repetitions(for timing)");
    bool ntq = false;
    NXARG(ntq, "Whether to use the tag-less version");
    for (ulong k=0; k<N; ++k)  f[k] = k^(k>>1);  // gray code
//    for (ulong k=0; k<N; ++k)  f[k] = N-1-k;  // reverse

    if ( ntq )
    {
        for (ulong j=0; j<r; ++j)  make_inverse_notag(f, N);
    }
    else
    {
        bitarray *bp = new bitarray(N);
        for (ulong j=0; j<r; ++j)  make_inverse(f, N, bp);
        delete bp;
    }
#else

    for (ulong k=0; k<N; ++k)  f[k] = k;
    random_permute(f, N);

    print_perm("Permutation:\n", f, N);
    cout << endl;

    ulong *g = new ulong[N];
    for (ulong k=0; k<N; ++k)  g[k] = f[k];

//    jjassert( is_valid_permutation(f, N) );
//    jjassert( is_valid_permutation(g, N) );

    bitarray *bp = new bitarray(N);
    make_inverse(f, N, bp);
    make_inverse(g, N);

    print_perm("Inverse:\n", g, N);
    cout << endl;

    for (ulong k=0; k<N; ++k)  jjassert( g[k] == f[k] );

    delete [] f;
    delete [] g;
    delete bp;
#endif

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 26 4
arg 1: 26 == n  [Array size = 2**n]  default=3
arg 2: 4 == r  [Number of repetitions(for timing)]  default=10
identity:
./bin 26 4  3.01s user 0.08s system 99% cpu 3.090 total  // bitarray version
./bin 26 4  2.71s user 0.55s system 99% cpu 3.279 total  // tag-bit version

gray:
./bin 26 4  4.97s user 0.44s system 99% cpu 5.408 total  // bitarray version
./bin 26 4  4.61s user 0.42s system 99% cpu 5.029 total  // tag-bit version

reverse:
./bin 26 4  2.80s user 0.41s system 99% cpu 3.213 total  // bitarray version
./bin 26 4  3.08s user 0.41s system 100% cpu 3.491 total  // tag-bit version

revbin_permute:
./bin 26 4  41.49s user 0.60s system 99% cpu 42.110 total  // bitarray version
./bin 26 4  28.05s user 0.56s system 99% cpu 28.626 total  // tag-bit version

% time ./bin 16 2000
revbin_permute:
./bin 16 2000  2.83s user 0.00s system 99% cpu 2.839 total  // bitarray version
./bin 16 2000  3.14s user 0.03s system 99% cpu 3.171 total  // tag-bit version

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

%  time ./bin 24 10 0  ## bitarray version
arg 1: 24 == n  [Array size = 2**n]  default=4
arg 2: 10 == r  [Number of repetitions(for timing)]  default=10
arg 3: 0 == ntq  [Whether to use the tag-less version]  default=0
./bin 24 10 0  2.04s user 0.04s system 99% cpu 2.085 total

%  time ./bin 24 10 1  ## tag-bit version
arg 1: 24 == n  [Array size = 2**n]  default=4
arg 2: 10 == r  [Number of repetitions(for timing)]  default=10
arg 3: 1 == ntq  [Whether to use the tag-less version]  default=0
./bin 24 10 1  1.94s user 0.04s system 99% cpu 1.984 total

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/perm-invert-notag-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/perm-invert-notag-demo.cc DEMOFLAGS=-DTIMING"
/// End:
