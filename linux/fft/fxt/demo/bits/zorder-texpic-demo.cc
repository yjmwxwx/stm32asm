
#include "bits/zorder.h"
#include "aux0/tex-line.h"

#include <cmath>  // sqrt()

#include "fxtio.h"

#include "nextarg.h"
#include "fxttypes.h"  // ulong

//% TeX picture of the Z-order curve.

int
main(int argc, char **argv)
{
    ulong ldn = 6;
    NXARG(ldn, "number of moves == 2**ldn (fxtbook uses 8)");
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
        lin2zorder(t, x, y);

//        cout << "\\curve(" << tx << "," << ty << ", " << x << "," << y << ")" << endl;

        tex_line(tx, ty, x, y);

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

\usepackage{pict2e}% <--=  before \begin{document}

\begin{figure}%[hbt]
\begin{center}
\setlength{\unitlength}{6.0mm}
\begin{picture}(17,17)(-0.5,-0.5)% with ldn==8
  \thicklines
 [OUTPUT of the program HERE] <--= there!
\end{picture}
\end{center}
\caption{\jjlabel{fig:zorder2d}
The Z-order curve.}
\end{figure}

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/zorder-texpic-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/zorder-texpic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

