#if !defined  HAVE_STRINGSUBST_H__
#define       HAVE_STRINGSUBST_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong


class string_subst
// String substitution engine (Lindenmayer system, or L-system).
{
public:
    // example values generate rabbit sequence:
    // supplied arg { "a", "b",  "b", "ba" } (for  a |-> b,  b |-> ba)
    // will result in
    ulong nsym_;    // number of symbols
    // nsym_ == 2
    char *symbol_;   // alphabet
    // symbol_[] == { 'a', 'b' }
    const char ** symrule_;  // symrule_[i] points to string to replace i-th symbol with
    // symrule_[] = == { &"b",  &"ba" }  (referenced, not copied)

    ulong xlate_[128];  // translate char |-> rule
    //  'a' |-> symrule[ xlate['a'] ]

    ulong cmax_;  // max string length
    char  *cc_;  // string to hold result
    ulong ctc_;  // count chars of result actually produced

private:  // have pointer data
    string_subst(const string_subst&);  // forbidden
    string_subst & operator = (const string_subst&);  // forbidden

private:
    void setup(ulong cmax, ulong nsym, const char ** symrule)
    {
        nsym_=  nsym;
        cmax_ = cmax;
        cc_ = new char[cmax_ + 1];
        symbol_ = new char[nsym_+1];
        symbol_[nsym_] = 0;
        symrule_ = new const char *[nsym_+1];  // one for the start-string

        for (ulong i=0; i<128; ++i)  xlate_[i] = ~0UL;

        for (ulong i=0, k=0;  i<nsym_;  ++i, k+=2)  // fill in symbols
        {
            // no check whether string longer than 1:
            symbol_[i] = symrule[k][0];
            symrule_[i] = symrule[k+1];  // strings are not copied
            xlate_[ (ulong)symbol_[i] ] = i;
        }
    }


public:
    explicit string_subst(ulong cmax, ulong nsym, const char ** symrule)
    {
        setup(cmax, nsym, symrule);
    }

    ~string_subst()
    {
        delete [] symbol_;
        delete [] symrule_;
        delete [] cc_;
    }

    const char* string()  const  { return cc_; }


private:
    const char *get_repstr(char c)  const
    // Return (pointer to) string that replaces c
    {
        ulong r = (ulong)c;
        ulong x = xlate_[r];  // position of rule in symrule_
        return symrule_[x];   // the string that replaces c
    }

    void do_subst(ulong n, const char *rule)
    {
        if ( 0==n )  // append string rule[]:
        {
            for (ulong i=0;  0!=rule[i];  ++i)
            {
                if ( ctc_ >= cmax_ )  return;
                cc_[ ctc_++ ] = rule[i];
            }
        }
        else  // recurse:
        {
            for (ulong i=0;  0!=rule[i];  ++i)
            {
                do_subst(n-1, get_repstr( rule[i] ) );
            }
        }
    }


public:
    ulong subst(ulong maxn, const char *start)
    // Return number of characters written to string cc_[].
    // maxn:=number of generations,  start:=axiom
    {
        ctc_ = 0;
        do_subst(maxn, start);
        cc_[ctc_] = 0;  // terminate string
        return  ctc_;
    }


    void print_rules(const char *start=0);

    int verify(const char *start="", bool vq=true);
};
// -------------------------


#endif  // !defined HAVE_STRINGSUBST_H__
