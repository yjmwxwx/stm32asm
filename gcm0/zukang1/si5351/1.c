#include <stdio.h>
void xianshi (unsigned int jicunqi, unsigned int jicunqi_zhi){
  printf("%d,0x%02X, \n", jicunqi, jicunqi_zhi);
}
void main() {
  float fvco, fout, fxtal, a_jia_b_chu_c, b_chu_c;
  int a, b, c, msnx_p1, msnx_p2, msnx_p3, b_chu_c_cheng_128;
  int msx_p1, msx_p2, msx_p3;
  char r_fenpin, chu_4;
  fvco = 900000000;
  fxtal = 25000000;
  a_jia_b_chu_c = fvco / fxtal;
  a = a_jia_b_chu_c;
  b_chu_c = a_jia_b_chu_c - a;
  c=1048575;
  b = b_chu_c * c;
  b_chu_c_cheng_128 = 128 * b_chu_c;
  msnx_p1 = 128 * a + b_chu_c_cheng_128 - 512;
  msnx_p2 = 128 * b - c * b_chu_c_cheng_128;
  msnx_p3 = c;
  
  fout = 439667;
  a_jia_b_chu_c = fvco / fout;
  a = a_jia_b_chu_c;
  b_chu_c = a_jia_b_chu_c - a;
  b = b_chu_c * c;
  b_chu_c_cheng_128 = 128 * b_chu_c;
  msx_p1 = 128 * a + b_chu_c_cheng_128 - 512;
  msx_p2 = 128 * b - c * b_chu_c_cheng_128;
  msx_p3 = c;

  r_fenpin = 0x70;
  chu_4 = 0x00;
  
  xianshi (17, 128);
  xianshi (26, (msnx_p3 & 65280) >> 8);
  xianshi (27, msnx_p3 & 255);
  xianshi (28, (msnx_p1 & 196608) >> 16);
  xianshi (29, (msnx_p1 & 652280) >> 8);
  xianshi (30,msnx_p1 & 255);  
  xianshi (31, ((msnx_p3 & 0xf0000) >> 12) | ((msnx_p2 & 0xf0000) >> 16));
  xianshi (32, (msnx_p2 & 0xff00) >> 8);
  xianshi (33, msnx_p2 & 0xff);
  
  xianshi (50, (msx_p3 & 0xff00) >> 8);
  xianshi (51, msx_p3 & 0xff);
  xianshi (52, (msx_p1 & 0x30000) >> 16 | r_fenpin | chu_4);
  xianshi (53, (msx_p1 & 0xff00) >> 8);
  xianshi (54, msx_p1 & 0xff);
  xianshi (55, ((msx_p3 & 0xf0000) >> 12) | ((msx_p2 & 0xf0000) >> 16));
  xianshi (56, (msx_p2 & 0xff00) >> 8);
  xianshi (57, msx_p2 & 0xff);
  xianshi (177, 32);
  xianshi (17, 0x4c);
}
	
