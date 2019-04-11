

#ifndef __LOADER_H__
#define __LOADER_H__


typedef struct loader_s
{
	char *rom;
	char *base;
	char *sram;
	char *state;
	int ramloaded;
} loader_t;


extern loader_t loader;
extern char *romfile;
extern char *romdir;
extern char *savedir;


int rom_load();
int sram_load();
int sram_save();
int loader_init();
void loader_unload();

#endif


