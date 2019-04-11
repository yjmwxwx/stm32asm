
#include "bits/bitcount.h"
// demo-include "bits/bitcount-v.cc"

#include "bits/print-bin.h"
#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

#include "jjassert.h"

//% bit-count many words via vertical addition

ulong
bit_count_leq31(const ulong *x, ulong n)
// Return sum(j=0, n-1, bit_count(x[j]) )
// Must have  n<=31
{
    ulong a0=0, a1=0, a2=0, a3=0, a4=0;
    //       1,    3,    7,   15,   31,  <--= max n
    for (ulong k=0; k<n; ++k)
    {
        ulong cy = x[k];
        { ulong t = a0 & cy;  a0 ^= cy;  cy = t; }
        { ulong t = a1 & cy;  a1 ^= cy;  cy = t; }
        { ulong t = a2 & cy;  a2 ^= cy;  cy = t; }
        { ulong t = a3 & cy;  a3 ^= cy;  cy = t; }
        { a4 ^= cy; }

        cout << "x[" << setw(2) << k << "]=";
        print_bin("", x[k], 8);
        print_bin("  a0=", a0, 8);
        print_bin("  a1=", a1, 8);
        print_bin("  a2=", a2, 8);
        print_bin("  a3=", a3, 8);
        print_bin("  a4=", a4, 8);
        cout << endl;
    }
    ulong b = bit_count(a0);
    b += (bit_count(a1)<<1);
    b += (bit_count(a2)<<2);
    b += (bit_count(a3)<<3);
    b += (bit_count(a4)<<4);
    return  b;
}
// -------------------------

ulong
bit_count_v2(const ulong *x, ulong n)
// Return sum(j=0, n-1, bit_count(x[j]) )
{
    ulong b = 0;
    for (ulong k=0; k<n; ++k)  b += bit_count(x[k]);
    return  b;
}
// -------------------------


//#define TEST

int
#ifdef TEST
main(int argc, char **argv)
#else  // TEST
main()
#endif  // TEST
{
    ulong n = 17;
#ifdef TEST
    NXARG(n, "Number of words n");
#endif  // TEST

    ulong *x = new ulong[n];
    for (ulong k=0; k<n; ++k)  x[k] = ~0UL;  // all ones
//    for (ulong k=0; k<n; ++k)  x[k] = k;


#ifdef TEST

    cout << "start" << endl;
    ulong ct = bit_count_v(x, n);    cout << "ct=" << ct << endl;
    ulong ct2 = bit_count_v2(x, n);  cout << "ct2=" << ct2 << endl;
    jjassert( ct==ct2 );

#else  // TEST

    bit_count_leq31(x, n);

#endif  // TEST

    delete [] x;

    return 0;
}
// -------------------------

/*
Profiling: (define TEST and compile with profiling options)

time ./bin 100000000
arg 1: 100000000 == n  [Number of words n]  default=16
start
ct=6400000000
ct2=6400000000
./bin 100000000  1.73s user 0.86s system 97% cpu 2.665 total

  %      self
 time     seconds     name
 18.81     0.46       bit_count_v2(ulong const*, ulong)
 13.09     0.32       bit_count_v(ulong const*, ulong)

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/bitcount-v-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/bitcount-v-demo.cc DEMOFLAGS=-DTIMING"
/// End:
