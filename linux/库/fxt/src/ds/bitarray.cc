// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "ds/bitarray.h"

#include "bits/print-bin.h"
#include "bits/bitsperlong.h"

#include "fxtio.h"

#include "fxttypes.h"


//#define  PRINTVAR(x)  cout << "  "#x" = " << x << endl
#define  PRINTVAR2(s, x)  cout << s << "  "#x" = " << x << endl
void
bitarray::dump()  const
{
    cout << __PRETTY_FUNCTION__ << ": " << endl;
//    cout << "  n_=" << n_ << endl;
    PRINTVAR2("number of bits:", n_);
//    PRINTVAR2("number of words:", nw_);
    PRINTVAR2("fully used words:", nfw_);
//    PRINTVAR2("bits in partially used word:", nbl_);
    PRINTVAR2("mask for partially used word:", mp_);
    cout << " = " << endl;
    print_bin("",mp_, BITS_PER_LONG);
    cout << endl;

    dump_bits();
}
// -------------------------

void
bitarray::dump_bits(ulong prettyq/*=0*/)  const
{
    if ( 0==prettyq )
    {
        for (ulong k=0; k<n_; ++k)  cout << ( test(k) ? '1' : '.' );
//        cout << endl;
    }
    else
    {
        for (ulong k=0; k<n_; ++k)
        {
            if ( (0==(k%8)) && (0!=k) )
            {
                if ( 0==(k%64) )  cout << endl;
                else
                {
                    if ( 0==(k%32) )  cout << " ";
                    cout << " ";
                }
            }
            cout << ( test(k) ? '1' : '.' );
        }
        cout << endl;

        cout << hex;
        ulong k = 0;
        for (  ; k<nfw_; ++k) cout << "[0x" << setw(31) << f_[k] << "]  ";
        if ( mp_ )  cout << "[0x" << f_[k++] << "]";
//        cout << "   [0x" << f_[k] << "]";
        cout << dec;
        cout << endl;
    }
}
// -------------------------
