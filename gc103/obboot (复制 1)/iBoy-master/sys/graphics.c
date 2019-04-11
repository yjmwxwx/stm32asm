
#include <string.h>

#include "graphics.h"
#include "nix.h"


unsigned short draw_screen[144][20];  // 160 x 144

void draw_fill(unsigned short pat)
{
	int x,y;

	for(y=0;y<20;y++)
		for(x=0;x<128;x++)
			draw_screen[y][x/8] = 0x5555; //rand();

}


void draw_rect(int x, int y, int xx, int yy, unsigned short pat)
{
	int hx = x, hy = y;

	if(x>xx) THREESWAP(x,xx);
	if(y>yy) THREESWAP(y,yy);

	for(hy = y; hy < yy; hy++) {

		for (hx = x/8; hx < xx/8; hx++ )
			if(hy==y || hy==(yy-1)) draw_screen[hy][hx] = 0xffff;
			else if(hx==x/8) draw_screen[hy][hx] = pat | 0x0003;
			else if(hx==(xx/8-1)) draw_screen[hy][hx] = pat | 0xC000;
			else draw_screen[hy][hx] = pat;
	}
	#ifdef KB_PORTABLE
	flush_lcd();
	#endif
}

//		lcd_cmd_and_data(0x11, hy*0x20+x/8);
//		lcd_prepare_cmd(0x12);
//		lcd_cmd_and_data(0x11, (y+dy)*0x20+x/8);
//		lcd_prepare_cmd(0x12);

void draw_string(int x, int y, const char *s, int inv)
{
	int dx, dy;

	if(!s || !(*s)) return;

	for(dy=0; dy<8; dy++)
	{
		for (dx = 0; s[dx]; dx++ )
			if(!inv) draw_screen[y+dy][x/8+dx] = fontbm[(unsigned int)(unsigned char)s[dx]][dy];
			else if(inv&1) draw_screen[y+dy][x/8+dx] = ~fontbm[(unsigned int)(unsigned char)s[dx]][dy];
			else draw_screen[y+dy][x/8+dx] = 0xaaaa & fontbm[(unsigned int)(unsigned char)s[dx]][dy];
	}

	#ifdef USE_TEXTMENU
	printf("\n %c %s", inv&1?'+':'-', s);
	#endif

	#ifdef KB_PORTABLE
	flush_lcd();
	#endif
}


void draw_refresh()
{
	lcdll_blit((unsigned short *) draw_screen, BLITTER_FORMAT_2BP_MENU);
}



void err_msg(char *msg, int ms, ...)
{
	int x;
	va_list ap;
	char msgs[256];

	#ifdef PORTABLE
		printf(msg);
		printf("\n");
	#endif

	va_start(ap, ms);
	vsprintf(msgs, msg, ap);
		#ifdef USE_TEXTMENU
		vprintf(msg,ap);
		puts("\npress any key...");
		getchar();
		#endif
	va_end(ap);

	draw_rect(16, 48, 144, 64, 0xffff);
	x = strlen(msgs)*4;
	draw_string(80-x, 52, msgs, 1);
	draw_refresh();
	if(ms) sys_sleep(1000*ms);


}
