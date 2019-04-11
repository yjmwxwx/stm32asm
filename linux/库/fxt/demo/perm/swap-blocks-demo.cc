
#include "perm/swapblocks.h"

#include "fxtio.h"
#include "aux0/swap.h"
#include "perm/reverse.h"
#include "nextarg.h"
#include "jjassert.h"
#include "fxttypes.h"

//% The quadruple reversal trick.

const char s[]="01234abcde78wxyzNNN";
//                   ^++++  ^+++
//              01234567890123456790

void Print0(const char *g, ulong x1, ulong n1, ulong x2, ulong n2)
{
    cout << "      ";
    ulong k = 0;
    for ( ; k<x1; ++k)  cout << "  ";
    for ( ; k<x1+n1; ++k)  cout << "v ";
    for ( ; k<x2; ++k)  cout << "  ";
    for ( ; k<x2+n2; ++k)  cout << "v ";
    for ( ; g[k]; ++k)  cout << "  ";
    cout << "   " << "<--= want to swap these blocks" << endl;
}
// -------------------------

void Print(const char *g, const char* bla)
{
    cout << "    [ ";
    for (ulong k=0; g[k]; ++k)  cout << g[k] << " ";
    cout << "]  " << bla << endl;
}
// -------------------------

void demo_swap_blocks(char *f, ulong x1, ulong n1, ulong x2, ulong n2)
// Swap the blocks starting at indices x1 and x2
// n1 and n2 are the block lengths
{
    if ( x1>x2 ) { swap2(x1, x2); swap2(n1, n2); }
    Print0(f, x1, n1, x2, n2);
    char *g = f;
    f += x1;
    x2 -= x1;
    ulong n = x2 + n2;
    Print(g, "orig. data");
    reverse(f, n1);
    Print(g, "reverse first block");
    if ( n>=n1+n2 )  reverse(f+n1, n-n1-n2);
    else             reverse(f+n1, -(n-n1-n2));  // allow overlapping blocks
    Print(g, "reverse range between blocks");
    reverse(f+x2, n2);
    Print(g, "reverse last block");
    reverse(f, n);
    Print(g, "reverse whole range");
}
// -------------------------

int
main(int argc, char **argv)
{
    char *z = new char[20];
    for (ulong k=0; k<20; ++k)  z[k]=s[k];

    ulong x1=5, n1=5;
    ulong x2=12, n2=4;

    NXARG(x1, "Start of first block");
    NXARG(n1, "Length of first block");
    NXARG(x2, "Start of second block");
    NXARG(n2, "Length of second block");

    demo_swap_blocks(z, x1, n1, x2, n2);
    cout << endl;
    demo_swap_blocks(z, x1, n2, x2+n2-n1, n1);

    // test:
    for (ulong k=0; k<20; ++k)  z[k]=s[k];
    swap_blocks(z, x1, n1, x2, n2);
    swap_blocks(z, x1, n2, x2+n2-n1, n1);
    for (ulong k=0; k<20; ++k)  jjassert( z[k]==s[k] );

    for (ulong k=0; k<20; ++k)  z[k]=s[k];
    swap_blocks(z, x1, n1, x2, n2);
    inverse_swap_blocks(z, x1, n1, x2, n2);
    for (ulong k=0; k<20; ++k)  jjassert( z[k]==s[k] );

    delete [] z;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/perm"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/perm/swap-blocks-demo.cc"
/// make-target2: "1demo DSRC=demo/perm/swap-blocks-demo.cc DEMOFLAGS=-DTIMING"
/// End:

