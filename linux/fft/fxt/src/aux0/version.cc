// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtio.h"


// Next line changed by make target "version":
static const char *version_string = "25-July-2017";


void
print_fxt_version()
// Print fxt version (by date), compile time, and flags.
{
    cout << "  ----=============== FXT version " << version_string << " ================---- " << endl;
    cout << "       author: Joerg Arndt,  email: arndt (AT) jjj.de " << endl;
#if defined  __GNUC__
//#define  XSTR(s)  STR(s)
//#define  STR(s)  #s
    cout << "     compiler used: GNU C " << __VERSION__ << endl;
    cout << "     compilation date: " << __DATE__  << ", " << __TIME__ << endl;
#if defined OFLAGS
    cout << "     compilation flags were:\n   " << OFLAGS << endl;
#endif  // OFLAGS
#endif  // __GNUC__
    cout << "        FXT is online at http://www.jjj.de/fxt/   " << endl;
    cout << "  ----===========================================================----  " << endl;
    cout << endl;
}
// -------------------------
