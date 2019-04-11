// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include <sys/types.h>
#include <csignal>  // raise()
//#include <unistd.h>  // getpid(), pause()

#include <cstdlib>  // abort()
//#include <cstdio>  // setvbuf()

#include "jjassert.h"
#include "fxtio.h"

static int fail_action = JJ_ASSERT_DEFAULT;

void
set_fail_action(int a/*=JJ_ASSERT_DEFAULT*/)
{
    fail_action = a;
}
// -------------------------


void
jjassert_fail(
              const char *func,
              const char *pretty_func,
              const char *file,
              const int   line,
              const char *expr,
              const char *bla
              )
{
//    setvbuf(stdout, NULL, _IONBF, 0); // changes stdout to unbuffered (_IONBF) mode.

    cout.flush();  // want stdout flushed before the messages below

    cerr << endl;

    cerr << "FAILED ASSERTION: ( " << expr << " )";
    cerr << endl;

    cerr << " FUNCTION: \"" << func << "()\"";
    cerr << endl;

    cerr << " FILE: " << file
         << " (line " << line << ")";
    cerr << endl;

    cerr << " PRETTY_FUNCTION: \"" << pretty_func << "\"";
    cerr << endl;

    if ( bla )  cerr << " REASON: " << bla << endl;

    cerr << endl;


 do_fail:
    switch ( fail_action )
    {
    case JJ_ASSERT_IGNORE: ; break;  // happily continue into disaster

    case JJ_ASSERT_ABORT:  abort(); //break;  // no return
        // See man 2 abort

//    case JJ_ASSERT_PAUSE:  pause(); break;
    case JJ_ASSERT_SEGV:  raise(SIGSEGV); break;  // no return
    case JJ_ASSERT_STOP:  raise(SIGSTOP); break;

    default: fail_action = JJ_ASSERT_DEFAULT;  goto do_fail;
    }
}
// -------------------------



