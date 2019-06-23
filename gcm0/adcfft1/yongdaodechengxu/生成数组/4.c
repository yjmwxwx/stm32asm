#include<stdio.h>
void main(){
int a;
int b;
printf("请输入一个整数\n");
scanf("%d",&a);	
while(a>0){
b=a%10;
a=a/10;
printf("%d",b);
}
}