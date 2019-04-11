
#include "comb/perm-trotter.h"
#include "ds/bitarray.h"
#include "aux0/binomial.h"

//#include "comb/fact2perm.h"
//#include "comb/mixedradix.h"

#include "jjassert.h"
#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"

//% OEIS sequence A066411:
//% Number of sums of c_k * (n choose k) where the c_k are a permutation of 0 through n.
//% Sequence A126972: permutations of [1..n], sum(k=1..n, (pi(k)-k)^2).
//% Sequence A189043: permutations of [1..n], sum(k=1..n, k^2 * pi(k) ).

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Permutations of n elements.");
    perm_trotter P(n);
    P.first();
    const ulong *x = P.data();

    ulong C[32];

    for (ulong k=0; k<n; ++k)  C[k] = binomial(n-1, k);  // A066411

//    for (ulong k=0; k<n; ++k)  C[k] = k;  // A126972
//    for (ulong k=0; k<n; ++k)  C[k] = (k+1);  // A126972

//    for (ulong k=0; k<n; ++k)  C[k] = k*k;  // A000000 (initial erroneous A189043)
//    for (ulong k=0; k<n; ++k)  C[k] = (k+1)*(k+1);  // A189043

//    for (ulong k=0; k<n; ++k)  C[k] = k%2;  // A033638
//    for (ulong k=0; k<n; ++k)  C[k] = 1-(k%2);  // A033638

//    for (ulong k=0; k<n; ++k)  C[k] = k/2;  // A000000: 1, 1, 3, 5, 11, 17, 29, 41, 61, 81, 111, 141, ...

//    const ulong N = n * binomial(n+1, (n+1)/2);  // large enough for A066411
    const ulong N = 1UL<<23;  // large enough
//    cout << ":: N=" << N << endl;
    bitarray B(N);
    B.clear_all();


    ulong s = 0;
    // compute initial sum:
//    for (ulong k=0; k<n; ++k)  s += C[k] * x[k];
    for (ulong k=0; k<n; ++k)  s += C[k]*(x[k]+1);  // A189043
    B.set( s );  // mark

//    P.print(" ");  cout << "  s=" << setw(2) << s << endl;

    while ( P.next() )
    {
#if 1  // Using Gray code property for faster update:
        // update sum:
        ulong sw1, sw2;
        P.get_swap(sw1, sw2);
        const ulong e1 = x[sw1], e2 = x[sw2];
//        s -= C[sw1]*e2;  s -= C[sw2]*e1;  s += C[sw1]*e1;  s += C[sw2]*e2;
//        s += C[sw1]*(e1-e2) + C[sw2]*(e2-e1);
        s += (e1-e2)*(C[sw1]-C[sw2]);

#else  // Recompute sum each time:
        s = 0;
//        for (ulong k=0; k<n; ++k)  s += C[k]*(x[k]+1);
        for (ulong k=0; k<n; ++k)  s += C[k]*(x[k]+0);

#endif
//        jjassert( s < N );

        B.set( s );  // mark
    }

#ifndef TIMING
    cout << "Possible values of the sum:" << endl;
    for (ulong k=0, z=0; k < B.size(); ++k)
    {
        if ( B.test(k) )
        {
            ++z;
            cout << setw(4) << z << ": " << k << endl;
        }
    }
#endif  // TIMING

    ulong ct = B.count_ones();  // number of different values
    cout << "ct=" << ct << endl;

#if 0
    ulong mx = 0;  // max value: A000000
    for (ulong j=0; j<N; ++j)  if (0!=B.test(j)) mx = j;
    cout << "mx=" << mx << endl;

    ulong mn = 0;  // min value: A000000
    for (ulong j=0; j<N; ++j)  if (0!=B.test(j)) {mn = j; break;}
    cout << "mn=" << mn << endl;
#endif

    return 0;
}
// -------------------------

/*
for n in $(seq 1 24); do time ./bin $n; done 2>&1 | tee tt
echo $(g ct tt | cut -d= -f2) | sed 's/ /, /g;'
*/


/*
Timing:  (AMD Phenom II, 3GHz)

% time ./bin 12
arg 1: 12 == n  [Permutations of n elements.]  default=4
ct=12907
mx=18008
mn=4520
./bin 12  3.09s user 0.00s system 99% cpu 3.092 total
 ==> 12!/3.09 == 155,016,699 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A066411-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A066411-demo.cc DEMOFLAGS=-DTIMING"
/// End:
