


#ifndef __DEFS_H__
#define __DEFS_H__

#ifdef IS_LITTLE_ENDIAN
#define LO 0
#define HI 1
#else
#define LO 1
#define HI 0
#endif

#include <stdarg.h>

typedef unsigned char byte;

typedef unsigned char un8;
typedef unsigned short un16;
typedef unsigned int un32;

typedef signed char n8;
typedef signed short n16;
typedef signed int n32;

typedef un16 word;
typedef word addr;

void die(char *fmt, ...);
void vdie(char *fmt, va_list ap);

//int time (int); // Prototype Disables Warning (use include)

extern void cop_begin();
extern void cop_end();
extern void err_msg(char *msg, int ms, ...);
#endif
