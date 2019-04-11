
#include "bits/bit-paper-fold.h"
#include "aux0/tex-line.h"

#include <cmath>  // sqrt(), cos(), sin()

#include "nextarg.h"
#include "fxttypes.h"  // ulong


//% TeX picture of the dragon curve.


//#define TIMING  // uncomment to disable printing

const ulong csn = 4;  // 90 degrees
double C[csn], S[csn];  // direction vectors

int
main(int argc, char **argv)
{
    ulong n = 64;
    NXARG(n, "Number of moves (fxtbook uses n=1024)");


#ifdef TIMING
    bool t = 0;
    for (ulong k=1; k<=n; ++k)  t ^= bit_paper_fold(k);
    cout << " t=" << t << endl;
#else  // TIMING

    ulong style = 2;
    NXARG(style, "Drawing style (fxtbook uses style=2 and 1)");
//    cout << "%% style=" << style << endl;

    ulong w = 0;
    NXARG(w, "If !=0 then draw curve from paper-folding sequence with control world w");
//    cout << "%% style=" << style << endl;
    if ( 0==w )  w = ~0UL;

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
    ulong dir = 1;  // make horizontal (with n==1024)
    for (ulong k=1; k<=n; ++k)  // note: start with k=1
    {
        double dx = C[dir],  dy = S[dir];

        const bool f = bit_paper_fold_general(k, w);
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
arg 1: 1000000000 == n  [Number of moves (fxtbook uses n=1024)]  default=64
 t=1
./bin 1000000000  1.81s user 0.00s system 99% cpu 1.819 total
 ==> 1000000000/1.81 == 552,486,187 per second
*/

/*
Embedding LaTeX code is:

\begin{figure}
\begin{center}
//\setlength{\unitlength}{4.5mm} % fxtbook, 1024 moves
\setlength{\unitlength}{10.0mm}
%%\begin{picture}(width,height)(x offset,y offset)
\begin{picture}(8,12)(-5.5,-9.5) % 64 moves
%\begin{picture}(16,13)(-5.5,-10.5) % 128 moves
%\begin{picture}(24,16)(-5.5,-10.5) % 256 moves
%\begin{picture}(27,32)(-5.5,-10.5) % 512 moves
%\begin{picture}(32,48)(-10.5,-10.5) % 1024 moves (fxtbook)
  \thicklines
 [OUTPUT of the program HERE] <--= there!
\end{picture}
\end{center}
\caption{\jjlabel{fig:dragon-curve}
The dragon curve.}
\end{figure}
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/dragon-curve-texpic-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/dragon-curve-texpic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

