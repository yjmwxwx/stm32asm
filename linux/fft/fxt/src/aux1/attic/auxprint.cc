// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "complextype.h"
#include "aux1/aux1double.h"  // norm()

#include "fxtio.h"



#define CHOP(x,eps)  (fabs(x)<(eps) ? 0 : (x))

double print_epsilon = 0.0;

void
print(const char *bla, const double *f, ulong n, double eps/*=0.0*/)
{
    if ( eps==0.0 )  eps = print_epsilon;

    cout << endl;
    if ( bla )  cout << bla;
    cout << "  = | " << norm(f, n) << " |" << endl;

    cout.setf(ios::showpos);
    cout.precision(6);
    for (ulong k=0; k<n; ++k)
    {
        cout.width(3);
        cout << k << "-  ";
        double r = CHOP(f[k], eps);
        cout.width(8);
        cout << r;
        cout << endl;
    }
    cout << endl;
}
// -------------------------


void
print_twodim(const char *bla, const double *f, ulong r, ulong c, double eps/*=0.0*/)
{
    cout << endl;
    if ( bla )  cout << bla << endl;

    for (ulong k=0; k<r; ++k)
    {
        cout.width(2);
        cout << k << ":  ";
        for (ulong j=0; j<c; ++j)
        {
            double t = f[j+k*c];
            if ( eps!=0.0 )  t = CHOP(t,eps);
            cout.flags(ios::left /*| ios::showpos*/);
            cout.width( 12 );
            cout << t;
        }
        cout << endl;
    }
}
// -------------------------


void
c_print(const char *bla, const Complex *c, long n, double eps/*=0.0*/)
{
    cout << endl;
    if ( bla )  cout << bla << endl;

    for (long k=0; k<n; ++k)
    {
        double r = c[k].real();
        double i = c[k].imag();

        if ( eps!=0.0 )
        {
            r = CHOP(r,eps);
            i = CHOP(i,eps);
        }

        cout.width(8);
        cout << r;
        cout.width(8);
        cout << " + i* " << i << endl;
    }
    cout << endl;
}
// -------------------------


void
ri_print(const char *bla, const double *fr, const double *fi,
         long n, double eps/*=0.0*/)
{
    cout << endl;
    if ( bla )  cout << bla << endl;

    for (long k=0; k<n; ++k)
    {
        double r = fr[k];
        double i = fi[k];

        if ( eps!=0.0 )
        {
            r = CHOP(r,eps);
            i = CHOP(i,eps);
        }

        cout.width(8);
        cout << r;
        cout.width(8);
        cout << " + i* " << i << endl;
    }
    cout << endl;
}
// -------------------------


static int
print_approx_eq(const double *f, const double *g, ulong n,
                ulong skip, double eps)
//
// for debugging
//
{
#define  CHOPX(x)  CHOP(x,1e-6)
//           |    -2.40223      =       3.05663  -**[ 0]**-       5.45886     8.51549     1.78591
    cout << "        diff       =           f    - [idx]  -            g          sum          quot   " << endl;

    int failq = 0;
    for (ulong i=0, j=0;  i<n;  i+=skip, ++j)
    {
        int di = 0;
        double d = f[i]-g[i];
        if ( fabs(d)>eps )  di = 1;
        if ( di )  failq = 1;
        cout.width(12);
//        if ( di )
        cout << CHOPX(d);
//        else cout << "            ";
        cout << "       =  ";
        cout.width(12);  cout << CHOPX(f[i]);
        cout << (di ? "  -**" : "  -  ");
        cout << "[";  cout.width(2);  cout << j << "]";
        cout << (di ? "**-  " : "  -  ");
        cout.width(12);  cout << CHOPX(g[i]);
//        if ( di )
        {
//            cout << "   yuck  ";
            cout.width(12);
            cout << CHOPX(f[i]+g[i]);
            cout.width(12);
            if ( CHOPX(f[i])!=0 && CHOPX(g[i])!=0 )  cout << g[i]/f[i];
        }
        cout << " " << endl;
    }
    return failq;
#undef  CHOPX
}
// -------------------------


void
approx_eq(const double *f, const double *g, ulong n,
          const char *bla, double eps/*=1e-12*/)
//
// for debugging
//
{
    cout << bla << ": " << endl;
    int failq = print_approx_eq(f, g, n, 1, eps);

    cout << (failq ? " *** !ERROR! *** " : "OK.") << endl;
}
// -------------------------

void
approx_eq(const Complex *f, const Complex *g, ulong n,
          const char *bla, double eps/*=1e-12*/)
//
// for debugging
//
{
    cout << bla << ": " << endl;

    int failq = 0;

    cout << " real: " << endl;
    failq |= print_approx_eq((double *)f, (double *)g, n, 2, eps); // jjcast

    cout << " imag: " << endl;
    failq |= print_approx_eq((double *)f+1, (double *)g+1, n, 2, eps); // jjcast

    cout << (failq ? " *** !ERROR! *** " : "OK.") << endl;
}
// -------------------------

static bool
print_approx_eq(const ulong *f, const ulong *g, ulong n, ulong skip)
//
// for debugging
//
{
#define  CHOPX(x)  (x)
    cout << "        diff       =           f    - [idx]  -            g " << endl;

    bool failq = false;
    for (ulong i=0, j=0;  i<n;  i+=skip, ++j)
    {
        int di = 0;
        long d = (long)(f[i]-g[i]);
        if ( d )  di = 1;
        if ( di )  failq = true;
        cout.width(12);
        cout << CHOPX(d);
//        else cout << "            ";
        cout << "       =  ";
        cout.width(12);  cout << CHOPX(f[i]);
        cout << (di ? "  -**" : "  -  ");
        cout << "[";  cout.width(2);  cout << j << "]";
        cout << (di ? "**-  " : "  -  ");
        cout.width(12);  cout << CHOPX(g[i]);
        cout << " " << endl;
    }
    return failq;

#undef CHOPX
}
// -------------------------

void
approx_eq(const ulong *f, const ulong *g, ulong n, const char *bla)
//
// for debugging
//
{
    cout << bla << ": " << endl;

    cout << " exact: " << endl;
    print_approx_eq(f, g, n, 1);
}
// -------------------------

