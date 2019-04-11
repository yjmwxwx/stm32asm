
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/soundcard.h>


#include "../defs.h"
#include "../pcm.h"
#include "../sound.h"


#define MIN(x, y) ((x)<(y)?(x):(y))

/* FIXME - all this code is VERY basic, improve it! */

int dsp = -1;

struct pcm pcm;

int mixer = -1;
char *dsp_device = "/dev/dsp";
char *mixer_device = "/dev/mixer";
int stereo = 1;
int samplerate = 44100;
int oss_enabled = 1;
int oss_speed = 100;
int oss_volume = 50;
int sound = 1;

#ifdef OLD_KERNEL
int buf_len = 1024 * 40;   // in halfwords
#else
int buf_len = 1024 * 15;   // in halfwords
#endif


audio_buf_info buf_info;


void pcm_init()
{
	int n;

	if(!oss_enabled) {
		pcm_close();
		return; //NOSOUND
	}

	/*if (!sound)
	{
		pcm.hz = 11025;
		pcm.len = 4096;
		pcm.buf = malloc(pcm.len);
		pcm.pos = 0;
		dsp = -1;
		return;
	}*/

	//if (!dsp_device) dsp_device = strdup(DSP_DEVICE);
	if(dsp<0) dsp = open(dsp_device, O_WRONLY);
	if(mixer<0) mixer=open(mixer_device, O_RDWR);

	//n = 0x80009;
	//ioctl(dsp, SNDCTL_DSP_SETFRAGMENT, &n);
	//n = AFMT_S8;

	n = AFMT_S16_LE;
	ioctl(dsp, SNDCTL_DSP_SETFMT, &n);
	n = stereo;
	//ioctl(dsp, SNDCTL_DSP_STEREO, &n);
	pcm.stereo = n;
	n++;
	ioctl(dsp, SNDCTL_DSP_CHANNELS, &n);

	n = samplerate;
	ioctl(dsp, SNDCTL_DSP_SPEED, &n);
	pcm.hz = (n * 100) / oss_speed; //FIXME TEST speed
	pcm.len = n / 60;
	pcm.buf = malloc(sizeof(short)*pcm.len);

	n = buf_len;
	ioctl(dsp, SNDCTL_DSP_SETFRAGMENT, &n);

	if (pcm.hz) snd.rate = (1<<21) / pcm.hz; //apply soundspeed now!

	n = (oss_volume << 8 )| oss_volume;
	ioctl(mixer, SOUND_MIXER_WRITE_PCM, &n);
}

void pcm_close()
{
	if (pcm.buf) free(pcm.buf);
	memset(&pcm, 0, sizeof pcm);
	if (dsp>=0) close(dsp);
	dsp = -1;
	if (mixer>=0) close(mixer);
	mixer = -1;
}

int pcm_submit()
{

	if(!oss_enabled) return 0; //NOSOUND
	if (dsp < 0)
	{
		pcm.pos = 0;
		return 0;
	}

	do {
		ioctl(dsp, SNDCTL_DSP_GETOSPACE, &buf_info);
		// FIXME: sys_sleep(0);
#ifdef OLD_KERNEL
	} while(buf_info.bytes<(54*1024+256)); //FIXME
#else
	} while(buf_info.bytes<4*1024+256); //FIXME
#endif

	if (pcm.buf) write(dsp, pcm.buf, sizeof(short)*pcm.pos);
	pcm.pos = 0;
	return 1;
}

