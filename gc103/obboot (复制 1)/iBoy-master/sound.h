

#ifndef __SOUND_H__
#define __SOUND_H__

#include "defs.h"

struct sndchan
{
	int on, pos, cnt, encnt, swcnt;
	int len, enlen, swlen;
	int freq;
	int envol, endir;
};


struct snd
{
	int rate;
	struct sndchan ch[4];
};


extern struct snd snd;


void sound_reset();
void sound_mix();
void sound_write(byte r, byte b);
byte sound_read(byte r);
void sound_dirty();

int pcm_submit();
void pcm_init();
void pcm_close();


#endif

