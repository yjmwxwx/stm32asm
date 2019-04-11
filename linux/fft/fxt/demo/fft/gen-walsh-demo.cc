
// demo-is-self-contained

#include "perm-all.h"

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"


//% Generate code for short-length Walsh transforms.


void gen_walsh_wak(const char *f, ulong ldn, bool difq, const char *skip=0)
// Generate code for length-(2**ldn) Walsh (wak) transform.
{
#define Z(k)  t << (k)

    const ulong n = (1UL<<ldn);
    cout << endl;
    cout << "template <typename Type>" << endl;
    cout << "inline void" << endl;
    if ( difq )  cout << "short_walsh_wak_dif_";
    else         cout << "short_walsh_wak_dit_";

    cout << n << "(Type *" << f;
    if ( skip )  cout << ", ulong " << skip;
    cout << ")" << endl;
    cout << "{" << endl;


    char t[] = "t";
    cout << " Type ";
    for (ulong k=0; k<n; ++k)
    {
        cout << Z(k);
        if ( k<n-1 )  cout << ", ";
        else   cout << ";" << endl;
    }

    if ( skip==0 )
    {
        for (ulong k=0; k<n; ++k)
        {
            cout << " " << Z(k) << " = " << f << "[" << k << "];" << endl;
        }
    }
    else
    {
        cout << " {" << endl;
        cout << " ulong x = 0;" << endl;
        for (ulong k=0; k<n; ++k)
        {
            cout << " " << Z(k) << " = " << f << "[x];";
            if ( k<n-1 )  cout << "  x += " << skip << ";";
            cout << endl;
        }
        cout << " }" << endl;
    }

    ulong ldm0, ldm1, sldm;
    if ( difq )  { ldm0=ldn; ldm1=0;     sldm=(ulong)-1; }  // DIF
    else         { ldm0=1;   ldm1=ldn+1; sldm=+1; }  // DIT
//  for (ulong ldm=ldn; ldm>=1; --ldm)  // DIF
//  for (ulong ldm=1; ldm<=ldn; ++ldm)  // DIT
    for (ulong ldm=ldm0; ldm!=ldm1; ldm+=sldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        for (ulong r=0; r<n; r+=m)
        {
            ulong t1 = r;
            ulong t2 = r+mh;
            for (ulong j=0;  j<mh;  ++j, ++t1, ++t2)
            {
                cout << " sumdiff( " << Z(t1) << ", " << Z(t2) << " );" << endl;
            }
        }
    }

    if ( skip==0 )
    {
        for (ulong k=0; k<n; ++k)
        {
            cout << " " << f << "[" << k << "] = "  << Z(k) << ";" << endl;
        }
    }
    else
    {
        cout << " {" << endl;
        cout << " ulong x = 0;" << endl;
        for (ulong k=0; k<n; ++k)
        {
            cout << " " << f << "[x] = " << Z(k) << ";";
            if ( k<n-1 )  cout << "  x += " << skip << ";";
            cout << endl;
        }
        cout << " }" << endl;
    }

    cout << "}" << endl;
    cout << "// -------------------------" << endl;
    cout << endl;
#undef Z
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong ldn = 3;
    NXARG(ldn, "Generate code for 2**ldn Walsh (wak) transform.");
    bool difq = 1;
    NXARG(difq, "Whether to generate code for DIF algorithm, (else DIT)");
    int sq = 3;
    NXARG(sq, "What to generate: 1==>plain,  2==>skip variant,  3==>both");

    if ( sq&1 )  gen_walsh_wak("f", ldn, difq, 0  );
    if ( sq&2 )  gen_walsh_wak("f", ldn, difq, "s");

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/fft"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/fft/gen-walsh-demo.cc"
/// make-target2: "1demo DSRC=demo/fft/gen-walsh-demo.cc DEMOFLAGS=-DTIMING"
/// End:

