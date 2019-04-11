
#include "bits/bit-dragon-r7.h"
#include "aux0/tex-line.h"

#include <cmath>  // sqrt(), cos(), sin()

#include "fxtio.h"
#include "bits/print-bin.h"

#include "jjassert.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong


//% TeX picture of the R7-dragon curve.
//% Cf. OEIS sequence A176405.

//#define TIMING  // uncomment to disable printing

const ulong csn = 3;  // 120 degrees
double C[csn], S[csn];  // direction vectors

int
main(int argc, char **argv)
{
    ulong n = 7*7 + 1;
    NXARG(n, "Number of moves (fxtbook uses n=2401)");

#ifdef TIMING
    ulong rx7 = 1;
    bool t = 0;
    for (ulong k=1; k<=n; ++k)  t ^= bit_dragon_r7_turn(rx7);
    cout << " rx7=" << rx7 << "  t=" << t << endl;

//    rx7 = 0;
//    for (ulong k=1; k<=n; ++k)
//    {
//        print_bin(" ", rx7, 9);
//        cout << "  ";
//        cout << (ulong)bit_dragon_r7_turn(rx7);
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
    ulong rx7 = 1;
    ulong dir = 0;
    for (ulong k=0; k<n; ++k)
    {
        double dx = C[dir],  dy = S[dir];

        const bool f = bit_dragon_r7_turn(rx7);
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

Start: 0
Rules:
  0 --> 0100110
  1 --> 0110110

0100110011011001101100100110010011001101100100110010011001101100110110010011001001100110110010011
*/

/*
Embedding LaTeX code is:

\begin{figure}%[hbt]
\begin{center}
\setlength{\unitlength}{3mm}
%\begin{picture}(width,height)(x offset,y offset)
\begin{picture}(39.5,33.91)(-1.5,-0.5)
% \line(x-slope,y-slope){length}
% [OUTPUT of the program HERE] <--= there!
\end{picture}
\caption{\jjlabel{fig:r7-dragon}
The R7-dragon.}
\end{figure}
*/

/*
Timing:
% time ./bin 1000000000
arg 1: 1000000000 == n  [Number of moves (fxtbook uses n=2401)]  default=50
 rx7=3714515344  t=1
./bin 1000000000  3.15s user 0.00s system 99% cpu 3.154 total
 ==> 1000000000/3.15 == 317,460,317 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/dragon-r7-texpic-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/dragon-r7-texpic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

