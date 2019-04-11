
#include "bits/bit-dragon-r5.h"
#include "aux0/tex-line.h"

#include <cmath>  // sqrt(), cos(), sin()

#include "fxtio.h"
#include "bits/print-bin.h"

#include "jjassert.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong


//% TeX picture of the R5-dragon curve.
//% Cf. OEIS sequence A175337.

//#define TIMING  // uncomment to disable printing

const ulong csn = 4;  // 90 degree
double C[csn], S[csn];  // direction vectors

int
main(int argc, char **argv)
{
    ulong n = 5*5 + 1;
    NXARG(n, "Number of moves (fxtbook uses n=625)");

#ifdef TIMING
    ulong rx5 = 1;
    bool t = 0;
    for (ulong k=1; k<=n; ++k)  t ^= bit_dragon_r5_turn(rx5);
    cout << " rx5=" << rx5 << "  t=" << t << endl;

//    rx5 = 0;
//    for (ulong k=1; k<=n; ++k)
//    {
//        print_bin(" ", rx5, 9);
//        cout << "  ";
//        cout << (ulong)bit_dragon_r5_turn(rx5);
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
    ulong rx5 = 1;
    ulong dir = 0;
    for (ulong k=1; k<=n; ++k)
    {
        double dx = C[dir],  dy = S[dir];

        const bool f = bit_dragon_r5_turn(rx5);
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
        tex_draw_turn(x, y,  dx, dy,  ndx, ndy,  style);
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

Start: 0
Rules:
  0 --> 00110
  1 --> 00111
 00110001100011100111001100011000110001110011100110001100011000111001110011100110001100011100111001110011000110001110011100110

*/

/*
Embedding LaTeX code is:

\begin{figure}%[hbt]
\begin{center}
\setlength{\unitlength}{4mm}
%\begin{picture}(width,height)(x offset,y offset)
\begin{picture}(35,26)(-29.5,-17.5)
% \line(x-slope,y-slope){length}
% [OUTPUT of the program HERE] <--= there!
\end{picture}
\end{center}
\caption{\jjlabel{fig:r5-dragon}
The R5-dragon curve.}
\end{figure}

*/

/*
Timing:

% time ./bin 1000000000
arg 1: 1000000000 == n  [Number of moves (fxtbook uses n=625)]  default=26
 rx5=277293826049  t=0
./bin 1000000000  3.22s user 0.00s system 99% cpu 3.219 total
 ==> 1000000000/3.22 == 310,559,006 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/dragon-r5-texpic-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/dragon-r5-texpic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

