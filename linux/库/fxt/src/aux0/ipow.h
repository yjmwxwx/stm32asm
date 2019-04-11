#if !defined  HAVE_IPOW_H__
#define       HAVE_IPOW_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

template <typename Type1, typename Type2>
Type1 ipow(Type1 a, Type2 ex)
// Return a**ex
{
    if ( 0==ex )  return 1;
    else
    {
        Type1 z = a;
        Type1 y = 1;
        while ( 1 )
        {
            if ( ex & 1 )  y *= z;
            ex /= 2;
            if ( 0==ex )  break;
            z *= z;
        }
        return y;
    }
}
// -------------------------


#endif  // !defined HAVE_IPOW_H__
