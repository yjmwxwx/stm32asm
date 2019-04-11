
// demo-is-self-contained

#include "aux0/tex-line.h"  // tex_line()

#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "fxtio.h"

//% TeX picture of dataflow for radix-2 fast transforms (butterfly diagram).

inline void line2(ulong t1, ulong t2, ulong ldm, bool pm)
{
    ulong y0 = 3*ldm;
    ulong y1 = y0+2;
    if ( pm )
    {
        tex_line(t1, y0, t1, y1);
        tex_line(t1, y0, t2, y1);
        tex_line(t2, y0, t1, y1);

        double yt = (double)y0-0.5;
        cout << "\\put(" << (double)t1-0.2 << "," << yt << ")" << "{" << t1 << "}" << endl;
        cout << "\\put(" << (double)t2-0.2 << "," << yt << ")" << "{" << t2 << "}" << endl;
    }
    else
    {
        tex_line(t2, y0, t2, y1);
    }
}
// -------------------------

void set_lt(bool pm)
{
    if ( pm )
    {
        cout << "%% additions:" << endl;
#ifdef TEX_USE_PICT2E
        cout << "\\linethickness{0.4mm}" << endl;
#else
        cout << "\\linethickness{0.3mm}" << endl;
#endif
    }
    else
    {
        cout << "%% subtractions:" << endl;
#ifdef TEX_USE_PICT2E
        cout << "\\linethickness{0.2mm}" << endl;
#else
        cout << "\\linethickness{0.1mm}" << endl;
#endif
    }
}
// -------------------------


void dit2_butterfly(ulong ldn, bool pm)
{
    ulong n = 1 << ldn;
    for (ulong ldm=1; ldm<=ldn; ++ldm)
    {
        cout << "% ldm=" << ldm << endl;
        if ( pm )
        {
            cout << "\\put(" << n+2 << "," << 3*ldm+1 << "){ldm=" << ldm << "}" << endl;
        }

        const ulong m = (1<<ldm);
        const ulong mh = (m>>1);
        for (ulong j=0; j<mh; ++j)
        {
            for (ulong r=0; r<n; r+=m)
            {
                const ulong t1 = r+j;
                const ulong t2 = t1+mh;

                line2(t1, t2, ldm, pm);

//                double u = f[t1];
//                double v = f[t2];
//                f[t1] = u + v;
//                f[t2] = u - v;
            }
        }
    }
}
// -------------------------



//template <typename Type>
void walsh_gray(ulong ldn, ulong pm)
{
    const ulong n = (1UL<<ldn);

    for (ulong ldm=ldn; ldm>0; --ldm)  // DIF
    {
        cout << "% ldm=" << ldm << endl;
        if ( pm )
        {
            cout << "\\put(" << n+2 << "," << 3*ldm+1 << "){ldm=" << ldm << "}" << endl;
        }
        const ulong m = (1UL<<ldm);
        for (ulong r=0; r<n; r+=m)
        {
            ulong t1 = r;
            ulong t2 = r + m - 1;
            for (  ;  t1<t2;  ++t1, --t2)
            {
//                Type u = f[t1];
//                Type v = f[t2];
//                f[t1] = u + v;
//                f[t2] = u - v;
                line2(t1, t2, ldm, pm);
            }
        }
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong ldn = 4;
    NXARG(ldn, "length of tranform == 2**ldn");
    ulong wh = 1;
    NXARG(wh, "what to produce:"
          "  1==> Walsh radix-2 DIF (same as radix-2 DIF FFT)"
          "  2==> Walsh-gray"
          );

    switch ( wh )
    {
    case 1:
        set_lt(1); dit2_butterfly(ldn, 1);
        set_lt(0); dit2_butterfly(ldn, 0);
        break;
    case 2:
        set_lt(1); walsh_gray(ldn, 1);
        set_lt(0); walsh_gray(ldn, 0);
        break;
//    default:
//        set_lt(1); fht_dit2(ldn, 1);
//        set_lt(0); fht_dit2(ldn, 0);
//        break;
    }

    return 0;
}
// -------------------------

/*
Embedding LaTeX code is:

\usepackage{pict2e}% <--=  before \begin{document}
%% or, when TEX_USE_PICT2E is NOT defined:
//\usepackage{curves}% <--=  before \begin{document}

\begin{figure}%[hbt]
\begin{center}
\setlength{\unitlength}{7.0mm}
\begin{picture}(16.5,12.5)(+2.0,+2.3)
 [OUTPUT of the program HERE] <--= there!
\end{picture}
\end{center}
\caption{\jjlabel{fig:dit2butterfly}
Data flow for the length-16, radix-2, decimation in time (DIT) transform.}
\end{figure}

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/fft"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/fft/butterfly-texpic-demo.cc"
/// make-target2: "1demo DSRC=demo/fft/butterfly-texpic-demo.cc DEMOFLAGS=-DTIMING"
/// End:

