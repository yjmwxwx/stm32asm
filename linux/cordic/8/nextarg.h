#if !defined HAVE_NEXTARG_H__
    2 #define      HAVE_NEXTARG_H__
    3 
    4 // This file is part of the FXT library.
    5 // Copyright (C) 2010, 2011, 2012, 2013, 2014, 2015 Joerg Arndt
    6 // License: GNU General Public License version 3 or later,
    7 // see the file COPYING.txt in the main directory.
    8 
    9 //: simple argument parser, mostly for demo programs.
   10 
   11 #include "fxtio.h"
   12 #include "fxttypes.h"
   13 
   14 #include <cstdlib>  // atol(), atof(), strtoul(), strtod()
   15 
   16 // To suppress the output such as
   17 //   arg 1: val == explanation
   18 // insert the (following) line
   19 //#define FXT_SILENT_NXARG
   20 // before the inclusion of this header file.
   21 
   22 // To prefix each line with a string, define
   23 //#define FXT_PREF_NXARG  "## "
   24 // This can be useful with redirections and filtering.
   25 
   26 static int nextarg_act = 0;
   27 
   28 template <typename Type>
   29 void next_arg(Type &v, const char *vname, const char *what,
   30               int argc, char **argv)
   31 {
   32     const Type def = v;
   33     ++nextarg_act;
   34 
   35     if ( argc > nextarg_act )
   36     {
   37         if ( argv[nextarg_act][0] != '.' )  // "." for default
   38         {
   39             int b = 10;  // default is base 10
   40 
   41             // leading "0x" for base 16:
   42             if ( (argv[nextarg_act][0]=='0') && (argv[nextarg_act][1]=='x') )  b = 16;
   43 
   44             // leading "_" for base 2:
   45             if ( argv[nextarg_act][0]=='_' )  { b = 2; argv[nextarg_act]+=1; }
   46 
   47             // check signed-ness:
   48             Type nextarg_x = 1;
   49             nextarg_x = -nextarg_x;
   50             if ( nextarg_x > 0 )  // we have an unsigned type
   51                 v = (Type)strtoul(argv[nextarg_act], 0, b);
   52             else
   53                 v = (Type)strtol(argv[nextarg_act], 0, b);
   54         }
   55     }
   56 
   57 
   58 #ifndef FXT_SILENT_NXARG
   59 #ifdef FXT_PREF_NXARG
   60     cout << FXT_PREF_NXARG;
   61 #endif
   62     cout << "arg " << nextarg_act << ": ";
   63     cout << v << " == " << vname;
   64     cout << "  [" << what << "]";
   65     cout << "  default=" << def;
   66     cout << endl;
   67 #else
   68     // supress warnings about unused parameters:
   69     (void)what;
   70     (void)vname;
   71     (void)def;
   72 #endif
   73 
   74 }
   75 // -------------------------
   76 
   77 void
   78 next_float_arg(double &v, const char *vname, const char *what,
   79                int argc, char **argv)
   80 {
   81     const double def = v;
   82     ++nextarg_act;
   83 
   84     if ( argc > nextarg_act )
   85     {
   86         // "." for default, but do parse .123
   87         if ( (argv[nextarg_act][0] != '.') && (argv[nextarg_act][1] != 0) )
   88             v = strtod(argv[nextarg_act], 0);
   89     }
   90 
   91 #ifndef FXT_SILENT_NXARG
   92 #ifdef FXT_PREF_NXARG
   93     cout << FXT_PREF_NXARG;
   94 #endif
   95     cout << "arg " << nextarg_act << ": ";
   96     cout << v << " == " << vname;
   97     cout << "  [" << what << "]";
   98     cout << "  default=" << def;
   99     cout << endl;
  100 #else
  101     // supress warnings about unused parameters:
  102     (void)what;
  103     (void)vname;
  104     (void)def;
  105 #endif
  106 }
  107 // -------------------------
  108 
  109 void
  110 next_string_arg(char *&v, const char *vname, const char *what,
  111                int argc, char **argv,
  112                 char *def)  // need explicit default with strings
  113 {
  114 //    cout << " :: String" << endl;
  115 
  116     ++nextarg_act;
  117     if ( argc > nextarg_act )  v = argv[nextarg_act];
  118     else  v = def;
  119 
  120 #ifndef FXT_SILENT_NXARG
  121 #ifdef FXT_PREF_NXARG
  122     cout << FXT_PREF_NXARG;
  123 #endif
  124     cout << "arg " << nextarg_act << ": ";
  125     cout << '"' << v << '"' << " == " << vname;
  126     cout << "  [" << what << "]";
  127     cout << "  default=" << '"' << def << '"';
  128     cout << endl;
  129 #else
  130     // supress warnings about unused parameters:
  131     (void)what;
  132     (void)vname;
  133 #endif
  134 }
  135 // -------------------------
  136 
  137 
  138 #define NXARG(v, what) { next_arg(v, #v, what, argc, argv); }
  139 #define NXARGFL(v, what) { next_float_arg(v, #v, what, argc, argv); }
  140 #define NXARGSTR(v, what, def) { next_string_arg(v, ""#v, what, argc, argv, (char *)def); }
  141 
  142 #ifdef FXT_SILENT_NXARG
  143 #define RESTARGS_MSG(what)  // silence
  144 #else
  145 #define RESTARGS_MSG(what) \
  146   cout << "args " << nextarg_act \
  147   << ","<< nextarg_act+1 << ",... : [" << what <<"]" << endl;
  148 #endif
  149 
  150 #define RESTARGS(what) { ++nextarg_act; RESTARGS_MSG(what); }
  151 
  152 
  153 
  154 #endif // !defined HAVE_NEXTARG_H__
