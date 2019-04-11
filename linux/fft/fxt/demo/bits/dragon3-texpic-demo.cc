
#include "bits/bit-dragon3.h"
#include "aux0/tex-line.h"

#include <cmath>  // sqrt(), cos(), sin()

#include "fxtio.h"

#include "jjassert.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong


//% TeX picture of the terdragon curve.
//% Cf. OEIS sequence A080846.

//#define TIMING  // uncomment to disable printing

const ulong csn = 3;  // 120 degree
double C[csn], S[csn];  // direction vectors


int
main(int argc, char **argv)
{
    ulong n = 27 + 1;
    NXARG(n, "Number of moves (fxtbook uses n=729)");

#ifdef TIMING
    ulong rx3 = 1;
    bool t = 0;
    for (ulong k=1; k<=n; ++k)  t ^= bit_dragon3_turn(rx3);
    cout << " rx3=" << rx3 << "  t=" << t << endl;
#else  // TIMING

    ulong style = 2;
    NXARG(style, "Drawing style (fxtbook uses style=2, and style=1)");
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
    ulong rx3 = 1;
    ulong dir = 2;  // make horizontal (with n==729)
    for (ulong k=1; k<=n; ++k)  // note: start with k=1
    {
        double dx = C[dir],  dy = S[dir];
//        cout << "%% " << (dir+3-2)%3 << endl;

        const bool f = bit_dragon3_turn(rx3);

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
        tex_draw_turn(x, y,  dx, dy,  ndx, ndy,  style, 1);
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
Embedding LaTeX code is:

\begin{figure}
\begin{center}
\setlength{\unitlength}{7mm} % fxtbook 729 moves
%%\begin{picture}(width,height)(x offset,y offset)
\begin{picture}(17.5,29.58)(-1.5,-27.35)% fxtbook 729 moves
  \thicklines
 [OUTPUT of the program HERE] <--= there!
\end{picture}
\end{center}
\caption{\jjlabel{fig:dragon3}
The terdragon curve.}
\end{figure}
*/

/*
Timing:

 time ./bin 1000000000
arg 1: 1000000000 == n  [Number of moves (fxtbook uses n=729)]  default=28
 rx3=163754053890  t=1
./bin 1000000000  4.51s user 0.00s system 99% cpu 4.518 total
 ==> 1000000000/4.51 == 221,729,490 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/dragon3-texpic-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/dragon3-texpic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

