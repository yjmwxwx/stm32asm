// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/stringsubst.h"

#include "fxtio.h"
#include "fxttypes.h"  // ulong, uchar
#include <cstring>  // strlen()


bool
string_subst::set_axiom(const char *ax)
{
    if ( axiom_ != NULL )  // can/should we avoid this?
    {
        cerr << " string_subst: set_axiom(): axiom already set." << endl;
        return false;
    }
    ulong e = 0;
    while ( ax[e] != '\0' )  { ++e; }

    if ( e == 0 )  // we could allow this
    {
        cerr << " string_subst: set_axiom(): empty axiom forbidden." << endl;
        return false;
    }

    axiom_ = new uchar[e+1];
    for (ulong j=0; j<=e; ++j)  axiom_[j] = ax[j];
    return true;
}
// -------------------------


bool
string_subst::set_rules(const char *rules[], ulong nr)
{
    if ( end_rule_ptr_ != rules_ )  // can/should we avoid this?
    {
        cerr << " string_subst: set_rules():"
             << " rules already set." << endl;
        return false;
    }

    if ( (nr & 1) == 1 )
    {
        cerr << " string_subst: set_rules():"
             << " need an even number of strings." << endl;
        return false;
    }

    ulong rsz = 0;  // sum of sizes of all images
    for (ulong j=1; j<nr; j+=j)
        rsz += strlen(rules[j]) + 1;

    if ( rsz > maxrlen_ )  // need to resize rules_[]
    {
        maxrlen_ = rsz;
        delete [] rules_;
        rules_ = new uchar[maxrlen_];
        end_rule_ptr_ = rules_;
    }


    for (ulong j=0; j<nr; j+=2)
    {
//        cout << " :: adding rule ";
//        cout << " [" << rules[j] << "]  -->";
//        cout << " [" << rules[j+1] << "]";
//        cout << endl;
        if ( ! add_rule(rules[j], rules[j+1]) )
            return false;
    }
    return true;
}
// -------------------------

bool
string_subst::add_rule(uchar c, const char *str)
{
    if ( c == '\0')
    {
        cerr << " string_subst: add_rule(): char == 0 forbidden." << endl;
        return false;
    }

    if ( rule_start_[(ulong)c] != NULL )
    {
        cerr << " string_subst: add_rule(): rule for char = [" << c << "] already set." << endl;
        return false;
    }
    rule_start_[(ulong)c] = end_rule_ptr_;

    ulong j = 0;
    uchar r;
    do  // can only fail with invalid call from within class
    {
        r = str[j];
        ++j;
        if ( end_rule_ptr_ >= rules_ + maxrlen_  )
        {
            cerr << " string_subst: add_rule(): internal error: out of space for rules." << endl;
            return false;
        }
        *end_rule_ptr_ = r;
        ++end_rule_ptr_;
    }
    while ( r != '\0' );
    return true;
}
// -------------------------

bool
string_subst::add_rule(const char *c, const char *str)
{
    if ( c[0] == '\0')
    {
        cerr << " string_subst: add_rule(): char == 0 forbidden." << endl;
        return false;
    }

    if ( c[1] != '\0' )
    {
        cerr << " string_subst: add_rule(): left side more than one symbol." << endl;
        return false;
    }
    return  add_rule(c[0], str);
}
// -------------------------

void
string_subst::print_rules()  const
{
//    cout << "Start: " << axiom_ << endl;
    cout << "Axiom: " << axiom_ << endl;
    cout << "Rules:" << endl;
    for (ulong j=0; j<256; ++j)
    {
        uchar *c = rule_start_[j];
        if ( c == NULL )  continue;
        cout << "  " << (char)j << " --> ";
        uchar s;
        while ( (s = *c) != '\0' )
        {
            cout << s;
            ++c;
        }
        cout << endl;
    }
}
// -------------------------


void
string_subst::print_all()  const
{
    print_rules();
    for (ulong lev=0; lev <= nlev_; ++lev)
        cout << " lev " << lev << ": [" << current(lev) << "]" << endl;
}
// -------------------------

ulong
string_subst::num_rules()  const
{
    ulong ct = 0;
    for (ulong j=0; j<256; ++j)  ct += (rule_start_[j] != NULL);
    return ct;
}
// -------------------------

bool
string_subst::OK()  const
// Shall be called only after set_axiom() and set_rules() are called.
{
    if ( axiom_ == NULL )
    {
        cerr << " string_subst:"
             << " axiom not set." << endl;
        return false;
    }

    if ( end_rule_ptr_ == rules_ )
    {
        cerr << " string_subst:"
             << " no rules set." << endl;
        return false;
    }

    if ( *(end_rule_ptr_ - 1) != '\0' )
    {
        cerr << " string_subst:"
             << " internal error: [*(end_rule_ptr_ - 1) != null_char]." << endl;
        return false;
    }

    // have rules for all symbols?
    for (ulong j=1; j<256; ++j)  // symbols in rules_[]
    {
        uchar * p = rule_start_[j];
        if ( p == NULL )  continue;
        uchar c0 = (uchar)j;
        while ( *p != '\0' )
        {
            if ( rule_start_[*p] == NULL )
            {
                cerr << " string_subst:  char == '" << *p << "'"
                     << " in rhs. of rule for '" << c0 << "'"
                     << " has no rule." << endl;
                return false;
            }
            ++p;
        }
    }
    for (uchar *p=axiom_; *p != '\0'; ++p)  // symbols in axiom_[]
    {
        if ( rule_start_[*p] == NULL )
        {
            cerr << " string_subst:  char == '" << *p << "'"
                 << " in axiom has no rule." << endl;
            return false;
        }
    }
    return true;
}
// -------------------------

