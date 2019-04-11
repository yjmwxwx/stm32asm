
// demo-is-self-contained

#include "comb/comb-print.h"
#include "fxtio.h"
#include "fxtalloca.h"
#include "fxttypes.h"
#include "nextarg.h"

//% Minimal-change order for combinations with k>=2 elements.
//% Good performance for small k.

// Code adapted from:
//  Clement W.\ H.\ Lam, Leonard H.\ Soicher:
//  "Three new combination algorithms with the minimal change property",
//  Communications of the ACM, vol.25, no.8, pp.555-559, August-1982.

//#define TIMING  // uncomment to disable printing

ulong ct = 0;
#ifdef TIMING
void Print(const ulong *, ulong, ulong)
{
    ++ct;
}
#else  // TIMING
void Print(const ulong *a, ulong n, ulong k)
{
    ++ct;
    cout << setw(3) << ct << ":  ";
    print_set("    ", a+1, k);
    print_set1_as_deltaset("    ", a+1, k, n);
    cout << endl;
}
// -------------------------
#endif  // TIMING


#define PROCESS Print(a, n, k)

int main(int argc, char **argv)
{
    ulong top = 0;  // (* clear the stack *)
    ulong n = 7;
    NXARG(n, "Combinations (n choose k)");
    ulong k = 3;
    NXARG(k, "");
    //    ulong a[k+1];  // one-based
    ALLOCA(ulong, a, k+1);  // one-based
    //    ulong t[k+1];
    ALLOCA(ulong, t, k+1);


    if ( k % 2 == 0  )
    {
        a [ k + 1 ] = n + 1; a[k] = k;
        if ( k < n  ) top = k;
    }
    else
    {
        a[k] = n;
        if ( k<n ) top=k-1;
    }

    a[1] = 1;
    t[k] = 0;
    ulong i;
    for (i=2; i<k; ++i)  { a[i] = i;  t[i] = i + 1; }

    PROCESS;  // (* first combination *)
    // (* main loop to generate all other combinations *)
    while ( top != 0 )
    {
        if ( top == 2  )
        {  // (* special handling for a[2] and a[1] *)
            top = t[2];  t[2] = 3;
            do
            {
                a[1] = a[2];  a[2] = a[2] + 1;
                PROCESS;
                do
                {
                    a[1] = a[1] - 1;
                    PROCESS;
                }
                while ( ! ( a[1] == 1 ) );
            }
            while ( ! ( a[2] == a[3] - 1) );
        }
        else
        {
            if ( top % 2 == 0  )
            {
                a[top-1] = a[top];  a[top] = a[top] + 1;
                if ( a[top] == a[top+1] - 1  )
                {
                    t[top-1] = t[top];  t[top] = top + 1;
                }
                top = top - 2;
            }
            else
            {
                a[top] = a[top]-1;
                if ( a[top] > top  )
                {
                    top = top-1;  a[top] = top;
                }
                else
                {
                    a[top-1] = top-1;  i = top;
                    top = t[top];  t[i] = i + 1;
                }
            }
            PROCESS;
        }
    }

#ifdef TIMING
    ulong s = 0;
    for (ulong j=1; j<=k; ++j)  s += a[j];
    cout << " dummy: " << s << endl;
#endif

    cout << "ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:
 time ./bin 32 20
binomial(32, 20)=225792840
ct=225792840
./bin 32 20  1.49s user 0.00s system 99% cpu 1.494 total
 ==> 225792840/1.49 == 151,538,818 per second

 time ./bin 32 12
ct=225792840
./bin 32 12  1.17s user 0.00s system 99% cpu 1.172 total
 ==> 225792840/1.17 == 192,985,333 per second

 time ./bin 64 7
ct=621216192
./bin 64 7  2.44s user 0.00s system 99% cpu 2.448 total
 ==> 621216192/2.44 == 254,596,800 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)
(the compiler apparently optimizes things out of existence)

 time ./bin 32 20
arg 1: 32 == n  [Combinations (n choose k)]  default=7
arg 2: 20 == k  []  default=3
ct=225792840
./bin 32 20  0.45s user 0.00s system 99% cpu 0.452 total
 ==> 225792840/0.45 == 501,761,866 per second

 time ./bin 32 12
arg 1: 32 == n  [Combinations (n choose k)]  default=7
arg 2: 12 == k  []  default=3
ct=225792840
./bin 32 12  0.21s user 0.00s system 99% cpu 0.216 total
 ==> 225792840/0.21 == 1,075,204,000 per second

 time ./bin 64 7
arg 1: 64 == n  [Combinations (n choose k)]  default=7
arg 2: 7 == k  []  default=3
ct=621216192
./bin 64 7  0.09s user 0.00s system 98% cpu 0.096 total
 ==> 621216192/0.09 == 6,902,402,133 per second

 time ./bin 80 7
arg 1: 80 == n  [Combinations (n choose k)]  default=7
arg 2: 7 == k  []  default=3
ct=3176716400
./bin 80 7  0.35s user 0.00s system 99% cpu 0.352 total
 ==> 3176716400/0.35 == 9,076,332,571 per second


*/

/*
BENCHARGS=32 20
BENCHARGS=32 12
BENCHARGS=64 7
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/combination-lam-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/combination-lam-demo.cc DEMOFLAGS=-DTIMING"
/// End:
