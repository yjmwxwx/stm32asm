//期望角度0*32768到360*32768之间
#define gain 0x00004dba
#define MUL 32768.000000
int cordic_ctab [] = {0x00168000,0x000D4853,0x000704A3,0x00039000,0x0001C9C5,0x0000E51B,0x00007295,0x0000394B,0x00001CA5,0x00000E52,0x00000729,0x00000394,0x000001CA,0x000000E5,0x00000072,0x00000039, };

void cordic(int qiwang_jiaodu, int *s, int *c, int n)
{
  int k, d, xx,yy,dangqian_jiaodu;
  n=16;
dangqian_jiaodu=0;
  int x=gain,y=0;
 if(qiwang_jiaodu>90*32768)
 dangqian_jiaodu = 180*32768;
 if(qiwang_jiaodu>270*32768)
	dangqian_jiaodu = 360 * 32768;
  for (k=0; k<n; ++k)
  {
	if(qiwang_jiaodu>dangqian_jiaodu){
	xx = x-(y >> k);
	yy=y+(x>>k);
	dangqian_jiaodu=dangqian_jiaodu+cordic_ctab[k];
	}
	else{ 
	xx = x+(y >> k);
	yy=y-(x>>k);
	dangqian_jiaodu=dangqian_jiaodu-cordic_ctab[k]; 
	}
	x=xx;
	y=yy;
  }  
if ((qiwang_jiaodu > 90*32768) && (qiwang_jiaodu <270*32768)){
	x = -x;  
      y= -y;
}
 *c = x; *s = y;
}
