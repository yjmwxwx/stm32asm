
// demo-is-self-contained

#include "bits/bitcombcolex.h"  // first_comb()
#include "bits/print-bin.h"


#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong


//% Towers of Hanoi, recursive algorithm.


ulong n;
ulong f[3];  // the three piles

static void
print_hanoi(ulong s)
{
    // print the towers:
    for (ulong j=0; j<3; ++j)  print_bin("    ", f[j], n, ".1");

    // print move:
    print_bin("    ", s, n, ".1");

    // print summary:
    cout << "   ";
    for (ulong k=n-1, b=1<<(n-1);  0!=b;  --k, b>>=1)
    {
        cout << ' ';
        if ( b & f[0] )  cout << '0';
        else
        {
            if ( b & f[1] )  cout << '+';
            else             cout << '-';
        }
    }

    cout << endl;
}
// -------------------------


void
hanoi(ulong k, ulong A, ulong B, ulong C)
// Move k disks from pile A to pile C
{
    if ( k==0 ) return;

    // 1. move k-1 disks from pile A to pile B:
    hanoi(k-1, A, C, B);

    // 2. move disk k from pile A to pile C:
    ulong b = 1UL << (k-1);
    f[A] ^= b;
    f[C] ^= b;

    print_hanoi(b);  // visit state

    // 3. move k-1 disks from pile B to pile C:
    hanoi(k-1, B, A, C);
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 5;
    NXARG(n, "Number of disks");

    // Initial configuration:
    f[0] = first_comb(n);  // n ones as lowest bits
    f[1] = 0;  f[2] = 0;   // empty

    print_hanoi(0);  // visit initial state

    hanoi(n, 0, 1, 2);  // solve

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/hanoi-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/hanoi-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:

