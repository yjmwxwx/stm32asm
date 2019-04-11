
#include "bits/bitlow.h"
#include "bits/bitsperlong.h"

#include "fxtio.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A278479:
//% Least k such that the 2-adic valuation of the k-th partition number is n.


//#define TIMING  // uncomment to disable printing

class triang_num
// OEIS sequence A001318 with signs:
// +1, +2, -5, -7, +12, +15, -22, -26, +35, +40,
{
private:
    ulong t;
    ulong n;
    bool ps;
    ulong eo(ulong y)  const
    // A026741: a(n) = n if n odd, n/2 if n even.
    { return y >> ( (y & 1)==0); }
public:
    triang_num()
    {
        t = 0;
        n = 0;
        ps = false;
        next();
    }

    bool pos()  const  { return ps; }

    ulong next()
    {
        // a(n+1) = a(n) + A026741(n)
        t += eo(n);
        if ( n & 1 )  ps = ! ps;
        n += 1;
        return t;
    }
};
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 1000;
    NXARG(n, "Compute partition numbers (modulo BITS_PER_LONG) up to n");
    ulong * P = new ulong[n];

#if 0
    { triang_num T;
        for (ulong j=0; j<n; ++j)
        {
            ulong t = T.next();
            cout << ( T.pos() ? '+' : '-' ) << t << ", ";
        }
        cout << endl;
//        return 0;
    }
#endif

#if 0  // slow computation:
    for (ulong j = 0; j<n; ++j)  P[j] = 1;
    for (ulong d = 2; d<n; ++d)
        for (ulong j = d; j<n; ++j)
            P[j] += P[j-d];

#else  // fast computation:
    P[0] = 1;
    for (ulong j = 1; j<n; ++j)
    {
        /*
          p(0) = 1 and, for n >= 1,
          p(n) = + p(n-1) + p(n-2) - p(n-5) - p(n-7) + p(n-12) + p(n-15) --++...
         */

//        cout << " j = " << j << ":  ..." << endl;
        triang_num T;
        ulong t = T.next();
        ulong s = 0;
        while ( t <= j )
        {
//            cout << ( T.pos() ? '+' : '-' ) << t << ", ";
            ulong r = P[j-t];
            if ( T.pos() )  s += r;  else  s -= r;
            t = T.next();
        }
//        cout << endl;
//        cout << " j = " << j << ":  s = " << s << endl;
        P[j] = s;
    }
#endif
//    for (ulong j = 0; j<n; ++j)  cout << P[j] << ", ";
//    cout << endl;
//    return 0;

    ulong N = BITS_PER_LONG;
    ulong Z[N];
    for (ulong j = 0; j<N; ++j)  Z[j] = 0;
    for (ulong j = 0; j<n; ++j)
    {
        const ulong i = lowest_one_idx(P[j]);
        if ( Z[i] == 0 )  Z[i] = j;
    }

    while ( Z[N-1]==0 )  { N-=1; }  // omit trailing zeros

    Z[0] = 0;
    for (ulong j = 0; j<N; ++j)  cout << Z[j] << ", ";
    cout << endl;

    delete [] P;
    return 0;
}
// -------------------------

/*
Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)

GCC 4.9.2:

## slow computation:
 time ./bin 1000000
./bin 1000000  365.21s user 0.18s system 99% cpu 6:05.79 total

## fast computation:
 time ./bin 1000000
./bin 1000000  4.86s user 0.00s system 99% cpu 4.871 total

 time ./bin 1000000000
arg 1: 1000000000 == n  [Compute partition numbers (modulo BITS_PER_LONG) up to n]  default=1000
0, 2, 26, 11, 15, 70, 66, 109, 154, 478, 441, 96, 3693, 15005, 66934, 99420, 18978, 43002, 55943, 972190, 1151214, 2799146, 26801784, 46632889, 15519397, 122101417, 210553237, 289585489, 473093534, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
./bin 1000000000  612092.43s user 270.32s system 99% cpu 170:16:46.41 total

// In the following the memory consumption under 'RES' indicates progress:
  PID USER      PRI  NI  VIRT   RES   SHR S CPU% MEM%   TIME+  Command
 4897 jj         20   0 7641M 22648  2264 R 99.8  0.1  0:32.54 ./bin 1000000000
 4897 jj         20   0 7641M  987M  2264 R 99.9  3.1  5h22:53 ./bin 1000000000
 4897 jj         20   0 7641M 2069M  2264 R 100.  6.4 17h21:49 ./bin 1000000000
 4897 jj         20   0 7641M 2539M  2264 R 99.9  7.9 24h09:24 ./bin 1000000000
 4897 jj         20   0 7641M 3504M  2264 R 100. 10.9 41h19:32 ./bin 1000000000
 4897 jj         20   0 7641M 4042M  2264 R 99.6 12.6 52h51:35 ./bin 1000000000
 4897 jj         20   0 7641M 4616M  2264 R 99.8 14.4 66h47:56 ./bin 1000000000
 4897 jj         20   0 7641M 5537M  2264 R 99.8 17.2 93h27:59 ./bin 1000000000
 4897 jj         20   0 7641M 5744M  2264 R 99.8 17.9     100h ./bin 1000000000
 4897 jj         20   0 7641M 6181M  2264 R 99.6 19.2     115h ./bin 1000000000
 4897 jj         20   0 7641M 6883M  2264 R 99.7 21.4     142h ./bin 1000000000
 4897 jj         20   0 7641M 7041M  2264 R 99.8 21.9     149h ./bin 1000000000
 4897 jj         20   0 7641M 7358M  2264 R 99.9 22.9     161h ./bin 1000000000
 4897 jj         20   0 7641M 7501M  2264 R 99.9 23.3     165h ./bin 1000000000

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A278479-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A278479-demo.cc DEMOFLAGS=-DTIMING"
/// End:
