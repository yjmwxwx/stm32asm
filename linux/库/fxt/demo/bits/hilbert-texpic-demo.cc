
#include "bits/hilbert.h"

#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

//% TeX picture of the Hilbert curve.


int
main(int argc, char **argv)
{
    ulong ldn = 6;
    NXARG(ldn, "number of moves == 2**ldn (fxtbook uses ldn==8)");
    ulong n = 1UL<<ldn;

    ulong tx, ty;
    ulong x = 0, y = 0;
    cout << "\\put(" << x << "," << y << ")" << "{\\circle{0.5}}" << endl;
    cout << "\\put(" << x << "," << y << ")" << "{\\circle{0.25}}" << endl;
    ulong ax=0, ay=0;  //  max  x/y
    for (ulong t=1; t<n; ++t)
    {
        tx = x;
        ty = y;
        lin2hilbert(t, x, y);
        long dx = (long)(x - tx);  // jjcast
        long dy = (long)(y - ty);  // jjcast
        cout << "\\put(" << tx << "," << ty << ")"
             << "{\\vector(" << dx << "," << dy << ")"
             << "{" << 1.0 << "}}" << endl;

        // update max:
        if ( x>ax )  ax = x;
        if ( y>ay )  ay = y;
    }

    double wd = (double)ax + 1.0,  hg = (double)ay + 1.0;
    cout << "%% Put next line (un-commented) on top of pic:" << endl;
    cout << "%\\begin{picture}("
         << wd+1 << "," << hg+1 << ")"
         << "(" << -0.5 << "," << -0.5 << ")" << endl;

    return 0;
}
// -------------------------

/*
Embedding LaTeX code is:

\begin{figure}
\begin{center}
\setlength{\unitlength}{6.0mm}
\begin{picture}(17,17)(-0.5,-0.5)
  \thicklines
 [OUTPUT of the program HERE] <--= there!
\end{picture}
\end{center}
\caption{\jjlabel{fig:hilbert2d}
The Hilbert curve.}
\end{figure}
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/hilbert-texpic-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/hilbert-texpic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

