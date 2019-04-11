
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#include "defs.h"
#include "regs.h"
#include "mem.h"
#include "hw.h"
#include "rtc.h"
#include "save.h"
#include "sound.h"
#include "loader.h"
#include "lcd.h"


#include "sys/nix.h"



static const int mbc_table[256] =
{
	0, 1, 1, 1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 3, 3, 3, 0, 0, 0, 0, 0, 5, 5, 5, MBC_RUMBLE, MBC_RUMBLE, MBC_RUMBLE, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MBC_HUC3, MBC_HUC1
};

static int rtc_table[] =   // 256!!!!
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0
};

static int batt_table[] =  // 256 !!!
{
	0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0,
	1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
	0
};

static int romsize_table[] =   // 256 !!!
{
	2, 4, 8, 16, 32, 64, 128, 256, 512,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 128, 128, 128
	/* 0, 0, 72, 80, 96  -- actual values but bad to use these! */
};

static int ramsize_table[] =   // 256!!!
{
	1, 1, 1, 4, 16,
	4 /* FIXME - what value should this be?! */
};

/********** GLOBALS ************/
/*******************************/
char *romdir = 0;
char *savedir = 0;

char *romfile = 0;		// must not contain dir
char *sramfile = 0;
char *rtcfile = 0;

int forcebatt = 0, nobatt = 0;
int forcedmg = 0;

int memfill = -1, memrand = -1;


static void initmem(void *mem, int size)
{
	char *p = (char *) mem;

	if (memrand >= 0)
	{
		srand(memrand ? memrand : time(0));
		while(size--) *(p++) = rand();
	}
	else if (memfill >= 0)
		memset(mem, memfill, size);
}


int rom_load()
{
	FILE *f;
	byte c, header[16384];
	char *del;

	f = fopen2(del = get_current_dir_name(), romfile, "rb");
	free(del);
	if (!f) {
		err_msg("cant %s %s", 4000, romdir, romfile);
		return 1;
	}

	memset(header, 0xff, 16384);
	fread(header, 16384, 1, f);

	strncpy(rom.name, header+0x0134, 16);
	if (rom.name[14] & 0x80) rom.name[14] = 0;
	if (rom.name[15] & 0x80) rom.name[15] = 0;
	rom.name[16] = 0;

	c = header[0x0147];
	mbc.type = mbc_table[c];
	mbc.batt = (batt_table[c] && !nobatt) || forcebatt;
	rtc.batt = rtc_table[c];
	mbc.romsize = romsize_table[header[0x0148]];
	mbc.ramsize = ramsize_table[header[0x0149]];

	if (!mbc.romsize) {
		err_msg("unknown ROM size %02X\n", 4000, header[0x0148]);
	 	return 2;
	}
	if (!mbc.ramsize) {
		err_msg("unknown SRAM size %02X\n", 4000, header[0x0149]);
		return 3;
	}

//	err_msg("rom banks: %d", 1000, mbc.romsize);

	rom.bank = malloc(16384 * mbc.romsize);

	if(rom.bank == NULL) die("out of mem for rom");

	memset(rom.bank, 0xff, 16384 * mbc.romsize);
	memcpy(rom.bank, header, 16384);
	fread(rom.bank+1, 16384, mbc.romsize-1, f);

	ram.sbank = malloc(8192 * mbc.ramsize);
	if(ram.sbank == NULL) die("out of mem for ram");

	if (!ram.loaded)  /* just in case... */
		initmem(ram.sbank, 8192 * mbc.ramsize);
	initmem(ram.ibank, 4096 * 8);
	initmem(ram.hi, 256);

	mbc.rombank = 1;
	mbc.rambank = 0;

	c = header[0x0143];
	hw.cgb = ((c == 0x80) || (c == 0xc0)) && !forcedmg;
	if(hw.cgb) err_msg("COLOR ROM", 400);
	else err_msg("MONO ROM", 400);

	// Use compatible mode on grayscale ipods if available
	if(c == 0x80 && !sys_ipod_is_color()) {
	  hw.cgb = 0;
	  err_msg("COMPATIBLE_MODE", 400);
	}

	/*else if(c == 0xC0) {
	  err_msg("NOT_COMPATIBLE", 1500);
	}*/


	if (strcmp(romfile, "-")) fclose(f);

	return 0;
}

int sram_load()
{
	FILE *f;

	if (!mbc.batt || !sramfile || !*sramfile) return -1;

	/* Consider sram loaded at this point, even if file doesn't exist */
	ram.loaded = 1;

	f = fopen2(savedir, sramfile, "rb");

	if (!f) return -1;
	fread(ram.sbank, 8192, mbc.ramsize, f);
	fclose(f);

	return 0;
}


int sram_save()
{
	FILE *f;

	/* If we crash before we ever loaded sram, DO NOT SAVE! */
	if (!mbc.batt || !sramfile || !ram.loaded || !mbc.ramsize)
		return -1;

	f = fopen2(savedir, sramfile, "wb");
	if (!f) return -1;
	fwrite(ram.sbank, 8192, mbc.ramsize, f);
	fclose(f);

	return 0;
}


void rtc_save()
{
	FILE *f;
	if (!rtc.batt) return;
	if (!(f = fopen2(savedir, rtcfile, "wb"))) return;
	rtc_save_internal(f);
	fclose(f);
}


void rtc_load()
{
	FILE *f;
	if (!rtc.batt) return;
	if (!(f = fopen2(savedir, rtcfile, "r"))) return;
	rtc_load_internal(f);
	fclose(f);
}


void loader_unload()
{
	sram_save();
	//if (romfile) free(romfile);
	if (sramfile) free(sramfile);
	if (rtcfile) free(rtcfile);
	if (rom.bank) free(rom.bank);
	if (ram.sbank) free(ram.sbank);
	sramfile = 0;
	rom.bank = 0;
	ram.sbank = 0;
	rtcfile = 0;
	mbc.type = mbc.romsize = mbc.ramsize = mbc.batt = 0;
}


static void cleanup()
{
	sram_save();
	rtc_save();
	/* IDEA - if error, write emergency savestate..? */
}

int loader_init()
{
	char *saveprefix, *p;
	//sys_checkdir(savedir);

	if(rom_load()) return 1;

	//vid_settitle(rom.name);

	saveprefix = strdup(romfile);
	p = strrchr(saveprefix, '.');
	if(p) *p = 0;

	sramfile = malloc(strlen(saveprefix) + 5);
	strcpy(sramfile, saveprefix);
	strcat(sramfile, ".ram");

	rtcfile = malloc(strlen(saveprefix) + 5);
	strcpy(rtcfile, saveprefix);
	strcat(rtcfile, ".rtc");

	free(saveprefix);

	sram_load();
	rtc_load();

	atexit(cleanup);

	return 0;
}
