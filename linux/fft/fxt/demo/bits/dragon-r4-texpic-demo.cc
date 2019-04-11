
#include "bits/bit-dragon-r4.h"
#include "aux0/tex-line.h"

#include <cmath>  // sqrt(), cos(), sin()

#include "fxtio.h"
#include "bits/print-bin.h"

#include "jjassert.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong


//% TeX picture of the R4-dragon curve.

//#define TIMING  // uncomment to disable printing


const ulong csn = 3;  // 120 degrees
double C[csn], S[csn];  // direction vectors

int
main(int argc, char **argv)
{
    ulong n = 4*4 + 1;
    NXARG(n, "Number of moves.");

#ifdef TIMING
    ulong rx4 = 0;
    bool t = 0;
    for (ulong k=0; k<n; ++k)  t ^= bit_dragon_r4_turn(rx4);
    cout << " rx4=" << rx4 << "  t=" << t << endl;

//    rx4 = 0;
//    for (ulong k=0; k<n; ++k)
//    {
//        print_bin(" ", rx4, 9);
//        cout << "  ";
//        cout << bit_dragon_r4_turn(rx4);
//        cout << endl;
//    }
//    cout << endl;

#else  // TIMING

    ulong style = 2;
    NXARG(style, "Drawing style (fxtbook uses style=2)");
    cout << "%% style=" << style << endl;

    for (ulong j=0; j<csn; ++j)
    {
        const double p2 = 6.28318530717959;
        const double ph = p2 / (double)csn * (double)j;
        C[j] = cos(ph);  S[j] = sin(ph);
    }

    double x = 0, y = 0;
    cout << "\\put(" << x << "," << y << ")" << "{\\circle{0.5}}" << endl;
    cout << "\\put(" << x << "," << y << ")" << "{\\circle{0.25}}" << endl;

    double ix=0, ax=0, iy=0, ay=0;  //  min/max  x/y
    ulong rx4 = 0;
    ulong dir = 0;
    for (ulong k=0; k<n; ++k)
    {
        double dx = C[dir],  dy = S[dir];

        const int f = bit_dragon_r4_turn(rx4);
        if ( f )
        {
            dir += (ulong)f;
            if ( dir>=csn )  dir=0;
            if ( (long)dir < 0 )  dir=csn;
        }

        double ndx = C[dir],  ndy = S[dir];
        tex_draw_turn(x, y,  dx, dy,  ndx, ndy,  style, 0);
        x += dx;  y += dy;  // move

        // update max/min:
        if ( x<ix )  ix = x;
        if ( x>ax )  ax = x;
        if ( y<iy )  iy = y;
        if ( y>ay )  ay = y;
    }

    double wd = ax-ix, hg = ay-iy;
    double xo = ix, yo = iy;

    cout << "%% Put next line (un-commented) on top of pic:" << endl;
    cout << "%\\begin{picture}("
         << wd+1 << "," << hg+1 << ")"
         << "(" << xo-0.5 << "," << yo-0.5 << ")" << endl;

#endif  // TIMING
    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 1000000000
arg 1: 1000000000 == n  [Number of moves.]  default=17
 rx4=1000000000  t=1
./bin 1000000000  3.62s user 0.00s system 99% cpu 3.620 total
 ==> 1000000000/3.62 == 276,243,093 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/dragon-r4-texpic-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/dragon-r4-texpic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

