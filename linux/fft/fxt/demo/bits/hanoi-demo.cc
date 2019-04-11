
// demo-is-self-contained

#include "bits/bitcombcolex.h"  // first_comb()
#include "bits/bitlow.h"  // lowest_one()
#include "bits/print-bin.h"


#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong


//% Towers of Hanoi and the period-doubling sequence.


static void
print_hanoi(const ulong *f, ulong n, ulong s, int md)
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

    if ( md>=0 )  // period-doubling sequence
    {
        cout << "   ";
        if ( md>0 )  cout << '0';
        else         cout << '1';
    }

    cout << endl;
}
// -------------------------

void
hanoi(ulong n)
{
    ulong f[3];
    f[0] = first_comb(n);  f[1] = 0;  f[2] = 0;  // Initial configuration

    const int dr = (n&1 ? -1 : +1);  // == +1 (if n even),  else  == -1

    cout << setw(4) << 0 << ":";
    print_hanoi(f, n, 0, -1);
    int u;  // index of tower untouched in current move
    if ( dr<0 ) u=2;  else u=1;

    ulong n2 = 1UL<<n;
    for (ulong k=1; k<n2; ++k)
    {
        ulong s = lowest_one(k);

        int rp = 3;  while ( rp-- )  if ( f[rp]&s )  break;  // pile where disk is removed

        ulong j = 3;  while ( j-- )  f[j] ^= s;  // change all piles
        f[u] ^= s;  // undo change for untouched pile

        int ap = 3;  while ( ap-- )  if ( f[ap]&s )  break;  // pile where disk was added

        u += dr;
        if ( u<0 ) u=2;  else if ( u>2 ) u=0;  // modulo 3

        int md = (int)( ap == (rp+1)%3 );  // direction of move (0 or 1)
        if ( dr<0 )  md ^= 1;  // complement if n odd

        cout << setw(4) << k << ":";
        print_hanoi(f, n, s, md);
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of disks");

    hanoi(n);

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/hanoi-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/hanoi-demo.cc DEMOFLAGS=-DTIMING"
/// End:

