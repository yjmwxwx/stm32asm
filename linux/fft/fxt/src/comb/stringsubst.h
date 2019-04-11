#if !defined  HAVE_STRINGSUBST_H__
#define       HAVE_STRINGSUBST_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong, uchar
#include "fxtio.h"
//#include "jjassert.h"


class string_subst
// String substitution engine (Lindenmayer system, or L-system).
{
public:
    ulong nlev_;  // that many levels
    uchar *axiom_;  // the axiom
    uchar *rules_;  // all rules
    uchar **lev_ptr_;  // position in levels: [nlev+1]
    // [0] points into axiom_[], [1, 2, ... , nlev_] into rules_[]
    uchar *rule_start_[256];  // ASCII only, pointers into rules_[]

    // the following are only used during initialization
    ulong maxrlen_;  // max that many symbols in all rules combined
    uchar *end_rule_ptr_;  // position in rules_[] after last rule

private:  // have pointer data
    string_subst(const string_subst&);  // forbidden
    string_subst & operator = (const string_subst&);  // forbidden

private:
    void ctor_core(ulong nlev, ulong maxrlen)
    {
        axiom_ = NULL;

        nlev_ = nlev;
        lev_ptr_ = new uchar *[nlev_+1];

        rules_ = new uchar[maxrlen];
        end_rule_ptr_ = rules_;

        for (ulong j=0; j < 256; ++j)  rule_start_[j] = NULL;
        maxrlen_ = maxrlen;
        for (ulong j=0; j < maxrlen_; ++j)  rules_[j] = '\0';
    }

public:
    explicit string_subst(ulong nlev, ulong maxrlen=2048)
    {
        ctor_core(nlev, maxrlen);
    }
    // should write ctor with args (nlev, ax, rules) ?

    ~string_subst()
    {
        delete [] lev_ptr_;
        delete [] rules_;
        delete [] axiom_;
    }

    bool set_axiom(const char *ax);
    bool set_rules(const char *rules[], ulong nr);

private:
    bool add_rule(uchar c, const char *str);
    bool add_rule(const char *c, const char *str);


public:
    char current()  const
    // Current char in lowest level.
    { return *lev_ptr_[nlev_]; }

private:
    char current(ulong lev)  const
    // Current char in level lev.
    {
//        jjassert( lev <= nlev_ );
        return *lev_ptr_[lev];
    }

private:
    bool next(ulong lev)
    // Return whether new symbol could be computed.
    // Once false has been returned, further calls
    //  lead to undefinded behaviour (unless first()
    //  is called again and returns true).
    {
        ++lev_ptr_[lev];  // advance in lev

        if ( *(lev_ptr_[lev]) == '\0' )  // at end?
        {
            if ( lev==0 )  return false;  // current is last (reached end in axiom)

            uchar * c;
            do
            {
                if ( ! next(lev-1) )  return false;  // recursion

                uchar *pc = lev_ptr_[lev-1];
                c = rule_start_[*pc];  // char in level above
            }
            while ( *c == '\0' );  // repeat for 'empty' rules

            lev_ptr_[lev] = c;
        }

        return true;
    }

public:
    bool next()  { return  next(nlev_); }

    bool first()
    {
        if ( ! OK() )  return false;

        lev_ptr_[0] = axiom_ - 1;
        for (ulong j=1; j<=nlev_; ++j)
            lev_ptr_[j] = end_rule_ptr_ - 2;  // shall give '\0' after increment

        return next();
    }

    void print_rules()  const;
    void print_all()  const;

    ulong num_rules()  const;

    bool OK()  const;
};
// -------------------------




#endif  // !defined HAVE_STRINGSUBST_H__
