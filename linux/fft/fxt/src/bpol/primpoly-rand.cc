// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "array-len.h"
#include "fxttypes.h"
#include "bits/bitsperlong.h"

extern const ulong rand_primpoly[]=
//
//  'random' primitive polynomials over Z/2Z
//  Generated by Joerg Arndt, 2002-December-16
//
{
    //  hex_val,  // ==dec_val  (deg)  [weight]
    0x1,         // 1  (0)  [1]
    0x3,         // 3  (1)  [2]
    0x7UL,   // ==7  (2)  [3]
    0xdUL,   // ==13  (3)  [3]
    0x19UL,   // ==25  (4)  [3]
    0x2fUL,   // ==47  (5)  [5]
    0x61UL,   // ==97  (6)  [3]
    0xcbUL,   // ==203  (7)  [5]
    0x169UL,   // ==361  (8)  [5]
    0x22dUL,   // ==557  (9)  [5]
    0x519UL,   // ==1305  (10)  [5]
    0xdd7UL,   // ==3543  (11)  [9]
    0x1e19UL,   // ==7705  (12)  [7]
    0x2cd1UL,   // ==11473  (13)  [7]
    0x6fc7UL,   // ==28615  (14)  [11]
    0x9ab9UL,   // ==39609  (15)  [9]
    0x167bfUL,   // ==92095  (16)  [13]
    0x20dd3UL,   // ==134611  (17)  [9]
    0x5e01dUL,   // ==385053  (18)  [9]
    0x8bb35UL,   // ==572213  (19)  [11]
    0x1f31adUL,   // ==2044333  (20)  [13]
    0x2ff40dUL,   // ==3142669  (21)  [13]
    0x55341bUL,   // ==5583899  (22)  [11]
    0xbcbcd5UL,   // ==12369109  (23)  [15]
    0x11ac2a9UL,   // ==18530985  (24)  [11]
    0x2ce0549UL,   // ==47056201  (25)  [11]
    0x5614a83UL,   // ==90262147  (26)  [11]
    0xd4d43bfUL,   // ==223167423  (27)  [17]
    0x1362b069UL,   // ==325234793  (28)  [13]
    0x34f78df1UL,   // ==888638961  (29)  [19]
    0x672e380bUL,   // ==1731082251  (30)  [15]
    0xa0aa95b5UL,   // ==2695534005  (31)  [15]

#if  ( BITS_PER_LONG <= 32 )
    0xb58407f3UL,   // ==7340296179  (32)  [17]  // highest bit stripped
#endif

#if  ( BITS_PER_LONG > 32 )
    0x1b58407f3UL,   // ==7340296179  (32)  [17]
    0x2ba1a2d63UL,   // ==11712212323  (33)  [17]
    0x68b45dfd5UL,   // ==28106416085  (34)  [21]
    0xb6ff04549UL,   // ==49122657609  (35)  [19]
    0x1adf188abdUL,   // ==115412077245  (36)  [21]
    0x29137b093bUL,   // ==176420489531  (37)  [19]
    0x6da387ecf7UL,   // ==470895029495  (38)  [25]
    0xaec451ff35UL,   // ==750618017589  (39)  [23]
    0x1037c711aebUL,   // ==1114484316907  (40)  [21]
    0x3c4bfd42371UL,   // ==4143566824305  (41)  [23]
    0x7c76ef77783UL,   // ==8553141598083  (42)  [29]
    0x9926c63bb2bUL,   // ==10524488350507  (43)  [23]
    0x128567464a91UL,   // ==20364172610193  (44)  [19]
    0x30553e820e61UL,   // ==53142679064161  (45)  [19]
    0x4e1e7d477c5fUL,   // ==85892857822303  (46)  [29]
    0xf98b297fbc2dUL,   // ==274376092007469  (47)  [29]
    0x175172c131c2bUL,   // ==410217360858155  (48)  [23]
    0x3b4d2b731290bUL,   // ==1043242039716107  (49)  [25]
    0x780c53ec06213UL,   // ==2111909486682643  (50)  [21]
    0xa2dcde152d581UL,   // ==2865112038954369  (51)  [25]
    0x1fe3170f11372bUL,   // ==8975412454569771  (52)  [29]
    0x2d1eecbbef641dUL,   // ==12700376066122781  (53)  [33]
    0x52c695edeb3f1bUL,   // ==23299295334317851  (54)  [33]
    0xb81d4e2f988aebUL,   // ==51823617357941483  (55)  [29]
    0x16ee571eef65fb7UL,   // ==103272118979289015  (56)  [39]
    0x32cad78a78b3c95UL,   // ==228748414807653525  (57)  [31]
    0x614c43d1eb82377UL,   // ==438190830549214071  (58)  [29]
    0xfbc74fab33eba5dUL,   // ==1133909826288400989  (59)  [39]
    0x106d48b6f49abddfUL,   // ==1183682227693338079  (60)  [35]
    0x2ec7a0dafd22d727UL,   // ==3370839708520339239  (61)  [35]
    0x7bb112d2b9a692cbUL,   // ==8912925833810055883  (62)  [33]
    0xf57e4c46021c3b03UL,   // ==17689660249924713219  (63)  [29]
//#if 0
    0x830f7db354117363UL,   // ==9443905152782267235  (64)  [33]
//#endif  // 0
#endif  // ( BITS_PER_LONG > 32 )
};
// -------------------------

extern const ulong rand_primpoly_len = ARRAY_LEN(rand_primpoly);

