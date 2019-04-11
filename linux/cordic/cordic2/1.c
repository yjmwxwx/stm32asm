#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main(int argc, char **argv)
{
	int i,aa,bb,cc,dd,ee,ff;
	aa = 180;  //表的点数
        bb = 180;  //一个圆分成多少分
        cc = 0 ;   // 相位偏移
        dd = 20;   // 幅值
        ee = 20;   // 幅值偏移
	
    for (i=0; i<aa; i++) 
	{
         printf("%6d \n", (int)(ee + dd*sin((cc+i)*2*3.1415927/bb)));
        }
	}
