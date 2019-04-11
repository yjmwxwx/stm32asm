
#include "bits/hilbert.h"
//demo-include "bits/lin2hilbert.cc"
#include "bits/graycode.h"
#include "bits/bitzip.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "bits/print-bin.h"

#include "jjassert.h"

#include "nextarg.h"

//% Hilbert curve and Gray code.


#define PP(x)  cout << "   " << #x << "="; print_bin("", x, pd);
int
main(int argc, char **argv)
{
    ulong ldn = 5;
    NXARG(ldn, "Use ldn-bit words");
    ulong  n = (1UL<<ldn);

    ulong pd = ldn + 1;
    cout << "    t ->    binary(x)  binary(y)= ( x,  y)"
         << "   gx=gray(x)  gy=gray(y)"
         << "  z=bitzip2(gx,gy) == g"
         << endl;

    for (ulong k=0; k<n; ++k)
    {
        ulong &t = k;
        cout << " #" << setw(3) << t << " -> ";

        ulong x, y;
        lin2hilbert(t, x, y);
        PP(x); PP(y);
        cout << " = (" << setw(2) << x << ", " << setw(2) << y << ")";
        ulong gx = gray_code(x);
        ulong gy = gray_code(y);
        PP( gx );  PP( gy );
        ulong z = bit_zip2(gx, gy);
        PP(z);

        ulong g = hilbert_gray_code(t);
        PP(g);


        ulong tt = hilbert2lin(x, y);
//        PP(tt);

//        ulong u = inverse_gray_code(g);
//        u = inverse_gray_code(u);
//        u = bit_unzip(u);
//        PP(u);

        cout << endl;

        jjassert( tt==t );
        jjassert( z==g );
    }

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/hilbert-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/hilbert-demo.cc DEMOFLAGS=-DTIMING"
/// End:

