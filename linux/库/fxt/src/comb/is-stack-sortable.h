#if !defined HAVE_IS_STACK_SORTABLE_H__
#define      HAVE_IS_STACK_SORTABLE_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxtalloca.h"
#include "fxttypes.h"
//#include "jjassert.h"

template <typename Type>
bool is_stack_sortable(const Type *a, ulong n)
// Return whether array a[] is stack-sortable.
// Routine also works for non-distinct values.
//
// Among the permutations of n elements the stack-sortable ones are
// counted by the Catalan numbers (OEIS sequence A000108), these
// are the 231-avoiding permutations.
// See:
//   Mireille Bousquet-Melou:
//   Sorted and/or sortable permutations,
//   Discrete Mathematics, vol.225, no.1-3, pp.25-50, (2000).
{
    if ( n <= 2 )  return true;  // always stack-sortable

    ALLOCA(Type, S, n);  // stack
    S[0] = a[0];
    ulong ns = 1;  // stack end (number of elements on stack)

    Type tt = 0;  // largest element of already sorted elements

    // try to stack-sort:
    for (ulong j=1; j<n; ++j)
    {
        Type d = a[j];  // next element to process

        // remove elements from stack while stack top > d
//        jjassert( ns );  // OK
        do
        {
            Type st = S[ns-1];  // peek at stack top
            if ( st >= d )  break;  // can push d on stack
            if ( st < tt )  return false;
            tt = st;  // update largest of already sorted elements
            --ns;  // pop stack top
        }
        while ( ns != 0 );

        S[ns++] = d;  // push d on stack
    }

//    jjassert( ns );  // OK as last action in loop is a push
    // dropping the following gives A033321:
    Type st = S[ns-1];
    if ( st < tt )  return false;

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_STACK_SORTABLE_H__
