// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/catalan-path-lex.h"

#include "fxtio.h"
#include "fxttypes.h"

void
print_catalan_path_aa(const ulong *a_, ulong n_, bool nfs/*=false*/)
// Render path as ASCII art.
{
    if ( nfs )
    {
        for (ulong k=1;  k<=n_;  ++k)
        {
            cout << ' ';
            const ulong ak = a_[k],  ak1 = a_[k-1];
            const bool rq = ( ak > ak1 );  // rise?
            for (ulong j=1; j < ak+!rq; ++j)  cout << ' ';
            cout << ( rq ? '\\' : '/' );
            cout << endl;
        }
    }
    else
    {
        for (ulong k=1;  k<=n_;  ++k)
        {
            cout << ' ';
            const ulong ak = a_[k],  ak1 = a_[k-1];
            const bool rq = ( ak > ak1 );  // rise?
            for (ulong j=1; j < ak+!rq; ++j)  cout << ' ';
            cout << ( rq ? '\\' : ( ak==ak1 ? '|' : '/' ) );
            cout << endl;
        }
    }
}
// -------------------------


void
catalan_path_print_horiz_aa(const ulong *a, ulong n2)
{
    ulong mx = 0;  // max value
    for (ulong j=1; j<n2; ++j)
        if ( a[j] > mx )  mx = a[j];

    ulong v = mx;
    do
    {
#if 1  // simple format using dots
        cout << "  ";
        for (ulong j=0; j<=n2; ++j)
        {
            if ( a[j] == v )  cout << '.';
            else              cout << ' ';
        }
        cout << endl;
#else
        cout << ( v==0 ? '/' : ' ' );
        for (ulong j=1; j<n2; ++j)
        {
            if ( a[j] == v )
            {
                long ql = v - a[j-1];
                long qr = v - a[j+1];
                if ( qr == 0 )  cout << '-';
                else
                {
                    if ( ql > 0 )  // upstep or peak
                    {
                        if ( qr > 0 )  cout << '^';
                        else           cout << '/';
                    }
                    else
                    {
                        if ( (qr < 0 ) )  cout << 'v';
                        else              cout << '\\';
                    }
                }
            }
            else  cout << ' ';
        }
        if ( v==0 )  cout << '\\';
        cout << endl;
#endif
    }
    while ( v-- );

}
// -------------------------

