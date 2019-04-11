// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/crc32.h"
#include "fxttypes.h"


// A few binary primitive polynomials that
// can be used to initialize a crc32.
// The highest bit is not (and cannot be for wordsize<=32) included.
// Example:
//  crc32 crc( crc32::cc[3] );
// These are the first 16 polynomials given in data/rand32-hex-primpoly.txt
const uint crc32::cc[] = {
    0x9a743f93U,  // [0]
    0x85640defU,  // [1]
    0xad90d77fU,  // [2]
    0xf5929c15U,  // [3]
    0xcb6c2743U,  // [4]
    0xc5df469fU,  // [5]
    0xbcae95b1U,  // [6]
    0x8fa999e9U,  // [7]
    0xdb19f7c9U,  // [8]
    0xc72c7061U,  // [9]
    0xfd6e4507U,  // [10]
    0xb7602b21U,  // [11]
    0xf535fcffU,  // [12]
    0xbda7ac7fU,  // [13]
    0x99db510bU,  // [14]
    0xc5d379dbU,  // [15]
};
// -------------------------
