#if !defined HAVE_NEXTARG_H__
#define      HAVE_NEXTARG_H__

// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//: simple argument parser, mostly for demo programs.

#include "fxtio.h"
#include "fxttypes.h"

#include <cstdlib>  // atol(), atof(), strtoul(), strtod()

// To suppress the output such as
//   arg 1: val == explanation
// insert the (following) line
//#define FXT_SILENT_NXARG
// before the inclusion of this header file.

// To prefix each line with a string, define
//#define FXT_PREF_NXARG  "## "
// This can be useful with redirections and filtering.

static int nextarg_act = 0;

template <typename Type>
void next_arg(Type &v, const char *vname, const char *what,
              int argc, char **argv)
{
    const Type def = v;
    ++nextarg_act;

    if ( argc > nextarg_act )
    {
        if ( argv[nextarg_act][0] != '.' )  // "." for default
        {
            int b = 10;  // default is base 10

            // leading "0x" for base 16:
            if ( (argv[nextarg_act][0]=='0') && (argv[nextarg_act][1]=='x') )  b = 16;

            // leading "_" for base 2:
            if ( argv[nextarg_act][0]=='_' )  { b = 2; argv[nextarg_act]+=1; }

            // check signed-ness:
            Type nextarg_x = 1;
            nextarg_x = -nextarg_x;
            if ( nextarg_x > 0 )  // we have an unsigned type
                v = (Type)strtoul(argv[nextarg_act], 0, b);
            else
                v = (Type)strtol(argv[nextarg_act], 0, b);
        }
    }


#ifndef FXT_SILENT_NXARG
#ifdef FXT_PREF_NXARG
    cout << FXT_PREF_NXARG;
#endif
    cout << "arg " << nextarg_act << ": ";
    cout << v << " == " << vname;
    cout << "  [" << what << "]";
    cout << "  default=" << def;
    cout << endl;
#else
    // supress warnings about unused parameters:
    (void)what;
    (void)vname;
    (void)def;
#endif

}
// -------------------------

void
next_float_arg(double &v, const char *vname, const char *what,
               int argc, char **argv)
{
    const double def = v;
    ++nextarg_act;

    if ( argc > nextarg_act )
    {
        // "." for default, but do parse .123
        if ( (argv[nextarg_act][0] != '.') && (argv[nextarg_act][1] != 0) )
            v = strtod(argv[nextarg_act], 0);
    }

#ifndef FXT_SILENT_NXARG
#ifdef FXT_PREF_NXARG
    cout << FXT_PREF_NXARG;
#endif
    cout << "arg " << nextarg_act << ": ";
    cout << v << " == " << vname;
    cout << "  [" << what << "]";
    cout << "  default=" << def;
    cout << endl;
#else
    // supress warnings about unused parameters:
    (void)what;
    (void)vname;
    (void)def;
#endif
}
// -------------------------

void
next_string_arg(char *&v, const char *vname, const char *what,
               int argc, char **argv,
                char *def)  // need explicit default with strings
{
//    cout << " :: String" << endl;

    ++nextarg_act;
    if ( argc > nextarg_act )  v = argv[nextarg_act];
    else  v = def;

#ifndef FXT_SILENT_NXARG
#ifdef FXT_PREF_NXARG
    cout << FXT_PREF_NXARG;
#endif
    cout << "arg " << nextarg_act << ": ";
    cout << '"' << v << '"' << " == " << vname;
    cout << "  [" << what << "]";
    cout << "  default=" << '"' << def << '"';
    cout << endl;
#else
    // supress warnings about unused parameters:
    (void)what;
    (void)vname;
#endif
}
// -------------------------


#define NXARG(v, what) { next_arg(v, #v, what, argc, argv); }
#define NXARGFL(v, what) { next_float_arg(v, #v, what, argc, argv); }
#define NXARGSTR(v, what, def) { next_string_arg(v, ""#v, what, argc, argv, (char *)def); }

#ifdef FXT_SILENT_NXARG
#define RESTARGS_MSG(what)  // silence
#else
#define RESTARGS_MSG(what) \
  cout << "args " << nextarg_act \
  << ","<< nextarg_act+1 << ",... : [" << what <<"]" << endl;
#endif

#define RESTARGS(what) { ++nextarg_act; RESTARGS_MSG(what); }



#endif // !defined HAVE_NEXTARG_H__
