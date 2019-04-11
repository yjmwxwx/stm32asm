//位反转
#include <stdio.h>
void main() {
	int zhuansu,tiqianjiao,tiqianjiao1;
    zhuansu = 1000;
    tiqianjiao= 0;
    tiqianjiao1=tiqianjiao;
    while(zhuansu <= 16000){
        tiqianjiao1= tiqianjiao * 256; 
        printf("%d,",tiqianjiao1);
        zhuansu = zhuansu + 150;
        tiqianjiao = tiqianjiao + 2;
    }
    printf("\n");
}
