
#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitasm.h"
#include "bits-all.h"
#include "bits/print-bin.h"
#include "jjassert.h"
#include "fxtio.h"

#include <cstdlib> // rand()



#if  BITS_PER_LONG == 64
static inline ulong knuth_revbin64(ulong x)
{
  ulong y;
  x = ((x>>1) & 0x5555555555555555UL) | ((x & 0x5555555555555555UL) << 1);
  y = (x ^ (x>>4))  & 0x0300c0303030c303UL;  x ^= y ^ (y<<4);
  y = (x ^ (x>>8))  & 0x00c0300c03f0003fUL;  x ^= y ^ (y<<8);
  y = (x ^ (x>>20)) & 0x00000ffc00003fffUL;  x ^= y ^ (y<<20);
  x = (x>>34) | (x<<30);
  return(x);
}
// -------------------------

//static inline ulong jjx_revbin54(ulong x)
//{
//    ulong z;
//    z = (x ^ (x <<  2)) & 0x4924924924924924UL;  x ^= z ^ (z >>  2);  // 3-runs reversed
//    z = (x ^ (x <<  6)) & 0x70381c0e070381c0UL;  x ^= z ^ (z >>  6);  // 9-runs reversed
//    z = (x ^ (x << 18)) & 0x003fe00007fc0000UL;  x ^= z ^ (z >> 18);  // 27-runs reversed
////    z = (x ^ (x << 54)) & 0xffc0000000000000UL;  x ^= z ^ (z >> 54);  // 81-runs ???
//    x = ( (x<<27) | (x>>27) ) & ( (1UL<<54) - 1 );  // 54-runs reversed OK
//    return x;
//}
//// -------------------------


static inline ulong jj3_revbin64(ulong x)
{
    ulong z;
//    z = (x ^ (x >>  2)) & 0b1001001001001001001001001001001001001001001001001001001001001001UL;  x ^= z ^ (z <<  2);  // clear highest bit
//    z = (x ^ (x >>  2)) & 0x9249249249249249UL;  x ^= z ^ (z <<  2);  // clear highest bit

#if 1
    const ulong m02 = 0x1249249249249249UL;
    const ulong m06 = 0x01c0e070381c0e07UL;
    const ulong m18 = 0x00001ff0000001ffUL;
    const ulong m36 = 0x0000000007ffffffUL;
#else  // using GCC's binary literals
    const ulong m02 = 0b0001001001001001001001001001001001001001001001001001001001001001UL;
    const ulong m06 = 0b0000000111000000111000000111000000111000000111000000111000000111UL;
    const ulong m18 = 0b0000000000000000000111111111000000000000000000000000000111111111UL;
    const ulong m36 = 0b0000000000000000000000000000000000000111111111111111111111111111UL;
#endif

    z = (x ^ (x >>  2)) & m02;  x ^= z ^ (z <<  2);  // low  3 bits reversed
    z = (x ^ (x >>  6)) & m06;  x ^= z ^ (z <<  6);  // low  9 bits reversed
    z = (x ^ (x >> 18)) & m18;  x ^= z ^ (z << 18);  // low 27 bits reversed
    z = (x ^ (x >> 36)) & m36;  x ^= z ^ (z << 36);  // low 63 bits reversed

    x = (x>>63) | (x<<1);  // rotate left by 1
    return x;
}
// -------------------------


static inline uint jj3_revbin32(uint x)
{
    uint z;
#if 1
    z = (x ^ (x >>  2)) & 0x12491249U;  x ^= z ^ (z <<  2);
    z = (x ^ (x >>  6)) & 0x00380038U;  x ^= z ^ (z <<  6);
    z = (x ^ (x >> 12)) & 0x00070007U;  x ^= z ^ (z << 12);
    z = (x ^ (x >> 16)) & 0x00007fffU;  x ^= z ^ (z << 16);
#else  // same code using GCC's binary literals
    z = (x ^ (x >>  2)) & 0b00010010010010010001001001001001U;  x ^= z ^ (z <<  2);
    z = (x ^ (x >>  6)) & 0b00000000001110000000000000111000U;  x ^= z ^ (z <<  6);
    z = (x ^ (x >> 12)) & 0b00000000000001110000000000000111U;  x ^= z ^ (z << 12);
    z = (x ^ (x >> 16)) & 0b00000000000000000111111111111111U;  x ^= z ^ (z << 16);
#endif
    x = (x>>31) | (x<<1);  // rotate left by 1
    return x;
}
// -------------------------

static inline uint jj3_revbin32_4a(uint x)
{
    uint z;
#if 1
    z = (x ^ (x >>  1)) & 0x4a52a529U;  x ^= z ^ (z <<  1);
    z = (x ^ (x >>  3)) & 0x18c60c63U;  x ^= z ^ (z <<  3);
    z = (x ^ (x >> 10)) & 0x003e001fU;  x ^= z ^ (z << 10);
    z = (x ^ (x >> 17)) & 0x00007fffU;  x ^= z ^ (z << 17);
#else  // same code using GCC's binary literals
    z = (x ^ (x >>  1)) & 0b01001010010100101010010100101001U;  x ^= z ^ (z <<  1);
    // [ 2 ] --> [ 1 1 ]
    z = (x ^ (x >>  3)) & 0b00011000110001100000110001100011U;  x ^= z ^ (z <<  3);
    // [ 5 ] --> [ 2 1 2 ]
    z = (x ^ (x >> 10)) & 0b00000000001111100000000000011111U;  x ^= z ^ (z << 10);
    // [ 15 ] --> [ 5 5 5 ]  ~ [ 5 5 5  2  5 5 5 ]
    z = (x ^ (x >> 17)) & 0b00000000000000000111111111111111U;  x ^= z ^ (z << 17);
    // [ 32 ] --> [ 15 2 15 ]
#endif
    return x;
}
// -------------------------
/*
scheme:  [ 5 5 5 2 5 5 5 ]
   7: [ 4]   [ 1 3 10 17 ]
 - 1   - 3   -10   -17   == -31
 + 1   - 3   -10   -17   == -29
             -10   -17   == -27
 - 1   + 3   -10   -17   == -25
 + 1   + 3   -10   -17   == -23
 - 1   - 3         -17   == -21
 + 1   - 3         -17   == -19
                   -17   == -17
 - 1   + 3         -17   == -15
 + 1   + 3         -17   == -13
 - 1   - 3   +10   -17   == -11
 + 1   - 3   +10   -17   == -9
             +10   -17   == -7
 - 1   + 3   +10   -17   == -5
 + 1   + 3   +10   -17   == -3
 - 1                     == -1
 + 1                     == +1
 - 1   - 3   -10   +17   == +3
 + 1   - 3   -10   +17   == +5
             -10   +17   == +7
 - 1   + 3   -10   +17   == +9
 + 1   + 3   -10   +17   == +11
 - 1   - 3         +17   == +13
 + 1   - 3         +17   == +15
                   +17   == +17
 - 1   + 3         +17   == +19
 + 1   + 3         +17   == +21
 - 1   - 3   +10   +17   == +23
 + 1   - 3   +10   +17   == +25
             +10   +17   == +27
 - 1   + 3   +10   +17   == +29
 + 1   + 3   +10   +17   == +31
*/


static inline uint jj3_revbin32_4b(uint x)
{
    uint z;
#if 0
#else  // same code using GCC's binary literals
    z = (x ^ (x >>  1)) & 0b01010000101000010100001010000101U;  x ^= z ^ (z <<  1);
    // [ 2 ] --> [ 1, 1  ]  ~ [ 1, 1, 1, ..., 1, 1 ]

    z = (x ^ (x >>  2)) & 0b00110010011001001100100110010011U;  x ^= z ^ (z <<  2);
    // [ 3 ] --> [ 1, 1, 1 ] and [ 4 ] --> [ 2, 2 ]  ~ [ 2,2, 1,1,1, 2,2,  2,2, 2, 2,2,  2,2, 1,1,1, 2,2 ]

    z = (x ^ (x >>  7)) & 0b00000001111000000011100000001111U;  x ^= z ^ (z <<  7);
    // [ 11 ] --> [ 4, 3, 4 ] and [ 10 ] --> [ 4, 2, 4 ]  ~ [ 4,3,4, 4,2,4, 4,3,4 ]

    z = (x ^ (x >> 21)) & 0b00000000000000000000011111111111U;  x ^= z ^ (z << 21);
    // [ 32 ] --> [ 11, 10, 11 ]
#endif
    return x;
}
// -------------------------
/*
scheme:  [ 11 3 4 3 11 ]
   1: [ 4]   [ 1 2 7 21 ]
 - 1   - 2   - 7   -21   == -31
 + 1   - 2   - 7   -21   == -29
 - 1   + 2   - 7   -21   == -27
 + 1   + 2   - 7   -21   == -25
       - 2         -21   == -23
                   -21   == -21
       + 2         -21   == -19
 - 1   - 2   + 7   -21   == -17
 + 1   - 2   + 7   -21   == -15
 - 1   + 2   + 7   -21   == -13
 + 1   + 2   + 7   -21   == -11
       - 2   - 7         == -9
             - 7         == -7
       + 2   - 7         == -5
 - 1   - 2               == -3
 + 1   - 2               == -1
 - 1   + 2               == +1
 + 1   + 2               == +3
       - 2   + 7         == +5
             + 7         == +7
       + 2   + 7         == +9
 - 1   - 2   - 7   +21   == +11
 + 1   - 2   - 7   +21   == +13
 - 1   + 2   - 7   +21   == +15
 + 1   + 2   - 7   +21   == +17
       - 2         +21   == +19
                   +21   == +21
       + 2         +21   == +23
 - 1   - 2   + 7   +21   == +25
 + 1   - 2   + 7   +21   == +27
 - 1   + 2   + 7   +21   == +29
 + 1   + 2   + 7   +21   == +31
*/

static inline uint jj3_revbin32_4c(uint x)
{
    uint z;
#if 0
#else  // same code using GCC's binary literals
    z = (x ^ (x >>  1)) & 0b01001001001001001001001001001001U;  x ^= z ^ (z <<  1);
    z = (x ^ (x >>  3)) & 0b00011000100011000100011000100011U;  x ^= z ^ (z <<  3);
    z = (x ^ (x >>  9)) & 0b00000000011111000000000000011111U;  x ^= z ^ (z <<  9);
    z = (x ^ (x >> 18)) & 0b00000000000000000011111111111111U;  x ^= z ^ (z << 18);
#endif
    return x;
}
/*
scheme:  [ 14 4 14  ]
  6: [ 4]   [ 1 3 9 18 ]
 - 1   - 3   - 9   -18   == -31
 + 1   - 3   - 9   -18   == -29
             - 9   -18   == -27
 - 1   + 3   - 9   -18   == -25
 + 1   + 3   - 9   -18   == -23
       - 3         -18   == -21
 - 1               -18   == -19
 + 1               -18   == -17
       + 3         -18   == -15
 - 1   - 3   + 9   -18   == -13
 + 1   - 3   + 9   -18   == -11
             + 9   -18   == -9
 - 1   + 3   + 9   -18   == -7
 + 1   + 3   + 9   -18   == -5
       - 3               == -3
 - 1                     == -1
 + 1                     == +1
       + 3               == +3
 - 1   - 3   - 9   +18   == +5
 + 1   - 3   - 9   +18   == +7
             - 9   +18   == +9
 - 1   + 3   - 9   +18   == +11
 + 1   + 3   - 9   +18   == +13
       - 3         +18   == +15
 - 1               +18   == +17
 + 1               +18   == +19
       + 3         +18   == +21
 - 1   - 3   + 9   +18   == +23
 + 1   - 3   + 9   +18   == +25
             + 9   +18   == +27
 - 1   + 3   + 9   +18   == +29
 + 1   + 3   + 9   +18   == +31
*/


static inline uint jj3_revbin32_4d(uint x)
{
    uint z;
#if 0
#else  // same code using GCC's binary literals
    z = (x ^ (x >>  2)) & 0b00100100010010010010010010001001U;  x ^= z ^ (z <<  2);
    z = (x ^ (x >>  3)) & 0b00011100001110001110001110000111U;  x ^= z ^ (z <<  3);
    z = (x ^ (x >>  7)) & 0b00000001111110000000000000111111U;  x ^= z ^ (z <<  7);
    z = (x ^ (x >> 19)) & 0b00000000000000000001111111111111U;  x ^= z ^ (z << 19);
#endif
    return x;
}
/*
scheme:  [ 13 6 13 ]  [ 6 1 6 6 6 1 6 ]
  14: [ 4]   [ 2 3 7 19 ]
 - 2   - 3   - 7   -19   == -31
       - 3   - 7   -19   == -29
 + 2   - 3   - 7   -19   == -27
 - 2   + 3   - 7   -19   == -25
       + 3   - 7   -19   == -23
 + 2   + 3   - 7   -19   == -21
                   -19   == -19
 - 2   - 3   + 7   -19   == -17
       - 3   + 7   -19   == -15
 + 2   - 3   + 7   -19   == -13
 - 2   + 3   + 7   -19   == -11
       + 3   + 7   -19   == -9
 + 2   + 3   + 7   -19   == -7
 - 2   - 3               == -5
       - 3               == -3
 + 2   - 3               == -1
 - 2   + 3               == +1
       + 3               == +3
 + 2   + 3               == +5
 - 2   - 3   - 7   +19   == +7
       - 3   - 7   +19   == +9
 + 2   - 3   - 7   +19   == +11
 - 2   + 3   - 7   +19   == +13
       + 3   - 7   +19   == +15
 + 2   + 3   - 7   +19   == +17
                   +19   == +19
 - 2   - 3   + 7   +19   == +21
       - 3   + 7   +19   == +23
 + 2   - 3   + 7   +19   == +25
 - 2   + 3   + 7   +19   == +27
       + 3   + 7   +19   == +29
 + 2   + 3   + 7   +19   == +31

*/

/*
yet another scheme:
 -31 ==   - 1  - 4  - 7  -19
 -29 ==   + 1  - 4  - 7  -19
 -27 ==   - 1       - 7  -19
 -25 ==   + 1       - 7  -19
 -23 ==   - 1  + 4  - 7  -19
 -21 ==   + 1  + 4  - 7  -19
 -19 ==                  -19
 -17 ==   - 1  - 4  + 7  -19
 -15 ==   + 1  - 4  + 7  -19
 -13 ==   - 1       + 7  -19
 -11 ==   + 1       + 7  -19
  -9 ==   - 1  + 4  + 7  -19
  -7 ==   + 1  + 4  + 7  -19
  -5 ==   - 1  - 4
  -3 ==   + 1  - 4
  -1 ==   - 1
   1 ==   + 1
   3 ==   - 1  + 4
   5 ==   + 1  + 4
   7 ==   - 1  - 4  - 7  +19
   9 ==   + 1  - 4  - 7  +19
  11 ==   - 1       - 7  +19
  13 ==   + 1       - 7  +19
  15 ==   - 1  + 4  - 7  +19
  17 ==   + 1  + 4  - 7  +19
  19 ==                  +19
  21 ==   - 1  - 4  + 7  +19
  23 ==   + 1  - 4  + 7  +19
  25 ==   - 1       + 7  +19
  27 ==   + 1       + 7  +19
  29 ==   - 1  + 4  + 7  +19
  31 ==   + 1  + 4  + 7  +19

*/

static inline ulong jj3_revbin64_5(ulong x)
{
    ulong z;
    z = (x ^ (x >>  1)) & 0x4a52a5294a52a529UL;  x ^= z ^ (z <<  1);
    z = (x ^ (x >>  3)) & 0x18c60c6318c60c63UL;  x ^= z ^ (z <<  3);
    z = (x ^ (x >> 10)) & 0x003e001f003e001fUL;  x ^= z ^ (z << 10);
    z = (x ^ (x >> 17)) & 0x00007fff00007fffUL;  x ^= z ^ (z << 17);
    z = (x ^ (x >> 32)) & 0x00000000ffffffffUL;  x ^= z ^ (z << 32);
    return x;
}
// -------------------------


static inline uint jj3_revbin17(uint x)
{ // [ 3 1 3 3 3 1 3 ]
    uint z;
#if 0
#else  // same code using GCC's binary literals
    z = (x ^ (x >>  2)) & 0b00100010010010001;  x ^= z ^ (z <<  2);
    z = (x ^ (x >>  4)) & 0b00001110000000111;  x ^= z ^ (z <<  4);
    z = (x ^ (x >> 10)) & 0b00000000001111111;  x ^= z ^ (z << 10);
#endif
    return x;
}
// -------------------------
/*
  17:  [ 2 4 10 ]
 - 2   - 4   -10   == -16
       - 4   -10   == -14
 + 2   - 4   -10   == -12
             -10   == -10
 - 2   + 4   -10   == -8
       + 4   -10   == -6
 + 2   + 4   -10   == -4
 - 2               == -2
                   == +0
 + 2               == +2
       + 4         == +4
 + 2   + 4         == +6
       - 4   +10   == +6
 - 2         +10   == +8
             +10   == +10
 + 2         +10   == +12
 - 2   + 4   +10   == +12
       + 4   +10   == +14
 + 2   + 4   +10   == +16

*/


static inline ulong jj_revbin16(ulong x)  // NOT OK
{
    ulong z;
#if 0
#else  // same code using GCC's binary literals
    const ulong m01 = 0b0000000010000000UL;
    const ulong m02 = 0b0010001000010001UL;
    const ulong m04 = 0b0000111000000111UL;
    const ulong m09 = 0b0000000001111111UL;
    z = (x ^ (x >>  1)) & m01;  x ^= z ^ (z <<  1);
    z = (x ^ (x >>  2)) & m02;  x ^= z ^ (z <<  2);
    z = (x ^ (x >>  4)) & m04;  x ^= z ^ (z <<  4);
    z = (x ^ (x >>  9)) & m09;  x ^= z ^ (z <<  9);
#endif
    return x;
}
// -------------------------
/*
scheme:
 P = [ 1 2 4 9 ]  (partition of 16)
 -15 ==        - 2  - 4  - 9
 -13 ==             - 4  - 9
 -11 ==        + 2  - 4  - 9
  -9 ==                  - 9
  -7 ==        - 2  + 4  - 9
  -5 ==             + 4  - 9
  -3 ==        + 2  + 4  - 9
  -1 ==   - 1
   1 ==   + 1
   3 ==        - 2  - 4  + 9
   5 ==             - 4  + 9
   7 ==        + 2  - 4  + 9
   9 ==                  + 9
  11 ==        - 2  + 4  + 9
  13 ==             + 4  + 9
  15 ==        + 2  + 4  + 9
*/


static inline ulong jj_revbin19(ulong x)
{
    ulong z;
#if 0
#else  // same code using GCC's binary literals
//    const ulong m02 = 0bxxxxxxxxxxxxxxxxxxxUL;
    const ulong m02 = 0b0010001000100010001UL;
    const ulong m04 = 0b0000111000010000111UL;
    const ulong m12 = 0b0000000000001111111UL;
    z = (x ^ (x >>  2)) & m02;  x ^= z ^ (z <<  2);
    z = (x ^ (x >>  4)) & m04;  x ^= z ^ (z <<  4);
    z = (x ^ (x >> 12)) & m12;  x ^= z ^ (z << 12);
#endif
    return x;
}
// -------------------------
/*
scheme:
 -18 ==   - 2  - 4  -12
 -16 ==        - 4  -12
 -14 ==   + 2  - 4  -12
 -12 ==             -12
 -10 ==   - 2  + 4  -12
  -8 ==        + 4  -12
  -6 ==   + 2  + 4  -12
  -4 ==        - 4
  -2 ==   - 2
   0 ==
   2 ==   + 2
   4 ==        + 4
   6 ==   - 2  - 4  +12
   8 ==        - 4  +12
  10 ==   + 2  - 4  +12
  12 ==             +12
  14 ==   - 2  + 4  +12
  16 ==        + 4  +12
  18 ==   + 2  + 4  +12

*/

/*
schemes for jj_revbin29:

 P = [ 1 2 6 19 ]
 -28 ==   - 1  - 2  - 6  -19
 -26 ==   + 1  - 2  - 6  -19
 -24 ==   - 1  + 2  - 6  -19
 -22 ==   + 1  + 2  - 6  -19
 -20 ==   - 1            -19
 -18 ==   + 1            -19
 -16 ==   - 1  - 2  + 6  -19
 -14 ==   + 1  - 2  + 6  -19
 -12 ==   - 1  + 2  + 6  -19
 -10 ==   + 1  + 2  + 6  -19
  -8 ==        - 2  - 6
  -6 ==             - 6
  -4 ==        + 2  - 6
  -2 ==        - 2
   0 ==
   2 ==        + 2
   4 ==        - 2  + 6
   6 ==             + 6
   8 ==        + 2  + 6
  10 ==   - 1  - 2  - 6  +19
  12 ==   + 1  - 2  - 6  +19
  14 ==   - 1  + 2  - 6  +19
  16 ==   + 1  + 2  - 6  +19
  18 ==   - 1            +19
  20 ==   + 1            +19
  22 ==   - 1  - 2  + 6  +19
  24 ==   + 1  - 2  + 6  +19
  26 ==   - 1  + 2  + 6  +19
  28 ==   + 1  + 2  + 6  +19


 P = [ 1 3 5 19 ]
 -28 ==   - 1  - 3  - 5  -19
 -26 ==   + 1  - 3  - 5  -19
 -24 ==             - 5  -19
 -22 ==   - 1  + 3  - 5  -19
 -20 ==   + 1  + 3  - 5  -19
 -18 ==   - 1  - 3  + 5  -19
 -16 ==   + 1  - 3  + 5  -19
 -14 ==             + 5  -19
 -12 ==   - 1  + 3  + 5  -19
 -10 ==   + 1  + 3  + 5  -19
  -8 ==        - 3  - 5
  -6 ==   - 1       - 5
  -4 ==   + 1       - 5
  -2 ==        + 3  - 5
   0 ==
   2 ==        - 3  + 5
   4 ==   - 1       + 5
   6 ==   + 1       + 5
   8 ==        + 3  + 5
  10 ==   - 1  - 3  - 5  +19
  12 ==   + 1  - 3  - 5  +19
  14 ==             - 5  +19
  16 ==   - 1  + 3  - 5  +19
  18 ==   + 1  + 3  - 5  +19
  20 ==   - 1  - 3  + 5  +19
  22 ==   + 1  - 3  + 5  +19
  24 ==             + 5  +19
  26 ==   - 1  + 3  + 5  +19
  28 ==   + 1  + 3  + 5  +19

schemes for jj_revbin21:
 -20 ==   - 2  - 4  -14
 -18 ==        - 4  -14
 -16 ==   + 2  - 4  -14
 -14 ==             -14
 -12 ==   - 2  + 4  -14
 -10 ==        + 4  -14
  -8 ==   + 2  + 4  -14
  -6 ==   - 2  - 4
  -4 ==        - 4
  -2 ==   + 2  - 4
   0 ==
   2 ==   - 2  + 4
   4 ==        + 4
   6 ==   + 2  + 4
   8 ==   - 2  - 4  +14
  10 ==        - 4  +14
  12 ==   + 2  - 4  +14
  14 ==             +14
  16 ==   - 2  + 4  +14
  18 ==        + 4  +14
  20 ==   + 2  + 4  +14


*/


static inline ulong jj3_revbin40(ulong x)
{  // cf. https://oeis.org/A125173
    ulong z;
#if 0
#else  // same code using GCC's binary literals
    const ulong m01 = 0b0010010010010010010010010010010010010010UL;
    const ulong m03 = 0b0001000110001000110001000110001000110001UL;
    const ulong m09 = 0b0000000001111000000000111110000000001111UL;
    const ulong m27 = 0b0000000000000000000000000001111111111111UL;
    z = (x ^ (x >>  1)) & m01;  x ^= z ^ (z <<  1);
    z = (x ^ (x >>  3)) & m03;  x ^= z ^ (z <<  3);
    z = (x ^ (x >>  9)) & m09;  x ^= z ^ (z <<  9);
    z = (x ^ (x >> 27)) & m27;  x ^= z ^ (z << 27);
#endif
    return x;
}
// -------------------------
/*
scheme:
   1: [ 4]   [ 1 3 9 27 ]  (partition of 40)

       - 3   - 9   -27   == -39
 - 1         - 9   -27   == -37
 + 1         - 9   -27   == -35
       + 3   - 9   -27   == -33
 - 1   - 3         -27   == -31
 + 1   - 3         -27   == -29
                   -27   == -27
 - 1   + 3         -27   == -25
 + 1   + 3         -27   == -23
       - 3   + 9   -27   == -21
 - 1         + 9   -27   == -19
 + 1         + 9   -27   == -17
       + 3   + 9   -27   == -15
 - 1   - 3   - 9         == -13
 + 1   - 3   - 9         == -11
             - 9         == -9
 - 1   + 3   - 9         == -7
 + 1   + 3   - 9         == -5
       - 3               == -3
 - 1                     == -1
 + 1                     == +1
       + 3               == +3
 - 1   - 3   + 9         == +5
 + 1   - 3   + 9         == +7
             + 9         == +9
 - 1   + 3   + 9         == +11
 + 1   + 3   + 9         == +13
       - 3   - 9   +27   == +15
 - 1         - 9   +27   == +17
 + 1         - 9   +27   == +19
       + 3   - 9   +27   == +21
 - 1   - 3         +27   == +23
 + 1   - 3         +27   == +25
                   +27   == +27
 - 1   + 3         +27   == +29
 + 1   + 3         +27   == +31
       - 3   + 9   +27   == +33
 - 1         + 9   +27   == +35
 + 1         + 9   +27   == +37
       + 3   + 9   +27   == +39
*/




ulong transpose_bit_board(ulong x)
{  // from "Hacker's delight": transpose8rS64(...) from file transpose8.c
    ulong t;
    t = (x ^ (x >>  7)) & 0x00aa00aa00aa00aaUL;  x = x ^ t ^ (t <<  7);
    // mask = 0b0000000010101010000000001010101000000000101010100000000010101010UL
    t = (x ^ (x >> 14)) & 0x0000cccc0000ccccUL;  x = x ^ t ^ (t << 14);
    // mask = 0b0000000000000000110011001100110000000000000000001100110011001100UL
    t = (x ^ (x >> 28)) & 0x00000000f0f0f0f0UL;  x = x ^ t ^ (t << 28);
    // mask = 0b0000000000000000000000000000000011110000111100001111000011110000UL
    return x;
}
// -------------------------

/*
scheme:

........
1.1.1.1.
........
1.1.1.1.
........
1.1.1.1.
........
1.1.1.1.


........
........
11..11..
11..11..
........
........
11..11..
11..11..


........
........
........
........
1111....
1111....
1111....
1111....
*/


#endif


static inline void lin2hilbert_2(ulong t, ulong &x, ulong &y)
// Based on code by Juha Jaervi
{
    const ulong M5 = ~0UL/0x3;  // == 0x55555555...

//    // De-interleave t.
//    y = t & M5;
//    y = (y|(y>>1)) & ~0UL/0xf*0x3;
//    y = (y|(y>>2)) & ~0UL/0xff*0xf;
//    y = (y|(y>>4)) & ~0UL/0xffff*0xff;
//    y = (y|(y>>8)) & 0xffff;
    y = bit_unzip0( t & M5 );

    // Count total number of 00 crumbs (bit pairs) mod 2 times 2 and
    // number of 11 crumbs mod 2 on the left side of each crumb.
    const ulong t1 = (t|(t>>1)) & M5;  // at least one bit set
    const ulong t2 = (t&(t>>1)) & M5;  // exactly two bits set
    ulong ct = (t1>>1) | (t2>>2);

    ct ^= ct>>2;
    ct ^= ct>>4;
    ct ^= ct>>8;
    ct ^= ct>>16;
#if  BITS_PER_LONG >= 64
    ct ^= ct>>32;
#endif

    // Bit-twiddling magic to get hilbert curve x at t interleaved with 0.
    // ^-(order&1) rotates entire curve for every second order...
//    const ulong order = 0;  // ???
//    x = ( ct ^ (t>>1) ^ ( (ct ^ (ct>>1) ^ -(~order&1) ^ ~0UL/15*4 ) & t ) ) & M5;
//    x = ( ct ^ (t>>1) ^ ( (ct ^ (ct>>1) ^ -1UL ^ ~0UL/15UL*4 ) & t ) ) & M5;
//    x = ( ct ^ (t>>1) ^ ( (ct ^ (ct>>1) ^ 0xbbbbbbbbbbbbbbbbUL ) & t ) ) & M5;
    const ulong Mb =  -1UL ^ ~0UL/15UL*4;  // == 0xbbbbbbb...
//    x = ( ct ^ (t>>1) ^ ( (ct ^ (ct>>1) ^ Mb ) & t ) ) & M5;
    x = ct ^ (t>>1) ^ ( (ct ^ (ct>>1) ^ Mb ) & t );

    // De-interleave x.
//    x=(x|(x>>1)) & ~0UL/0xf*0x3;
//    x=(x|(x>>2)) & ~0UL/0xff*0xf;
//    x=(x|(x>>4)) & ~0UL/0xffff*0xff;
//    x=(x|(x>>8)) & 0xffff;

    x = bit_unzip0( x & M5 );

//    y = x ^ y;
    y ^= x;
}
// -------------------------



static inline ulong lowest_block_2(ulong x)
// Isolate lowest block of ones.
{
    ulong l = x & -x;  // lowest bit
    ulong y = x + l;
#if 0  // jj's version (incorrect for words 1+0*)
    x ^= y;
    return  x & (x>>1);
#else  // Mike Engber's (correct) version
    y ^= x;
    return  y & x;
#endif
}
// -------------------------

static inline ulong lowest_block_3(ulong x)
// Isolate lowest block of ones.
{
    ulong l = x & -x;  // lowBitMask
    ulong c = (l + x) & x;  // lowBitRunCleared
    return c ^ x;  // lowBitRunMask
}
// -------------------------


static inline ulong highest_one_idx_2(ulong x)
// Return index of highest bit set.
// Return 0 if no bit is set.
{
    if ( 0==x )  return  0;
    ulong r = 0;
#if  BITS_PER_LONG >= 64
//    if ( x & (~0UL<<32) )  { x >>= 32;  r += 32; }
    if ( x & 0xffffffff00000000UL )  { x >>= 32;  r += 32; }
#endif
    if ( x & 0xffff0000UL )  { x >>= 16;  r += 16; }
    if ( x & 0x0000ff00UL )  { x >>=  8;  r +=  8; }
    if ( x & 0x000000f0UL )  { x >>=  4;  r +=  4; }
    if ( x & 0x0000000cUL )  { x >>=  2;  r +=  2; }
    if ( x & 0x00000002UL )  {            r +=  1; }
    return r;
}
// -------------------------

#if BITS_PER_LONG == 64

#define ONES_STEP_4    0x1111111111111111UL
#define AAHS_STEP_4    0xaaaaaaaaaaaaaaaaUL
#define THRS_STEP_4    0x3333333333333333UL
#define ONES_STEP_8    0x0101010101010101UL
#define EFFS_STEP_8    0x0f0f0f0f0f0f0f0fUL
//#define MSBS_STEP_8 ( 0x80UL * ONES_STEP_8 )
#define MSBS_STEP_8    0x8080808080808080UL
//#define INCR_STEP_8  ( 0x80UL << 56 | 0x40UL << 48 | 0x20UL << 40 | 0x10UL << 32 | 0x8UL << 24 | 0x4UL << 16 | 0x2UL << 8 | 0x1 )
#define INCR_STEP_8    0x8040201008040201UL

//#define LEQ_FUNC(x,y)  ( ( ( ( ( (y) | MSBS_STEP_8 ) - ( (x) & ~MSBS_STEP_8 ) ) ^ (x) ^ (y) ) & MSBS_STEP_8 ) >> 7 )
static inline ulong leq_func(ulong x, ulong y)
{
    ulong r = ( y | MSBS_STEP_8 ) - ( x & ~MSBS_STEP_8 );
    r ^= (x ^ y);
    r &= MSBS_STEP_8;
    r >>= 7;
    return r;
}
// -------------------------

//#define ZCMP_FUNC(x)  ( ( ( (x) | ( ( (x) | MSBS_STEP_8 ) - ONES_STEP_8 ) ) & MSBS_STEP_8 ) >> 7 )
static inline ulong zcmp_func(ulong x)
{
    ulong r = x | ( ( x | MSBS_STEP_8 ) - ONES_STEP_8 );
    r &= MSBS_STEP_8;
    r >>= 7;
    return r;
}
// -------------------------

static inline ulong ith_one_idx_1(ulong x, ulong i)
// Return index of the i-th set bit of x where 0 <= i < bit_count(x).
// Return 72 if i >= bit_count(x).
// Adaptation from code given by Sebastiano Vigna.
{
    // Phase 1: sums by byte
//    ulong byte_sums = x - ( ( x & 0xa * ONES_STEP_4 ) >> 1 );
    ulong byte_sums = x - ( ( x & AAHS_STEP_4 ) >> 1 );
//    byte_sums = ( byte_sums & 3 * ONES_STEP_4 ) + ( ( byte_sums >> 2 ) & 3 * ONES_STEP_4 );
    byte_sums = ( byte_sums & THRS_STEP_4 ) + ( ( byte_sums >> 2 ) & THRS_STEP_4 );
//    byte_sums = ( byte_sums + ( byte_sums >> 4 ) ) & 0x0F * ONES_STEP_8;
    byte_sums = ( byte_sums + ( byte_sums >> 4 ) ) & EFFS_STEP_8;
    byte_sums *= ONES_STEP_8;

    // Phase 2: compare each byte sum with i
    const ulong i_step_8 = i * ONES_STEP_8;
//    const ulong place = ( ( LEQ_FUNC( byte_sums, i_step_8 ) * ONES_STEP_8 ) >> 53 ) & ~0x7UL;
    const ulong place = ( ( leq_func( byte_sums, i_step_8 ) * ONES_STEP_8 ) >> 53 ) & ~0x7UL;

    // Phase 3: Locate the relevant byte and make 8 copies with incremental masks
    const ulong byte_rank = i - ( ( ( byte_sums << 8 ) >> place ) & 0xFF );

    const ulong spread_bits = ( ( x >> place & 0xFF ) * ONES_STEP_8 ) & INCR_STEP_8;
//    const ulong bit_sums = ZCMP_FUNC( spread_bits ) * ONES_STEP_8;
    const ulong bit_sums = zcmp_func( spread_bits ) * ONES_STEP_8;

    // Compute the inside-byte location and return the sum
    const ulong byte_rank_step_8 = byte_rank * ONES_STEP_8;

//    return  place + ( ( LEQ_FUNC( bit_sums, byte_rank_step_8 ) * ONES_STEP_8 ) >> 56 );
    return  place + ( ( leq_func( bit_sums, byte_rank_step_8 ) * ONES_STEP_8 ) >> 56 );
}
// -------------------------


static inline ulong highest_one_idx_1(ulong x)
// == highest_one_idx() implementation
{
    if ( x == 0 )  return 0;
    ulong r = 0;
    if ( x & 0xffffffff00000000UL )  { x >>= 32;  r += 32; }
    if ( x & 0xffff0000UL )          { x >>= 16;  r += 16; }
    x |= (x << 16);
    x |= (x << 32);
    const ulong y = x & 0xff00f0f0ccccaaaaUL;
    const ulong z = 0x8000800080008000UL;
    ulong t = z & ( y | (( y | z ) - ( x ^ y )));
    t |= (t << 15);
    t |= (t << 30);
    t |= (t << 60);
    return  r + ( t >> 60 );
}
// -------------------------

#endif // BITS_PER_LONG == 64


//static inline ulong hbi(ulong x)
//// this is a INCORRECT highest_one_idx() implementation
//{
//    ulong r = 0;
//#if  BITS_PER_LONG >= 64
//    if ( x & (~0UL<<32) )  r += 32;
//#endif
//    if ( x & 0xffff0000UL )  r += 16;
//    if ( x & 0xff00ff00UL )  r +=  8;
//    if ( x & 0xf0f0f0f0UL )  r +=  4;
//    if ( x & 0xccccccccUL )  r +=  2;
//    if ( x & 0xaaaaaaaaUL )  r +=  1;
//    return r;
//}
//// -------------------------
//
//static inline ulong bc15(uint x)
//// Return number of set bits, must have at most 15 set bits,
//{
//    x -=  (x>>1) & 0x55555555UL;
//    x  = ((x>>2) & 0x33333333UL) + (x & 0x33333333UL);
//    x *= 0x11111111UL;
//    return  x>>28;
//}
//// -------------------------


#if BITS_PER_LONG == 64

static inline ulong bs1(ulong x)
// == bit_swap_1(x)
{
#if 0
    ulong m = 0xaaaaaaaaaaaaaaaaUL;
    ulong t = x & m;
    x ^= t;
    t >>= 1;
    x += x;
    x |= t;
    return x;
#else
    ulong m = 0x5555555555555555UL;
//    ulong t = x & m;
//    x = ( (x>>1) & m );
    return  ( (x>>1) & m ) | ( (x & m) << 1 );
#endif
}
// -------------------------
#endif


static inline ulong low1(ulong x)
{
    if ( ~0UL==x )  return ~0UL;
    x = (x ^ (x+1)) >> 1;
    return x;
}
// -------------------------




#define BH (BITS_PER_LONG/2)
#define CLH(v) ((v<<BH)>>BH)  // clear left half

void
do_some_tests(ulong v)
{
    ulong t;

#if BITS_PER_LONG == 64
    { const ulong c = bit_count(v);
//        print_bin("v=",v);  cout << endl;
//        cout << "bit_count=" << c << endl;
        for (ulong i=0; i<c; ++i)
        {
//            cout << "i=" << i << endl;
            ulong i0 = ith_one_idx(v, i);
            ulong i1 = ith_one_idx_1(v, i);
            jjassert( i0 == i1 );
        }
    }
#endif

#if 1
    {
        ulong x1, y1;
        ulong x2, y2;
        lin2hilbert(v, x1, y1);
        lin2hilbert_2(v, x2, y2);
        if ( 0 )
        {
            print_bin(" v=",v);  cout << endl;
            print_bin("x1=",x1);  cout << endl;
            print_bin("x2=",x2);  cout << endl;
            if ( x1!=x2 )  cout << "  *** DX ***" << endl;
            print_bin("y1=",y1);  cout << endl;
            print_bin("y2=",y2);  cout << endl;
            if ( y1!=y2 )  cout << "  *** DY ***" << endl;
            cout << endl;
        }
        jjassert( x1==x2 );
        jjassert( y1==y2 );
    }
#endif

    {
        ulong t1 = lowest_block(v);
        ulong t2 = lowest_block_2(v);
        ulong t3 = lowest_block_3(v);
//        if ( t1!=t2 )
//        {
//            print_bin(" v=",v);  cout << endl;
//            print_bin("t1=",t1);  cout << endl;
//            print_bin("t2=",t2);  cout << endl;
//            cout << endl;
//        }
        jjassert( t1==t2 );
        jjassert( t1==t3 );
    }

#if BITS_PER_LONG == 64
//    jjassert( bit_swap_1(v) == bs1(v) );

    jjassert( v == butterfly_16(butterfly_16(v)) );
#endif
    jjassert( v == butterfly_8(butterfly_8(v)) );
    jjassert( v == butterfly_4(butterfly_4(v)) );
    jjassert( v == butterfly_2(butterfly_2(v)) );
    jjassert( v == butterfly_1(butterfly_1(v)) );
    jjassert( v == bit_unzip(bit_zip(v)) );

    jjassert( v == bit_inverse_gray_permute(bit_gray_permute(v)) );

    t = CLH(v);  jjassert( bit_zip(t)==bit_zip0(t) );
    t = CLH(v);  jjassert( t==bit_unzip0(bit_zip0(t)) );

    { ulong lo, hi;
        bit_zip2(v, lo, hi); t=bit_unzip2(lo, hi); jjassert( v==t );

        t = CLH(v);  t=bit_zip0(t);
        bit_zip2(v, lo, hi);
        jjassert( t==lo );
    }

    { ulong x = v,  y=v>>1;
//        cout << " x=" << x << endl;
//        cout << " y=" << y << endl;
        jjassert( (x+y) == (((x&y)<<1) + (x^y)) );
        jjassert( (x+y) == (((x|y)<<1) - (x^y)) );
        ulong af = average(x,y);
        ulong ac = ceil_average(x,y);
//        print_bin(" x=",x,0);  cout << endl;
//        print_bin(" y=",y,0);  cout << endl;
//        print_bin("af=",af,0);  cout << endl;
//        print_bin("ac=",ac,0);  cout << endl;
        jjassert( ac == (af + ((x^y)&1)) );
    }

//    print_bin("  l1a=",low_ones(v),0);
//    print_bin("  l1b=",low1(v),0);
//    cout << endl;
    jjassert( low_ones(v) == low1(v) );

    jjassert( (low_ones(v) & low_zeros(v)) == 0 );
    jjassert( (low_ones(v) | low_zeros(v)) != 0 );

    jjassert( high_ones(v) == high_zeros(~v) );
    jjassert( (high_ones(v) & high_zeros(v)) == 0 );
    jjassert( (high_ones(v) | high_zeros(v)) != 0 );

    jjassert( (highest_one_01edge(v) & highest_one_10edge(v)) == highest_one(v) );

    t = highest_one_01edge(v);  jjassert( bit_count(t) == bit_count_01(t) );

    jjassert( (lowest_one_01edge(v) & lowest_one_10edge(v)) == lowest_one(v) );

    jjassert( (v==0) || (lowest_one_idx(v) == (BITS_PER_LONG-1 - highest_one_idx(revbin(v)))) );

    jjassert( (v!=0) || (lowest_one_idx(v) == highest_one_idx(revbin(v))) );

    jjassert( lowest_one(v) == lowest_zero(~v) );
    jjassert( highest_one(v) == highest_zero(~v) );
    jjassert( revbin( highest_one(v) ) == lowest_one( revbin(v) ) );
    jjassert( revbin(v) == revbin(v, BITS_PER_LONG) );
#if  BITS_PER_LONG == 64
    jjassert( revbin(v) == knuth_revbin64(v) );

//    const ulong w = 63;
//    v &= (1UL<<w) - 1;
//    print_bin("     v = " , v);  cout << endl;
//    print_bin(" jj(v) = " , jj3_revbin64(v));  cout << endl;
//    print_bin(" ww(v) = " , revbin(v, w));  cout << endl;
//    print_bin(" rb(v) = " , revbin(v));  cout << endl;
//    cout << endl;
//    jjassert( revbin(v, w) == jj3_revbin64(v) );

    jjassert( revbin(v) == jj3_revbin64(v) );
    jjassert( revbin(v) == jj3_revbin64_5(v) );
//    if ( revbin(v) != jj3_revbin64(v) )  cout << " xxx " << endl;

    { uint tt = v & 0xffffffffUL;
//        ulong a = revbin(tt, 32),  b = jj3_revbin32(tt);
//        ulong a = revbin(tt, 32),  b = jj3_revbin32_4a(tt);
        ulong a = revbin(tt, 32),  b = jj3_revbin32_4b(tt);
//        ulong a = revbin(tt, 32),  b = jj3_revbin32_4c(tt);
//        ulong a = revbin(tt, 32),  b = jj3_revbin32_4d(tt);
//        print_bin("     v = " , tt, 33);  cout << endl;
//        print_bin(" ww(v) = " , a, 33);  cout << endl;
//        print_bin(" jj(v) = " , b, 33);  cout << endl;
        jjassert( a == b );
    }

    { uint tt = v & 0x7ffffUL;
        ulong a = revbin(tt, 19),  b = jj_revbin19(tt);
        jjassert( a == b );
    }

    { uint tt = v & 0xffffUL;
        ulong a = revbin(tt, 16),  b = jj_revbin16(tt);
        jjassert( a == b );
    }

    { uint tt = v & 0x1ffffUL;
        ulong a = revbin(tt, 17),  b = jj3_revbin17(tt);
        jjassert( a == b );
    }

    { ulong tt = v & ((1UL<<40)-1);
        ulong a = revbin(tt, 40),  b = jj3_revbin40(tt);
        jjassert( a == b );
    }


#endif

#define COND  ! ( ((v==0) && (r==1)) || ((v==1) && (r==0)) )
//#define COND  true  // test
#if 1 // silent:
#define X(r,v)
#else // verbose:
#define X(r,v) \
    cout << endl; \
    print_bin(" v = " , v);  cout << endl; \
    print_bin(" r = " , r);  cout << endl; \
    print_bin(" COND = " , COND, 3);  cout << endl;           \
    print_bin(" ld(r) = " , ld(r), 8);  cout << endl;       \
    print_bin(" ld(v) = " , ld(v), 8);  cout << endl;              \
    print_bin(" ld_eq  v r = " , ld_eq(v,r), 3);  cout << endl; \
    print_bin(" ld_neq v r = " , ld_neq(v,r), 3);  cout << endl; \
    print_bin(" ld(v)==ld(r) = " , ld(v)==ld(r), 3);  cout << endl; \
    print_bin(" ld(v)!=ld(r) = " , ld(v)!=ld(r), 3);  cout << endl;
#endif

    { ulong r;
        r = revbin(v);
        if ( COND )
        {
            X(r,v);
            jjassert( (ld(v)==ld(r)) == ( ld_eq(v,r) ) );
            jjassert( (ld(v)!=ld(r)) == ( ld_neq(v,r) ) );
        }

        r = v-1;
        if ( COND )
        {
            X(r,v);
            jjassert( (ld(v)==ld(r)) == ( ld_eq(v,r) ) );
            jjassert( (ld(v)!=ld(r)) == ( ld_neq(v,r) ) );
        }

        r = v+1;
        if ( COND )
        {
            X(r,v);
            jjassert( (ld(v)==ld(r)) == ( ld_eq(v,r) ) );
            jjassert( (ld(v)!=ld(r)) == ( ld_neq(v,r) ) );
        }
    }
//    cout << endl;
//    print_bin(" v=" , v);  cout << endl;
//    cout << "  a=" << highest_one_idx(v);
//    cout << "  b=" << highest_one_idx__(v);
//    cout << endl;
//    jjassert( highest_one_idx(v) == (63-highest_one_idx__(v)) );
#if BITS_PER_LONG == 64
    jjassert( highest_one_idx(v) == highest_one_idx_1(v) );
#endif
    jjassert( highest_one_idx(v) == highest_one_idx_2(v) );

    {
        ulong s0 = single_zeros(v);
        ulong s1 = single_ones(v);
//        ulong c0 = single_zeros(~v);
//        ulong c1 = single_ones(~v);
        ulong s01 = s0 | s1;
        ulong sv = single_values(v);
//        print_bin("  v=", v);  cout << endl;
//        print_bin(" s0=", s0);  cout << endl;
//        print_bin(" s1=", s1);  cout << endl;
//        print_bin(" ~v=", ~v);  cout << endl;
//        print_bin(" c0=", c0);  cout << endl;
//        print_bin(" c1=", c1);  cout << endl;
//        print_bin("s01=", s01);  cout << endl;
//        print_bin(" sv=", sv);  cout << endl;
//        cout << endl;

        jjassert( sv == s01 );

//        jjassert( s1 == c0 );  // not true
//        jjassert( c1 == s0 );  // not true

        jjassert( single_ones_xi(v) == single_ones(v) );
        jjassert( single_zeros_xi(v) == single_ones(~v) );

        jjassert( (single_ones_xi(v) | single_zeros_xi(v)) == single_values_xi(v) );
    }

    jjassert( border_ones(v) == (high_border_ones(v) | low_border_ones(v)) );
//    jjassert( border_ones(v) == border_ones(~v) );  // not true

    jjassert( block_border_ones(v) == (low_block_border_ones(v) ^ high_block_border_ones(v)) );
    jjassert( block_ones(v) == (block_border_ones(v) | interior_ones(v)) );

    jjassert( v == (block_ones(v) | single_ones(v)) );

    t = bit_count(v);
    jjassert( t == bit_count_sparse(v) );
    if ( t<16 )  jjassert( t == bit_count_15(v) );
    if ( t<4 )  jjassert( t == bit_count_3(v) );

//    t = CLH(v);  t = bit_count(t);
//    if ( t<16 )  jjassert( t == bc15(v) );

    jjassert( interior_ones(v) == (interior_ones(v) & interior_values(v)) );

//    jjassert( (interior_ones(v) | interior_ones(~v)) == interior_values(v) ); //  not true

    jjassert( parity(v) == (inverse_gray_code(v) & 1) );

    const ulong irg = inverse_rev_gray_code(v);
    const ulong ig = inverse_gray_code(v);
    const ulong igs = inverse_gray_code(v) >> 1;
    jjassert( inverse_gray_code( (v)>>1 ) == inverse_gray_code(v) >> 1 );
    if ( parity(v) )
    {
        jjassert( ~v == (irg ^ ig) );
        jjassert( ~irg == igs );
    }
    else
    {
        jjassert( v == (irg ^ ig) );
        jjassert( irg == igs );
    }

//    jjassert( yellow_code(v) == revbin( blue_code( revbin( v ) ) ) );
//    jjassert( red_code(v) == revbin( blue_code( v ) ) );
//    jjassert( green_code(v) == blue_code( revbin( v ) ) );

//    jjassert( (~inverse_rev_gray_code(v)) == (inverse_gray_code(v)>>1) ); // not true

    if ( v ) { jjassert( (1UL<<ld(v)) <= v ); }  else { jjassert( ld(v) == 0 ); }

    for (ulong r=0; r<(BITS_PER_LONG); ++r)
    {
        jjassert( v==bit_rotate_right(bit_rotate_left(v,r), r) );
        jjassert( v==bit_rotate_right(bit_rotate_right(v,r), BITS_PER_LONG-r) );
        jjassert( v==bit_rotate_left(bit_rotate_left(v,r), BITS_PER_LONG-r) );
    }

    if ( contains_zero_byte(v) )
    {
        char str[BYTES_PER_LONG];
        ulong x = v;
        for (ulong k=0; k<BYTES_PER_LONG; ++k)
        {
            str[k] = (char)(x & 0xff);
            x >>= 8;
        }
        ulong k;
        for (k=0; k<BYTES_PER_LONG; ++k)  if ( 0==str[k] )  break;
        if ( k==BYTES_PER_LONG )
        {
            cout << hex << " contains_zero_byte( 0x" << v << " )";
            cout        << "   gave  0x" << contains_zero_byte(v) << endl;
            jjassert(0); //  contains_zero_byte() failed
        }
    }
}
// -------------------------


int
main()
{
    cout << "Running tests for low level (bit-) functions "
#ifdef  NO_ONES_USE_ASM
        "WITHOUT asm-functions"
#else
        "with ASM-versions"
#endif
         "..." << endl;
//    cout << "RAND_MAX=" << (RAND_MAX) << endl;

    // some special values we'd like to test:

    for (ulong x=0; x<100; x++)  do_some_tests( x );

    for (ulong x=1; x; x<<=1)
    {
        do_some_tests( x );    // one bit
        do_some_tests( x-1 );  // low burst
        do_some_tests( ~(x-1) );  // high burst
    }

    do_some_tests( 0 );
    do_some_tests( ~0UL );

    ulong x = 1UL<<(BITS_PER_LONG-1);  // highest bit set
    do_some_tests( x );
    do_some_tests( x + 1 );
    do_some_tests( x - 1 );


    ulong n = 300*1000;  // this many tests with random values
    for (ulong i=0; i<n; ++i)
    {
        ulong v = (ulong)rand();
        v ^= ((ulong)rand())<<(BH); // also want high bit !=0

        do_some_tests(v);
        if ( 0==(i%1024) )  { cout << "."; cout.flush(); }
    }

    cout << "\nOK passed " << n << " tests." << endl;

    return 0;
}
// -------------------------
