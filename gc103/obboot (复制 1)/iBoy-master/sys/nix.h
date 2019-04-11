
#ifndef _NIX_H__
#define _NIX_H__

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>

typedef struct
{
	unsigned int version;
	unsigned int flags; /* display type etc. */
	unsigned int lcd_type;
	unsigned int lcd_base;
	unsigned int lcd_busy_mask;
	unsigned int lcd_width;
	unsigned int lcd_height;
	unsigned int ipod_rtc;
	char *       ipod_type;
} hw_info;


void sys_fb_ioctl(int request, int *val);
void sys_sleep(int us);
void *sys_timer();
int sys_elapsed(struct timeval *prev);

void sys_set_backlight(int on);
int sys_get_backlight();
void sys_set_contrast(int cont);

FILE * fopen2(char *dir, char *file, char *mode);

void sys_ipod_cleanup();
void sys_ipod_init();
int sys_getkey();

int sys_ipod_is_color();
int sys_ipod_hw_type(void);
void sys_ipod_hw_info(hw_info *info);


// Busy mask
#define IPOD_STD_LCD_BUSY_MASK  0x8000
#define IPOD_COL_LCD_BUSY_MASK  0x80000000
#define IPOD_NANO_LCD_BUSY_MASK IPOD_COL_LCD_BUSY_MASK
#define IPOD_VIDEO_LCD_BUSY_MASK IPOD_NANO_LCD_BUSY_MASK

// Screen Sizes
#define IPOD_STD_LCD_WIDTH    160
#define IPOD_STD_LCD_HEIGHT   128
#define IPOD_MINI_LCD_WIDTH   138
#define IPOD_MINI_LCD_HEIGHT  110
#define IPOD_COL_LCD_WIDTH    220
#define IPOD_COL_LCD_HEIGHT   176
#define IPOD_NANO_LCD_WIDTH   176
#define IPOD_NANO_LCD_HEIGHT  132
#define IPOD_VIDEO_LCD_WIDTH  320
#define IPOD_VIDEO_LCD_HEIGHT 240

// Other stuff
#define IPOD_PP5002_RTC      0xcf001110
#define IPOD_PP5020_RTC      0x60005010
#define IPOD_PP5002_LCD_BASE 0xc0001000
#define IPOD_PP5020_LCD_BASE 0x70003000
#define IPOD_COLOR_LCD_BASE  0x70008a0c
#define IPOD_NANO_LCD_BASE   IPOD_COLOR_LCD_BASE
#define IPOD_VIDEO_LCD_BASE  IPOD_NANO_LCD_BASE

#define LCD_CMD  0x8
#define LCD_DATA 0x10

/* ===== Flags ===== */

#define LCD_COLOR  0x00000001 // = 00000001_b
#define LCD_GRAY  ~LCD_COLOR
#define LCD_VIDEO  0x00000004 // = 00000100_b


#endif /* _NIX_H__ */
