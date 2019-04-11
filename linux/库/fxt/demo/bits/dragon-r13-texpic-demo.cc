
#include "bits/bit-dragon-r13.h"
#include "aux0/tex-line.h"

#include <cmath>  // sqrt(), cos(), sin()

#include "fxtio.h"
#include "bits/print-bin.h"

#include "jjassert.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong


//% TeX picture of the R13-dragon curve.


//#define TIMING  // uncomment to disable printing

const ulong csn = 4;  // 90 degrees
double C[csn], S[csn];  // direction vectors

int
main(int argc, char **argv)
{
    ulong n = 13 + 1;
    NXARG(n, "Number of moves (fxtbook uses n=2197)");

#ifdef TIMING
    ulong rx13 = 0;
    bool t = 0;
    for (ulong k=0; k<n; ++k)  t ^= bit_dragon_r13_turn(rx13);
    cout << " rx13=" << rx13 << "  t=" << t << endl;

//    rx13 = 0;
//    for (ulong k=0; k<n; ++k)
//    {
//        print_bin(" ", rx13, 9);
//        cout << "  ";
//        cout << (ulong)bit_dragon_r13_turn(rx13);
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
        const double ph = p2/(double)csn * (double)j;
        C[j] = cos(ph);  S[j] = sin(ph);
    }

    double x = 0, y = 0;
    cout << "\\put(" << x << "," << y << ")" << "{\\circle{0.5}}" << endl;
    cout << "\\put(" << x << "," << y << ")" << "{\\circle{0.25}}" << endl;

    double ix=0, ax=0, iy=0, ay=0;  //  min/max  x/y
    ulong rx13 = 1;
    ulong dir = 0;
    for (ulong k=0; k<n; ++k)
    {
        double dx = C[dir],  dy = S[dir];

        const bool f = bit_dragon_r13_turn(rx13);
        if ( f )
        {
            ++dir;
            if ( dir==csn )  dir=0;
        }
        else
        {
            if ( dir==0 )  dir=csn;
            --dir;
        }

        double ndx = C[dir],  ndy = S[dir];
        tex_draw_turn(x, y,  dx, dy,  ndx, ndy,  style, 0);
        x += dx;  y += dy;  // move


        // update max/min:
        if ( x<ix )  ix = x;  if ( x>ax )  ax = x;
        if ( y<iy )  iy = y;  if ( y>ay )  ay = y;
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
Timing:
% time ./bin 1000000000
arg 1: 1000000000 == n  [Number of moves (fxtbook uses n=2197)]  default=14
 rx13=5035499932  t=1
./bin 1000000000  4.17s user 0.01s system 100% cpu 4.178 total
 ==> 1000000000/4.17 == 239,808,153 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/dragon-r13-texpic-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/dragon-r13-texpic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

