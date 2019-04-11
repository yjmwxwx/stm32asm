
#include "bits/bit-dragon3.h"
#include "aux0/tex-line.h"

#include <cmath>  // sqrt(), cos(), sin()

#include "fxtio.h"

#include "jjassert.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong


//% TeX picture of the hexdragon curve.



const ulong csn = 6;  // 60 degrees
double C[csn], S[csn];  // direction vectors

int
main(int argc, char **argv)
{
    ulong n = 27 + 1;
    NXARG(n, "Number of moves (fxtbook uses n=729)");

    bool vq = 0;
//    NXARG(vq, "Whether to draw arrow heads");

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
    ulong dir = 1;  // make horizontal (with n==729)
    for (ulong k=1; k<=n; ++k)  // note: start with k=1
    {
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

        double dx = C[dir],  dy = S[dir];
        tex_line_fl(x, y,  x+dx, y+dy,  vq);
        x += dx;  y += dy;  // move


        // update max/min:
        if ( x<ix )  ix = x;
        if ( x>ax )  ax = x;
        if ( y<iy )  iy = y;
        if ( y>ay )  ay = y;


        // and again:
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

        dx = C[dir],  dy = S[dir];
        tex_line_fl(x, y,  x+dx, y+dy,  vq);
        x += dx;  y += dy;  // move

        // update max/min:
        if ( x<ix )  ix = x;
        if ( x>ax )  ax = x;
        if ( y<iy )  iy = y;
        if ( y>ay )  ay = y;
    }

//    cout << "% ix = " << ix << endl;
//    cout << "% ax = " << ax << endl;
//    cout << "% iy = " << iy << endl;
//    cout << "% ay = " << ay << endl;
    double wd = ax-ix, hg = ay-iy;
    double xo = ix, yo = iy;
//    cout << "% width = " << wd << endl;
//    cout << "% height = " << hg << endl;
//    cout << "% xoff = " << xo << endl;
//    cout << "% yoff = " << yo << endl;

    cout << "%% Put next line (un-commented) on top of pic:" << endl;
    cout << "%\\begin{picture}("
         << wd+1 << "," << hg+1 << ")"
         << "(" << xo-0.5 << "," << yo-0.5 << ")" << endl;

    return 0;
}
// -------------------------

/*
Embedding LaTeX code is:

\begin{figure}%[hbt]
\begin{center}
\setlength{\unitlength}{1.7mm}
%\begin{picture}(width,height)(x offset,y offset)
\begin{picture}(90,51.2295)(-2.5,-27.3468)
% \line(x-slope,y-slope){length}
% [OUTPUT of the program HERE] <--= there!
\end{picture}
\end{center}
\caption{\jjlabel{fig:hex-dragon}
The hexdragon.}
\end{figure}

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/dragon-hex-texpic-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/dragon-hex-texpic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

