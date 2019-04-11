// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/stringsubst.h"
#include "fxtio.h"
#include "fxttypes.h"  // ulong


void
string_subst::print_rules(const char *start/*=0*/)
{
    cout << "Number of symbols = " << nsym_ << endl;
    if ( start )  cout << "Start: " << start << endl;
    cout << "Rules:" << endl;
    for (ulong j=0; j<nsym_; ++j)
    {
        cout << "  " << symbol_[j] << " --> " << symrule_[j] << endl;
    }
}
// -------------------------

int
string_subst::verify(const char *start/*=""*/, bool vq/*=true*/)
{
    int ret = 0;
    for (ulong i=0;  0!=symbol_[i];  ++i)  // for all symbols
    {
        char si = symbol_[i];
        // check it appears just once:
        ulong j;
        for (j=i+1;  0!=symbol_[j];  ++j)
        {
            if ( si == symbol_[j] )  break;
        }
        if ( j < nsym_ )
        {
            if ( vq )
            {
                cout << "ERROR:" << endl;
                cout << " there are two rules for symbol " << si << endl;
                cout << " (rules #" << i << " and #" << j << ")" << endl;
            }
            ret += 1;
        }
    }

    symrule_[nsym_] = start;
    for (ulong i=0;  i<nsym_+1;  ++i)  // for all rules and start:
    {
        const char *r = symrule_[i];
        for (ulong j=0;  0!=r[j];  ++j)  // ... and each symbol in rule:
        {
            char rs = r[j];
            ulong k;
            // search whether symbol is in table:
            for (k=0; k<nsym_; ++k)  if ( rs == symbol_[k] )  break;

            if ( k==nsym_ )
            {
                if ( vq )
                {
                    cout << endl;
                    cout << "ERROR in rules (or start):" << endl;
                    cout << " found rule == '" << symrule_[i] << "'" << endl;
                    cout << "   contains a symbol '" << rs << "'"
                         << " but there is no rule for that symbol." << endl;
                }
                ret += 2;
                goto end_2;
            }
        }
    }
 end_2:

    return  ret;
}
// -------------------------
