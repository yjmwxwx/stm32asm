// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/reverse-paren-string.h"
#include "fxttypes.h"


void
rgs_to_paren_string(const ulong *rgs, ulong n, char *str, bool rq=false)
// Convert restricted growth string (Catalan-RGS) to paren-string.
// If rq is set then the reversed paren string is computed.
{
    str[2*n] = '\0';
    if ( n==0 )  return;  // nothing to do

    for (ulong k=0; k < 2*n; ++k)  str[k] = ')';
    for (ulong k=0, j=0;  k<n;  ++k, j+=2)  str[ j - rgs[k] ] = '(';

    if ( rq )  reverse_paren_string(str, 2*n);
}
// -------------------------


bool
paren_string_to_rgs(const char *str, ulong *rgs)
// Convert paren-string to RGS,
// return whether parenthesis string is valid.
// rgs[j] = number of unclosed open parenthesis when
//  the j-th opening is found (j>=0).
// If rq is set then the RGS for the reversed paren string is computed.
{
    if ( str[0] == 0 )  return true;  // nothing to do

    long s = 0;  // running sum
    ulong jr = 0;  // position in RGS
    const char c1 = str[0];
//    if ( !rq )
    {
        for (ulong js=0; str[js]!=0; ++js)
        {
//            if ( str[js] == '(' )
            if ( str[js] == c1 )
            {
                rgs[jr] = (ulong)s;
                ++jr;
                ++s;
            }
            else
            {
                --s;
                if ( s<0 )  return false;
            }
        }
    }
//    else
//    {
//        ulong js = 0;
//        while ( str[js] )  ++js;  // seek end
//
//        while ( js-- )
//        {
////            if ( str[js] == ')' )
//            if ( str[js] != c1 )
//            {
//                rgs[jr] = (ulong)s;
//                ++jr;
//                ++s;
//            }
//            else
//            {
//                --s;
//                if ( s<0 )  return false;
//            }
//        }
//    }

    return (s==0);
}
// -------------------------



static const char *S = ".1";

void
rgs_to_paren_bit_string(const ulong *rgs, ulong n, char *str, bool rq=false)
// Convert restricted growth string (Catalan-RGS) to paren-bit-string.
// If rq is set then the reversed paren string is computed.
{
    if ( n==0 )  return;  // nothing to do

    for (ulong k=0; k < 2*n; ++k)  str[k] = S[0];  // ')';
    for (ulong k=0, j=0;  k<n;  ++k, j+=2)  str[ j - rgs[k] ] = S[1] ;  // '(';

    if ( rq )  reverse_paren_string(str, 2*n);
}
// -------------------------



bool
paren_bit_string_to_rgs(const char *str, ulong *rgs)
// Convert paren-bit-string to RGS.
// Return whether parenthesis string is valid.
// If rq is set then the RGS for the reversed paren string is computed.
{
    if ( str[0] == 0 )  return true;  // nothing to do

    long s = 0;  // running sum
    ulong jr = 0;  // position in RGS

    const char c1 = str[0];

//    if ( !rq )
    {
        for (ulong js=0; str[js]!=0; ++js)
        {
//            if ( str[js] == 1 )  // '('
//            if ( str[js] == S[1] )  // '('
            if ( str[js] == c1 )  // '('
            {
                rgs[jr] = (ulong)s;
                ++jr;
                ++s;
            }
            else
            {
                --s;
                if ( s<0 )  return false;
            }
        }
    }
//    else
//    {
//        ulong js = 0;
//        while ( str[js]!=0 )  ++js;
//
//        while ( js-- )
//        {
////            if ( str[js] == 0 )  // ')'
////            if ( str[js] == S[0] )  // ')'
//            if ( str[js] != c1 )  // ')'
//            {
//                rgs[jr] = (ulong)s;
//                ++jr;
//                ++s;
//            }
//            else
//            {
//                --s;
//                if ( s<0 )  return false;
//            }
//        }
//    }

    return (s==0);
}
// -------------------------

