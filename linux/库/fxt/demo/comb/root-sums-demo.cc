
#include "comb/binary-necklace.h"

#include "nextarg.h"
#include "fxttypes.h"
#include "complextype.h"

#include "fxtio.h"

//% Zero-sums of roots of unity.


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 12;
    NXARG(n, "n-th roots of unity");

    binary_necklace N(n);

    Complex *R = new Complex[n];  // roots of unity
    const double ph = 2.0 * M_PI / (double)n;
    for (ulong k=0; k<n; ++k)  R[k] = Complex( cos((double)k*ph), sin((double)k*ph) );
    // note: could use (complex) SinCos()
//    for (ulong k=0; k<n; ++k)  cout << " " << R[k];  cout << endl;


//#define MA
#ifdef MA
    double ma = (double)n;  // min abs(rs) not taken as zero
#endif
    ulong ct = 0;   // number of sums
    ulong act = 0;  // aperiodic sums
    ulong sj = 0;   // number of sums, regarding cyclic shifts as different
    ulong j = 1;
    const ulong *dn = N.data();
    do
    {
        Complex rs = 0;
        for (ulong k=0; k<n; ++k)  rs += ( dn[k] ? R[k] : 0 );

        const double as = abs(rs);
        if ( as < 1e-7 )  // note magic constant
        {  // could omit test with j<n
            sj += j;
            const bool aq = ( n==j );  // Lyndon word
            act += aq;
            ++ct;
#ifndef TIMING
            cout << setw(4) << ct << ":  ";
//            cout << n << ": ";
            for (ulong k=0; k<n; ++k)  cout << ( dn[k] ? '1' : '.' );
            cout << "  " << setw(2) << j;  // period
            cout << ( aq ? " L " : "   " );  // whether Lyndon word
            for (ulong k=0; k<n; ++k)  if ( dn[n-1-k] )  cout << " " << k;
//            for (ulong k=0; k<n; ++k)  if ( dn[n-1-k] )  cout << " +x^" << k;
            cout << endl;
#endif
        }
#ifdef MA
        else
        {
            if ( as < ma )
            {
                ma = as;
                for (ulong k=0; k<n; ++k)  cout << ( dn[k] ? '1' : '.' );
                cout << "  M ma=" << ma << endl;
            }
        }
#endif  // MA
    }
    while ( ( j=N.next() ) );

    cout << endl;

    cout << " ct=" << ct;
    cout << " act=" << act;
    cout << " sj=" << sj;
#ifdef MA
    cout << " ma=" << ma;
#endif
    cout << endl;


    delete [] R;
    return 0;
}
// -------------------------

/*


 for n in $(seq 1 30); do echo -n "$n: "; ./bin $n | g ct ; done | sed -u 's/act=//g; s/ct=//g; s/sj=//g;'
//  11.58s user 0.08s system 99% cpu 11.667 total

 for n in $(seq 1 63); do echo -n "$n: "; ./bin $n | g ct ; done | sed -u 's/act=//g; s/ct=//g; s/sj=//g;' | tee zsums-out.txt
 (stopped after n=39)

n:  ct act sj
1:  1 1 1
2:  2 0 2
3:  2 0 2
4:  3 0 4
5:  2 0 2
6:  5 0 10
7:  2 0 2
8:  6 0 16
9:  4 0 8
10:  9 0 34
11:  2 0 2
12:  19 2 100
13:  2 0 2
14:  21 0 130
15:  10 0 38
16:  36 0 256
17:  2 0 2
18:  94 24 1000
19:  2 0 2
20:  117 6 1156
21:  22 0 134
22:  189 0 2050
23:  2 0 2
24:  618 236 10000
25:  8 0 32
26:  633 0 8194
27:  60 0 512
28:  1203 18 16900
29:  2 0 2
30:  6069 3768 146854
31:  2 0 2
32:  4116 0 65536
33:  190 0 2054
34:  7713 0 131074
35:  26 0 158
36:  35324 20384 1000000
37:  2 0 2
38:  27597 0 524290
39:  634 0 8198

n:   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,  20, 21,  22, 23,  24, 25,  26, 27,   28, 29,   30
ct:  1, 2, 2, 3, 2, 5, 2, 6, 4,  9,  2, 19,  2, 21, 10, 36,  2, 94,  2, 117, 22, 189,  2, 618,  8, 633, 60, 1203,  2, 6069
act: 1, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  2,  0,  0,  0,  0,  0, 24,  0,   6,  0,   0,  0, 236,  0,   0,  0,   18,  0, 3768
sj:  1, 2, 2, 4, 2,10, 2,16, 8, 34,  2,100,  2,130, 38,256,  2,1000, 2,1156,134,2050,  2,10000,32,8194,512,16900,  2,146854

Corresponding OEIS sequences:
ct == A164896 a(n) = the number of subsets S of the n-th roots of 1 with zero sum (modulo cyclic shifts)
act== A110981 a(n) = the number of aperiodic subsets S of the n-th roots of 1 with zero sum
sj == A103314 Total number of subsets of the n-th roots of 1 that add to zero

act!=0 for n in A102467: neither prime powers nor semiprimes
 1, 12, 18, 20,  24, 28,  30,   36,    40,    42,    44,   45,          48,                 50,       52,    54,
 1,  2, 24,  6, 236, 18, 3768, 20384, 7188, 227784, 186, 481732448, 23760631602816306684, 341521732, 4896, 1417919208,
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/root-sums-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/root-sums-demo.cc DEMOFLAGS=-DTIMING"
/// End:
