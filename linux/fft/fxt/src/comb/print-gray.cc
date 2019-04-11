// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/print-bin.h"
#include "bits/bitlow.h"
#include "bits/bit2pow.h"
#include "bits/bitcount.h"

#include "fxtio.h"
#include "fxttypes.h"  // ulong


void
print_gray(const ulong *f, ulong n)
// Pretty print Gray path
{
    const ulong nb = next_exp_of_2(n);
    for (ulong k=0; k<n; ++k)
    {
        ulong p = f[k];
        cout << setw(3) << k << ":  ";
        print_bin("", p, nb);
        cout << " " << bit_count(p);
        cout << "  " << setw(3) << p;
        if ( k<n-1 )
        {
            ulong d = p^f[k+1];
            print_bin("    ", d, nb);
            cout << "  " << lowest_one_idx(d);
        }
        else
        {
            ulong d = p^f[0];
            print_bin("   [", d, nb);
            if ( one_bit_q(d) )  cout << "  " << lowest_one_idx(d) << "";
            else                 cout << "  -";
            cout << "]";
        }
        cout << endl;
    }
    cout << endl;
}
// -------------------------

void
print_gray_delta(const ulong *f, ulong n, ulong lb/*=0*/)
// Print delta seqeunce (base-36).
// If lg!=0 then break line after lg characters.
{
    const char dd[65] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ulong v = f[0];
    for (ulong k=1; k<n; ++k)
    {
        ulong vk = f[k];
        ulong d = v ^ vk;
        v = vk;
        ulong i = lowest_one_idx(d);
        cout << dd[i];
        if ( (lb) && (0==(k%lb)) )  cout << endl;
    }
    cout << endl;
}
// -------------------------
