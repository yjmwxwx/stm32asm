
// demo-is-self-contained

#include "aux0/swap.h"

#include "fxtio.h"
#include "fxttypes.h"

//% Show steps of the revbin algorithm


void Print(const char *w)
{
    cout << "[ ";
    for (ulong j=0; j<16; ++j)  cout << w[j] << " ";
    cout << "]" << endl;
}
// -------------------------

int
main()
{
    const char str[]="0123456789abcdef";
    char w[16];
    for (ulong j=0; j<16; ++j)  w[j] = str[j];

    Print(w);
    for (ulong k=1; k<16; k*=2)
    {
        // swap adjacent blocks of k bits:
        for (ulong j=0; j<16; j+=2*k)
        {
            for (ulong i=0; i<k; ++i)
            {
                swap2(w[j+i], w[j+i+k]);
            }
        }
        Print(w);
    }


    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/revbin-steps-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/revbin-steps-demo.cc DEMOFLAGS=-DTIMING"
/// End:
